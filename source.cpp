#include "crc.hpp"
#include <iostream>
#include <fstream>
#include <utility>

void print_help_message(){
    std::cout << "CRC calculator, available: crc4/crc8/crc16/crc32." << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\t-t [type]  -- type = crc4/crc8/crc16/crc32 (used crc8 by default)" << std::endl;
    std::cout << "\t-h         -- print this message" << std::endl;
    std::cout << "[arg1] -- path to file (no default value)" << std::endl;
}

uint8_t get_type( std::string arg ){
    if( arg == "crc4" ){
        return 4;
    } else if( arg == "crc8" ){
        return 8;
    } else if( arg =="crc16" ){
        return 16;
    } else if( arg == "crc32" ){
        return 32;
    } else {
        return 0;
    }
}

std::pair<uint8_t, std::ifstream> parse_agrs( int argc, char** argv ){
    if( argc != 4 && argc != 2 ){
        std::cout << "Invalid args!" << std::endl;
        print_help_message();
        exit(1);
    }

    if( argc == 2 ){
        if( argv[1][1] == 'h' ) {
            print_help_message();
            exit(0);
        } else{
            return std::make_pair( 8, std::ifstream( argv[1] ) );
        }
    } else {
        uint8_t bits = 0;
        std::string arg1( argv[1] ), arg2( argv[2] ), arg3( argv[3] );
        if( arg1 == "-t" ){
            bits = get_type( arg2 );
            return make_pair( bits, std::ifstream( arg3 ) );
        } else if( arg2 == "-t" ) {
            bits = get_type( arg3 );
            return make_pair( bits, std::ifstream( arg1 ) );
        } else {
            std::cout << "Invalid args!" << std::endl;
            print_help_message();
            exit(1);          
        }
    }

}

template< class crcType, crcType polinomal >
void print_result( const CRC< crcType, polinomal > &crc, uint8_t bits ){
    std::cout << "Result CRC" << bits << std::endl << crc << std::endl;
}

int main( int argc, char** argv ){
    auto pair_of_crc = parse_agrs( argc, argv );
    if( !pair_of_crc.second.is_open() ){
        std::cout << "Invalid path to file! (or invalid args, use -h to see help" << std::endl;
    }
    switch( pair_of_crc.first ) {
        case 0: print_help_message(); break;
        case 4:  { CRC4  crc4 ( pair_of_crc.second ); print_result( crc4,  4  ); break; }
        case 8:  { CRC8  crc8 ( pair_of_crc.second ); print_result( crc8,  8  ); break; }
        case 16: { CRC16 crc16( pair_of_crc.second ); print_result( crc16, 16 ); break; }
        case 32: { CRC32 crc32( pair_of_crc.second ); print_result( crc32, 32 ); break; }
    }
}