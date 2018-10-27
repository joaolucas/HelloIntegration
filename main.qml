import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Integration World")

    Column{
        Text {         
            text: qsTr("Hello New World")
        }
        Button{
            text : "Change Text"
            onClicked: messageClass.doMessageChange()
        }
    }
}
