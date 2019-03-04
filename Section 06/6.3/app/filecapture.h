#ifndef FILECAPTURE_H
#define FILECAPTURE_H

#include <QObject>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn.hpp>

using namespace cv;
using namespace dnn;

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class FileCapture : public QObject
{
    Q_OBJECT

    VideoCapture *videoCapture;
    QString url;
    bool stopVideo;

public:
    explicit FileCapture(QObject *parent = nullptr);

    void setUrl(QString &value);
    void findObjects(Mat &frame, vector<Mat> &outs, Net &net,
                     vector<string> classes);
    void drawObjectBox(int classId, int left, int top, int right, int bottom,
                       Mat &frame, vector<string> &classes);

signals:

    void newFrameCaptured(Mat frame);

public slots:

    bool openVideo();
    void substractBackground();
    void detectColor();
    void openCamera();
    void detectFaces();
    void trackYolo();

};

#endif // FILECAPTURE_H
