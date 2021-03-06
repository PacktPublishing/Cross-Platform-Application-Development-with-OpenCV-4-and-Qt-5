import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import com.app.frame 1.0

Page {
    anchors.fill: parent

    Rectangle{
        id: bar
        width: parent.width
        height: parent.height * 0.1
        color: "orange"

        Label{
            text: "Show Image"
            color: "white"
            anchors.centerIn: parent
        }
    }

    ColumnLayout{
        id: imageContainer
        width: 640
        height: 480

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

    RowLayout{
        anchors.top: imageContainer.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.6
        spacing: width*0.2

        Button{
            text: "Open Image"
            Layout.preferredWidth: parent.width*0.2
            onClicked: imageDialog.open()
        }
        Button{
            text: "Smooth"
            Layout.preferredWidth: parent.width*0.2
            onClicked: {
                if(!selectedImage.smoothImage())
                {
                   errorAlert.open();
                }
            }
        }
        Button{
            text: "Go Back"
            Layout.preferredWidth: parent.width*0.2
            onClicked: loader.pop()
        }

    }

    Dialog{
        id: errorAlert
        title: "Error"
        contentItem: Rectangle{
            Text{
                text: "Open an Image First"
                anchors.centerIn: parent
            }
        }
    }

    FileDialog{
        id: imageDialog
        title: "Choose Image"
        folder: shortcuts.pictures
        onAccepted: {
            selectedImage.openImage(imageDialog.fileUrl);
            picture.visible = false;
            selectedImage.visible = true;
        }
    }

}
