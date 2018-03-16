#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T13:47:38
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataConEq
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    formmain.cpp \
    formreal.cpp \
    formabout.cpp \
    formhistory.cpp \
    formsetting.cpp \
    formanalysis.cpp \
    formstate.cpp \
    formonline.cpp \
    formquery.cpp \
    formsetting_cg.cpp \
    formsetting_ck.cpp \
    formsetting_adc.cpp \
    formsetting_sb.cpp \
    formsetting_yzsb.cpp \
    formsetting_wlsz.cpp \
    formsetting_sjjy.cpp \
    cdbcoustom.cpp \
    coperationconfig.cpp \
    qdatatype.cpp \
    cmythread.cpp \
    cmysocket.cpp \
    cmysocketthread.cpp \
    cnetconthread.cpp \
    cprotocol.cpp \
    ctool.cpp \
    ccompro.cpp \
    cjcbase.cpp \
    cdbstjc.cpp \
    cserialthread.cpp \
    cmysqlite.cpp \
    ctesttcpthd.cpp \
    cdqhjwry.cpp \
    ccolsvr.cpp \
    cqjcyz.cpp

HEADERS += \
        mainwindow.h \
    formmain.h \
    formreal.h \
    formabout.h \
    formhistory.h \
    formsetting.h \
    formanalysis.h \
    formstate.h \
    formonline.h \
    formquery.h \
    formsetting_cg.h \
    formsetting_ck.h \
    formsetting_adc.h \
    formsetting_sb.h \
    formsetting_yzsb.h \
    formsetting_wlsz.h \
    formsetting_sjjy.h \
    cdbcoustom.h \
    coperationconfig.h \
    qdatatype.h \
    cmythread.h \
    cmysocket.h \
    cmysocketthread.h \
    cnetconthread.h \
    cprotocol.h \
    ctool.h \
    ccompro.h \
    cjcbase.h \
    cdbstjc.h \
    cserialthread.h \
    cmysqlite.h \
    ctesttcpthd.h \
    cdqhjwry.h \
    ccolsvr.h \
    cqjcyz.h

FORMS += \
        mainwindow.ui \
    formmain.ui \
    formreal.ui \
    formabout.ui \
    formhistory.ui \
    formsetting.ui \
    formanalysis.ui \
    formstate.ui \
    formonline.ui \
    formquery.ui \
    formsetting_cg.ui \
    formsetting_ck.ui \
    formsetting_adc.ui \
    formsetting_sb.ui \
    formsetting_yzsb.ui \
    formsetting_wlsz.ui \
    formsetting_sjjy.ui
