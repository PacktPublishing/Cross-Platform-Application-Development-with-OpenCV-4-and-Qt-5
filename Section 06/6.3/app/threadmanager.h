#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QThread>
#include "filecapture.h"

class threadManager : public QObject
{
    Q_OBJECT

    QThread thread;
    FileCapture capture;

public:
    explicit threadManager(QObject *parent = nullptr);

    Q_INVOKABLE void runCapture(QString url);
    Q_INVOKABLE void runBackgroundSubstraction(QString url);
    Q_INVOKABLE void runDetectColor(QString url);
    Q_INVOKABLE void runCamera();
    Q_INVOKABLE void runDetectFaces(QString url);
    Q_INVOKABLE void runTrackYolo(QString url);

signals:

    void updateView(Mat frame);

public slots:

    void receiveFrame(Mat frame);

};

#endif // THREADMANAGER_H
