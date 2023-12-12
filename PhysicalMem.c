#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 256 // frame size is 256 frames.
#define PAGE_SIZE 256 // page size of 2^8 bytes.
#define TLB_SIZE 16 // 16 entries in the TLB
#define MEM_SIZE 65336 // physical memory is 65336 bytes
#define PAGE_ENTRIES 256 // 2^8 entries in the page table.
#define CHUNK 256 // amount of bytes we need to load into a frame

int physical_Memory[MEM_SIZE];
int frame_Counter = 0;
signed char chunk_Store[CHUNK];

void insert_Chunk(int page_Number){
    FILE *backing_Store = fopen("BACKING_STORE.bin", "rb");

    if (fseek(backing_Store, page_Number * 256, SEEK_SET) != 0){
        fprintf(stderr, "Error\n");
        return;
    }

    if (fread(chunk_Store, sizeof(signed char), 256, backing_Store) == 0){
        fprintf(stderr, "Error\n");
        return;
    }

    int chunk_Counter = 0;

    for (int i = frame_Counter * 256; i < frame_Counter * 256 + 256; i++){
        physical_Memory[i] = chunk_Store[chunk_Counter];
        chunk_Counter++;
    }

    /* for (int i = 0; i < 256; i++){
        printf("%d\n", chunk_Store[i]);
    } */

    frame_Counter++;
}

