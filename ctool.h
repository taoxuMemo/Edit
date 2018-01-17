#ifndef CTOOL_H
#define CTOOL_H


class CTool
{
public:
    CTool();

    static char chartoint(char d);
    static char chartohex(char d);
    static unsigned int CRC16_Checkout ( unsigned char *puchMsg, unsigned int usDataLen );

};

#endif // CTOOL_H
