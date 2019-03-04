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
        z: 1

        Label{
            text: "Show Image"
            color: "white"
            anchors.centerIn: parent
        }
    }

    Flickable{
        width: parent.width
        height: parent.height
        anchors.top: bar.bottom
        contentWidth: parent.width
        contentHeight: parent.header*1.5

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
            columns: 3

            Button{
                text: "Open Image"
                onClicked: imageDialog.open()
            }

            Button{
                text: "Smooth"
                onClicked:{
                    if(!selectedImage.smoothImage())
                    {
                        errorAlert.open();
                    }
                }
            }

            Button{
                text: "Erode"
                onClicked:{
                    if(!selectedImage.erodeImage())
                    {
                        errorAlert.open();
                    }
                }
            }

            Button{
                text: "Dilate"
                onClicked:{
                    if(!selectedImage.dilateImage())
                    {
                        errorAlert.open();
                    }
                }
            }

            Button{
                text: "Canny"
                onClicked:{
                    if(!selectedImage.applyCanny())
                    {
                        errorAlert.open();
                    }
                }
            }

            Button{
                text: "H Lines"
                onClicked:{
                    if(!selectedImage.findHorizontalLines())
                    {
                        errorAlert.open();
                    }
                }
            }

            Button{
                text: "V Lines"
                onClicked:{
                    if(!selectedImage.findVerticalLines())
                    {
                        errorAlert.open();
                    }
                }
            }

            Button{
                text: "Laplacian"
                onClicked:{
                    if(!selectedImage.laplacianFilter())
                    {
                        errorAlert.open();
                    }
                }
            }

            Button{
                text: "Go Back"
                onClicked: loader.pop()
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

    Dialog
    {
        id: errorAlert
        title: "error"
        Text{
            text: "Please open an Image"
        }

        standardButtons: StandardButton.Ok
    }

}
