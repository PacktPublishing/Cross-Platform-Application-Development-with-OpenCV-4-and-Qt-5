#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent) : QObject(parent)
{

}

void ThreadManager::runCapture(QString url)
{
    videocapture.setUrl(url);

    connect(&videoThread, &QThread::started,
            &videocapture, &FileCapture::openVideo);
    connect(&videoThread, &QThread::finished,
            &videocapture, &FileCapture::deleteLater);
    connect(&videocapture, &FileCapture::newFrameCaptured,
            this, &ThreadManager::receiveNewFrame);

    videocapture.moveToThread(&videoThread);
    videoThread.start();

}

void ThreadManager::receiveNewFrame(Mat rawFrame)
{
    emit(updateFrame(rawFrame));
}
