#include "CRC.h"

unsigned short CRC16(const unsigned char *puchMsg, const unsigned short usDataLen)
//unsigned char *puchMsg ; /* message to calculate CRC upon */
//unsigned short usDataLen ; /* quantity of bytes in message */
{
    unsigned char uchCRCHi = 0xFF ; /* high byte of CRC initialized */
    unsigned char uchCRCLo = 0xFF ; /* low byte of CRC initialized */
    unsigned uIndex ; /* will index into CRC lookup table */
    unsigned short count = usDataLen;
    while (count--) /* pass through message buffer */
    {
        uIndex = uchCRCHi ^ *puchMsg++ ; /* calculate the CRC */
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
        uchCRCLo = auchCRCLo[uIndex] ;
    }
    return (uchCRCHi << 8 | uchCRCLo) ;
}
