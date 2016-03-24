import QtQuick 2.2
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
                clip: true
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
        id: paramsTable
        anchors.fill: parent

        model: ListModel {
            id: paramsModel
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

            delegate: TextField {
                Layout.fillWidth: true
                inputMethodHints: Qt.ImhNoPredictiveText
                text: model.value

                onTextChanged: paramsModel.setProperty(index, "value", text)
            }
        }
    }

    function populateArgsModel()
    {
        var params = methodItem.name.match(/\(.*?\)/)[0].split("")
        params = params.slice(1, params.length - 1)
        for (var i = 0; i < params.length; ++i)
        {
            if(params[i] == "s")
            {
                paramsModel.append({ "parameter": "arg"+i, "type": "String", "value": "" })
            }
        }
    }

    function paramsFromModel()
    {
        var args = []
        for (var i = 0; i < paramsModel.count; ++i)
        {
            args.push(paramsModel.get(i).value)
        }

        return args;
    }
}
