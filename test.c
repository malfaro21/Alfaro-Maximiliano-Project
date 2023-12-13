#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FRAME_SIZE 256 // frame size is 256 frames.
#define PAGE_SIZE 256 // page size of 2^8 bytes.
#define MEM_SIZE 65336 // physical memory is 65336 bytes
#define PAGE_ENTRIES 256 // 2^8 entries in the page table.
#define CHUNK 256 // amount of bytes we need to load into a frame
#define TLB_SIZE 16 // 16 entries in the TLB

FILE *address_file;

int logical_address;
int physical_address;
int page_Number;
int offset;
int physical_Memory[MEM_SIZE];
int frame_Counter = 0;
int page_Fault_Counter = 0;
int tlbCounter = 0;
int tlbhitcount = 1;
int tlbmisscount = 0;
char address[7]; //Store address
signed char chunk_Store[CHUNK];
signed char value;

struct page_Table_Cell{
    int frame;
    int vi_Bit;
};

struct tlb_cell{
    int page_number;
    int frame_number;
};

struct page_Table_Cell page_Table[256];
struct tlb_cell TLB[TLB_SIZE];

void checktlb(int page);
void tlbhit(int frame_number);
void check_Page_Table(int pageNumber);
void updateTLB(int pageNumber);
void insert_Chunk(int page_Number);
void getPage(int logical_address);
void getOffset(int logical_address);

int checkpg = 0;

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
void updateTLB(int pageNumber){
    if(tlbCounter<16){
        TLB[tlbCounter].frame_number = page_Table[pageNumber].frame;
        TLB[tlbCounter].page_number = pageNumber;
    }else{
        for(int i = 1; i<TLB_SIZE;i++){
            TLB[i-1].page_number = TLB[i].page_number;
            TLB[i-1].frame_number = TLB[i].frame_number;
        }
        TLB[TLB_SIZE-1].frame_number = page_Table[pageNumber].frame;
        TLB[TLB_SIZE-1].page_number = pageNumber;
    }
    tlbCounter++;
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

    for (int i = 0; i < 16; i++){
        printf("Frame: %d Page: %d\n", TLB[i].frame_number, TLB[i].page_number);
    }

    printf("hits: %d\n", tlbhitcount);
    printf("page faults: %d", page_Fault_Counter);
    
}
