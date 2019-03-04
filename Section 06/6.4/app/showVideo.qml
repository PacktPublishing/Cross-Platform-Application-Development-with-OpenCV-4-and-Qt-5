import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import com.app.frame 1.0

Page {
    anchors.fill: parent

    property int type: 0

    Connections{
        target: videoThread
        onUpdateView: selectedImage.setRawFrame(frame)
    }

    Rectangle{
        id: bar
        width: parent.width
        height: parent.height * 0.1
        color: "orange"

        Label{
            text: "Show Video"
            color: "white"
            anchors.centerIn: parent
        }
    }

    ColumnLayout{
        id: imageContainer
        width: parent.width*0.5 //640
        height: parent.height*0.5 //480

        anchors.top: bar.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: picture
            source: "qrc:/logo"
            Layout.preferredWidth: imageContainer.width
            Layout.preferredHeight: imageContainer.height
            fillMode: Image.PreserveAspectFit
        }

        Frame{
            id: selectedImage
            Layout.preferredWidth: imageContainer.width
            Layout.preferredHeight: imageContainer.height
            visible: false
        }
    }

    Grid{
        anchors.top: imageContainer.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.6
        columns: 4

        Button{
            text: "Open Video"
            onClicked: {
                type = 0;
                videoDialog.open();
            }
        }

        Button{
            text: "Substract BG"
            onClicked: {
                type = 1;
                videoDialog.open();
            }
        }

        Button{
            text: "Detect Color"
            onClicked: {
                type = 2;
                videoDialog.open();
            }
        }

        Button{
            text: "Open Cam"
            onClicked: {
                picture.visible = false;
                selectedImage.visible = true;
                videoThread.runCamera()
            }
        }

        Button{
            text: "Faces"
            onClicked: {
                type = 3;
                videoDialog.open();
            }
        }

        Button{
            text: "Yolo"
            onClicked: {
                type = 4;
                videoDialog.open();
            }
        }

        Button{
            text: "Go Back"
            onClicked: loader.pop()
        }

    }

    FileDialog{
        id: videoDialog
        title: "Choose Video"
        folder: shortcuts.movies
        onAccepted: {
            picture.visible = false;
            selectedImage.visible = true;
            switch(type){
            case 0:
                videoThread.runCapture(videoDialog.fileUrl);
                break;
            case 1:
                videoThread.runBackgroundSubstraction(videoDialog.fileUrl);
                break;
            case 2:
                videoThread.runDetectColor(videoDialog.fileUrl);
                break;
            case 3:
                videoThread.runDetectFaces(videoDialog.fileUrl);
                break;
            case 4:
                videoThread.runTrackYolo(videoDialog.fileUrl);
                break;
            }


        }
    }

}
