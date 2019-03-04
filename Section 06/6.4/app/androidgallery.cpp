#include "androidgallery.h"

QString AndroidGallery::getSelectedFile() const
{
    return selectedFile;
}

void AndroidGallery::setSelectedFile(const QString &value)
{
    selectedFile = value;
}

#ifdef Q_OS_ANDROID
void AndroidGallery::open()
{
    QAndroidJniObject intent_ACTION_PICK =
            QAndroidJniObject::getStaticObjectField("android/content/Intent",
                                                    "ACTION_PICK",
                                                    "Ljava/lang/String;");

    QAndroidJniObject EXTERNAL_CONTENT_URI =
            QAndroidJniObject::getStaticObjectField("android/provider/MediaStore$Images$Media",
                                                    "EXTERNAL_CONTENT_URI",
                                                    "Landroid/net/Uri;");

    QAndroidJniObject intent = QAndroidJniObject("android/content/Intent",
                                                 "(Ljava/lang/String;Landroid/net/Uri;)V",
                                                 intent_ACTION_PICK.object<jstring>(),
                                                 EXTERNAL_CONTENT_URI.object<jobject>());

    QtAndroid::startActivity(intent, 101, this);
}

void AndroidGallery::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data)
{
    jint RESULT_CODE =
            QAndroidJniObject::getStaticField<jint>("android/app/Activity",
                                                    "RESULT_OK");

    if(receiverRequestCode == 101 && resultCode == RESULT_CODE)
    {
        QAndroidJniObject uri =
                data.callObjectMethod("getData",
                                      "()Landroid/net/Uri;");

        QAndroidJniObject androidData =
          QAndroidJniObject::getStaticObjectField("android/provider/MediaStore$MediaColumns",
                                                  "DATA", "Ljava/lang/String;");
        QAndroidJniEnvironment env;

        jobjectArray projection =
                (jobjectArray)env->NewObjectArray(1,
                                            env->FindClass("java/lang/String"),
                                            NULL);
        jobject androidDataProjection =
                env->NewStringUTF(androidData.toString().toStdString().c_str());

        env->SetObjectArrayElement(projection, 0, androidDataProjection);

        QAndroidJniObject contentResolver =
                QtAndroid::androidActivity().callObjectMethod("getContentResolver",
                                                              "()Landroid/content/ContentResolver;");
        QAndroidJniObject nullObj;

        QAndroidJniObject cursor =
                contentResolver.callObjectMethod("query",
                                                 "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;",
                                                 uri.object<jobject>(),
                                                 projection,
                                                 nullObj.object<jstring>(),
                                                 nullObj.object<jobjectArray>(),
                                                 nullObj.object<jstring>());
        jint columnIndex =
                cursor.callMethod<jint>("getColumnIndexOrThrow","(Ljava/lang/String;)I",
                                         androidData.object<jstring>());

        cursor.callMethod<jboolean>("moveToFirst");

        QAndroidJniObject path = cursor.callObjectMethod("getString",
                                                         "(I)Ljava/lang/String;",
                                                         columnIndex);

        selectedFile = "file://" + path.toString();

        cursor.callMethod<jboolean>("close");

        emit selectedFileChanged();
    }
}
#endif

bool AndroidGallery::verifyOS()
{
#ifdef Q_OS_ANDROID
    return true;
#endif
    return false;
}

AndroidGallery::AndroidGallery(QObject *parent) : QObject(parent)
{

}
