import QtQuick
import QtQuick.Layouts
import "./binaryClock" as BinClock

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Do It, YOU can do IT")

    BinClock.BinaryClock
    {
        clock: mainApp.binClock
        width: parent.width
        height: parent.height
    }

}
