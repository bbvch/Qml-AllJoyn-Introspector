import QtQuick 2.0

Rectangle {
    id: container

    anchors.margins: 20
    radius: 30
    border.color: "black"
    border.width: 2
    color: "white"
    clip: true
    visible: opacity > 0
    opacity: 0

    anchors.right: parent.right
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    height: Math.min(displayedText.contentHeight + 40, parent.height - 40)
    width: parent.width

    SequentialAnimation on opacity {
        id: animation
        running: false

        NumberAnimation {
            to: 0.7
            duration: 100
        }

        PauseAnimation {
            duration: 3000
        }

        NumberAnimation {
            to: 0
            duration: 500
        }
    }

    function show(text)
    {
        displayedText.text = text
        console.log(text);
        animation.start()
    }

    Text {
        id: displayedText
        anchors.fill: parent
        anchors.margins: 20
        wrapMode: Text.WordWrap
        clip: true
    }
}
