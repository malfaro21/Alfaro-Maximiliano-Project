#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pageTable.h"
#include "TLB.h"
#include "main.h"
#include "PhysicalMem.h"
#include "functions.h"
#include "TLB.c"

FILE *address_file;

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
        checktlb(page_Number);
        printf("(%d, %d), %d, %d, %d\n", page_Number, offset, logical_address, physical_address, value);
    }
    
}
