/*
--- Day 4: The Ideal Stocking Stuffer ---

Santa needs help mining some AdventCoins (very similar to bitcoins) to use as gifts for all the economically forward-thinking little girls and boys.

To do this, he needs to find MD5 hashes which, in hexadecimal, start with at least five zeroes. 
The input to the MD5 hash is some secret key (your puzzle input, given below) followed by a number in decimal. 
To mine AdventCoins, you must find Santa the lowest positive number (no leading zeroes: 1, 2, 3, ...) that produces such a hash.

For example:

If your secret key is abcdef, the answer is 609043, 
because the MD5 hash of abcdef609043 starts with five zeroes (000001dbbfa...), 
and it is the lowest such number to do so.
If your secret key is pqrstuv, 
the lowest number it combines with to make an MD5 hash starting with five zeroes is 1048970; 
that is, the MD5 hash of pqrstuv1048970 looks like 000006136ef....
Your puzzle input is iwrupvqb.
*/


#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>
#include <array>      
#include <cassert>    
#include <cstdint>
#include <cstring>    
#include <iostream>     
#include <vector>     
#include <thread>
#include <list>

std::string seed =  "iwrupvqb";

namespace hashing {
namespace md5 {

uint32_t leftRotate32bits(uint32_t n, std::size_t rotate) {
    return (n << rotate) | (n >> (32 - rotate));
}

bool isBigEndian() {
    union {
        uint32_t i;
        std::array<char, 4> c;
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

uint32_t toLittleEndian32(uint32_t n) {
    if (!isBigEndian()) {
        return ((n << 24) & 0xFF000000) | ((n << 8) & 0x00FF0000) |
               ((n >> 8) & 0x0000FF00) | ((n >> 24) & 0x000000FF);
    }
    // Machine works on little endian, no need to change anything
    return n;
}

uint64_t toLittleEndian64(uint64_t n) {
    if (!isBigEndian()) {
        return ((n << 56) & 0xFF00000000000000) |
               ((n << 40) & 0x00FF000000000000) |
               ((n << 24) & 0x0000FF0000000000) |
               ((n << 8) & 0x000000FF00000000) |
               ((n >> 8) & 0x00000000FF000000) |
               ((n >> 24) & 0x0000000000FF0000) |
               ((n >> 40) & 0x000000000000FF00) |
               ((n >> 56) & 0x00000000000000FF);
        ;
    }
    // Machine works on little endian, no need to change anything
    return n;
}

std::string sig2hex(void* sig) {
    const char* hexChars = "0123456789abcdef";
    auto* intsig = static_cast<uint8_t*>(sig);
    std::string hex = "";
    for (uint8_t i = 0; i < 16; i++) {
        hex.push_back(hexChars[(intsig[i] >> 4) & 0xF]);
        hex.push_back(hexChars[(intsig[i]) & 0xF]);
    }
    return hex;
}

void* hash_bs(const void* input_bs, uint64_t input_size) {
    auto* input = static_cast<const uint8_t*>(input_bs);

    // Step 0: Initial Data (Those are decided in the MD5 protocol)
    // s is the shift used in the leftrotate each round
    std::array<uint32_t, 64> s = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    // K is pseudo-random values used each round
    // The values can be obtained by the following python code:

    std::array<uint32_t, 64> K = {
        3614090360, 3905402710, 606105819,  3250441966, 4118548399, 1200080426,
        2821735955, 4249261313, 1770035416, 2336552879, 4294925233, 2304563134,
        1804603682, 4254626195, 2792965006, 1236535329, 4129170786, 3225465664,
        643717713,  3921069994, 3593408605, 38016083,   3634488961, 3889429448,
        568446438,  3275163606, 4107603335, 1163531501, 2850285829, 4243563512,
        1735328473, 2368359562, 4294588738, 2272392833, 1839030562, 4259657740,
        2763975236, 1272893353, 4139469664, 3200236656, 681279174,  3936430074,
        3572445317, 76029189,   3654602809, 3873151461, 530742520,  3299628645,
        4096336452, 1126891415, 2878612391, 4237533241, 1700485571, 2399980690,
        4293915773, 2240044497, 1873313359, 4264355552, 2734768916, 1309151649,
        4149444226, 3174756917, 718787259,  3951481745};

    // The initial 128-bit state
    uint32_t a0 = 0x67452301, A = 0;
    uint32_t b0 = 0xefcdab89, B = 0;
    uint32_t c0 = 0x98badcfe, C = 0;
    uint32_t d0 = 0x10325476, D = 0;

    // Step 1: Processing the bytestring

    // First compute the size the padded message will have
    // so it is possible to allocate the right amount of memory
    uint64_t padded_message_size = 0;
    if (input_size % 64 < 56) {
        padded_message_size = input_size + 64 - (input_size % 64);
    } else {
        padded_message_size = input_size + 128 - (input_size % 64);
    }

    std::vector<uint8_t> padded_message(padded_message_size);

    // Beginning of the padded message is the original message
    std::copy(input, input + input_size, padded_message.begin());

    // Afterwards comes a single 1 bit and then only zeroes
    padded_message[input_size] = 1 << 7;  // 10000000
    for (uint64_t i = input_size; i % 64 != 56; i++) {
        if (i == input_size) {
            continue;  // pass first iteration
        }
        padded_message[i] = 0;
    }

    // We then have to add the 64-bit size of the message at the end
    // When there is a conversion from int to bytestring or vice-versa
    // We always need to make sure it is little endian
    uint64_t input_bitsize_le = toLittleEndian64(input_size * 8);
    for (uint8_t i = 0; i < 8; i++) {
        padded_message[padded_message_size - 8 + i] =
            (input_bitsize_le >> (56 - 8 * i)) & 0xFF;
    }

    // Already allocate memory for blocks
    std::array<uint32_t, 16> blocks{};

    // Rounds
    for (uint64_t chunk = 0; chunk * 64 < padded_message_size; chunk++) {
        // First, build the 16 32-bits blocks from the chunk
        for (uint8_t bid = 0; bid < 16; bid++) {
            blocks[bid] = 0;

            // Having to build a 32-bit word from 4-bit words
            // Add each and shift them to the left
            for (uint8_t cid = 0; cid < 4; cid++) {
                blocks[bid] = (blocks[bid] << 8) +
                              padded_message[chunk * 64 + bid * 4 + cid];
            }
        }

        A = a0;
        B = b0;
        C = c0;
        D = d0;

        // Main "hashing" loop
        for (uint8_t i = 0; i < 64; i++) {
            uint32_t F = 0, g = 0;
            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7 * i) % 16;
            }

            // Update the accumulators
            F += A + K[i] + toLittleEndian32(blocks[g]);

            A = D;
            D = C;
            C = B;
            B += leftRotate32bits(F, s[i]);
        }
        // Update the state with this chunk's hash
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    // Build signature from state
    // Note, any type could be used for the signature
    // uint8_t was used to make the 16 bytes obvious
    // The sig needs to be little endian
    auto* sig = new uint8_t[16];
    for (uint8_t i = 0; i < 4; i++) {
        sig[i] = (a0 >> (8 * i)) & 0xFF;
        sig[i + 4] = (b0 >> (8 * i)) & 0xFF;
        sig[i + 8] = (c0 >> (8 * i)) & 0xFF;
        sig[i + 12] = (d0 >> (8 * i)) & 0xFF;
    }

    return sig;
}

void* hash(const std::string& message) {
    return hash_bs(&message[0], message.size());
}

}  // namespace md5
}  // namespace hashing

static void test() {
    // Hashes empty string and stores signature
    void* sig = hashing::md5::hash("");
    std::cout << "Hashing empty string" << std::endl;
    // Prints signature hex representation
    std::cout << hashing::md5::sig2hex(sig) << std::endl << std::endl;
    // Test with cassert whether sig is correct from the expected value
    assert(hashing::md5::sig2hex(sig).compare(
               "d41d8cd98f00b204e9800998ecf8427e") == 0);

    // Hashes "The quick brown fox jumps over the lazy dog" and stores signature
    void* sig2 =
        hashing::md5::hash("The quick brown fox jumps over the lazy dog");
    std::cout << "Hashing The quick brown fox jumps over the lazy dog"
              << std::endl;
    // Prints signature hex representation
    std::cout << hashing::md5::sig2hex(sig2) << std::endl << std::endl;
    // Test with cassert whether sig is correct from the expected value
    assert(hashing::md5::sig2hex(sig2).compare(
               "9e107d9d372bb6826bd81d3542a419d6") == 0);

    // Hashes "The quick brown fox jumps over the lazy dog." (notice the
    // additional period) and stores signature
    void* sig3 =
        hashing::md5::hash("The quick brown fox jumps over the lazy dog.");
    std::cout << "Hashing "
                 "The quick brown fox jumps over the lazy dog."
              << std::endl;
    // Prints signature hex representation
    std::cout << hashing::md5::sig2hex(sig3) << std::endl << std::endl;
    // Test with cassert whether sig is correct from the expected value
    assert(hashing::md5::sig2hex(sig3).compare(
               "e4d909c290d0fb1ca068ffaddf22cbd0") == 0);

    // Hashes "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
    // and stores signature
    void* sig4 = hashing::md5::hash(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    std::cout
        << "Hashing "
           "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
        << std::endl;
    // Prints signature hex representation
    std::cout << hashing::md5::sig2hex(sig4) << std::endl << std::endl;
    // Test with cassert whether sig is correct from the expected value
    assert(hashing::md5::sig2hex(sig4).compare(
               "d174ab98d277d9f5a5611c2c9f419d9f") == 0);
}


static void interactive() {
    while (true) {
        std::string input;
        std::cout << "Enter a message to be hashed (Ctrl-C to exit): "
                  << std::endl;
        std::getline(std::cin, input);
        void* sig = hashing::md5::hash(input);
        std::cout << "Hash is: " << hashing::md5::sig2hex(sig) << std::endl;

        while (true) {
            std::cout << "Want to enter another message? (y/n) ";
            std::getline(std::cin, input);
            if (input.compare("y") == 0) {
                break;
            } else if (input.compare("n") == 0) {
                return;
            }
        }
    }
}

void Worker(int start, int length){
        int stop = start + length;
        std::string input, output;

        for(int i = start; i < stop; i++ ){
            input = seed + std::to_string(i++);

            void* sig = hashing::md5::hash(input);
            output = hashing::md5::sig2hex(sig);
            
            if(output.substr(0,5) == "00000") {
                std::cout << "I: " << i << " - " << input << " Hash is: " << output << std::endl;
                Found = true;
            }

            if(Found) break;

        }
}

bool Found = false;
int NumOfThreads = 8;
int WorkSize = 100000;

int main() {
    int i = 0;
    do
    {
        for(int tn = 0; i< NumOfThreads; tn++){
            int ts = i+(tn*WorkSize);
            std::thread T(Worker,ts,WorkSize);
        }
        i += NumOfThreads * WorkSize;

    } while (!Found);
    
}

