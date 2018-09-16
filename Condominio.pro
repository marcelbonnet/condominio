#-------------------------------------------------
#
# Project created by QtCreator 2018-09-04T18:31:42
#
#-------------------------------------------------

# webkitwidgets if QT >= 5.9 - https://doc-snapshots.qt.io/qt5-5.9/qtwebenginewidgets-qtwebkitportingguide.html
QT       += core gui webkitwidgets webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
TARGET = QCondominiX

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
    formunidade.cpp \
    DAO.cpp \
    formdespesa.cpp \
    formnaturezadespesa.cpp \
    formgrupodespesa.cpp \
    formrateio.cpp

HEADERS += \
        mainwindow.h \
    formunidade.h \
    DAO.h \
    entidade/unidade.h \
    entidade/despesa.h \
    formdespesa.h \
    formnaturezadespesa.h \
    entidade/naturezadespesa.h \
    formgrupodespesa.h \
    entidade/grupodespesa.h \
    formrateio.h \
    entidade/rateio.h

FORMS += \
        mainwindow.ui \
    formunidade.ui \
    formdespesa.ui \
    formnaturezadespesa.ui \
    formgrupodespesa.ui \
    formrateio.ui

QMAKE_LIBS += -lsqlite3 -L/home/marcelbonnet/devel/cpp/SQLiteCpp-master/build -lSQLiteCpp

INCLUDEPATH += /home/marcelbonnet/devel/cpp/SQLiteCpp-master/include/
