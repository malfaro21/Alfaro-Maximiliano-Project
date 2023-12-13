struct page_Table_Cell{
    int frame;
    int vi_Bit;
};

struct page_Table_Cell page_Table[256];

int page_Fault_Counter = 0;