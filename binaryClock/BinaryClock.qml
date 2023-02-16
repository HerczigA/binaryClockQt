import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id : mainBlock
    function setActive(idx)
    {
        //matt red
        return idx ? "#B33F40" : "white"
    }
    property int blockWidthRate : 6
    property int blockHeightRate : 4
    property var clock
    property var type
    //metalblue
    color : "#1B3D81"
    RowLayout{
        width: parent.width
        height: parent.height
        Column
        {
            width: parent.width / blockWidthRate
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/blockHeightRate
                    color : setActive(clock.binaryHour[index])
                    radius: parent.width/2
                }
            }
        }
        Column
        {
            width: parent.width / blockWidthRate
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/blockHeightRate
                    color : setActive(clock.binaryHour[4+index])
                    radius: parent.width/2
                }
            }
        }
        Column
        {
            width: parent.width / blockWidthRate
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/blockHeightRate
                    color : setActive(clock.binaryMinute[index])
                    radius: parent.width/2
                }
            }
        }
        Column
        {
            width: parent.width / blockWidthRate
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/blockHeightRate
                    color : setActive(clock.binaryMinute[4+index])
                    radius: parent.width/2
                }
            }
        }
        Column
        {
            width: parent.width / blockWidthRate
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/blockHeightRate
                    color : setActive(clock.binarySecond[index])
                    radius: parent.width/2
                }
            }
        }
        Column
        {
            width: parent.width / blockWidthRate
            height: parent.height

            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/blockHeightRate
                    color : setActive(clock.binarySecond[4+index])
                    radius: parent.width/2
                }
            }
        }
    }

}
