#define FRAME_SIZE 256 // frame size is 256 frames.
#define PAGE_SIZE 256 // page size of 2^8 bytes.
#define MEM_SIZE 65336 // physical memory is 65336 bytes
#define PAGE_ENTRIES 256 // 2^8 entries in the page table.
#define CHUNK 256 // amount of bytes we need to load into a frame

int physical_Memory[MEM_SIZE];
int frame_Counter = 0;
signed char chunk_Store[CHUNK];