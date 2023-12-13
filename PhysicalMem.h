#define FRAME_SIZE 256 // frame size is 256 frames.
#define PAGE_SIZE 256 // page size of 2^8 bytes.
#define MEM_SIZE 65336 // physical memory is 65336 bytes
#define PAGE_ENTRIES 256 // 2^8 entries in the page table.
#define CHUNK 256 // amount of bytes we need to load into a frame

int physical_Memory[MEM_SIZE];
int frame_Counter = 0;
signed char chunk_Store[CHUNK];
int page_Number;
int offset;
signed char value;
int checkpg = 0;
int physical_address;
char address[7]; //Store address
int address_Counter = 0;
float tlbHitRate = 0.0000;
float pageFaultRate = 0.0000;

void insert_Chunk(int page_Number);
void getPage(int logical_address);
void getOffset(int logical_address);