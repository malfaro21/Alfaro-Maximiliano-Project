#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tlb_cell{
    int page_number;
    int frame_number;
};

struct tlb_cell TLB[16];
int tlbCounter = 0;

