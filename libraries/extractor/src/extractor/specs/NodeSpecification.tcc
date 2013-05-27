#include "NodeSpecification.hpp"
#include "ValuesSpecification.hpp"
#include "NumbersSpecification.hpp"

#include <extractor/inputFile/File.hpp>
#include <extractor/inputFile/Translator.hpp>
#include <extractor/expressionParser/ExpressionParser.hpp>


#include <boost/foreach.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <common/global.hpp>

#include <iomanip>
#include <cstdlib>
#include <cmath>

NodeSpecification::NodeSpecification( File* file )
	: _file     ( file )
{

}

bool NodeSpecification::isValidOrderedGroup( SubSpec& subSpec, GroupProperties& groupProperties, bpt::ptree& nodeReport )
{
	bool groupIsValid = true;
	// LOG_INFO( " ==> Ordered : " << groupProperties.getOrder() );
	BOOST_FOREACH( SubSpec& n, subSpec.second.get_child( kGroup ) )
	{
		std::vector< size_t > nodeRepetition = getRepetition( n, _headerElements );

		size_t min = nodeRepetition.at(0);
		size_t max = nodeRepetition.at(1);

		if( min != max )
		{
			std::stringstream sstr;
			sstr << "Invalid repetition value : " << min << " != " << max
				 << " : cannot be a range for ordered elements (" << subSpec.second.get< std::string >( "id" ) 
				 << "." << n.second.get< std::string >( "id" ) << ")";
			throw std::runtime_error( sstr.str() );
		}
		else
		{
			for( size_t i = 0 ; i < min ; i++ )
			{
				bpt::ptree subNodeReport;
				// LOG_INFO( " @ File : " << std::hex << _file->getPosition() << std::dec );
				if( isValid( n, groupProperties, subNodeReport ) )
				{
					if( subNodeReport.size() > 0 )
						nodeReport.push_back( bpt::ptree::value_type( n.second.get< std::string >( "id" ), subNodeReport ) );
				}
				else
				{
					LOG_ERROR( n.second.get< std::string >( "id" ) );
					groupIsValid = false;
				}

				if( _file->endOfFile() )
				{
					// LOG_INFO( common::Color::get()->_yellow << "==>  /!\\ EOF : " << _file->endOfFile() << common::Color::get()->_std );
					return groupIsValid;
				}
			}
		}
	}
	return groupIsValid;
}

bool NodeSpecification::oneNodeValidUnorderedGroup( SubSpec& subSpec, GroupProperties& groupProperties, bpt::ptree& nodeReport )
{
	bool oneNodeIsValid = false;
	BOOST_FOREACH( SubSpec& n, subSpec.second.get_child( kGroup ) )
	{
		bpt::ptree subNodeReport;
		// LOG_INFO( " @ File : " << _file->getPosition() );
		if( isValid( n, groupProperties, subNodeReport ) )
		{
			// LOG_INFO( " - Valid : " << n.second.get< std::string >( "id" ) << " at " << _file->getPosition());
			if( subNodeReport.size() > 0 )
			{
				oneNodeIsValid = true;
				nodeReport.push_back( bpt::ptree::value_type( n.second.get< std::string >( "id" ), subNodeReport ) );
				groupProperties.iterateIterationMapElement( n.second.get< std::string >( "id" ) );
				return oneNodeIsValid;
			}
		}
		if( _file->endOfFile() )
		{
			LOG_TRACE( common::Color::get()->_yellow << "==>  /!\\ EOF : " << _file->endOfFile() << common::Color::get()->_std );
			return oneNodeIsValid;
		}
	}
	return oneNodeIsValid;
}

bool NodeSpecification::isValidUnorderedGroup( SubSpec& subSpec, GroupProperties& groupProperties, bpt::ptree& nodeReport )
{
	bool groupIsValid = true;
	// LOG_INFO( " ==> Ordered : " << groupProperties.getOrder() );
	size_t i = 0;
	bool oneNodeIsValid = false;		
	
	BOOST_FOREACH( SubSpec& n, subSpec.second.get_child( kGroup ) )
	{
		// LOG_INFO( "     Set RepetitionMap Element : " << n.second.get< std::string >( "id" ) );
		bool optional = ( n.second.get<std::string>( kOptional, kOptionalFalse ) == kOptionalTrue );
		std::vector< size_t > nodeRepetition = getRepetition( n, _headerElements );
		groupProperties.addRepetitionMapElement( n.second.get< std::string >( "id" ), nodeRepetition, optional );
	}

	do
	{
		// LOG_INFO( ">>> Check an unordered group..." );
		i++;
		oneNodeIsValid = oneNodeValidUnorderedGroup( subSpec, groupProperties, nodeReport );
		// LOG_INFO( ">>> ... End of the specification" );
	}
	while( oneNodeIsValid && !_file->endOfFile() );

	if( i == 1)
	{
		groupIsValid = false;
		LOG_ERROR( "None is valid" );
	}
	else
	{
		groupIsValid = true;
	}

	BOOST_FOREACH( SubSpec& n, subSpec.second.get_child( kGroup ) )
	{
		if( !groupProperties.isIterationValid( n.second.get< std::string >( "id" ) ) )
		{
			groupIsValid = false;
		}
	}
	return groupIsValid;
}


bool NodeSpecification::isValidSubGroup( SubSpec& subSpec, GroupProperties& groupProperties, bpt::ptree& nodeReport )
{
	bool groupIsValid = true;

	LOG_INFO( common::Color::get()->_yellow << "Start Chunk : " << subSpec.second.get< std::string >( "id" ) << common::Color::get()->_std );

	if( groupProperties.getOrder() )	// ordered
	{
		groupIsValid = isValidOrderedGroup( subSpec, groupProperties, nodeReport );
	}
	else								// not ordered
	{
		groupIsValid = isValidUnorderedGroup( subSpec, groupProperties, nodeReport );
	}
	LOG_INFO( common::Color::get()->_yellow << "End Chunk : " << subSpec.second.get< std::string >( "id" ) << common::Color::get()->_std );
	
	return groupIsValid;
}


bool NodeSpecification::isValid( SubSpec& subSpec, GroupProperties& parentProperties, bpt::ptree& nodeReport )
{
	try
	{
		std::string message( "" );
		std::string id            = subSpec.second.get< std::string >( kId );
		std::string label         = subSpec.second.get< std::string >( kLabel,       "" );
		std::string typeValue     = subSpec.second.get< std::string >( kType,        "" );
		std::string count         = subSpec.second.get< std::string >( kCount,       "" );
		std::string groupSizeExpr = subSpec.second.get< std::string >( kGroupSize,   "" );
		std::string requiredExpr  = subSpec.second.get< std::string >( kRequired,    "" );
		std::string displayType   = subSpec.second.get< std::string >( kDisplayType, "" );
		
		std::vector< std::string > asciiValues = getMultipleValues< std::string >( subSpec, kAscii );
		std::vector< std::string > hexaValues  = getMultipleValues< std::string >( subSpec, kHexa  );

		bool endianValue = ( subSpec.second.get<std::string>( kEndian,   kEndianBig     ) == kEndianBig    );
		bool optional    = ( subSpec.second.get<std::string>( kOptional, kOptionalFalse ) == kOptionalTrue );
		bool ordered     = ( subSpec.second.get<std::string>( kOrdered,  kOrderedTrue   ) == kOrderedTrue  );

		bool group       = subSpec.second.get_child_optional( kGroup );
		bool isValidNode = false;
		// TLOG( "label " << label );
		
		if( asciiValues.size() != 0 )
		{
			message += kAscii + " => ";

			size_t size = asciiValues[0].size();
			for( size_t i = 0; i < asciiValues.size(); i++ )
			{
				Ascii value;

				if( i > 0 )
				{
					_file->goBack( size );
				}

				//TLOG( "read data " << size );
				char buffer[ size ];
				if( ! _file->readData( buffer, size ) )
					return optional;
				
				Translator<Ascii> tr;
				value = tr.translate( buffer, size );
				// LOG_INFO( " - value : " << value.originalCaseValue << ", " << value.lowCaseValue << ", " << value.upCaseValue << " | ==> asciiValues[" << i << "] : " << asciiValues[i] << " @ " << _file->getPosition() );

				if( asciiValues[i] ==  value.originalCaseValue || asciiValues[i] ==  value.lowCaseValue || asciiValues[i] == value.upCaseValue )
				{
					isValidNode = true;
					message += asciiValues[i];

					nodeReport.put( "<xmlattr>.optional", optional );
					nodeReport.put_value( asciiValues[i] );
					nodeReport.put( "<xmlattr>.type", "ascii" );
				}
				// TLOG_VAR2( asciiValues[i], value.value );
			}
			
			if( !requiredExpr.empty() )
			{					
				// LOG_INFO( ">>> " << id << " >>> requiredExpr : " << requiredExpr );
				ExpressionParser required = ExpressionParser();
				required.setVariables( _headerElements );
				bool condition = required.parseExpression< bool >( requiredExpr );
				if( !condition )
				{
					_file->goBack( size );
					return true;
				}
			}

			if( optional && !isValidNode )
			{
				_file->goBack( size );
				return true;
			}

			if( !parentProperties.getOrder() && !isValidNode )
			{
				_file->goBack( size );
				return false;
			}

			parentProperties.addSize( size );
		}

		if( hexaValues.size() != 0 )
		{
			message += kHexa + " => ";
			size_t size = 0.5 * hexaValues[0].size() ;
			
			for( size_t i = 0; i < hexaValues.size(); i++ )
			{
				Hexa value;

				if( i > 0 )
				{
					_file->goBack( size );
				}

				//TLOG( "read data " << size );
				char buffer[ size ];
				if( ! _file->readData( buffer, size ) )
					return optional;

				Translator<Hexa> tr;
				value = tr.translate( buffer, size );
				// LOG_INFO( " - value : " << value.originalCaseValue << ", " << value.lowCaseValue << ", " << value.upCaseValue << " | ==> hexaValues[" << i << "] : " << hexaValues[i] << " @ " << _file->getPosition() );

				if( hexaValues[i] ==  value.originalCaseValue || hexaValues[i] ==  value.lowCaseValue || hexaValues[i] == value.upCaseValue )
				{
					isValidNode = true;
					message += hexaValues[i];

					nodeReport.put( "<xmlattr>.optional", optional );
					nodeReport.put_value( hexaValues[i] );
					nodeReport.put( "<xmlattr>.type", "hexa" );
				}
				// TLOG_VAR2( hexaValues[i], value.value );
			}

			if( !requiredExpr.empty() )
			{					
				// LOG_INFO( ">>> " << id << " >>> requiredExpr : " << requiredExpr );
				ExpressionParser required = ExpressionParser();
				required.setVariables( _headerElements );
				bool condition = required.parseExpression< bool >( requiredExpr );
				if( !condition )
				{
					_file->goBack( size );
					return true;
				}
			}
			
			if( optional && !isValidNode )
			{
				_file->goBack( size );
				return true;
			}

			if( !parentProperties.getOrder() && !isValidNode )
			{
				_file->goBack( size );
				return false;
			}

			parentProperties.addSize( size );
		}

		if( !typeValue.empty() )
		{
			message += kType + " => " + typeValue;
			
			uint8   uint8Val = 0;
			int8     int8Val = 0;
			uint16 uint16Val = 0;
			int16   int16Val = 0;
			uint32 uint32Val = 0;
			int32   int32Val = 0;
			uint64 uint64Val = 0;
			int64   int64Val = 0;

			float   floatVal = 0;
			double doubleVal = 0;

			std::string uint8Map, int8Map, uint16Map, int16Map, uint32Map, int32Map, uint64Map, int64Map, floatMap, doubleMap;
			
			bool validUInt8  = isValidNumber<  uint8 >( _file, message, typeValue, endianValue, subSpec,  uint8Val,  uint8Map );
			bool validInt8   = isValidNumber<   int8 >( _file, message, typeValue, endianValue, subSpec,   int8Val,   int8Map );
			bool validUInt16 = isValidNumber< uint16 >( _file, message, typeValue, endianValue, subSpec, uint16Val, uint16Map );
			bool validInt16  = isValidNumber<  int16 >( _file, message, typeValue, endianValue, subSpec,  int16Val,  int16Map );
			bool validUInt32 = isValidNumber< uint32 >( _file, message, typeValue, endianValue, subSpec, uint32Val, uint32Map );
			bool validInt32  = isValidNumber<  int32 >( _file, message, typeValue, endianValue, subSpec,  int32Val,  int32Map );
			bool validUInt64 = isValidNumber< uint64 >( _file, message, typeValue, endianValue, subSpec, uint64Val, uint64Map );
			bool validInt64  = isValidNumber<  int64 >( _file, message, typeValue, endianValue, subSpec,  int64Val,  int64Map );

			bool validFloat  = isValidNumber< float > ( _file, message, typeValue, endianValue, subSpec,  floatVal,  floatMap );
			bool validDouble = isValidNumber< double >( _file, message, typeValue, endianValue, subSpec, doubleVal, doubleMap );
			
			if( !requiredExpr.empty() && typeValue != "data" )
			{
				size_t size = 0;
				
				if( validUInt8 )
					size = sizeof( uint8 );
				if( validInt8 )
					size = sizeof( int8 );
				if( validUInt16 )
					size = sizeof( uint16 );
				if( validInt16 )
					size = sizeof( int16 );
				if( validUInt32 )
					size = sizeof( uint32 );
				if( validInt32 )
					size = sizeof( int32 );
				if( validUInt64 )
					size = sizeof( uint64 );
				if( validInt64 )
					size = sizeof( int64 );
				if( validFloat )
					size = sizeof( float );
				if( validDouble )
					size = sizeof( double );
					
				// LOG_INFO( ">>> " << id << " >>> requiredExpr : " << requiredExpr );
				ExpressionParser required = ExpressionParser();
				required.setVariables( _headerElements );
				bool condition = required.parseExpression< bool >( requiredExpr );
				if( !condition )
				{
					_file->goBack( size );
					return true;
				}
			}

			exportValidData( validUInt8,  id,  uint8Val, parentProperties, nodeReport,  uint8Map );
			exportValidData( validInt8,   id,   int8Val, parentProperties, nodeReport,   int8Map );
			exportValidData( validUInt16, id, uint16Val, parentProperties, nodeReport, uint16Map );
			exportValidData( validInt16,  id,  int16Val, parentProperties, nodeReport,  int16Map );
			exportValidData( validUInt32, id, uint32Val, parentProperties, nodeReport, uint32Map );
			exportValidData( validInt32,  id,  int32Val, parentProperties, nodeReport,  int32Map );
			exportValidData( validUInt64, id, uint64Val, parentProperties, nodeReport, uint64Map );
			exportValidData( validInt64,  id,  int64Val, parentProperties, nodeReport,  int64Map );
			exportValidData( validFloat,  id,  floatVal, parentProperties, nodeReport,  floatMap );
			exportValidData( validDouble, id, doubleVal, parentProperties, nodeReport, doubleMap );
			
			
			bool validData   = false;

			if( typeValue == kData )
			{
				size_t size = 0;
				
				ExpressionParser ep = ExpressionParser();
				ep.setVariables( _headerElements );

				nodeReport.clear();

				if( !count.empty() )
				{
					size = ep.parseExpression<size_t>( count );
				}
				
				
				// TLOG( "*** Before error ***" );
				// char buffer[ size ];
				// TLOG( "*** After error ***" );

				// if( ! _file->readData( buffer, size ) )
				// {
				// 	return optional;
				// }

				if( !displayType.empty() )
				{
					if( displayType == "hexa" )
					{
						char buffer[ size ];
						if( ! _file->readData( buffer, size ) )
							return optional;

						Translator<Hexa> tr;
						Hexa data = tr.translate( buffer, size );
						message += " : '" + data.originalCaseValue + "'";
						// if( data.originalCaseValue.find('\0') )
							nodeReport.put_value( data.originalCaseValue );
						// LOG_INFO( "Data : " << data.originalCaseValue );
					}
					else if( displayType == "ascii" )
					{
						char buffer[ size ];
						if( ! _file->readData( buffer, size ) )
							return optional;

						Translator<Ascii> tr;
						Ascii data = tr.translate( buffer, size );
						message += " : '" + data.originalCaseValue + "'";

						if( data.originalCaseValue.find('\0') )
						{
							for( size_t i=0; i < data.originalCaseValue.size(); i++ )
							{
								if( (char)data.originalCaseValue.at(i) == 0 )
									data.originalCaseValue[i] = '\n';
							}
							nodeReport.put_value( data.originalCaseValue );
						}
						// LOG_INFO( "Data : " << data.originalCaseValue );
					}
					else
					{
						LOG_WARNING( id << " : Unknown display type");
					}
				}
				else
				{
					_file->goForward( size );
				}
				message += " ( size = " + getPrintable( size ) + " )";

				if( !requiredExpr.empty() )
				{
					// LOG_INFO( ">>> " << id << " >>> requiredExpr : " << requiredExpr );
					ExpressionParser required = ExpressionParser();
					required.setVariables( _headerElements );
					bool condition = required.parseExpression< bool >( requiredExpr );
					if( !condition )
					{
						_file->goBack( size );
						return true;
					}
				}

				validData = true;
				parentProperties.addSize( size );
				nodeReport.put( "<xmlattr>.optional", optional );
				nodeReport.put( "<xmlattr>.size", getPrintable( size ) );
				nodeReport.put( "<xmlattr>.type", "data" );
			}
			
			isValidNode = validUInt8 | validInt8 | validUInt16 | validInt16 | validUInt32 | validInt32 | validUInt64 | validInt64 | validFloat | validDouble | validData;
		}

		if( group && ( isValidNode || ( ! isValidNode && asciiValues.empty() && hexaValues.empty() && typeValue.empty() ) ) )
		{
			GroupProperties groupProperties;
			groupProperties.setOrder( ordered );
			// LOG_INFO( "groupProperties.getOrder() : " << groupProperties.getOrder() );
			bool groupIsValid = isValidSubGroup( subSpec, groupProperties, nodeReport );
			if( !groupIsValid )
			{
				isValidNode = false;
			}
			if( groupIsValid && asciiValues.empty() && hexaValues.empty() && typeValue.empty() )
			{
				isValidNode = true;
			}
			// LOG_INFO( ">>> " <<  subSpec.second.get< std::string >( "id" ) << ": isValidNode : " <<  isValidNode );

			if( !groupSizeExpr.empty() )
			{
				ExpressionParser groupLength = ExpressionParser();
				groupLength.setVariables( _headerElements );

				_file->goBack( groupProperties.getSize() );
				size_t gSize = groupLength.parseExpression<size_t>( groupSizeExpr );
				_file->goForward( gSize );

				size_t padding = 0;
				if( gSize%2 == 1 )
				{
					LOG_WARNING( "Padding : 1 byte (" << gSize << ")" );
					padding = 1;
					_file->goForward( padding );
				}

				if( groupProperties.getSize() < gSize )
				{
					LOG_WARNING( gSize << " - " << groupProperties.getSize() << " = " << gSize - groupProperties.getSize() << " unused bytes" );
				}
				if( groupProperties.getSize() > gSize )
				{
					isValidNode = false;
					LOG_ERROR( groupProperties.getSize() << " - " << gSize << " = " << groupProperties.getSize() - gSize << " bytes difference" );
				}
				parentProperties.addSize( groupProperties.getSize() + padding );
			}
		}

		if( typeValue.empty() && asciiValues.empty() && hexaValues.empty() && !group )
		{
			throw std::runtime_error( "Invalid tree : no value, group nor type node (" + id + ")" );
		}
		
		if( isValidNode )
		{
			LOG_INFO( common::Color::get()->_green << ( label + " - " + id ) << "\t" << message << common::Color::get()->_std );
		}
		else
		{
			LOG_ERROR( ( label + " - " + id ) << "\t" << message );
		}
	
		// nodeReport.put( "<xmlattr>.id", id );
		nodeReport.put( "<xmlattr>.label", label );
		nodeReport.put( "<xmlattr>.status", ( isValidNode ? "valid" : "invalid" ) );
		return isValidNode;

	}
	catch( const bpt::ptree_bad_path& pbp )
	{
		LOG_ERROR( "Invalid node in specification file : " << pbp.what() );
		throw;
	}
	catch( const bpt::ptree_bad_data& pbd )
	{
		LOG_ERROR( "Invalid data in specification node: " << pbd.what() );
		throw;
	}
	catch( const bpt::ptree_error& pe )
	{
		LOG_ERROR( "Specification file error : " << pe.what() );
		throw;
	}
	catch( std::runtime_error& e )
	{
		LOG_ERROR( e.what() );
		throw;
	}
	catch( std::exception& e )
	{
		LOG_ERROR( e.what() );
		throw;
	}
	catch(...)
	{
		LOG_ERROR( "Unknown error" );
		throw;
	}
}


template< typename DataType >
void NodeSpecification::exportValidData( const bool isValid, const std::string& id, const DataType& data, GroupProperties& groupProperties, bpt::ptree& nodeReport, std::string& mapStr )
{
	if( !isValid )
		return;
	Translator<DataType> tr;
	_headerElements[ id ] = data;
	groupProperties.addSize( sizeof( DataType ) );
	if( !mapStr.empty() )
		nodeReport.put_value( mapStr + " (" + tr.translate( data ) + ")" );
	else
		nodeReport.put_value( tr.translate( data ) );
	nodeReport.put( "<xmlattr>.type", getStringForType<DataType>() );
}
