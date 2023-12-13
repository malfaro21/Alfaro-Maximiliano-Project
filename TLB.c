#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.c"
#include "PhysicalMem.c"

#define TLB_SIZE 16 // 16 entries in the TLB

struct tlb_cell{
    int page_number;
    int frame_number;
};

struct tlb_cell TLB[TLB_SIZE];
int tlbCounter = 0;
int tlbhitcount = 0;
int tlbmisscount = 0;

void checktlb(int page){
    for(int i = 0; i < TLB_SIZE; i++){
        if(TLB[i].page_number == page){ //check if page is there
            tlbhitcount++; //add to hit count
            tlbhit(TLB[i].frame_number);
        }
        else{
            tlbmisscount++; //add to miss count
            //TODO checkpage_table
        }
    }
}

void tlbhit(int frame_number){
    value = physical_Memory[(frame_number * 256) + offset];
    physical_address = (frame_number * 256) + offset;
}