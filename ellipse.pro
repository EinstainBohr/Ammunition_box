TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    common.cpp \
    EllipseDetectorYaed.cpp

INCLUDEPATH += /usr/local/opencv3/include/opencv4/opencv2/ \
                /usr/local/opencv3/include/opencv4 \

LIBS += /usr/local/opencv3/lib/libopencv_*.so \

HEADERS += \
    common.h \
    EllipseDetectorYaed.h
