#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pageTable.h"
#include "TLB.h"
#include "main.h"
#include "PhysicalMem.h"
#include "functions.h"

void checktlb(int page){
    for(int i = 0; i < TLB_SIZE; i++){
        if(TLB[i].page_number == page){ //check if page is there
            tlbhitcount++; //add to hit count
            tlbhit(TLB[i].frame_number);
        }
        else{
            tlbmisscount++; //add to miss count
            check_Page_Table(page);
        }
    }
}

void tlbhit(int frame_number){
    value = physical_Memory[(frame_number * 256) + offset];
    physical_address = (frame_number * 256) + offset;
}