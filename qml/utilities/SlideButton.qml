import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle
{
    id:rootSlideButton
    property bool switchState : false
    property int rotateAngle : 0
    property string colorOn : "green"
    property string colorOff : "grey"
    implicitWidth: 100
    implicitHeight: 50
    radius: rootSlideButton.height
    color: colorOff
    border.width: 2
    Rectangle
    {
        id: circle
        implicitWidth: rootSlideButton.height
        implicitHeight: rootSlideButton.height - 4
        radius: rootSlideButton.height
        x: 2
        y: 2
    }
    onSwitchStateChanged:
    {
        rootSlideButton.state = rootSlideButton.switchState ? "ON" : "OFF";
    }
    MouseArea
    {
        anchors.fill: parent
        onPressed: 
        {
            rootSlideButton.switchState = !rootSlideButton.switchState
        }
    }
    states: [
        State{
            name: "ON"
            PropertyChanges{ target: circle; x: rootSlideButton.width -implicitHeight -6}
            PropertyChanges{ target: rootSlideButton; color: colorOn  }
        },
        State{
            name: "OFF"
            PropertyChanges{ target: circle; x: 2}
            PropertyChanges{ target: rootSlideButton; color: colorOff  }
        }
    ]
    transitions: Transition {
        NumberAnimation{ properties: "x"; easing.type:Easing.InOutQuad}
    }
    transform: Rotation{ angle: rootSlideButton.rotateAngle}
}
