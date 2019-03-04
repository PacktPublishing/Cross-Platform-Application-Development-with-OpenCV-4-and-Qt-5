#ifndef FILECAPTURE_H
#define FILECAPTURE_H

#include <QObject>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class FileCapture : public QObject
{
    Q_OBJECT

    VideoCapture *videoCapture;
    QString url;
    bool stopVideo;

public:
    explicit FileCapture(QObject *parent = nullptr);

    void setUrl(QString &value);

signals:

    void newFrameCaptured(Mat frame);

public slots:

    bool openVideo();

};

#endif // FILECAPTURE_H
