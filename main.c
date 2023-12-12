#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int physical_Memory[256 * 256];
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

int main(){
    address_file = fopen("addresses.txt", "r");

    while (fgets(address, 7, address_file) != NULL){
        logical_address = atoi(address); // convert char array to int
        printf("logical address: %d, PageNumber: %d, Offset: %d\n", logical_address,getPage(logical_address), getOffSet(logical_address));
    }
    
}
