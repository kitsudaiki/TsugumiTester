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
    src/common/test_step.cpp \
    src/common/test_thread.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_create_test.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_delete_test.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_get_test.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_list_test.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_load_test.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_save_test.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_switch_to_direct_test.cpp \
    src/rest_api_tests/kyouko/cluster/cluster_switch_to_task_test.cpp \
    src/rest_api_tests/kyouko/io/direct_io_test.cpp \
    src/rest_api_tests/kyouko/task/graph_learn_task_test.cpp \
    src/rest_api_tests/kyouko/task/graph_request_task_test.cpp \
    src/rest_api_tests/kyouko/task/image_learn_task_test.cpp \
    src/rest_api_tests/kyouko/task/image_request_task_test.cpp \
    src/rest_api_tests/kyouko/template/template_delete_test.cpp \
    src/rest_api_tests/kyouko/template/template_generate_test.cpp \
    src/rest_api_tests/kyouko/template/template_get_test.cpp \
    src/rest_api_tests/kyouko/template/template_list_test.cpp \
    src/rest_api_tests/kyouko/template/template_upload_test.cpp \
    src/rest_api_tests/misaka/user_create_test.cpp \
    src/rest_api_tests/misaka/user_delete_test.cpp \
    src/rest_api_tests/misaka/user_get_test.cpp \
    src/rest_api_tests/misaka/user_list_test.cpp \
    src/rest_api_tests/rest_api_tests.cpp \
    src/rest_api_tests/sagiri/datasets/dataset_check_test.cpp \
    src/rest_api_tests/sagiri/datasets/dataset_create_csv_test.cpp \
    src/rest_api_tests/sagiri/datasets/dataset_create_mnist_test.cpp \
    src/rest_api_tests/sagiri/datasets/dataset_delete_test.cpp \
    src/rest_api_tests/sagiri/datasets/dataset_get_test.cpp \
    src/rest_api_tests/sagiri/datasets/dataset_list_test.cpp \
    src/rest_api_tests/sagiri/snapshots/snapshot_delete_test.cpp \
    src/rest_api_tests/sagiri/snapshots/snapshot_get_test.cpp \
    src/rest_api_tests/sagiri/snapshots/snapshot_list_test.cpp

HEADERS += \
    src/args.h \
    src/common/test_step.h \
    src/common/test_thread.h \
    src/config.h \
    src/rest_api_tests/kyouko/cluster/cluster_create_test.h \
    src/rest_api_tests/kyouko/cluster/cluster_delete_test.h \
    src/rest_api_tests/kyouko/cluster/cluster_get_test.h \
    src/rest_api_tests/kyouko/cluster/cluster_list_test.h \
    src/rest_api_tests/kyouko/cluster/cluster_load_test.h \
    src/rest_api_tests/kyouko/cluster/cluster_save_test.h \
    src/rest_api_tests/kyouko/cluster/cluster_switch_to_direct_test.h \
    src/rest_api_tests/kyouko/cluster/cluster_switch_to_task_test.h \
    src/rest_api_tests/kyouko/io/direct_io_test.h \
    src/rest_api_tests/kyouko/task/graph_learn_task_test.h \
    src/rest_api_tests/kyouko/task/graph_request_task_test.h \
    src/rest_api_tests/kyouko/task/image_learn_task_test.h \
    src/rest_api_tests/kyouko/task/image_request_task_test.h \
    src/rest_api_tests/kyouko/template/template_delete_test.h \
    src/rest_api_tests/kyouko/template/template_generate_test.h \
    src/rest_api_tests/kyouko/template/template_get_test.h \
    src/rest_api_tests/kyouko/template/template_list_test.h \
    src/rest_api_tests/kyouko/template/template_upload_test.h \
    src/rest_api_tests/misaka/user_create_test.h \
    src/rest_api_tests/misaka/user_delete_test.h \
    src/rest_api_tests/misaka/user_get_test.h \
    src/rest_api_tests/misaka/user_list_test.h \
    src/rest_api_tests/rest_api_tests.h \
    src/rest_api_tests/sagiri/datasets/dataset_check_test.h \
    src/rest_api_tests/sagiri/datasets/dataset_create_csv_test.h \
    src/rest_api_tests/sagiri/datasets/dataset_create_mnist_test.h \
    src/rest_api_tests/sagiri/datasets/dataset_delete_test.h \
    src/rest_api_tests/sagiri/datasets/dataset_get_test.h \
    src/rest_api_tests/sagiri/datasets/dataset_list_test.h \
    src/rest_api_tests/sagiri/snapshots/snapshot_delete_test.h \
    src/rest_api_tests/sagiri/snapshots/snapshot_get_test.h \
    src/rest_api_tests/sagiri/snapshots/snapshot_list_test.h
