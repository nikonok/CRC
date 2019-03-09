#pragma once

#include <vector>
#include <sstream>
#include <bitset>

// TODO
#include <iostream>

class unit_tests;

using crc4Type = uint8_t;
using crc8Type = uint8_t;
using crc16Type = uint16_t;
using crc32Type = uint32_t;

template< class crcType, crcType polinomal >
class CRC {
public:
    CRC(): poly( polinomal ) { crc_table = generate_crc_table(); };

    crcType encode( std::istream &is ) {
        assert( crc_table.size() );
        crc_code = 0;
        uint8_t buff;
        uint8_t offset = sizeof( crcType ) > 1 ? 8 : 0;

        while( read_stream( is, buff ) ) {
            crc_code = ( crc_code << offset ) ^ crc_table[ ( ( crc_code >> offset ) ^ buff ) & 0xFF ];
        }

        if( typeid( crcType ) == typeid( crc32Type ) ) {
            crc_code ^= ( crcType ) -1;
        }

        return crc_code;
    }

    crcType get_crc_code() const { return crc_code; }

    crcType get_crc_poly() const { return poly; }

    friend unit_tests;

protected:

    crcType crc_code;

    const crcType poly;

    std::vector< crcType > crc_table;

    constexpr std::vector< crcType > generate_crc_table() {
        std::vector< crcType > crc_tab( 256 );
        crcType _crc;

        for( uint32_t x = 0; x < 0x100; x++ ) {
            _crc = x << ( sizeof( crcType ) * 8 - 8 );
           for ( uint32_t y = 0; y < 8; y++ ) {
               _crc = ( _crc & ( 1 << ( sizeof( crcType ) * 8 - 1 ) ) ) ? ( ( _crc << 1 ) ^ poly ) : ( _crc << 1 );
           }
           crc_tab[x] = _crc;
        }

        return crc_tab;
    }

    bool read_stream( std::istream& is, uint8_t& value ) {
        value = 0;
        value |= is.get();
        return !is.eof();
    }
};

template< class crcType, crcType polinomal >
std::ostream& operator<<( std::ostream &os, const CRC< crcType, polinomal > &crc ){
    crcType crc_code = crc.get_crc_code();
    os << "Binary value: 0b" << std::bitset< sizeof( crc_code ) * 8 >( crc_code ) << std::endl;
    os << "Hex value: 0x" << std::hex << (int)crc_code;
    return os;
}

template< class crcType, crcType polinomal >
std::istream& operator>>( std::istream &os, CRC< crcType, polinomal > &crc ){
    crc.encode( os );
    return os;
}

// Poly: 0x3
//       x^4 + x + 1
class CRC4: public CRC< crc4Type, 0x3 > { };

// Poly: 0x31
//       x^8 + x^5 + x^4 + 1
class CRC8: public CRC< crc8Type, 0x31 > { };

// Poly: 0x1021
//       x^16 + x^12 + x^5 + 1
class CRC16: public CRC< crc16Type, 0x1021 > { };


// Poly: 0x04C11DB7
//       x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
class CRC32: public CRC< crc32Type, 0x04C11DB7 > { };
