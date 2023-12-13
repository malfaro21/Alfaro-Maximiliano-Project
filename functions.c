#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TLB.h"
#include "pageTable.h"
#include "PhysicalMem.h"


void getPage(int logical_address){
    page_Number = (logical_address >> 8);
}

void getOffSet(int logical_address){
    offset = (logical_address & 0x00FF);
}

void checktlb(int page){
    for(int i = 0; i < TLB_SIZE; i++){
        if(page == TLB[i].page_number){ //check if page is there
            tlbhitcount++; //add to hit count
            tlbhit(TLB[i].frame_number);
            checkpg = 0;
            break;
        }
        else {
            checkpg = 1;
        }
    }
    if (checkpg){
        check_Page_Table(page);
        tlbmisscount++; //add to miss count
    }
}

void tlbhit(int frame_number){
    value = physical_Memory[(frame_number * 256) + offset];
    physical_address = (frame_number * 256) + offset;
}

void updateTLB(int pageNumber){
    if(tlbCounter<16){
        TLB[tlbCounter].frame_number = page_Table[pageNumber].frame;
        TLB[tlbCounter].page_number = pageNumber;
    }else{
        for(int i = 1; i<TLB_SIZE;i++){
            TLB[i-1].page_number = TLB[i].page_number;
            TLB[i-1].frame_number = TLB[i].frame_number;
        }
        TLB[15].frame_number = page_Table[pageNumber].frame;
        TLB[15].page_number = pageNumber;
    }
    tlbCounter++;
}

void check_Page_Table(int pageNumber){
    if (page_Table[page_Number].vi_Bit == 1){
        value = physical_Memory[(page_Table[pageNumber].frame * 256) + offset];
        physical_address = (page_Table[pageNumber].frame * 256) + offset;
        updateTLB(pageNumber);
    }else{
        page_Fault_Counter++;
        insert_Chunk(pageNumber);
        page_Table[pageNumber].frame = frame_Counter - 1;
        page_Table[pageNumber].vi_Bit = 1;
        checktlb(pageNumber);
    }
}

void insert_Chunk(int page_Number){
    FILE *backing_Store = fopen("BACKING_STORE.bin", "rb");

    fseek(backing_Store, page_Number * 256, SEEK_SET);
    fread(chunk_Store, sizeof(signed char), 256, backing_Store);

    int chunk_Counter = 0;

    for (int i = frame_Counter * 256; i < frame_Counter * 256 + 256; i++){
        physical_Memory[i] = chunk_Store[chunk_Counter];
        chunk_Counter++;
    }

    frame_Counter++;
}