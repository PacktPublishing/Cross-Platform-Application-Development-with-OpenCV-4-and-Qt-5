#include "frame.h"

Mat Frame::getRawFrame() const
{
    return rawFrame;
}

void Frame::setRawFrame(const Mat &value)
{
    rawFrame = value;
    convert2Qimage();
}

QImage Frame::getFrame() const
{
    return frame;
}

void Frame::setFrame(const QImage &value)
{
    frame = value;
    Frame::update();
    emit frameChanged();
}

void Frame::openImage(QString url)
{
    url.remove("file://");
    rawFrame = imread(url.toStdString());
    convert2Qimage();
}

Frame::Frame(QQuickItem *parent): QQuickPaintedItem(parent)
{

}

void Frame::paint(QPainter *painter)
{
    if(!frame.isNull())
    {
        QImage tempFrame = frame.scaled(640, 480,
                         Qt::IgnoreAspectRatio,
                         Qt::FastTransformation);

        painter->drawImage(0, 0, tempFrame, 0, 0,
                           -1, -1, Qt::AutoColor);
    }
}

void Frame::convert2Qimage()
{
    Mat tempMat;
    cvtColor(rawFrame, tempMat, COLOR_RGB2BGR);
    QImage tempImage((uchar*) tempMat.data, tempMat.cols, tempMat.rows, tempMat.step, QImage::Format_RGB888);

    frame = tempImage;
    frame.detach();
    Frame::update();
    emit (frameChanged());
}
