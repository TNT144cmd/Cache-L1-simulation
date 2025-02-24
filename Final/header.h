#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include <sstream>
#include <string.h>
#include <iomanip>

using namespace std;    

constexpr auto BYTE_OFFSET = 6;							// the byte offset is 6 bits
constexpr auto CACHE_INDEX = 14;						// the set bits/cache index is 14 bits
constexpr auto TAG_BITS = 12;							// the tag bits are (32 - 14 - 6 = 12 bits) 
constexpr auto MASK_BYTE_SELECT = 0x0000003F;			// mask the least significat 6 bits for the byte offset
constexpr auto MASK_CACHE_INDEX = 0x000FFFFF;			// mask the least significat 20 bits for the (byte offset + cache index/set)
constexpr auto MASK_TAG_BITS = 0xFFF0000;				// mask the most significat 12 bits for the byte offset
constexpr auto EMPTY_TAG = 4096;						//We are using the value 4096 to indicate an empty tag(since 0 - 4095 are used)


//Class/container for the cache variables (Properties)

class cache {
public:
	char State = 'I';							
	unsigned int LRU_bits;							// LRU bits 
	unsigned int address;							// Address bits
	unsigned int set_bits;							// Set bits
	unsigned int tag_bits;							// tag bits
};

// instantiate data and instruction caches from the cache class
cache L1_data[4][16384];							// 4-way 16k sets data cache		[4-way][16k]
cache L1_inst[2][16384];							// 2-way 16k sets instruction cache [2-way][16k]

// Cache statistics with parameters that counts number of reads, writes, hits, misses, and ratios
class usage_statistics {
	public:
	// Data cache
		unsigned int data_read;							// Data cache read count
		unsigned int data_write;						// Data cache write count
		unsigned int data_hit;							// Data cache hit count
		unsigned int data_miss;							// Data cache miss count
		float data_hit_ratio;							// Data hit/miss ratio

	// Instruction cache
		unsigned int inst_read;							// Instruction cache read count
		unsigned int inst_miss;							// Instruction cache miss count
		unsigned int inst_hit;							// Instruction cache hit count
		float inst_hit_ratio;							// Instruction hit/miss ratio
};

// Instantiation of the usage_statistics class
usage_statistics statistics;

// Output mode, mode is either 0 or 1. 
unsigned int mode;

/*........................................*/

// All functions used in the main .cpp file needs to be delcared here. 
void clear_cache();
int matching_tag(unsigned int tag, unsigned int set, char which_cache);
void L1_LRU(unsigned int way, unsigned int set, char which_cache);
int find_LRU(unsigned int set, char which_cache);
void invalidate(unsigned int addr);
void fetch_inst(unsigned int addr);
void cache_read(unsigned int addr);
void write(unsigned int addr);
void print_stats();
void parser(int argc, char** argv);