
#include <limits>

const char max_char = std::numeric_limits<unsigned char>::max();
const char mid_char = 0x7F;
const char min_char = std::numeric_limits<unsigned char>::min();

const char dataInt8Low[]  = { min_char };
const char dataInt8High[] = { max_char };

const char dataInt16Low[]  = { min_char, max_char };
const char dataInt16High[] = { max_char, min_char };
const char dataInt16Full[] = { max_char, max_char };

const char dataInt32Low[]  = { min_char, min_char, min_char, max_char };
const char dataInt32High[] = { max_char, min_char, min_char, min_char };
const char dataInt32Full[] = { max_char, max_char, max_char, max_char };

const char dataInt64Low[]  = { min_char, min_char, min_char, min_char, min_char, min_char, min_char, max_char };
const char dataInt64High[] = { max_char, min_char, min_char, min_char, min_char, min_char, min_char, min_char };
const char dataInt64Full[] = { max_char, max_char, max_char, max_char, max_char, max_char, max_char, max_char };


const char dataFloatZero[]                = { min_char, min_char, min_char, min_char };		// 0.0 ( http://babbage.cs.qc.cuny.edu/IEEE-754/index.xhtml )

const char dataFloatOneBigEndian[]        = { 0x3f, 0x80, 0x00, 0x00 };						// 1.0
const char dataFloatMaxBigEndian[]        = { mid_char, mid_char, max_char, max_char };		// max value supported by the float type :  3.4028234e+38
const char dataFloatNegMaxBigEndian[]     = { max_char, mid_char, max_char, max_char };		// min value supported by the float type : -3.4028234e+38
const char dataFloatMinBigEndian[]        = { min_char, mid_char, max_char, max_char };		// min positive value supported by the float type : 1.17549e-38

const char dataFloatOneLittleEndian[]     = { 0x00, 0x00, 0x80, 0x3f };						// 1.0
const char dataFloatMaxLittleEndian[]     = { max_char, max_char, mid_char, mid_char };		// max value supported by the float type :  3.4028234e+38
const char dataFloatNegMaxLittleEndian[]  = { max_char, max_char, mid_char, max_char };		// min value supported by the float type : -3.4028234e+38
const char dataFloatMinLittleEndian[]     = { max_char, max_char, mid_char, min_char };		// min positive value supported by the float type : 1.17549e-38


const char dataDoubleZero[]               = { min_char, min_char, min_char, min_char, min_char, min_char, min_char, min_char };	// 0.0 ( http://babbage.cs.qc.cuny.edu/IEEE-754/index.xhtml )

const char dataDoubleOneBigEndian[]       = { 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };									// 1.0
const char dataDoubleMaxBigEndian[]       = { mid_char, 0xef, max_char, max_char, max_char, max_char, max_char, max_char };		// max value supported by the double type :  1.7976931348623157e+308
const char dataDoubleNegMaxBigEndian[]    = { max_char, 0xef, max_char, max_char, max_char, max_char, max_char, max_char };		// min value supported by the double type : -1.7976931348623157e+308
const char dataDoubleMinBigEndian[]       = { min_char, 0x10, min_char, min_char, min_char, min_char, min_char, min_char };		// min positive value supported by the double type : 2.2250738585072014e−308

const char dataDoubleOneLittleEndian[]    = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f };									// 1.0
const char dataDoubleMaxLittleEndian[]    = { max_char, max_char, max_char, max_char, max_char, max_char, 0xef, mid_char };		// max value supported by the double type :  1.7976931348623157e+308
const char dataDoubleNegMaxLittleEndian[] = { max_char, max_char, max_char, max_char, max_char, max_char, 0xef, max_char };		// min value supported by the double type : -1.7976931348623157e+308
const char dataDoubleMinLittleEndian[]    = { min_char, min_char, min_char, min_char, min_char, min_char, 0x10, min_char };		// min positive value supported by the double type : 2.2250738585072014e−308


const char dataIeeeExtendedZero[]            = { min_char, min_char, min_char, min_char, min_char, min_char, min_char, min_char, min_char, min_char };	// 0

const char dataIeeeExtendedOneBigEndian[]    = {     0x3f, max_char,     0x80, min_char, min_char, min_char, min_char, min_char, min_char, min_char };	// 1
const char dataIeeeExtendedMaxBigEndian[]    = {     0x7f,     0xfe, max_char, max_char, max_char, max_char, max_char, max_char, max_char, max_char };	// max value supported by the IEEE Extended type :   1.18973149535723176502e+4932
const char dataIeeeExtendedNegMaxBigEndian[] = { max_char,     0xfe, max_char, max_char, max_char, max_char, max_char, max_char, max_char, max_char };	// min value supported by the IEEE Extended type :  -1.18973149535723176502e+4932
const char dataIeeeExtendedMinBigEndian[]    = { min_char, min_char,     0x80, min_char, min_char, min_char, min_char, min_char, min_char, min_char };	// min positive value supported by the double type : 3.36210314311209350626e-4932

const char dataIeeeExtendedOneLittleEndian[]    = { min_char, min_char, min_char, min_char, min_char, min_char, min_char,     0x80, max_char,     0x3f };	// 1
const char dataIeeeExtendedMaxLittleEndian[]    = { max_char, max_char, max_char, max_char, max_char, max_char, max_char, max_char,     0xfe,     0x7f };	// max value supported by the IEEE Extended type :   1.18973149535723176502e+4932
const char dataIeeeExtendedNegMaxLittleEndian[] = { max_char, max_char, max_char, max_char, max_char, max_char, max_char, max_char,     0xfe, max_char };	// min value supported by the IEEE Extended type :  -1.18973149535723176502e+4932
const char dataIeeeExtendedMinLittleEndian[]    = { min_char, min_char, min_char, min_char, min_char, min_char, min_char,     0x80, min_char, min_char };	// min positive value supported by the double type : 3.36210314311209350626e-4932


BOOST_AUTO_TEST_SUITE( basic_element_test_number )

BOOST_AUTO_TEST_CASE( basic_element_number )
{
	LOG_INFO( "\n>>> basic_element_number <<<" );
	std::string id    = "id";
	std::string label = "label";

	nbe::Number< nbe::uint8 > num;

	nbe::uint8 min = 0;
	nbe::uint8 max = 10;

	std::map< nbe::uint8, std::string > map;
	map.insert( std::pair< nbe::uint8, std::string >( 1, "First number"  ) );
	map.insert( std::pair< nbe::uint8, std::string >( 2, "Second number" ) );
	map.insert( std::pair< nbe::uint8, std::string >( 3, "Third number"  ) );

	{
		BOOST_CHECK_EQUAL( num.getType(),   be::Element::eTypeNumber  );
		BOOST_CHECK_EQUAL( num.getStatus(), be::Element::eStatusUnknown );

		num.setId( id );
		BOOST_CHECK_EQUAL( num.getId(), id );

		num.setLabel( label );
		BOOST_CHECK_EQUAL( num.getLabel(), label );
		
		num.getRange().setRange( min, max );
		BOOST_CHECK_EQUAL( num.getRange().at(0),  0 );
		BOOST_CHECK_EQUAL( num.getRange().at(1), 10 );
		BOOST_CHECK_EQUAL( num.getRange().getSize(), 2 );

		num.getMap().addPair( min, label );
		BOOST_CHECK_EQUAL( num.getMap().getLabel(0), label );
		BOOST_CHECK_EQUAL( num.getMap().getSize(), 1 );

		num.getMap().setMap( map );
		BOOST_CHECK_EQUAL( num.getMap().getLabel(0), ""              );
		BOOST_CHECK_EQUAL( num.getMap().getLabel(1), "First number"  );
		BOOST_CHECK_EQUAL( num.getMap().getLabel(2), "Second number" );
		BOOST_CHECK_EQUAL( num.getMap().getLabel(3), "Third number"  );
		BOOST_CHECK_EQUAL( num.getMap().getSize(), 3 );
	}
}

BOOST_AUTO_TEST_CASE( basic_element_number_translate )
{
	LOG_INFO( "\n>>> basic_element_number_translate <<<" );
	{
		LOG_INFO( "\n ====  int8  ==== " );
		nbe::Number< nbe::int8 > num;

		num.setData( dataInt8Low, 1 );
		BOOST_CHECK_EQUAL( num.getValue(), 0 );

		num.setData( dataInt8High, 1 );
		BOOST_CHECK_EQUAL( num.getValue(), -1 );
	}
	{
		LOG_INFO( "\n ==== uint8  ==== " );
		nbe::Number< nbe::uint8 > num;

		num.setData( dataInt8Low, 1 );
		BOOST_CHECK_EQUAL( num.getValue(), 0 );

		num.setData( dataInt8High, 1 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );
	}

	{
		LOG_INFO( "\n ====  int16 ====>> big endian " );
		nbe::Number< nbe::int16 > num;

		LOG_INFO( "___ dataInt16Low ___");
		num.setData( dataInt16Low, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		LOG_INFO( "___ dataInt16High ___");
		num.setData( dataInt16High, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), -256 );

		LOG_INFO( "___ dataInt16Full ___");
		num.setData( dataInt16Full, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), -1 );
	}
	{
		LOG_INFO( "\n ==== uint16 ====>> big endian " );
		nbe::Number< nbe::uint16 > num;

		LOG_INFO( "___ dataInt16Low ___");
		num.setData( dataInt16Low, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 0x00ff );

		LOG_INFO( "___ dataInt16High ___");
		num.setData( dataInt16High, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 65280 );

		LOG_INFO( "___ dataInt16Full ___");
		num.setData( dataInt16Full, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 0xffff );
	}
	{
		LOG_INFO( "\n ====  int16 ====>> little endian " );
		nbe::Number< nbe::int16 > num;
		num.setBigEndianness( false );

		LOG_INFO( "___ dataInt16Low ___");
		num.setData( dataInt16Low, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), -256 );

		LOG_INFO( "___ dataInt16High ___");
		num.setData( dataInt16High, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		LOG_INFO( "___ dataInt16Full ___");
		num.setData( dataInt16Full, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), -1 );
	}
	{
		LOG_INFO( "\n ==== uint16 ====>> little endian " );
		nbe::Number< nbe::uint16 > num;
		num.setBigEndianness( false );

		LOG_INFO( "___ dataInt16Low ___");
		num.setData( dataInt16Low, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 65280 );

		LOG_INFO( "___ dataInt16High ___");
		num.setData( dataInt16High, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		LOG_INFO( "___ dataInt16Full ___");
		num.setData( dataInt16Full, 2 );
		BOOST_CHECK_EQUAL( num.getValue(), 0xffff );
	}

	{
		LOG_INFO( "\n ====  int32 ====>> big endian " );
		nbe::Number< nbe::int32 > num;

		num.setData( dataInt32Low, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt32High, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), -16777216 );

		num.setData( dataInt32Full, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), -1 );
	}
	{
		LOG_INFO( "\n ==== uint32 ====>> big endian " );
		nbe::Number< nbe::uint32 > num;

		num.setData( dataInt32Low, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt32High, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), 4278190080 );

		num.setData( dataInt32Full, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), std::numeric_limits<unsigned int>::max() );
	}
	{
		LOG_INFO( "\n ====  int32 ====>> little endian " );
		nbe::Number< nbe::int32 > num;
		num.setBigEndianness( false );

		num.setData( dataInt32Low, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), -16777216 );

		num.setData( dataInt32High, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt32Full, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), -1 );
	}
	{
		LOG_INFO( "\n ==== uint32 ====>> little endian " );
		nbe::Number< nbe::uint32 > num;
		num.setBigEndianness( false );

		num.setData( dataInt32Low, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), 4278190080 );

		num.setData( dataInt32High, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt32Full, 4 );
		BOOST_CHECK_EQUAL( num.getValue(), std::numeric_limits<unsigned int>::max() );
	}

	{
		LOG_INFO( "\n ====  int64 ====>> big endian " );
		nbe::Number< nbe::int64 > num;

		num.setData( dataInt64Low, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt64High, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), -72057594037927936 );

		num.setData( dataInt64Full, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), -1 );
	}
	{
		LOG_INFO( "\n ==== uint64 ====>> big endian " );
		nbe::Number< nbe::uint64 > num;

		num.setData( dataInt64Low, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt64High, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), 0xff00000000000000 );

		num.setData( dataInt64Full, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), std::numeric_limits<unsigned long long>::max() );
	}
	{
		LOG_INFO( "\n ====  int64 ====>> little endian " );
		nbe::Number< nbe::int64 > num;
		num.setBigEndianness( false );

		num.setData( dataInt64Low, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), -72057594037927936 );

		num.setData( dataInt64High, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt64Full, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), -1 );
	}
	{
		LOG_INFO( "\n ==== uint64 ====>> little endian " );
		nbe::Number< nbe::uint64 > num;
		num.setBigEndianness( false );

		num.setData( dataInt64Low, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), 0xff00000000000000 );

		num.setData( dataInt64High, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), 255 );

		num.setData( dataInt64Full, 8 );
		BOOST_CHECK_EQUAL( num.getValue(), std::numeric_limits<unsigned long long>::max() );
	}

	{
		LOG_INFO( "\n ==== float ====>> big endian " );
		nbe::Number< float > num;

		num.setData( dataFloatZero, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), 0, 0.001 );

		num.setData( dataFloatOneBigEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), 1, 0.001 );

		num.setData( dataFloatMaxBigEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< float >::max(), 0.001 );

		num.setData( dataFloatNegMaxBigEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), -std::numeric_limits< float >::max(), 0.001 );

		num.setData( dataFloatMinBigEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< float >::min(), 0.001 );
	}
	{
		LOG_INFO( "\n ==== float ====>> little endian " );
		nbe::Number< float > num;
		num.setBigEndianness( false );
		
		num.setData( dataFloatZero, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), 0, 0.001 );

		num.setData( dataFloatOneLittleEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), 1, 0.001 );

		num.setData( dataFloatMaxLittleEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< float >::max(), 0.001 );

		num.setData( dataFloatNegMaxLittleEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), -std::numeric_limits< float >::max(), 0.001 );

		num.setData( dataFloatMinLittleEndian, 4 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< float >::min(), 0.001 );
	}

	{
		LOG_INFO( "\n ==== double ====>> big endian " );
		nbe::Number< double > num;

		num.setData( dataDoubleZero, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), 0, 0.001 );

		num.setData( dataDoubleOneBigEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), 1, 0.001 );

		num.setData( dataDoubleMaxBigEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< double >::max(), 0.001 );

		num.setData( dataDoubleNegMaxBigEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), -std::numeric_limits< double >::max(), 0.001 );

		num.setData( dataDoubleMinBigEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< double >::min(), 0.001 );
	}
	{
		LOG_INFO( "\n ==== double ====>> little endian " );
		nbe::Number< double > num;
		num.setBigEndianness( false );
		
		num.setData( dataDoubleZero, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), 0, 0.001 );

		num.setData( dataDoubleOneLittleEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), 1, 0.001 );

		num.setData( dataDoubleMaxLittleEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< double >::max(), 0.001 );

		num.setData( dataDoubleNegMaxLittleEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), -std::numeric_limits< double >::max(), 0.001 );

		num.setData( dataDoubleMinLittleEndian, 8 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< double >::min(), 0.001 );
	}

	{
		LOG_INFO( "\n ==== ieeeExtended ====>> big endian " );
		nbe::Number< nbe::ieeeExtended > num;

		num.setData( dataIeeeExtendedZero, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), 0, 0.001 );

		num.setData( dataIeeeExtendedOneBigEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), 1, 0.001 );

		num.setData( dataIeeeExtendedMaxBigEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< nbe::ieeeExtended >::max(), 0.001 );

		num.setData( dataIeeeExtendedNegMaxBigEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), -std::numeric_limits< nbe::ieeeExtended >::max(), 0.001 );

		num.setData( dataIeeeExtendedMinBigEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< nbe::ieeeExtended >::min(), 0.001 );
	}

	{
		LOG_INFO( "\n ==== ieeeExtended ====>> little endian " );
		nbe::Number< nbe::ieeeExtended > num;
		num.setBigEndianness( false );

		num.setData( dataIeeeExtendedZero, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), 0, 0.001 );

		num.setData( dataIeeeExtendedOneLittleEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), 1, 0.001 );

		num.setData( dataIeeeExtendedMaxLittleEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< nbe::ieeeExtended >::max(), 0.001 );

		num.setData( dataIeeeExtendedNegMaxLittleEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), -std::numeric_limits< nbe::ieeeExtended >::max(), 0.001 );

		num.setData( dataIeeeExtendedMinLittleEndian, 10 );
		BOOST_CHECK_CLOSE( num.getValue(), std::numeric_limits< nbe::ieeeExtended >::min(), 0.001 );
	}
}

BOOST_AUTO_TEST_CASE( basic_element_number_toString )
{
	LOG_INFO( "\n>>> basic_element_number_toString <<<" );
	{
		nbe::Number< nbe::int8 > num;
		num.setData( dataInt8High, 1 );
		BOOST_CHECK_EQUAL( num.toString(), "-1" );
	}
	{
		nbe::Number< nbe::uint8 > num;
		num.setData( dataInt8High, 1 );
		BOOST_CHECK_EQUAL( num.toString(), "255" );
	}
	{
		nbe::Number< nbe::int16 > num;
		num.setData( dataInt16Full, 2 );
		BOOST_CHECK_EQUAL( num.toString(), "-1" );
	}
	{
		nbe::Number< nbe::uint16 > num;
		num.setData( dataInt16Full, 2 );
		BOOST_CHECK_EQUAL( num.toString(), "65535" );
	}
	{
		nbe::Number< nbe::int32 > num;
		num.setData( dataInt32Full, 4 );
		BOOST_CHECK_EQUAL( num.toString(), "-1" );
	}
	{
		nbe::Number< nbe::uint32 > num;
		num.setData( dataInt32Full, 4 );
		BOOST_CHECK_EQUAL( num.toString(), "4294967295" );
	}
	{
		nbe::Number< nbe::int64 > num;
		num.setData( dataInt64Full, 8 );
		BOOST_CHECK_EQUAL( num.toString(), "-1" );
	}
	{
		nbe::Number< nbe::uint64 > num;
		num.setData( dataInt64Full, 8 );
		BOOST_CHECK_EQUAL( num.toString(), "18446744073709551615" );
	}
	{
		nbe::Number< float > num;
		num.setData( dataFloatOneBigEndian, 4 );
		BOOST_CHECK_EQUAL( num.toString(), "1" );
	}
	{
		nbe::Number< float > num;
		num.setData( dataFloatMaxBigEndian, 4 );
		BOOST_CHECK_EQUAL( num.toString(), "3.40282e+38" );
	}
	{
		nbe::Number< double > num;
		num.setData( dataDoubleOneBigEndian, 8 );
		BOOST_CHECK_EQUAL( num.toString(), "1" );
	}
	{
		nbe::Number< double > num;
		num.setData( dataDoubleMaxBigEndian, 8 );
		BOOST_CHECK_EQUAL( num.toString(), "1.79769e+308" );
	}
	{
		nbe::Number< nbe::ieeeExtended > num;
		num.setData( dataIeeeExtendedOneBigEndian, 10 );
		BOOST_CHECK_EQUAL( num.toString(), "1" );
	}
	{
		nbe::Number< nbe::ieeeExtended > num;
		num.setData( dataIeeeExtendedMaxBigEndian, 10 );
		BOOST_CHECK_EQUAL( num.toString(), "1.18973e+4932" );
	}
}

BOOST_AUTO_TEST_SUITE_END()
