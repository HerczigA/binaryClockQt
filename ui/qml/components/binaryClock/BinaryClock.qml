import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id: mainBlock
    function setActive(idx, color)
    {
        return idx ? color: "white"
    }
    function setCircleProperty()
    {
        return  mainBlock.height < mainBlock.width? mainBlock.height/4 - mainBlock.spaceSize*2 : mainBlock.width /6 - mainBlock.spaceSize*2
    }
    property int blockWidthRate: 6
    property int blockHeightRate: 4
    property var clock
    property string colorBlue: "#1B3D81"
    property string colorHour: "#B33F40"
    property string colorMinute: "#E9740E"
    property string colorSecond: "#4ABA31"
    property int spaceSize: 5

    GridLayout
    {
        id: grid
        width: parent.width
        height: parent.height
        columns: 6
        rows: 4
        columnSpacing: spaceSize
        rowSpacing: spaceSize
        flow: GridLayout.TopToBottom
        Repeater
        {
            model: clock.binaryHour
            Rectangle
            {
                Layout.maximumWidth: setCircleProperty()
                Layout.maximumHeight: setCircleProperty()
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.leftMargin: spaceSize
                Layout.rightMargin: spaceSize
                border{
                    width: 5
                    color: "black"
                }
                color: setActive(clock.binaryHour[index], colorHour)
                radius: width /2
            }
        }
        Repeater
        {
            model:clock.binaryMinute
            Rectangle
            {
                Layout.maximumWidth: setCircleProperty()
                Layout.maximumHeight: setCircleProperty()
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.leftMargin: spaceSize
                Layout.rightMargin: spaceSize
                color: setActive(clock.binaryMinute[index], colorMinute)
                border{
                    width: 5
                    color: "black"
                }
                radius: width /2
            }
        }
        Repeater
        {
            model:clock.binarySecond
            Rectangle
            {
                Layout.maximumWidth: setCircleProperty()
                Layout.maximumHeight:  setCircleProperty()
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.leftMargin: spaceSize
                Layout.rightMargin: spaceSize
                border{
                    width: 5
                    color: "black"
                }
                color:  setActive(clock.binarySecond[index], colorSecond)
                radius: width /2
            }
        }
    }
}
