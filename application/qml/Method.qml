import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    property string name
    property var node

    width: parent.width
    height: Math.max(btn.height, txt.contentHeight)

    RowLayout {
        anchors.fill: parent

        Button {
            id: btn
            height: 20
            width: 20
            text: ">"
            onClicked: {
                var args = [];

                if(name.indexOf("(s)") >= 0)
                {
                    args = ["XXX"];
                }

                var ret = node.callInterfaceMethod(name, args);
                toast.show("Method returned:\n"+ret)
            }
        }

        Text {
            id: txt
            text: name
            font.pixelSize: 20
        }
    }
}

