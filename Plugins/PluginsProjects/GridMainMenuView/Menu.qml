import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

MenuForm {
    anchors.fill: parent

    button.onHoveredChanged: button.text = button.hovered ? "Hover" : "Nope"
    button.onPressAndHold: button.text = "Pressed"
}
