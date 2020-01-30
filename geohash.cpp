#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

const char base32_encode_lut [32] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k', 'm', 'n', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

char b32_encode_num(uint16_t idx)
{
    return base32_encode_lut[idx];
}

uint16_t b32_decode_char(char c)
{
    for(uint16_t i = 0; i < 32; ++i)
    {
        if(base32_encode_lut[i] == c)
            return i;
    }
    return -1;
}

void encode_geohash(double lat, double lng, int bits, vector<char> &geohash)
{
    double minLat = -90,  maxLat = 90;
    double minLng = -180, maxLng = 180;
    uint16_t result = 0;

    for (int i = 0; i < bits; ++i)
    {
        if (i % 5 == 0 && i != 0)
        {
            geohash.push_back(b32_encode_num(result));
            result = 0;
        }
    
        if (i % 2 == 0)
        {                                     // even bit: bisect longitude
            double midpoint = (minLng + maxLng) / 2;
            if (lng < midpoint)
            {
                result <<= 1;                 // push a zero bit
                maxLng = midpoint;            // shrink range downwards
            }
            else
            {
                result = result << 1 | 1;     // push a one bit
                minLng = midpoint;            // shrink range upwards
            }
        }
        else
        {                                     // odd bit: bisect latitude
            double midpoint = (minLat + maxLat) / 2;
            if (lat < midpoint)
            {
                result <<= 1;                 // push a zero bit
                maxLat = midpoint;            // shrink range downwards
            }
            else
            {
                result = result << 1 | 1;     // push a one bit
                minLat = midpoint;            // shrink range upwards
            }
        }
    }
}

void decode_geohash(string geohash_str)
{
    for(char const &c : geohash_str)
    {
        char lower_c = tolower(c);

        for(uint8_t i = 4; i >= )
        {
            uint8_t bitN = i;   
        }

    }
}

int main(void)
{
    vector<char> gh;
    double lat = 41.8781;
    double lng = -87.6289;

    encode_geohash(lat, lng, 5*13, gh);
    gh.push_back('\0');

    cout << "(" << lat << ", " << lng << ")'s geohash: ";

    for (auto gh_char: gh)
        std::cout << gh_char;

    cout << "\n";

    string geohash_str = "tzqq4p9mt7et";

    for (char const &c : geohash_str)
    {
        cout << b32_decode_char(c);
    }


    
    std::cout << "\n";
}