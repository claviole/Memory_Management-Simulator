/*
This program is a  project to be completed for CS309 to simulate Memory Management within an operating system.

guidlines for the project:
Read a file containg several 32 bit integer numbers that represent logical addresses
However, only concerned with 16-bit address so we must mask the rightmost 16bits of each logical address
The 16-bit address is then divided into 8-bit page number and 8-bit offset

-2^8 entries in the page table
-Page size of 2^8 bytes
-16 entries in the TLB
-frame size of 2^8 bytes
-256 frames
-Physical memory of 65,536 bytes(256 frames x 256 byte frame size)
-Do not need to supportk wwriting to the logical address space


-Program need only be concerned with reading logical addresses and translating them to their corresponding physical addresses
This project is due on 4/10/23
