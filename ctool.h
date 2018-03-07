#ifndef CTOOL_H
#define CTOOL_H

#include "qstring.h"

class CTool
{
public:
    CTool();

    static int chartoint(char d);
    static int chartohex(char d);
    static int chartohex8(char h,char l);
    static int strtoint(char *p ,int len);
    static unsigned int CRC16_Checkout ( unsigned char *puchMsg, unsigned int usDataLen );
    static QString douTostr(double d,char *s);
};

#endif // CTOOL_H
