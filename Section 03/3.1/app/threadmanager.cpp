#include "threadmanager.h"

threadManager::threadManager(QObject *parent) : QObject(parent)
{

}

void threadManager::runCapture(QString url)
{
    capture.setUrl(url);

    connect(&thread, &QThread::started,
            &capture, &FileCapture::openVideo);

    connect(&thread, &QThread::finished,
            &capture, &FileCapture::deleteLater);

    connect(&capture, &FileCapture::newFrameCaptured,
            this, &threadManager::receiveFrame);

    capture.moveToThread(&thread);
    thread.start();
}

void threadManager::receiveFrame(Mat frame)
{
    emit(updateView(frame));
}
