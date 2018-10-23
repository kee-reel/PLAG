import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400
    property alias button: button

    Button {
        id: button
        x: 150
        y: 110
        text: qsTr("Button")
        autoRepeat: false
        checked: false
        checkable: false
        highlighted: false
    }

    Connections {
        target: button1
        onClicked: print("clicked")
    }

}
