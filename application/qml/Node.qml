import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: currentNode
    property var node

    color: "lightblue"
    clip: true

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
