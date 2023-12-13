#include <stdio.h>
#include <stdlib.h>
#include "pageTable.h"
#include "TLB.h"
#include "main.h"
#include "PhysicalMem.h"
#include "functions.h"

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

