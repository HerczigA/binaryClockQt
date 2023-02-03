import QtQuick 2.15

//Item



Rectangle {
    id : mainBlock
    function setActive(idx)
    {
        return idx ? "red" : "white"
    }
    property var clock;
    color : "red"
    Row{
        width: parent.width
        height: parent.height
        Column{
            width: parent.width /6
            height: parent.height
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[7])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[6])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[5])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[4])
            }
        }
        Column{
            width: parent.width /6
            height: parent.height
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[3])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[2])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[1])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryHour[0])
            }
        }        Column{
            width: parent.width /6
            height: parent.height
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[7])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[6])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[5])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[4])
            }
        }
        Column{
            width: parent.width /6
            height: parent.height
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[3])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[2])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[1])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binaryMinute[0])
            }
        }        Column{
            width: parent.width /6
            height: parent.height
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[7])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[6])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[5])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[4])
            }
        }
        Column{
            width: parent.width /6
            height: parent.height
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[3])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[2])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[1])
            }
            Rectangle
            {
                width: parent.width
                height: parent.height/4
                color : setActive(clock.binarySecond[0])
            }
        }


    }
}
