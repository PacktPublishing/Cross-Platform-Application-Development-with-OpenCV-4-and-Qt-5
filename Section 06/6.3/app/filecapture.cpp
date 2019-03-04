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

void FileCapture::substractBackground()
{
    Ptr<BackgroundSubtractor> substractionPtr;

    substractionPtr = createBackgroundSubtractorMOG2();

    Mat rawFrame;
    Mat backgroundMask;

    videoCapture = new VideoCapture;
    videoCapture->open(url.toStdString());

    if(!videoCapture->isOpened())
    {
        return;
    }

    while(videoCapture->read(rawFrame))
    {
        substractionPtr->apply(rawFrame, backgroundMask);
        emit(newFrameCaptured(backgroundMask));
    }
}

void FileCapture::detectColor()
{
    Mat rawFrame;
    Mat hsvFrame;
    Mat thresholdFrame;

    videoCapture = new VideoCapture;
    videoCapture->open(url.toStdString());

    if(!videoCapture->isOpened())
    {
        return;
    }

    while(videoCapture->read(rawFrame))
    {
        cvtColor(rawFrame, hsvFrame, COLOR_BGR2HSV);
        inRange(hsvFrame, Scalar(0, 100, 100), Scalar(10, 255, 255),
                thresholdFrame);
        emit(newFrameCaptured(thresholdFrame));
    }

}

void FileCapture::openCamera()
{
    Mat rawFrame;
    videoCapture = new VideoCapture;
    videoCapture->open(0);

    if(!videoCapture->isOpened())
    {
        return;
    }

    while(videoCapture->read(rawFrame) && !stopVideo)
    {
        emit(newFrameCaptured(rawFrame));
    }
}

void FileCapture::detectFaces()
{
    CascadeClassifier faceClassifier;

    if(!faceClassifier.load("/home/antonio/app/haarcascade_frontalface_alt_tree.xml"))
    {
        return;
    }

    Mat rawFrame;
    Mat grayMask;

    videoCapture = new VideoCapture;
    videoCapture->open(url.toStdString());

    if(!videoCapture->isOpened())
    {
        return;
    }

    while(videoCapture->read(rawFrame))
    {
        cvtColor(rawFrame, grayMask, COLOR_BGR2GRAY);
        equalizeHist(grayMask, grayMask);

        vector<Rect> faces;
        faceClassifier.detectMultiScale(grayMask, faces, 2, 0,
                                        0 | CASCADE_SCALE_IMAGE, Size(25, 25));

        for(unsigned int i = 0; i < faces.size(); i++ )
        {
            Point center(faces[i].x + faces[i].width/2,
                         faces[i].y + faces[i].height/2);
            ellipse(rawFrame, center,
                    Size(faces[i].width/2, faces[i].height/2),
                    0, 0, 360, Scalar(255, 0, 255), 4);
        }

        emit(newFrameCaptured(rawFrame));
    }
}

void FileCapture::trackYolo()
{
    Mat rawFrame;
    Mat blob;

    float scale = 0.00392;
    vector<string> classes;

    string modelConfiguration = "/home/antonio/app/yolo/yolov2-voc.cfg";
    string modelWeights = "/home/antonio/app/yolo/yolov2-voc.weights";
    string classesFileUrl = "/home/antonio/app/yolo/object_detection_classes_pascal_voc.txt";

    ifstream classesFile(classesFileUrl);

    if(!classesFile.is_open())
    {
        return;
    }

    string line;

    while(getline(classesFile, line))
    {
        classes.push_back(line);
    }

    Net net = readNet(modelWeights, modelConfiguration);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);

    vector<string> objectsName = net.getUnconnectedOutLayersNames();

    videoCapture = new VideoCapture;
    videoCapture->open(url.toStdString());

    if(!videoCapture->isOpened())
    {
        return;
    }

    while(videoCapture->read(rawFrame))
    {
        resize(rawFrame, rawFrame, Size(416, 416), 0, 0, INTER_CUBIC);
        blobFromImage(rawFrame, blob, scale, Size(rawFrame.cols, rawFrame.rows),
                      Scalar(0,0,0), 1, false);
        net.setInput(blob);
        vector<Mat> outs;
        net.forward(outs, objectsName);
        findObjects(rawFrame, outs, net, classes);
        emit(newFrameCaptured(rawFrame));
    }

}

void FileCapture::findObjects(Mat &frame, vector<Mat> &outs, Net &net, vector<string> classes)
{
    vector<int> outLayers = net.getUnconnectedOutLayers();
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;

    float confThreshold = 0.5;
    float nmsThreshold = 0.4;

    for(unsigned int i = 0; i < outs.size(); i++)
    {
        float* data = (float*) outs[i].data;
        for(unsigned int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            Point classIdPoint;
            double confidence;
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold)
            {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
    }

    vector<int> indices;
    NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        Rect box = boxes[idx];
        drawObjectBox(classIds[idx], box.x, box.y,
                      box.x + box.width, box.y + box.height, frame, classes);
    }

}

void FileCapture::drawObjectBox(int classId, int left, int top, int right, int bottom, Mat &frame, vector<string> &classes)
{
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0,0,255));
    string label = classes[classId];

    putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.5,
            Scalar(255,255,0));
}

FileCapture::FileCapture(QObject *parent) : QObject(parent)
{
    stopVideo = false;
}
