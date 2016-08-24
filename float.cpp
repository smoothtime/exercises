/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: James Wells $
   $Notice: (C) Copyright 2015 by Extreme, Inc. All Rights Reserved. $
   ======================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct fourChars
{
    unsigned char x, y, z, w;
};

union float_inspect
{
    float f;
    unsigned int i;
    fourChars c;
};

void printBits(unsigned char c)
{
    unsigned int numBits = 8 * sizeof(unsigned char);
    for(int ebit = 0; ebit < numBits; ++ebit)
    {
        fprintf(stdout, "%d", (c & (0x1 << (numBits - ebit - 1))) ? 1 : 0);
    }
    fprintf(stdout, " ");
}

void printBits(unsigned int i)
{
    unsigned int numBits = 8 * sizeof(unsigned int);
    for(int bit = 0; bit < numBits; ++bit)
    {
        fprintf(stdout, "%s", bit % 8 == 0 ? " " : "");
        fprintf(stdout, "%d", (i & (0x1 << (numBits - bit - 1))) ? 1 : 0);
    }
    fprintf(stdout, "\n");
}

float calcFrac(unsigned char c, unsigned int depth)
{
    float sum = 0.0f;
    for(int bit = 0; bit < 8; ++bit)
    {
        if(c & (0x1 << (8 - 1 - bit)))
        {
            int power = -1 * (bit + (depth * 8) + 1);
            float add = pow(2.0f, power);
            sum += add;
            printf("\nbit: %d, power: %d, add: %f, sum: %f", bit, power, add, sum);
        }
    }
    printf("\n");
    return sum;
}

int main(int argc, char **argv)
{
    printBits(0x80000000);
    
    float input, output; 
    fscanf(stdin, "%f", &input);

    float_inspect inputFI;
    inputFI.f = input;
    
    printBits(inputFI.i);
    printf("Sign is %s\n", (inputFI.i & 0x80000000) ? "negative" : "positive");

    // shift off the sign
    inputFI.i = inputFI.i << 1;
    printBits(inputFI.i);
    unsigned char biasedExponent = (unsigned char)(inputFI.i >> 24);
    printf("Biased exponent %d\n", biasedExponent);
    printf("\n");
    bool wantToPrintAddresses = true;
    if(wantToPrintAddresses)
    {
        printBits(inputFI.c.x);
        printf("%lu\n",(unsigned long) &inputFI.c.x);
        printBits(inputFI.c.y);
        printf("%lu\n",(unsigned long) &inputFI.c.y);
        printBits(inputFI.c.z);
        printf("%lu\n",(unsigned long) &inputFI.c.z);
        printBits(inputFI.c.w);
        printf("%lu\n",(unsigned long) &inputFI.c.w);
        
    }

    float significand = 1.0f + calcFrac(inputFI.c.z, 0) + calcFrac(inputFI.c.y, 1) + calcFrac(inputFI.c.x, 2);
    printf("significand: %f\n", significand);
    printf("%f\n", significand * pow(2.0f, (char)biasedExponent - 127));
    
}
