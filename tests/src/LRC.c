static unsigned char LRC(const unsigned char *auchMsg, size_t usDataLen)
{
    unsigned char uchLRC = 0 ; /* LRC char initialized */
    size_t count = usDataLen;
    while (count--){ /* pass through message buffer */
        uchLRC += *auchMsg++ ; /* add buffer byte without carry */
    }
    return ((unsigned char)(~((char)uchLRC))) + 1; /* return twos complement */
}
