#ifndef ANDROIDGALLERY_H
#define ANDROIDGALLERY_H

#include <QObject>

#ifdef Q_OS_ANDROID
    #include <QtAndroidExtras>
    #include <QAndroidActivityResultReceiver>
    #include <QAndroidJniObject>
    #include <QAndroidJniEnvironment>
#endif

#ifdef Q_OS_ANDROID
class AndroidGallery : public QObject, QAndroidActivityResultReceiver
#else
class AndroidGallery : public QObject
#endif
{
    Q_OBJECT

    Q_PROPERTY(QString selectedFile READ getSelectedFile WRITE setSelectedFile NOTIFY selectedFileChanged)

    QString selectedFile;

public:
    explicit AndroidGallery(QObject *parent = nullptr);

    QString getSelectedFile() const;
    void setSelectedFile(const QString &value);

#ifdef Q_OS_ANDROID
    Q_INVOKABLE void open();
    virtual void handleActivityResult(int receiverRequestCode,
                                      int resultCode,
                                      const QAndroidJniObject & data) override;
#endif
    Q_INVOKABLE bool verifyOS();

signals:

    void selectedFileChanged();

public slots:
};

#endif // ANDROIDGALLERY_H
