import QtQuick 2.0

Item{
    property rect myRect1 : Qt.rect(50,50,100,100)
    property rect myRect2 : "50,50,100x100"

    property size mySize1: Qt.size(10,20)
    property size mySize2: "10x20"

    property point myPoint1: Qt.point(30,40)
    property point myPoint2: "30,40"
}

