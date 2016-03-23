import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3


ColumnLayout {
    property var toolBar: null

    Text {
        id: title
        Layout.fillWidth: true

        text: "Discovered nodes"
        font.bold: true
        font.pixelSize: 36
        height: 40
    }

    GridView
    {
        id: grid

        Layout.fillHeight: true
        Layout.fillWidth: true

        cellHeight: 140
        cellWidth: 340

        model: presentNodes

        delegate: Node {
            node: model.node
            width: 300
            height: 120
        }
    }
}
