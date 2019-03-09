#include "crc.hpp"
#include <iostream>
#include <fstream>

int main(){
    std::ifstream inputfile( "/Users/antonshkinder/Projects/ti/lab1_crc/texts/text1.txt" );
    assert( inputfile.is_open() );
    assert( !inputfile.eof() );

    char bt;
    while( !inputfile.eof() ) {
        inputfile.read( &bt, 1 );
        std::cout << std::hex << (int)bt << " ";
    }
    std::cout << std::endl;

    inputfile.clear();
    inputfile.seekg(0, std::ios::beg);

    CRC4 crc4;
    CRC8 crc8;
    CRC16 crc16;
    CRC32 crc32;

    inputfile >> crc4;

    inputfile.clear();
    inputfile.seekg(0, std::ios::beg);

    inputfile >> crc8;

    inputfile.clear();
    inputfile.seekg(0, std::ios::beg);

    inputfile >> crc16;

    inputfile.clear();
    inputfile.seekg(0, std::ios::beg);

    inputfile >> crc32;

    std::cout << "CRC4:\n" << crc4 << std::endl;
    std::cout << "CRC8:\n" << crc8 << std::endl;
    std::cout << "CRC16:\n" << crc16 << std::endl;
    std::cout << "CRC32:\n" << crc32 << std::endl;
}