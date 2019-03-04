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
        z:1

        Label{
            text: "Show Image"
            color: "white"
            anchors.centerIn: parent
        }
    }

    Flickable
    {
        width: parent.width
        height: parent.height - bar.height
        contentWidth: parent.width
        contentHeight: height*1.5
        anchors.top: bar.bottom

        ColumnLayout{
            id: imageContainer
            width: 640
            height: 480

            anchors.top: parent.top
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
            id: buttonGrid
            anchors.top: imageContainer.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.6
            columns: 3

            Button{
                text: "Open Image"
                width: parent.width*0.3
                onClicked: imageDialog.open()
            }
            Button{
                text: "Smooth"
                width: parent.width*0.3
                onClicked: {
                    if(!selectedImage.smoothImage())
                    {
                       errorAlert.open();
                    }
                }
            }
            Button{
                text: "Erode"
                width: parent.width*0.3
                onClicked: {
                    if(!selectedImage.erodeImage())
                    {
                       errorAlert.open();
                    }
                }
            }
            Button{
                text: "Dilate"
                width: parent.width*0.2
                onClicked: {
                    if(!selectedImage.dilateImage())
                    {
                       errorAlert.open();
                    }
                }
            }
            Button{
                text: "Canny"
                width: parent.width*0.2
                onClicked: {
                    if(!selectedImage.findContours())
                    {
                       errorAlert.open();
                    }
                }
            }
            Button{
                text: "H lines"
                width: parent.width*0.2
                onClicked: {
                    if(!selectedImage.findHorizontalLines())
                    {
                       errorAlert.open();
                    }
                }
            }
            Button{
                text: "V Lines"
                width: parent.width*0.2
                onClicked: {
                    if(!selectedImage.findVerticalLines())
                    {
                       errorAlert.open();
                    }
                }
            }
            Button{
                text: "Go Back"
                width: parent.width*0.2
                onClicked: loader.pop()
            }

        }

    }


    Dialog{
        id: errorAlert
        title: "Error"
        Text {
            text: "First open an Image"
            anchors.centerIn: parent
        }

        standardButtons: StandardButton.Ok
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
