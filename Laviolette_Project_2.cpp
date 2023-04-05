/*
* Name : Christian Laviolette
* Class:CS302
* Project 2: Memory Management
* Date: 3/29/23
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>
using namespace std;

const int TLB_SIZE = 16;

struct TLBEntry {
    int pageNumber;
    int frameNumber;
};

int main()
{
    int* pageTable = new int[256];
    int* memory = new int[256 * 256];

    for (int i = 0; i < 256; i++)
    {
        pageTable[i] = -1;
    }

    vector<TLBEntry> TLB(TLB_SIZE);
    int nextFrame = 0;
    int pageFaults = 0;
    int pageHits = 0;
    int TLBHits = 0;
    int TLBMisses = 0;
    int pagesTranslated = 0;


    // open addresses.txt
    ifstream inputFile("addresses.txt");
    int virtualAddress;

    while (inputFile >> virtualAddress)
    {
        signed char buffer[256];

        int pageNumber = (virtualAddress >> 8) & 0xFF;
        int offset = virtualAddress & 0xFF;
        pagesTranslated++;

        // Check TLB
        bool TLBHit = false;
        int frameNumber = -1;
        for (int i = 0; i < TLB_SIZE; i++) {
            if (TLB[i].pageNumber == pageNumber) {
                frameNumber = TLB[i].frameNumber;
                TLBHit = true;
                break;
            }
        }

        if (!TLBHit) {
            // Check page table
            if (pageTable[pageNumber] == -1) { // Page fault
                ifstream input("BACKING_STORE.bin", ios::binary | ios::in);
                input.seekg(pageNumber * 256, std::ios::beg);
                input.read((char*)buffer, 256);
                input.seekg(0, std::ios::beg);
                input.close();

                for (int i = 0; i < 256; i++)
                {
                    memory[nextFrame * 256 + i] = static_cast<int>(static_cast<signed char>(buffer[i]));
                }
                pageTable[pageNumber] = nextFrame;
                nextFrame++;
                pageFaults++;
            }
            frameNumber = pageTable[pageNumber];
            // Update TLB
            TLB[TLBMisses % TLB_SIZE].pageNumber = pageNumber;
            TLB[TLBMisses % TLB_SIZE].frameNumber = frameNumber;
            TLBMisses++;
        }
        else {
            TLBHits++;
        }

        int physicalAddress = frameNumber * 256 + offset;

        int data = memory[physicalAddress];
        pageHits++;

        cout << "Virtual address: " << virtualAddress << " Physical address: " << physicalAddress << " Value: " << data << endl;
    }

    cout << "Number of Translated Addresses = " << pagesTranslated << endl;
    cout << "Page Faults= " << pageFaults << endl;
    cout << "Page Fault Rate= " << (double)pageFaults / pagesTranslated << endl;
    cout << "TLB Hits= " << TLBHits << endl;
    cout << "TLB Hit Rate= " << (double)TLBHits / pagesTranslated << endl;

    return 0;
}