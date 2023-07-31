import QtQuick 2.15
import QtQuick.Controls 2.15


Switch {
    id: control
    text: qsTr("Switch")


    indicator: Rectangle {
        implicitWidth: 48
        implicitHeight: 26
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#17a81a" : "#ffffff"
        border.color: control.checked ? "#17a81a" : "#cccccc"

        Rectangle {
            x: control.checked ? parent.width - width : 0
            width: 26
            height: 26
            radius: 13
            color: control.down ? "#cccccc" : "#ffffff"
            border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
        }
    }

    contentItem: Text {
        anchors{
            //left: parent.left
            top : control.bottom
        }
        //anchors.centerIn: parent
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: "#17a81a"
        verticalAlignment: Text.AlignVCenter
        //horizontalAlignment :Text.AlignHCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
