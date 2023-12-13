#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhysicalMem.c"

int logical_address;
signed char value;
FILE *address_file;
int physical_address;
char address[7]; //Store address

int page_Number;
int offset;

void getPage(int logical_address){
    page_Number = (logical_address >> 8);
}
void getOffSet(int logical_address){
    offset = (logical_address & 0x00FF);
}

int main(){
    address_file = fopen("addresses.txt", "r");

    while (fgets(address, 7, address_file) != NULL){
        logical_address = atoi(address); // convert char array to int
        getPage(logical_address);
        getOffSet(logical_address);
        // printf("logical address: %d, PageNumber: %d, Offset: %d\n", logical_address,getPage(logical_address), getOffSet(logical_address));
    }
    
}
