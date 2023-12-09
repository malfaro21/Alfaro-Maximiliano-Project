#include <stdio.h>
#include <stdlib.h>

int page_number(int logical_address);
int extract_offset(int ogical_address);


int extract_pagenum(int logical_address){
    int page_number = (logical_address >> 8) & 0x00FF;
}
int extract_offset(int logical_address){
    int Offset = logical_address & 0x00FF;
}

