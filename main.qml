import QtQuick
import QtQuick.Layouts
import "./components/binaryClock"

Window {
    id: mainWindow
    width: mainApp.width
    height: mainApp.height
    visible: true
    visibility: "FullScreen"
    title: qsTr("Do It, YOU can do IT")
    Image {
        id: woodImg
        source: "wood_surface.jpg"
        width: parent.width
        height : parent.height
    }
    Row
    {
        width : parent.width
        height: parent.height
        Rectangle{
            width: parent.width /2
            height: parent.height
            Text{
                anchors.centerIn: parent
                text: "Here will be a weather forecast"
            }
            color : "transparent"
        }

        BinaryClock
        {
          clock: mainApp.binClock
          width: parent.width /2
          height: parent.height
        }
    }


}
