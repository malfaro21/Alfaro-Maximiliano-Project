#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

FILE *address_file;

int main(int argc, char *argv[]){
    address_file = fopen(argv[1], "r");

    while (fgets(address, 7, address_file) != NULL){
        address_Counter++;
        logical_address = atoi(address); // convert char array to int
        getPage(logical_address);
        getOffSet(logical_address);
        checktlb(page_Number);
        printf("%d, %d, %d\n", logical_address, physical_address, value);
    }

    tlbHitRate = (float) tlbhitcount / 1000;
    pageFaultRate = (float) page_Fault_Counter / 1000;

    printf("TLB Hits: %d (%.3f%%)\n", tlbhitcount, tlbHitRate);
    printf("Page Faults: %d (%.3f%%)\n", page_Fault_Counter, pageFaultRate); 
}
