import QtQuick 2.0
import QtQuick.Layouts 1.1


ColumnLayout {
    Text {
        id: title
        Layout.fillWidth: true

        text: "Discovered nodes"
        font.bold: true
        font.pixelSize: 36
        height: 40
    }

    GridLayout
    {
        Layout.fillHeight: true
        Layout.fillWidth: true

        columnSpacing: 10
        rowSpacing: 10

        Repeater {
            model: presentNodes

            delegate: Node {
                node: model.node
                width: 340
                height: 180
            }
        }
    }
}
