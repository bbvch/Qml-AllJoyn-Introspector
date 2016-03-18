import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Rectangle {
    id: currentNode
    property var node

    radius: 20
    color: "#8899ff"

    Rectangle {
        clip: true
        radius: 16

        width: parent.width - 10
        height: parent.height - 10
        anchors.centerIn: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ccddff" }
            GradientStop { position: 1.0; color: "#aabbff" }
        }

        ColumnLayout {
            Text {
                text: node.name
                font.pointSize: 16
            }
            Text {
                text: node.methods.length + " methods"
                font.pointSize: 12
            }
            Text {
                text: node.propertyNames.length + " properties"
                font.pointSize: 12
            }
        }

        Component {
            id: nodeDetails

            NodeDetails {
                node: currentNode.node
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                stack.push(nodeDetails)
            }
        }
    }
}
