#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include <frame.h>
#include "threadmanager.h"
#include "androidgallery.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    threadManager videoThread;
    AndroidGallery androidGallery;

    qmlRegisterType<Frame>("com.app.frame", 1, 0, "Frame");
    qRegisterMetaType<cv::Mat>("Mat");

    engine.rootContext()->setContextProperty("videoThread", &videoThread);
    engine.rootContext()->setContextProperty("androidGallery", &androidGallery);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
