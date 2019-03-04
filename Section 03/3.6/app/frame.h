#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

#include <vector>

using namespace std;

class Frame : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QImage frame READ getFrame WRITE setFrame NOTIFY frameChanged)

    Mat rawFrame;
    QImage frame;

public:
    Frame(QQuickItem *parent = 0);

    void paint(QPainter *painter);
    Mat getRawFrame() const;
    Q_INVOKABLE void setRawFrame(const Mat &value);
    QImage getFrame() const;
    void setFrame(const QImage &value);

    Q_INVOKABLE bool smoothImage();
    Q_INVOKABLE bool erodeImage();
    Q_INVOKABLE bool dilateImage();
    Q_INVOKABLE void openImage(QString url);
    Q_INVOKABLE bool applyCanny();
    Q_INVOKABLE bool findHorizontalLines();
    Q_INVOKABLE bool findVerticalLines();
    Q_INVOKABLE bool laplacianFilter();
    Q_INVOKABLE bool findImageContours();

 signals:
    void frameChanged();

 public slots:
    void convert2QImage();
};

#endif // FRAME_H
