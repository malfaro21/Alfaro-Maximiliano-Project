#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TLB.h"
#include "pageTable.h"
#include "PhysicalMem.h"

// translates the logical address to a page number
void getPage(int logical_address){
    page_Number = (logical_address >> 8); 
}

// translates the logical address to the offset
void getOffSet(int logical_address){
    offset = (logical_address & 0x00FF);
}

// checks the TLB to see if the page is in there
void checktlb(int page){
    for(int i = 0; i < TLB_SIZE; i++){
        if(page == TLB[i].page_number){ //page is there
            tlbhitcount++; //add to hit count
            tlbhit(TLB[i].frame_number);//calls tlbhit()
            checkpg = 0; //check page there to make sure loop stops
            break;
        }
        else {
            checkpg = 1; // page is not in tlb, run lines below
        }
    }
    if (checkpg){
        checkpg = 0;
        check_Page_Table(page); // tlb miss so it then checks the page table
        tlbmisscount++; //add to miss count
        
    }
}

//if there is a tlb hit it updates the value and physical address so it can be printed
void tlbhit(int frame_number){
    value = physical_Memory[(frame_number * 256) + offset];
    physical_address = (frame_number * 256) + offset;
}
//updates the TLB
void updateTLB(int pageNumber){
    if(tlbCounter<16){ // if the TLB is not full it adds frame and page to next cell in TLB
        TLB[tlbCounter].frame_number = page_Table[pageNumber].frame;
        TLB[tlbCounter].page_number = pageNumber;
    }else{ // if TLB is full then it moves the first cell out and shifts all other cells up by one
        for(int i = 1; i<TLB_SIZE;i++){ 
            TLB[i-1].page_number = TLB[i].page_number;
            TLB[i-1].frame_number = TLB[i].frame_number;
        }
        TLB[15].frame_number = page_Table[pageNumber].frame; //These lines add the new cell to the end of the TLB
        TLB[15].page_number = pageNumber;
    }
    tlbCounter++; // updates the TLB counter
}

//Checks the page table to see if that page is valid and in physical memory
void check_Page_Table(int pageNumber){
    if (page_Table[page_Number].vi_Bit == 1){ // if bit is valid add page and frame to TLB
        value = physical_Memory[(page_Table[pageNumber].frame * 256) + offset];
        physical_address = (page_Table[pageNumber].frame * 256) + offset;
        updateTLB(pageNumber);
    }else{ // if bit is invald it loads chunk from backing store into physical memory
        page_Fault_Counter++; // adds to the page fault counter
        insert_Chunk(pageNumber);
        page_Table[pageNumber].frame = frame_Counter - 1;
        page_Table[pageNumber].vi_Bit = 1;
        checktlb(pageNumber); // restarts the whole loop now that the page has been loaded into physical memory
    }
}

// reads a chunk from the backings_store and stores it in physical memory
void insert_Chunk(int page_Number){
    FILE *backing_Store = fopen("BACKING_STORE.bin", "rb");

    fseek(backing_Store, page_Number * 256, SEEK_SET);
    fread(chunk_Store, sizeof(signed char), 256, backing_Store);

    int chunk_Counter = 0;

    for (int i = frame_Counter * 256; i < frame_Counter * 256 + 256; i++){
        physical_Memory[i] = chunk_Store[chunk_Counter];
        chunk_Counter++;
    }

    frame_Counter++; // update the frame counter so we know next avaliable frame and
}                    // so that we can store the frame into the page table