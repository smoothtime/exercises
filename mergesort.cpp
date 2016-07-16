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

inline int
min(unsigned int a, unsigned int b)
{
    return a < b ? a : b;
}

inline void
mergeTwo(int *a, int *b, int *dest, unsigned int countA, unsigned int countB)
{
    int *aEnd = a + countA;
    int *bEnd = b + countB;
    while(a < aEnd && b < bEnd)
    {
        if(*a < *b)
        {
            *dest++ = *a++;
        }
        else
        {
            *dest++ = *b++;
        }
    }
    while(a < aEnd)
    {
        *dest++ = *a++;
    }
    while(b < bEnd)
    {
        *dest++ = *b++;
    }
}

void
merge(int *a, unsigned int s, unsigned int m, unsigned int e)
{
    unsigned int i;
    unsigned int sizeFirst = m - s + 1;
    unsigned int sizeSecond = e - m;

    int firstSeparate[sizeFirst];
    int secondSeparate[sizeSecond];
    for(i = 0; i < sizeFirst; ++i)
    {
        firstSeparate[i] = *(a + s + i);
    }
    for(i = 0; i < sizeSecond; ++i)
    {
        secondSeparate[i] = *(a + m + 1 + i);
    }

    mergeTwo(firstSeparate, secondSeparate, a + s, m - s + 1, e - m);
}

void
mergeSortRecursive(int *a, unsigned int s, unsigned int e)
{
    
    int m = s + (e-s) / 2;
    if(e > s)
    {
        mergeSortRecursive(a, s, m);
        mergeSortRecursive(a, m + 1, e);
        merge(a, s, m, e);
    }
    
}

void mergeSortIterative(int *a, unsigned int e)
{
    unsigned int itrSize;
    unsigned int itrLeft;
    for(itrSize = 1; itrSize < e; itrSize *= 2)
    {
        for(itrLeft = 0; itrLeft < e-1; itrLeft += 2*itrSize)
        {
            unsigned int mid = min(itrLeft + itrSize - 1, e-1);
            unsigned int end = min(itrLeft + 2*itrSize - 1, e-1);
            merge(a, itrLeft, mid, end);
        }
    }
}

int
main(int argc, char **argv)
{
    int count = 997;
    int a[count];
    int b[count];
    srand(time((time_t *)0));
    for(int i = 0; i < count; ++i)
    {
        a[i] = rand();
        b[i] = rand();
    }

    mergeSortRecursive(a, 0, count - 1);
    mergeSortIterative(b, count);

    int i = 0;
    for(i = 0; i < count - 1; ++i)
    {
        assert(a[i] < a[i + 1]);
        fprintf(stdout, "%d, ", a[i]);
    }
    fprintf(stdout, "%d \n", a[i]);    
    for(i = 0; i < count - 1; ++i)
    {
        assert(b[i] < b[i + 1]);
        fprintf(stdout, "%d, ", b[i]);
    }
    fprintf(stdout, "%d \n", b[i]);

    fprintf(stdout, "We did it!\n");
    return 1;
}
