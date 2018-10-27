import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Integration World")


//    Connections{
//        target: messageClass
//        onMessageChanged: textId.text = value;
//    }

    Column{
        Text {
            id: textId
            //text: qsTr("Hello New World")
            text: messageClass.message
        }
        Button{
            text : "Change Text"
            onClicked: messageClass.doMessageChange()
        }
        Button{
            text : "Two way"
            onClicked: {
                var result = messageClass.sendMessageFromCpp("Lucas");
                print ("The Cpp file tell me: "+ result)
            }
        }
    }
}
