#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 256 // frame size is 256 frames.
#define PAGE_SIZE 256 // page size of 2^8 bytes.
#define TLB_SIZE 16 // 16 entries in the TLB
#define MEM_SIZE 65336 // physical memory is 65336 bytes

int page_number(int logical_address);
int extract_offset(int logical_address);
int translate_address(int logical_address);

int extract_page(int logical_address){
    int page_number = (logical_address >> 8) & 0x00FF;
    int offset = logical_address & 0x00FF;
}

