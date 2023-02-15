import QtQuick 2.15

//Item



Rectangle {
    id : mainBlock
    function setActive(idx)
    {
        return idx ? "red" : "white"
    }
    property int columnWidth : 6
    property var clock

    Row{

        width: parent.width
        height: parent.height
        Column
        {
            width: parent.width / columnWidth
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/4
                    color : setActive(clock.binaryHour[index])
                }
            }
        }
        Column
        {
            width: parent.width / columnWidth
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/4
                    color : setActive(clock.binaryHour[4+index])
                }
            }
        }
        Column
        {
            width: parent.width / columnWidth
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/4
                    color : setActive(clock.binaryMinute[index])
                }
            }
        }
        Column
        {
            width: parent.width / columnWidth
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/4
                    color : setActive(clock.binaryMinute[4+index])
                }
            }
        }
        Column
        {
            width: parent.width / columnWidth
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/4
                    color : setActive(clock.binarySecond[index])
                }
            }
        }
        Column
        {
            width: parent.width / columnWidth
            height: parent.height
            Repeater
            {
                model:4
                Rectangle
                {
                    width: parent.width
                    height: parent.height/4
                    color : setActive(clock.binarySecond[4+index])
                }
            }
        }
    }

}
