#include "LRC.h"

static unsigned char LRC(const unsigned char *auchMsg, const unsigned short usDataLen)
{
    unsigned char uchLRC = 0 ; /* LRC char initialized */
    unsigned short count = usDataLen;
    while (count--){ /* pass through message buffer */
        uchLRC += *auchMsg++ ; /* add buffer byte without carry */
    }
    return ((unsigned char)(~((char)uchLRC))) + 1; /* return twos complement */
}
