#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page_Table_Cell{
    int page;
    int vi_Bit;
};

struct page_Table_Cell page_Table[256];

int page_Fault_Counter = 0;
