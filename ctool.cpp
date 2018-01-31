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
int CTool::chartohex8(char h,char l)
{
    int high=0,low=0;
    high=CTool::chartohex(h);
    if(high==-1)
        return -1;
    low=CTool::chartohex(l);
    if(low==-1)
        return -1;
    return (high<<=4)|=low;

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
QString CTool::douTostr(double d, char *s)
{
    QString str=QString::number(d);
    int xs=0;
    s++;
    char ss=*s;
    int zs=ss-'0';//整数个数

    s++;
    if(*s=='.')
    {
        s++;
        xs=(*s)-'0';//小数个数
    }
    int jq=0;
    int wz=str.indexOf(".");
    if(wz>zs)
        jq=wz-zs;
    QString strRe=str.mid(jq,xs+zs+1);
    return strRe;
}
