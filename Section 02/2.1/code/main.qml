import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle{
        id: rect
        width:100
        height:100
        color: "red"
        anchors.centerIn: parent
    }

    Text{
        id: text1
        text: "Hello World"
        anchors.centerIn: rect
    }

    Button{
        text: "click me"
        anchors.top: rect.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: rect.horizontalCenter
        onClicked: text1.text = "Hello Again"
    }

    Button{
        text: "load"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: loader.push("qrc:/view")
    }

    StackView{
        id: loader
        anchors.fill: parent
    }
}
