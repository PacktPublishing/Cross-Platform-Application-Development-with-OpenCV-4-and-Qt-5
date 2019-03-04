QT += quick

android:{
    QT += androidextras
}

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    frame.cpp \
    filecapture.cpp \
    threadmanager.cpp \
    androidgallery.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    frame.h \
    filecapture.h \
    threadmanager.h \
    androidgallery.h


android:{
    equals(ANDROID_TARGET_ARCH, armeabi-v7a) {
        INCLUDEPATH = /opt/opencv_android/sdk/native/jni/include/
        DEPENDPATH = /opt/opencv_android/sdk/native/jni/include/

        ANDROID_EXTRA_LIBS = \
            $$PWD/libs/libopencv_aruco.so $$PWD/libs/libopencv_dpm.so $$PWD/libs/libopencv_imgproc.so \
            $$PWD/libs/libopencv_rgbd.so $$PWD/libs/libopencv_tracking.so $$PWD/libs/libopencv_bgsegm.so \
            $$PWD/libs/libopencv_face.so $PWD/libs/libopencv_line_descriptor.so $$PWD/libs/libopencv_saliency.so \
            $$PWD/libs/libopencv_videoio.so $$PWD/libs/libopencv_bioinspired.so $$PWD/libs/libopencv_features2d.so \
            $$PWD/libs/libopencv_ml.so $$PWD/libs/libopencv_shape.so $$PWD/libs/libopencv_video.so \
            $$PWD/libs/libopencv_calib3d.so $$PWD/libs/libopencv_flann.so $$PWD/libs/libopencv_objdetect.so \
            $$PWD/libs/libopencv_stereo.so $$PWD/libs/libopencv_videostab.so $$PWD/libs/libopencv_ccalib.so \
            $$PWD/libs/libopencv_fuzzy.so $$PWD/libs/libopencv_optflow.so $$PWD/libs/libopencv_stitching.so \
            $$PWD/libs/libopencv_xfeatures2d.so $$PWD/libs/libopencv_core.so $$PWD/libs/libopencv_hfs.so \
            $$PWD/libs/libopencv_phase_unwrapping.so $$PWD/libs/libopencv_structured_light.so $$PWD/libs/libopencv_ximgproc.so \
            $$PWD/libs/libopencv_datasets.so $$PWD/libs/libopencv_highgui.so $$PWD/libs/libopencv_photo.so \
            $$PWD/libs/libopencv_superres.so $$PWD/libs/libopencv_xobjdetect.so $$PWD/libs/libopencv_dnn_objdetect.so \
            $$PWD/libs/libopencv_imgcodecs.so $$PWD/libs/libopencv_plot.so $$PWD/libs/libopencv_surface_matching.so \
            $$PWD/libs/libopencv_xphoto.so $$PWD/libs/libopencv_dnn.so $$PWD/libs/libopencv_img_hash.so \
            $$PWD/libs/libopencv_reg.so $$PWD/libs/libopencv_text.so$$PWD/libs/libtbb.so

            LIBS += -L"$$PWD/libs/" \
            -lopencv_aruco -lopencv_dpm -lopencv_imgproc -lopencv_rgbd -lopencv_tracking -lopencv_bgsegm \
            -lopencv_face -lopencv_line_descriptor -lopencv_saliency -lopencv_videoio -lopencv_bioinspired -lopencv_features2d \
            -lopencv_ml -lopencv_shape -lopencv_video -lopencv_calib3d -lopencv_flann -lopencv_objdetect -lopencv_stereo \
            -lopencv_videostab -lopencv_ccalib -lopencv_fuzzy -lopencv_optflow -lopencv_stitching -lopencv_xfeatures2d \
            -lopencv_core -lopencv_hfs -lopencv_phase_unwrapping -lopencv_structured_light -lopencv_ximgproc -lopencv_datasets \
            -lopencv_highgui -lopencv_photo -lopencv_superres -lopencv_xobjdetect -lopencv_dnn_objdetect -lopencv_imgcodecs \
            -lopencv_plot -lopencv_surface_matching -lopencv_xphoto -lopencv_dnn -lopencv_img_hash -lopencv_reg lopencv_text \
            -ltbb

    }
    equals(ANDROID_TARGET_ARCH,  x86) {
        INCLUDEPATH = /opt/opencv_android_x86/sdk/native/jni/include/
        DEPENDPATH = /opt/opencv_android_x86/sdk/native/jni/include/
        ANDROID_EXTRA_LIBS = \
            $$PWD/libs_x86/libopencv_aruco.so $$PWD/libs_x86/libopencv_dpm.so $$PWD/libs_x86/libopencv_imgproc.so \
            $$PWD/libs_x86/libopencv_rgbd.so $$PWD/libs_x86/libopencv_tracking.so $$PWD/libs_x86/libopencv_bgsegm.so \
            $$PWD/libs_x86/libopencv_face.so $$PWD/libs_x86/libopencv_line_descriptor.so $$PWD/libs_x86/libopencv_saliency.so \
            $$PWD/libs_x86/libopencv_videoio.so $$PWD/libs_x86/libopencv_bioinspired.so $$PWD/libs_x86/libopencv_features2d.so \
            $$PWD/libs_x86/libopencv_ml.so $$PWD/libs_x86/libopencv_shape.so $$PWD/libs_x86/libopencv_video.so \
            $$PWD/libs_x86/libopencv_calib3d.so $$PWD/libs_x86/libopencv_flann.so $$PWD/libs_x86/libopencv_objdetect.so \
            $$PWD/libs_x86/libopencv_stereo.so $$PWD/libs_x86/libopencv_videostab.so $$PWD/libs_x86/libopencv_ccalib.so \
            $$PWD/libs_x86/libopencv_fuzzy.so $$PWD/libs_x86/libopencv_optflow.so $$PWD/libs_x86/libopencv_stitching.so \
            $$PWD/libs_x86/libopencv_xfeatures2d.so $$PWD/libs_x86/libopencv_core.so $$PWD/libs_x86/libopencv_hfs.so \
            $$PWD/libs_x86/libopencv_phase_unwrapping.so $$PWD/libs_x86/libopencv_structured_light.so $$PWD/libs_x86/libopencv_ximgproc.so \
            $$PWD/libs_x86/libopencv_datasets.so $$PWD/libs_x86/libopencv_highgui.so $$PWD/libs_x86/libopencv_photo.so \
            $$PWD/libs_x86/libopencv_superres.so $$PWD/libs_x86/libopencv_xobjdetect.so $$PWD/libs_x86/libopencv_dnn_objdetect.so \
            $$PWD/libs_x86/libopencv_imgcodecs.so $$PWD/libs_x86/libopencv_plot.so $$PWD/libs_x86/libopencv_surface_matching.so \
            $$PWD/libs_x86/libopencv_xphoto.so $$PWD/libs_x86/libopencv_dnn.so $$PWD/libs_x86/libopencv_img_hash.so \
            $$PWD/libs_x86/libopencv_reg.so $$PWD/libs_x86/libopencv_text.so $$PWD/libs_x86/libtbb.so

        LIBS += -L"$$PWD/libs_x86/" \
            -lopencv_aruco -lopencv_dpm -lopencv_imgproc -lopencv_rgbd -lopencv_tracking -lopencv_bgsegm \
            -lopencv_face -lopencv_line_descriptor -lopencv_saliency -lopencv_videoio -lopencv_bioinspired \
            -lopencv_features2d -lopencv_ml -lopencv_shape -lopencv_video -lopencv_calib3d -lopencv_flann \
            -lopencv_objdetect -lopencv_stereo -lopencv_videostab -lopencv_ccalib -lopencv_fuzzy -lopencv_optflow \
            -lopencv_stitching -lopencv_xfeatures2d -lopencv_core -lopencv_hfs -lopencv_phase_unwrapping \
            -lopencv_structured_light -lopencv_ximgproc -lopencv_datasets -lopencv_highgui -lopencv_photo \
            -lopencv_superres -lopencv_xobjdetect -lopencv_dnn_objdetect -lopencv_imgcodecs -lopencv_plot \
            -lopencv_surface_matching -lopencv_xphoto -lopencv_dnn -lopencv_img_hash -lopencv_reg -lopencv_text \
            -ltbb
    }
}
else: unix:{
LIBS += -L"/opt/opencv/lib" -lopencv_core -lopencv_imgproc \
        -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio \
        -lopencv_video -lopencv_objdetect -lopencv_dnn
INCLUDEPATH += /opt/opencv/include/opencv4/
DEPENDPATH += /opt/opencv/include/opencv4/
}



