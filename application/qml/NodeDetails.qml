import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    property var node

    id: nodeDetails

    property var toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent

            ToolButton {
                text: "< Back"
                onClicked: {
                    stack.pop()
                }
            }

            Text {
                Layout.alignment: Qt.AlignRight

                text: node.name
                font.bold: true
                font.pixelSize: 36
                height: 40
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "#ccddff"

            ColumnLayout {
                anchors.fill: parent

                Text {
                    text: "Methods"
                    font.pixelSize: 30
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
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "#aabbff"

            ColumnLayout {
                anchors.fill: parent

                Text {
                    text: "Properties"
                    font.pixelSize: 30
                }

                ListView {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: node.propertyNames

                    delegate: Text {
                        text: modelData + ": " + node.properties[modelData]
                    }
                }
            }
        }
    }
}
