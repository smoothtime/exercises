/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: James Wells $
   $Notice: (C) Copyright 2015 by Extreme, Inc. All Rights Reserved. $
   ======================================================================== */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned int l; 
    unsigned int r;
    fscanf(stdin, "%d", &l);
    fscanf(stdin, "%d", &r);
    unsigned int mOverflow = (r + l) / 2;
    unsigned int mOkay = l + (r - l) / 2;
    fprintf(stdout, "mOverflow: %u\nmOkay: %u\n", mOverflow, mOkay);
}
