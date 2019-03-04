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

signals:

    void updateView(Mat frame);

public slots:

    void receiveFrame(Mat frame);

};

#endif // THREADMANAGER_H
