QT += core
QT -= gui

TARGET = mobileNet_ssd_demo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mobilenetssd.cpp

HEADERS += \
    mobilenetssd.h


#opencv
INCLUDEPATH += /home/fuxueping/sdb/Installation/conda/include/
LIBS += -L/home/fuxueping/sdb/Installation/conda/lib/ \
-lopencv_dnn -lopencv_ml -lopencv_objdetect \
-lopencv_shape -lopencv_stitching \
-lopencv_superres -lopencv_videostab \
-lopencv_calib3d -lopencv_features2d \
-lopencv_highgui -lopencv_videoio \
-lopencv_imgcodecs -lopencv_video \
-lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core


#cuda
INCLUDEPATH += /usr/local/cuda-8.0/include/
LIBS += -L/usr/local/cuda-8.0/lib64 \
-lcublas  -lcufft    -lcurand    -lnppc  -lnvToolsExt   \
-lcudart  -lcufftw       \
-lcusparse  -lnpps

#caffe
#caffe
INCLUDEPATH += /home/fuxueping/sdb/Caffe_Project_Train/caffe-ssd2/include
INCLUDEPATH += /home/fuxueping/sdb/Caffe_Project_Train/caffe-ssd2/build/include
INCLUDEPATH +=/home/fuxueping/sdb/Caffe_Project_Train/caffe-ssd2/build/src
LIBS +=-L/home/fuxueping/sdb/Caffe_Project_Train/caffe-ssd2/build/lib \
-lcaffe


CUDA_SDK = "/usr/local/cuda"   # Path to cuda SDK install
CUDA_DIR = "/usr/local/cuda"   # Path to cuda toolkit install


LIBS += -L/usr/lib/x86_64-linux-gnu \
-lglog -lboost_system  -lboost_thread -lgflags   -lprotobuf
