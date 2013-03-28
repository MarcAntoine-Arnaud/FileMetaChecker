#include <common/global.hpp>

#include <systemInfo/FileSystemInfo.hpp>
#include <report/Report.hpp>

#include <iomanip>
#include <string>
#include <fstream>

#include <boost/exception/diagnostic_information.hpp>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>

namespace bpo = boost::program_options;

int main( int argc, char** argv )
{
	qc::common::Color color;
	bpo::options_description cmdlineOptions;
	bpo::positional_options_description pod;
	bpo::variables_map vm;

	std::vector<std::string> paths;
	
	/*** OPTIONS ***/
	// Declare the supported options
	cmdlineOptions.add_options()
		( "help,h", "produce help message" )
		( "input,i", bpo::value< std::vector<std::string> >(), "input file" )
		( "color", "display the output with colors" )
		( "script", "format the output such as it could be dump in a file" )
	;

	// define default options
	pod.add( "input", -1 );

	// Parsing options
	try
	{
		bpo::store( bpo::command_line_parser( argc, argv ).options( cmdlineOptions ).positional( pod ).run(), vm);

		// get environment options and parse them
		if( const char* env_options = std::getenv("MIKSI_OPTIONS") )
		{
			const std::vector<std::string> vecOptions = bpo::split_unix( env_options, " " );
			bpo::store(bpo::command_line_parser( vecOptions ).options( cmdlineOptions ).positional( pod ).run(), vm);
		}
		bpo::notify( vm );
	}
	catch( const bpo::error& e)
	{
		COMMON_COUT( "command line error: " << e.what() );
		exit( -2 );
	}
	catch(...)
	{
		COMMON_COUT( "unknown error in command line." );
		exit( -2 );
	}

	if( vm.count( "color" ) )
	{
		color.enable();
	}

	if( vm.count( "script" ) )
	{
		color.disable();
	}

	if( vm.count( "input" ) )
	{
		paths = vm[ "input" ].as< std::vector<std::string> >();
	}


	if( vm.count( "help" ) || paths.size() == 0 )
	{
		COMMON_COUT( color._blue  << "File System Information" << color._std << std::endl );
		COMMON_COUT( color._blue  << "NAME" << color._std );
		COMMON_COUT( color._green << "\tmiksi - file system information" << color._std << std::endl);
		COMMON_COUT( color._blue  << "SYNOPSIS" << color._std );
		COMMON_COUT( color._green << "\tmiksi [options] file[s]" << color._std << std::endl );
		COMMON_COUT( color._blue  << "DESCRIPTION" << color._std << std::endl );

		COMMON_COUT( "Report File status" << std::endl );
		COMMON_COUT( color._blue  << "OPTIONS" << color._std << std::endl );
		COMMON_COUT( cmdlineOptions );
		return 0;
	}

	BOOST_FOREACH( std::string& path, paths )
	{
		Report report;
		
		FileSystemInfo fileSystemInfo( path );
		COMMON_COUT( fileSystemInfo );
		
		fileSystemInfo.getReport( &report );
		
		report.exportReport( path + ".xml" );
	}

	return 0;
}


