import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
	id: root
	property var parentSize: width > height ? height : width
	signal onOptionChosen(int index)

	Rectangle {
		anchors.fill: parent
		color: "#3b4252"
	}
	
	ColumnLayout {
		id: layout
		anchors.fill: parent

		Image {
			id: logoImage
			source: "qrc:/Resources/Logo512.png"
			Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
			Layout.preferredWidth: parentSize / 3
			Layout.preferredHeight: width
			Layout.margins: parentSize / 20
		}
		Text {
			visible: false
			id: questionText
			Layout.fillWidth: true
			Layout.margins: parentSize / 20
			font.pixelSize: 26
			wrapMode: Text.WordWrap
			fontSizeMode: Text.Fit
			horizontalAlignment: Qt.AlignHCenter
			color: "#eceff4"
		}
		ScrollView {
			id: optionsScrollView
			visible: false
			clip: true
			Layout.alignment: Qt.AlignHCenter
			Layout.fillWidth: true
			Layout.fillHeight: true
			ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
			ScrollBar.vertical.policy: ScrollBar.AlwaysOn
			
			ListView {
				Rectangle {
					color: "black"
					width: parent.width
					height: 2
				}
				
				id: listView
				boundsBehavior: Flickable.StopAtBounds
				model: optionsModel
				delegate: OptionButton {}
			}
		}
	}
	
	ListModel {
		id: optionsModel
	}
			
	NumberAnimation {
		id: appearAnimation
		targets: [questionText, optionsScrollView]
		properties: "opacity"
		from: 0
		to: 1
		duration: 1000
	}
	
	function askUser(questionStr, optionsStrList) {
		questionText.text = questionStr
		for (var i = 0; i < optionsStrList.length; ++i)
		{
			optionsModel.append({
				"optionIndex": i,
				"optionText": optionsStrList[i]
			});
		}
		logoImage.visible = true
		questionText.visible = true
		optionsScrollView.visible = true
		appearAnimation.running = false
		appearAnimation.running = true
	}
	
	function onOptionButtonClick(index) {
		optionsModel.clear()
		logoImage.visible = false
		questionText.visible = false
		optionsScrollView.visible = false
		onOptionChosen(index)
	}
}
