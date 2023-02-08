import QtQuick
import QtQuick.Layouts
import "./binaryClock" as BinClock

Window {

    width: mainApp.width
    height: mainApp.height
    visible: true
    visibility: "FullScreen"
    title: qsTr("Do It, YOU can do IT")


    BinClock.BinaryClock
    {
        clock: mainApp.binClock
        width: parent.width
        height: parent.height
    }

}
