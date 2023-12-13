#define FRAME_SIZE 256 // frame size is 256 frames.
#define PAGE_SIZE 256 // page size of 2^8 bytes.
#define MEM_SIZE 65336 // physical memory is 65336 bytes
#define PAGE_ENTRIES 256 // 2^8 entries in the page table.
#define CHUNK 256 // amount of bytes we need to load into a frame
#define TLB_SIZE 16 // 16 entries in the TLB

int logical_address;
int physical_address;
int page_Number;
int offset;
int physical_Memory[MEM_SIZE];
int frame_Counter = 0;
int page_Fault_Counter = 0;
int tlbCounter = 0;
int tlbhitcount = 0;
int tlbmisscount = 0;
char address[7]; //Store address
signed char chunk_Store[CHUNK];
signed char value;
int checkpg = 0;

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