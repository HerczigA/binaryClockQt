import QtQuick
import QtQuick.Layouts
import "./components/binaryClock"

Window {

    width: mainApp.width
    height: mainApp.height
    visible: true
    visibility: "FullScreen"
    title: qsTr("Do It, YOU can do IT")

    Row{
        width: parent.width
        height: parent.height
      Rectangle{
          width: parent.width /2
          height: parent.height
      }
      BinaryClock
      {
          clock: mainApp.binClock
          width: parent.width /2
          height: parent.height
      }
    }



}
