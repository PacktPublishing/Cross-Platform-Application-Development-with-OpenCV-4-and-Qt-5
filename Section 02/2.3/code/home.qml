import QtQuick 2.0
import QtQuick.Controls 2.2

Page {

    Rectangle{
        id: bar
        width: parent.width
        height: parent.height * 0.1
        color: "orange"

        Label{
            text: "Welcome to the Qt OpenCV app"
            color: "white"
            anchors.centerIn: parent
        }
    }

    Button{
        text: "Show Image"
        onClicked: loader.push("qrc:/showImage")
        anchors.top: bar.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: bar.horizontalCenter
    }

}
