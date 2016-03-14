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
            delegate: Item {
                width: parent.width
                height: 30

                Button {
                    anchors.right: txt.left
                    height: txt.height
                    width: 20
                    text: ">"
                    onClicked: {
                        var method = modelData;
                        var args = [];

                        if(method.indexOf("(s)") >= 0)
                        {
                            args = ["XXX"];
                        }

                        var ret = node.callInterfaceMethod(method, args);
                        console.log(ret);
                    }
                }
                Text {
                    id: txt
                    text: modelData
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                }
            }
        }
    }
}
