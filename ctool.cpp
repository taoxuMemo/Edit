#include "ctool.h"

CTool::CTool()
{

}

int CTool::chartoint(char d)
{
    if(d>'9' || d<'0')
        return -1;
    int a=d-0x30;
    return a;
}

int CTool::chartohex(char d)
{
    if(d<='9' && d>='0')
        return (d-0x30);
    else if(d<='F' && d>='A')
        return 10+(d-0x41);
    else
        return -1;
}

unsigned int CTool::CRC16_Checkout ( unsigned char *puchMsg, unsigned int usDataLen )
{
    unsigned int i,j,crc_reg,check;
    crc_reg = 0xFFFF;
    for(i=0;i<usDataLen;i++)
    {
        crc_reg = (crc_reg>>8) ^ puchMsg[i];
        for(j=0;j<8;j++)
        {
            check = crc_reg & 0x0001;
            crc_reg >>= 1;
            if(check==0x0001)
            {
                crc_reg ^= 0xA001;
            }
        }
    }
    return crc_reg;
}
