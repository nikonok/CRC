#include "crc.hpp"
#include <iostream>
#include <sstream>
using namespace std;

#define MESSAGE( x ) \
    cout << x << endl;

#define CHECK( x, y ) \
    if( ! ( x ) ) { \
        cout << "Failed! " << y << endl; \
        assert( x ); \
    } \

class unit_tests {
public:
    static void generator_test_4() {
        CRC4 crc;
        auto crc_table = crc.generate_crc_table();

        for( uint32_t i = 0; i < 0x100; ++i ) {
            CHECK( crc_table[i] == crc.crc_table[i], "generator_test_4()" );
        }

        MESSAGE( "generator_test_4() passed" );
    }

    static void generator_test_8() {
        CRC8 crc;
        auto crc_table = crc.generate_crc_table();

        for( uint32_t i = 0; i < 0x100; ++i ) {
            CHECK( crc_table[i] == crc.crc_table[i], "generator_test_8()" );
        }

        MESSAGE( "generator_test_8() passed" );
    }

    static void generator_test_16() {
        CRC16 crc;
        auto crc_table = crc.generate_crc_table();

        for( uint32_t i = 0; i < 0x100; ++i ) {
            CHECK( crc_table[i] == crc.crc_table[i], "generator_test_16()" );
        }

        MESSAGE( "generator_test_16() passed" );
    }

    static void generator_test_32() {
        CRC32 crc;
        auto crc_table = crc.generate_crc_table();

        for( uint32_t i = 0; i < 0x100; ++i ) {
            CHECK( crc_table[i] == crc.crc_table[i], "generator_test_32()" );
        }

        MESSAGE( "generator_test_32() passed" );
    }

    static void base_crc_test_4() {
        stringstream ss("123456789");
        CRC4 crc;
        ss >> crc;
        std::cout << crc << std::endl;
        CHECK( crc.get_crc_poly() == 0x3, "CRC4 poly != 0x3");
        CHECK( crc.get_crc_code() == 0xc, "CRC4(123456789) != 0xc" );

        MESSAGE( "base_crc_test_4() passed" );
    }

    static void base_crc_test_8() {
        stringstream ss("123456789");
        CRC8 crc;
        ss >> crc;
        CHECK( crc.get_crc_poly() == 0x31, "CRC8 poly != 0x31");
        CHECK( crc.get_crc_code() == 0xF7, "CRC8(123456789) != 0xF7" );

        MESSAGE( "base_crc_test_8() passed" );
    }

    static void base_crc_test_16() {
        stringstream ss("123456789");
        CRC16 crc;
        ss >> crc;
        CHECK( crc.get_crc_poly() == 0x1021, "CRC16 poly != 0x1021");
        CHECK( crc.get_crc_code() == 0x29B1, "CRC16(123456789) != 0x29B1" );

        MESSAGE( "base_crc_test_16() passed" );
    }

    static void base_crc_test_32() {
        stringstream ss("123456789");
        CRC32 crc;
        ss >> crc;
        CHECK( crc.get_crc_poly() == 0xEDB88320, "CRC32 poly != 0xEDB88320");
        CHECK( crc.get_crc_code() == 0xCBF43926, "CRC32(123456789) != 0xCBF43926" );

        MESSAGE( "base_crc_test_32() passed" );
    }
};

int main(){
    cout << "Tests strated!" << endl << endl;

    cout << "Table generator tests" << endl << endl;

    unit_tests::generator_test_4();

    unit_tests::generator_test_8();

    unit_tests::generator_test_16();

    unit_tests::generator_test_32();

    cout << endl << "Base CRC tests (check \"123456789\")" << endl << endl;

    unit_tests::base_crc_test_4();

    unit_tests::base_crc_test_8();
    
    unit_tests::base_crc_test_16();

    unit_tests::base_crc_test_32();

    cout << endl << "Tests passed!" << endl << endl;
}