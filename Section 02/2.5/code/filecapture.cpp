#include "filecapture.h"

FileCapture::FileCapture(QObject *parent) : QObject(parent)
{
    stopVideo = false;
}

bool FileCapture::openVideo()
{
    Mat rawFrame;

    capture = new VideoCapture;
    capture->open(url.toStdString());


    if(!capture->isOpened())
    {
        return false;
    }

    while(capture->read(rawFrame) && !stopVideo)
    {
        emit(newFrameCaptured(rawFrame));
    }


    capture->release();

    return true;
}

void FileCapture::setUrl(QString &value)
{
    value.remove("file://");
    url = value;
}
