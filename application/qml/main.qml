import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3


ApplicationWindow {
    id: mainWindow

    visible: true
    width: 800
    height: 600
    toolBar: stack.currentItem.toolBar


    StackView {
        id: stack
        anchors.fill: parent
        initialItem: nodes

        Component {
            id: nodes

            NodesList { }
        }

        delegate: StackViewDelegate {
            function transitionFinished(properties)
            {
                properties.exitItem.opacity = 1
            }

            pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "opacity"
                    from: 0
                    to: 1
                }
                PropertyAnimation {
                    target: exitItem
                    property: "opacity"
                    from: 1
                    to: 0
                }
            }
        }
    }

    Component.onCompleted: {
        toast.show("Application started")
    }

    Toast {
        id: toast
    }
}
