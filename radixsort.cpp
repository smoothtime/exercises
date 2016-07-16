/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: James Wells $
   $Notice: (C) Copyright 2015 by Extreme, Inc. All Rights Reserved. $
   ======================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h> // memset

void
radixSort(int *a, unsigned int numElems, int *o)
{
    size_t elemSize = sizeof(int);
    memset(o, 0, numElems * elemSize);
    unsigned int *counter = (unsigned int *) malloc(sizeof(unsigned int) * 256 * elemSize);
    for(unsigned int b = 0; b < elemSize; ++b)
    {
        unsigned int *currentCount = counter + (b * 256);
        unsigned int i;
        for(i = 0; i < numElems; ++i)
        {
            unsigned char elem = (a[i] >> (8 * b)) & 0xFF;
            currentCount[elem]++;
        }
    }

    // This breaks?
    unsigned int offsetTable[256 * elemSize];
    //unsigned int *offsetTable = (unsigned int *) malloc(256 * elemSize);
    memset(offsetTable, 0, 256 * elemSize);
    offsetTable[0] = 0;
    for(unsigned int byteCount = 0; byteCount < elemSize; ++byteCount)
    {
        for(unsigned int i = 1; i < 256; ++i)
        {
            //offsetTable[(byteCount * 256) + i] = offsetTable[(byteCount * 256) + i - 1] + counter[(byteCount * 256) + i - 1];
            unsigned int counterCount = counter[(byteCount * 256) + i - 1];
            unsigned int toSet = offsetTable[(byteCount * 256) + i - 1] + counterCount;
            offsetTable[(byteCount * 256) + i] = toSet;
                
        }
    }

    for(unsigned int b = 0; b < elemSize; ++b)
    {
        for(unsigned int i = 0; i < numElems; ++i)
        {
            unsigned char elem = (a[i] >> (8 * b)) & 0xFF;
            unsigned int indexFromOffset = offsetTable[(256 * b) + elem]++;
            o[indexFromOffset] |= (elem << (8 * b));
        }
    }
}

int
main(int argc, char **argv)
{
    int count = 997;
    int *a = (int *) malloc(sizeof(int) * count);
    int *b = (int *) malloc(sizeof(int) * count);
    
    srand(time((time_t *)0));
    for(int i = 0; i < count; ++i)
    {
        a[i] = rand();
        b[i] = rand();
    }

    radixSort(a, count, b);
    
    int i = 0;
    for(i = 0; i < count - 1; ++i)
    {
        assert(b[i] <= b[i + 1]);
        fprintf(stdout, "%d, ", b[i]);
    }
    fprintf(stdout, "%d \n", b[i]);    
    
    fprintf(stdout, "We did it!\n");
    return 1;
}
