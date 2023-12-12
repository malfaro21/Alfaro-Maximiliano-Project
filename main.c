#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhysicalMem.c"

int logical_address;

FILE *address_file;
char address[7]; //Store address

int getPage(int logical_address){
    int pageNum = (logical_address >>8);
    return pageNum;
}
int getOffSet(int logical_address){
    int offSet = (logical_address & 0x00FF);
    return offSet;
}


void insert_Chunk(int page_Number){
    FILE *backing_Store = fopen("BACKING_STORE.bin", "rb");

    if (fseek(backing_Store, page_Number * 256, SEEK_SET) != 0){
        fprintf(stderr, "Error\n");
        return;
    }

    if (fread(chunk_Store, sizeof(signed char), 256, backing_Store) == 0){
        fprintf(stderr, "Error\n");
        return;
    }

    int chunk_Counter = 0;

    for (int i = frame_Counter * 256; i < frame_Counter * 256 + 256; i++){
        physical_Memory[i] = chunk_Store[chunk_Counter];
        chunk_Counter++;
    }

    for (int i = 0; i < 256; i++){
        printf("%d\n", chunk_Store[i]);
    }

    frame_Counter++;
}

int main(){
    address_file = fopen("addresses.txt", "r");

    insert_Chunk(117);
    signed char value = physical_Memory[(256*0) + 246];
    printf("Value: %d", value);

    while (fgets(address, 7, address_file) != NULL){
        logical_address = atoi(address); // convert char array to int
        // printf("logical address: %d, PageNumber: %d, Offset: %d\n", logical_address,getPage(logical_address), getOffSet(logical_address));
    }
    
}
