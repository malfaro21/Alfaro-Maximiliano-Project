#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhysicalMem.c"

int logical_address;

FILE *address_file;
char address[7]; //Store address

int page_Number;
int offset;

void getPage(int logical_address){
    page_Number = (logical_address >>8);
}
void getOffSet(int logical_address){
    offset = (logical_address & 0x00FF);
}

int main(){
    address_file = fopen("addresses.txt", "r");

    insert_Chunk(66);
    signed char value = physical_Memory[20];
    int physical_Address = 20;
    printf("Address: %d Value: %d\n", physical_Address, value);

    insert_Chunk(244);
    value = physical_Memory[(256*1) + 29];
    physical_Address = (256*1) + 29;
    printf("Address: %d Value: %d\n", physical_Address, value);

    insert_Chunk(117);
    value = physical_Memory[(256*2) + 246];
    physical_Address = (256*2) + 246;
    printf("Address: %d Value: %d\n", physical_Address, value);

    insert_Chunk(209);
    value = physical_Memory[(256*3) + 179];
    physical_Address = (256*3) + 179;
    printf("Address: %d Value: %d\n", physical_Address, value);

    while (fgets(address, 7, address_file) != NULL){
        logical_address = atoi(address); // convert char array to int
        getPage(logical_address);
        getOffSet(logical_address);
        // printf("logical address: %d, PageNumber: %d, Offset: %d\n", logical_address,getPage(logical_address), getOffSet(logical_address));
    }
    
}
