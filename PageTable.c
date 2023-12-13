#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TLB.c"
#include "main.c"
#include "PhysicalMem.c"

struct page_Table_Cell{
    int frame;
    int vi_Bit;
};

struct page_Table_Cell page_Table[256];

int page_Fault_Counter = 0;

void check_Page_Table(int pageNumber){
    if (page_Table[page_Number].vi_Bit == 1){
        value = physical_Memory[(page_Table[pageNumber].frame * 256) + offset];
        physical_address = (page_Table[pageNumber].frame * 256) + offset;
        updateTLB(pageNumber);
    }else{
        page_Fault_Counter++;
        insert_Chunk(pageNumber);
        page_Table[pageNumber].frame = frame_Counter;
        page_Table[pageNumber].vi_Bit = 1;
        checktlb(pageNumber);

    }
}
void updateTLB(pageNumber){
    if(tlbCounter<15){
        TLB[tlbCounter].frame_number = page_Table[pageNumber].frame;
        TLB[tlbCounter].page_number = pageNumber;
        tlbCounter++;
    }else{
        for(int i = 1; i<TLB_SIZE-1;i++){
            TLB[i-1].page_number = TLB[i].page_number;
            TLB[i-1].frame_number = TLB[i].frame_number;
        }
        TLB[15].frame_number = page_Table[pageNumber].frame;
        TLB[15].page_number = pageNumber;
}
}