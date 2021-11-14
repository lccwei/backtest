QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customplotWidget.cpp \
    main.cpp \
    backtestwidget.cpp \
    multiCurvesPlot.cpp \
    publicTableModel.cpp \
    publicTableView.cpp \
    qcustomplot.cpp \
    titlewidget.cpp

HEADERS += \
    MyAxisTickerText.h \
    backtestapi.h \
    backtestwidget.h \
    customplotWidget.h \
    multiCurvesPlot.h \
    publicTableModel.h \
    publicTableView.h \
    qcustomplot.h \
    smoothCurveGenerator.h \
    titlewidget.h

FORMS += \
    backtestwidget.ui \
    titlewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
