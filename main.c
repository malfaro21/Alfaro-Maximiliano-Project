#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int physical_Memory[256 * 256];
int logical_address;

FILE *address_file;
char address[7]; //Store address

int main(){
    address_file = fopen("addresses.txt", "r");

    while (fgets(address, 7, address_file) != NULL){
        logical_address = atoi(address); // convert char array to int
        printf("logical address: %d\n", logical_address);
    }
    
}
