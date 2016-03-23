import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    property string name
    property var node

    id: methodItem

    width: parent.width
    height: Math.max(btn.height, txt.contentHeight)

    function execute()
    {
        var args = [];

        if(name.match(/\(.*?\)/)[0].length > 2)
        {
            stack.push(methodCall);
        } else {
            executeWithArgs(args);
        }
    }

    function executeWithArgs(args)
    {
        var ret = node.callInterfaceMethod(name, args);
        if(ret)
        {
            toast.show("Method returned:\n"+ret)
        }
    }

    RowLayout {
        anchors.fill: parent

        Button {
            id: btn
            height: 20
            width: 20
            text: ">"
            onClicked: methodItem.execute()
        }

        Text {
            id: txt
            text: name
            font.pixelSize: 20
        }
    }

    Loader {
        Component {
            id: methodCall

            MethodCall {
                method: methodItem
            }
        }
    }
}

