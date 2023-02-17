import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id : mainBlock
    function setActive(idx, color)
    {
        //matt red
        return idx ? color : "white"
    }
    property int blockWidthRate : 6
    property int blockHeightRate : 4
    property var clock
    property var type
    property string colorBlue : "#1B3D81"
    property string colorHour : "#B33F40"
    property string colorMinute : "#E9740E"
    property string colorSecond : "#4ABA31"
    //metalblue
    color : colorBlue

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
                    color : setActive(clock.binaryHour[index], colorHour)
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
                    color : setActive(clock.binaryHour[4+index], colorHour)
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
                    color : setActive(clock.binaryMinute[index], colorMinute)
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
                    color : setActive(clock.binaryMinute[4+index], colorMinute)
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
                    color : setActive(clock.binarySecond[index], colorSecond)
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
                    color : setActive(clock.binarySecond[4+index], colorSecond)
                    radius: parent.width/2
                }
            }
        }
    }

}
