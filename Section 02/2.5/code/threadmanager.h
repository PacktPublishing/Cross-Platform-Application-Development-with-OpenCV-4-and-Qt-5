#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QThread>
#include "filecapture.h"

class ThreadManager : public QObject
{
    Q_OBJECT

    QThread videoThread;
    FileCapture videocapture;

public:
    explicit ThreadManager(QObject *parent = nullptr);
    Q_INVOKABLE void runCapture(QString url);

signals:
    void updateFrame(Mat rawFrame);

public slots:  
    void receiveNewFrame(Mat rawFrame);
};

#endif // THREADMANAGER_H
