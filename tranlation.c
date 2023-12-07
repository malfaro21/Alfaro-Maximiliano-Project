#include <stdio.h>
#include <stdlib.h>

int page_number(int logical_address);


int extract_pagenum(int logical_address){
    int page_number = (logical_address >> 8) & 0x00FF;
}