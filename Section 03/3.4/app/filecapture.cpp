#include "filecapture.h"

void FileCapture::setUrl(QString &value)
{
    value.remove("file://");
    url = value;
}

bool FileCapture::openVideo()
{
    Mat rawFrame;
    videoCapture = new VideoCapture;
    videoCapture->open(url.toStdString());

    if(!videoCapture->isOpened())
    {
        return false;
    }

    while(videoCapture->read(rawFrame) && !stopVideo)
    {
        emit(newFrameCaptured(rawFrame));
    }

    return true;
}

FileCapture::FileCapture(QObject *parent) : QObject(parent)
{
    stopVideo = false;
}
