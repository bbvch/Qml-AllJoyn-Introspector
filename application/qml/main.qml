import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Window {
    id: mainWindow

    visible: true
    minimumWidth:  800
    minimumHeight: 600

    ListView
    {
        anchors.fill: parent
        model: presentNodes

        delegate: ListView {
            width: parent.width
            height: contentHeight


            header: Text {
                text: name + " (" + methods.length + ")"
                font.bold: true
                font.pointSize: 20
            }

            model: methods
            delegate: Text {
                text: modelData
                width: parent.width - 20
                anchors.right: parent.right
                font.pointSize: 14
            }
        }
    }
}
