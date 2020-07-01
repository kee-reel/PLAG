import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
	anchors.horizontalCenter: parent.horizontalCenter
	width: parent.width * 0.8
	height: 100
	Button {
		anchors.fill: parent
		anchors.leftMargin: parent.width * 0.1
		anchors.rightMargin: parent.width * 0.1
		anchors.topMargin: parent.height * 0.1
		anchors.bottomMargin: parent.height * 0.1
		onClicked: root.onOptionButtonClick(optionIndex)
		
		background: Rectangle {
			color: parent.pressed ? "#88c0d0" : "#81a1c1"
			radius: 10
		}
		Text {
			id: itemName
			anchors.fill: parent
			text: optionText
			font.pixelSize: 28
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			color: "#eceff4"
			fontSizeMode: Text.VerticalFit
			wrapMode: Text.Wrap
		}
	}
}
