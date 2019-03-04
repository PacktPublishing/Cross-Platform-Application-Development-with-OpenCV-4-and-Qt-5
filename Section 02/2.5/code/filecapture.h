#ifndef FILECAPTURE_H
#define FILECAPTURE_H

#include <QObject>
#include <QThread>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class FileCapture : public QObject
{
    Q_OBJECT

    VideoCapture *capture;
    bool stopVideo;
    QString url;

public:
    FileCapture(QObject *parent = nullptr);
    void setUrl(QString &value);

signals:
    void newFrameCaptured(Mat rawFrame);

public slots:
    bool openVideo();
};

#endif // FILECAPTURE_H
