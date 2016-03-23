import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1


Item {
    property var method: methodItem
    property var toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent

            ToolButton {
                text: "< Back"
                onClicked: stack.pop()
            }

            Text {
                Layout.fillWidth: true
                text: method.name
                font.bold: true
                font.pixelSize: 20
            }

            ToolButton {
                Layout.alignment: Qt.AlignRight
                text: "Execute"
                onClicked: {
                    var args = paramsFromModel();
                    method.executeWithArgs(args);
                    stack.pop();
                }
            }
        }
    }

    Component.onCompleted: {
        populateArgsModel()
    }

    TableView {
        anchors.fill: parent

        model: ListModel {
            id: model
        }

        TableViewColumn {
            role: "parameter"
            title: "Parameter"
            width: 100
            horizontalAlignment: Qt.AlignRight
        }

        TableViewColumn {
            role: "type"
            title: "Type"
            width: 80
            horizontalAlignment: Qt.AlignCenter
        }

        TableViewColumn {
            role: "value"
            title: "Value"
            width: 200
            resizable: true
            horizontalAlignment: Qt.AlignLeft

            delegate: TextEdit {
                Layout.fillWidth: true
                text: model.value

                onTextChanged: model.value = text
            }
        }
    }

    function populateArgsModel()
    {
        var params = methodItem.name.match(/\(.*?\)/)[0].split("")
        params = params.slice(1, params.length - 1)
        for (var i =0; i < params.length; ++i)
        {
            if(params[i] == "s") {
                model.append({ "parameter": "arg"+i , "type": "String", "value": "" })
                console.log("arg"+i)
            }
        }
    }

    function paramsFromModel()
    {
        var args = []
        for (var i =0; i < model.count; ++i)
        {
            args.push(model.get(i).value)
        }

        return args;
    }
}
