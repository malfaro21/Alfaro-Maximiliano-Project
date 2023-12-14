#define TLB_SIZE 16 // 16 entries in the TLB

struct tlb_cell{
    int page_number;
    int frame_number;
};

struct tlb_cell TLB[TLB_SIZE];
int tlbCounter = 0;
int tlbmisscount = 0;
int tlbhitcount = 0;

void checktlb(int page);
void tlbhit(int frame_number);
void updateTLB(int pageNumber);
