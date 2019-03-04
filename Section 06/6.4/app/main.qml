import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("App")

    StackView{
        id: loader
        anchors.fill: parent
        initialItem: "qrc:/home"
    }
}
