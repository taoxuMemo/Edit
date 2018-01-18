#ifndef CTOOL_H
#define CTOOL_H


class CTool
{
public:
    CTool();

    static int chartoint(char d);
    static int chartohex(char d);
    static int chartohex8(char h,char l);
    static unsigned int CRC16_Checkout ( unsigned char *puchMsg, unsigned int usDataLen );

};

#endif // CTOOL_H
