import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3


ColumnLayout {
    property var toolBar: ToolBar {
        Text {
            text: "Discovered nodes"
            font.bold: true
            font.pixelSize: 36
            height: 40
        }
    }

    GridView
    {
        id: grid

        Layout.fillHeight: true
        Layout.fillWidth: true

        cellHeight: 140
        cellWidth: width / Math.max(1, Math.floor(grid.width/340.0))

        model: presentNodes

        delegate: Node {
            node: model.node
            width: grid.cellWidth - 40
            height: grid.cellHeight - 20
        }
    }
}
