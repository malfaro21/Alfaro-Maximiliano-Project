#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page_Table_Cell{
    int frame;
    int vi_Bit;
};

struct page_Table_Cell page_Table[256];

int page_Fault_Counter = 0;

void check_Page_Table(int page_Number){
    for (int i = 0; i < 256; i++){
        if (page_Table[i].vi_Bit == 1){
            
        }
    }
}
