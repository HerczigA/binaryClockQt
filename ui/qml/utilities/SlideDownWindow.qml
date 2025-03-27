import QtQuick
import "qrc:/qml/Components" as Components

Rectangle {
        id: newRectangle

        property alias triggerButtomHeight:topButton.height
        property int duration : 0

        property var model

//        property var loaderSourceComponent

        width: parent.width/2
        anchors.right:parent.right
        height: parent.height - topButton.height
        color: "#33FFFFFF"
        border.color: "#88FFFFFF"
        border.width: 1
        y: -height

        Rectangle {
            id: topButton
            width: parent.width /20
            height: 50
            color: "#e7e2e1"
            radius: {
                bottomLeft:10
                bottomRight:10
            }

            anchors.top: parent.bottom
            anchors.topMargin: -20

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (newRectangle.y === 0) {
                        slideUpAnimation.start()
                    }
                    else {
                        slideDownAnimation.start()
                    }
                }
            }
        }
        Components.BinaryClock{
            implicitWidth : parent.width
            implicitHeight: parent.height
            color: "transparent"
            clock: model
        }

        /*Loader{
            id: loader
            property var sourceComponent
            anchors.centerIn: parent
            sourceComponent: Components.BinaryClock{
                implicitWidth : parent.width
                implicitHeight: parent.height
                color: "transparent"
                clock: model
            }
        }*/

       SequentialAnimation {
            id: slideDownAnimation
            PropertyAnimation {
                target: newRectangle
                property: "y"
                from: -newRectangle.height
                to: 0
                duration: duration ? duration: 1000
                easing.type: Easing.InOutQuad
            }
        }

        SequentialAnimation {
            id: slideUpAnimation
            PropertyAnimation {
                target: newRectangle
                property: "y"
                from: 0
                to: -newRectangle.height
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }

}
