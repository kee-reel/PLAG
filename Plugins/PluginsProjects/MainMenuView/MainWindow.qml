import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "white"

    Slider {
        id: slide
        width: parent.width
        enabled: true
        value: 0
        minimumValue: 0
        maximumValue: 360
        onValueChanged: {
            rect.rotation = slide.value;
        }
    }

    Rectangle {
        id: rect
        width: parent.width / 3
        height: parent.height / 3
        anchors.centerIn: parent

        color: "#a5ffe9"
        border.color: "black"
        border.width: 3

        Rectangle {
            x: 30
            anchors.centerIn: parent.Center
            width: parent.width / 3
            height: parent.width / 3
            radius: width * 0.5

            color: "#a5c7e9"
            border.color: "black"
            border.width: 3
        }
    }

}
