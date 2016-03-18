import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    property var node

    id: nodeDetails

    ColumnLayout {
        anchors.fill: parent

        Text {
            Layout.fillWidth: true
            text: node.name
        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: node.methods

            delegate: Method {
                name: modelData
                node: nodeDetails.node
            }
        }

        Button {
            text: "Exit"
            onClicked: {
                stack.pop()
            }
        }
    }
}
