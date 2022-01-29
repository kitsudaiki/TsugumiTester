QT -= qt core gui

TARGET = TsugumiTester
CONFIG += console c++17
CONFIG -= app_bundle

LIBS += -L../libKitsunemimiHanamiSdk/src -lKitsunemimiHanamiSdk
LIBS += -L../libKitsunemimiHanamiSdk/src/debug -lKitsunemimiHanamiSdk
LIBS += -L../libKitsunemimiHanamiSdk/src/release -lKitsunemimiHanamiSdk
INCLUDEPATH += ../libKitsunemimiHanamiSdk/cpp/include

LIBS += -L../libKitsunemimiHanamiCommon/src -lKitsunemimiHanamiCommon
LIBS += -L../libKitsunemimiHanamiCommon/src/debug -lKitsunemimiHanamiCommon
LIBS += -L../libKitsunemimiHanamiCommon/src/release -lKitsunemimiHanamiCommon
INCLUDEPATH += ../libKitsunemimiHanamiCommon/include

LIBS += -L../libKitsunemimiSakuraNetwork/src -lKitsunemimiSakuraNetwork
LIBS += -L../libKitsunemimiSakuraNetwork/src/debug -lKitsunemimiSakuraNetwork
LIBS += -L../libKitsunemimiSakuraNetwork/src/release -lKitsunemimiSakuraNetwork
INCLUDEPATH += ../libKitsunemimiSakuraNetwork/include

LIBS += -L../libKitsunemimiNetwork/src -lKitsunemimiNetwork
LIBS += -L../libKitsunemimiNetwork/src/debug -lKitsunemimiNetwork
LIBS += -L../libKitsunemimiNetwork/src/release -lKitsunemimiNetwork
INCLUDEPATH += ../libKitsunemimiNetwork/include

LIBS += -L../libKitsunemimiConfig/src -lKitsunemimiConfig
LIBS += -L../libKitsunemimiConfig/src/debug -lKitsunemimiConfig
LIBS += -L../libKitsunemimiConfig/src/release -lKitsunemimiConfig
INCLUDEPATH += ../libKitsunemimiConfig/include

LIBS += -L../libKitsunemimiJson/src -lKitsunemimiJson
LIBS += -L../libKitsunemimiJson/src/debug -lKitsunemimiJson
LIBS += -L../libKitsunemimiJson/src/release -lKitsunemimiJson
INCLUDEPATH += ../libKitsunemimiJson/include

LIBS += -L../libKitsunemimiIni/src -lKitsunemimiIni
LIBS += -L../libKitsunemimiIni/src/debug -lKitsunemimiIni
LIBS += -L../libKitsunemimiIni/src/release -lKitsunemimiIni
INCLUDEPATH += ../libKitsunemimiIni/include

LIBS += -L../libKitsunemimiArgs/src -lKitsunemimiArgs
LIBS += -L../libKitsunemimiArgs/src/debug -lKitsunemimiArgs
LIBS += -L../libKitsunemimiArgs/src/release -lKitsunemimiArgs
INCLUDEPATH += ../libKitsunemimiArgs/include

LIBS += -L../libKitsunemimiCrypto/src -lKitsunemimiCrypto
LIBS += -L../libKitsunemimiCrypto/src/debug -lKitsunemimiCrypto
LIBS += -L../libKitsunemimiCrypto/src/release -lKitsunemimiCrypto
INCLUDEPATH += ../libKitsunemimiCrypto/include

LIBS += -L../libKitsunemimiCommon/src -lKitsunemimiCommon
LIBS += -L../libKitsunemimiCommon/src/debug -lKitsunemimiCommon
LIBS += -L../libKitsunemimiCommon/src/release -lKitsunemimiCommon
INCLUDEPATH += ../libKitsunemimiCommon/include

LIBS += -lcryptopp -lssl -luuid -lcrypto

INCLUDEPATH += $$PWD \
               src

SOURCES += src/main.cpp \
    src/rest_api_tests/kyouko/cluster_tests.cpp \
    src/rest_api_tests/kyouko/task_tests.cpp \
    src/rest_api_tests/kyouko/template_test.cpp \
    src/rest_api_tests/misaka/user_tests.cpp \
    src/rest_api_tests/rest_api_tests.cpp \
    src/rest_api_tests/sagiri/train_data_tests.cpp

HEADERS += \
    src/args.h \
    src/config.h \
    src/rest_api_tests/kyouko/cluster_tests.h \
    src/rest_api_tests/kyouko/task_tests.h \
    src/rest_api_tests/kyouko/template_test.h \
    src/rest_api_tests/rest_api_tests.h \
    src/rest_api_tests/misaka/user_tests.h \
    src/rest_api_tests/sagiri/train_data_tests.h
