#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 256 // Size of a page/frame
#define NUM_PAGES 16  // Number of pages in the virtual address space
#define NUM_FRAMES 8  // Number of frames in the physical memory

// Page table entry structure
typedef struct {
    int frameNumber; // Frame number in physical memory
    int valid;       // Valid bit to check if page is in memory
} PageTableEntry;

// Function to initialize the page table
void initializePageTable(PageTableEntry *pageTable) {
    for (int i = 0; i < NUM_PAGES; i++) {
        pageTable[i].frameNumber = -1; // Initialize with invalid frame number
        pageTable[i].valid = 0;        // Mark page as not valid
    }
}

// Function to simulate address translation
int translateAddress(PageTableEntry *pageTable, int virtualAddress) {
    int pageNumber = (virtualAddress / PAGE_SIZE);
    int offset = (virtualAddress % PAGE_SIZE);

    if (pageTable[pageNumber].valid) {
        int frameNumber = pageTable[pageNumber].frameNumber;
        int physicalAddress = frameNumber * PAGE_SIZE + offset;
        return physicalAddress;
    } else {
        printf("Page fault! Page %d is not in memory.\n", pageNumber);
        // Handle page fault (for simplicity, we won't implement it here)
        return -1;
    }
}

int main() {
    // Initialize page table
    PageTableEntry pageTable[NUM_PAGES];
    initializePageTable(pageTable);

    // Example of loading pages into frames (for simplicity)
    pageTable[0].frameNumber = 0; pageTable[0].valid = 1;
    pageTable[1].frameNumber = 1; pageTable[1].valid = 1;
    pageTable[2].frameNumber = 2; pageTable[2].valid = 1;
    pageTable[3].frameNumber = 3; pageTable[3].valid = 1;

    // Translate some virtual addresses
    int virtualAddresses[] = {0, 256, 512, 768, 1024}; // Some virtual addresses to translate
    for (int i = 0; i < sizeof(virtualAddresses) / sizeof(int); i++) {
        int physicalAddress = translateAddress(pageTable, virtualAddresses[i]);
        if (physicalAddress != -1) {
            printf("Virtual Address %d -> Physical Address %d\n", virtualAddresses[i], physicalAddress);
        }
    }

    return 0;
}
