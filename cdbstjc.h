#ifndef CDBSTJC_H
#define CDBSTJC_H

#include "cjcbase.h"
class CDBSTJC : public CJCBase
{
    Q_OBJECT
public:
    explicit CDBSTJC(CJCBase *parent = nullptr);
    bool setData();
signals:

public slots:
};

#endif // CDBSTJC_H
