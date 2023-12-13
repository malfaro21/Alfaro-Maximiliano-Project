#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

FILE *address_file;

int main(){
    address_file = fopen("addresses.txt", "r");

    while (fgets(address, 7, address_file) != NULL){
        logical_address = atoi(address); // convert char array to int
        getPage(logical_address);
        getOffSet(logical_address);
        checktlb(page_Number);
        // printf("(%d, %d), %d, %d, %d\n", page_Number, offset, logical_address, physical_address, value);
    }
    
    for (int i = 0; i < 16; i++){
        printf("Frame: %d Page: %d\n", TLB[i].frame_number, TLB[i].page_number);
    }
}