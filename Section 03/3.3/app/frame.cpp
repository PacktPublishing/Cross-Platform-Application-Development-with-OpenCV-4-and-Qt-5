#include "frame.h"

Mat Frame::getRawFrame() const
{
    return rawFrame;
}

void Frame::setRawFrame(const Mat &value)
{
    rawFrame = value;
    convert2QImage();
}

QImage Frame::getFrame() const
{
    return frame;
}

void Frame::setFrame(const QImage &value)
{
    frame = value;
    Frame::update();
    emit(frameChanged());
}

bool Frame::smoothImage()
{
    if(!rawFrame.empty())
    {
        Mat temp;
        GaussianBlur( rawFrame, temp, Size( 31, 31 ), 0, 0 );
        setRawFrame(temp);
        return true;
    }
    return false;
}

bool Frame::erodeImage()
{
    if(!rawFrame.empty()){
        Mat temp;
        Mat kernel = getStructuringElement(MORPH_RECT, Size(16,16));
        erode(rawFrame, temp, kernel);
        setRawFrame(temp);
        return true;
    }
    return false;
}

bool Frame::dilateImage()
{
    if(!rawFrame.empty()){
        Mat temp = rawFrame;
        Mat kernel = getStructuringElement(MORPH_RECT, Size(6,6));
        dilate(temp, temp, kernel);
        setRawFrame(temp);
        return true;
    }
    return false;
}

void Frame::openImage(QString url)
{
    url.remove("file://");
    rawFrame = imread(url.toStdString());
    convert2QImage();
}

bool Frame::findContours()
{
    if(!rawFrame.empty())
    {
        Mat tempGray;
        cvtColor( rawFrame, tempGray, COLOR_BGR2GRAY );
        Canny( tempGray, tempGray, 0, 150, 3 );
        setRawFrame(tempGray);
    }
    return false;
}

void Frame::convert2QImage()
{
    Mat tempMat;
    cvtColor(rawFrame, tempMat, COLOR_RGB2BGR);
    QImage tempImage((uchar*) tempMat.data, tempMat.cols,tempMat.rows, tempMat.step, QImage::Format_RGB888);

    frame = tempImage;
    frame.detach();
    Frame::update();
    emit(frameChanged());
}

Frame::Frame(QQuickItem *parent): QQuickPaintedItem(parent)
{

}

void Frame::paint(QPainter *painter)
{
    frame.scaled(640, 480, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    painter->drawImage(0, 0, frame, 0, 0, -1, -1, Qt::AutoColor);
}
