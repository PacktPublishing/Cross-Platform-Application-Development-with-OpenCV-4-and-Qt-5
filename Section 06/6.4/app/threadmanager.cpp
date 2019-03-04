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

void threadManager::runBackgroundSubstraction(QString url)
{
    capture.setUrl(url);

    connect(&thread, &QThread::started,
            &capture, &FileCapture::substractBackground);

    connect(&thread, &QThread::finished,
            &capture, &FileCapture::deleteLater);

    connect(&capture, &FileCapture::newFrameCaptured,
            this, &threadManager::receiveFrame);

    capture.moveToThread(&thread);
    thread.start();
}

void threadManager::runDetectColor(QString url)
{
    capture.setUrl(url);

    connect(&thread, &QThread::started,
            &capture, &FileCapture::detectColor);

    connect(&thread, &QThread::finished,
            &capture, &FileCapture::deleteLater);

    connect(&capture, &FileCapture::newFrameCaptured,
            this, &threadManager::receiveFrame);

    capture.moveToThread(&thread);
    thread.start();
}

void threadManager::runCamera()
{
    connect(&thread, &QThread::started,
            &capture, &FileCapture::openCamera);

    connect(&thread, &QThread::finished,
            &capture, &FileCapture::deleteLater);

    connect(&capture, &FileCapture::newFrameCaptured,
            this, &threadManager::receiveFrame);

    capture.moveToThread(&thread);
    thread.start();
}

void threadManager::runDetectFaces(QString url)
{
    capture.setUrl(url);

    connect(&thread, &QThread::started,
            &capture, &FileCapture::detectFaces);

    connect(&thread, &QThread::finished,
            &capture, &FileCapture::deleteLater);

    connect(&capture, &FileCapture::newFrameCaptured,
            this, &threadManager::receiveFrame);

    capture.moveToThread(&thread);
    thread.start();
}

void threadManager::runTrackYolo(QString url)
{
    capture.setUrl(url);

    connect(&thread, &QThread::started,
            &capture, &FileCapture::trackYolo);

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
