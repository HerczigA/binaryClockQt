import QtQuick 2.15

//Item



Rectangle {
    id : mainBlock
//    LayoutMirroring.enabled : True
    function setActive(idx)
    {
        return idx ? "red" : "white"
    }
    property var clock;

    Row{

        width: parent.width
        height: parent.height


        Column
        {
//            LayoutMirroring.enabled : true
            width: parent.width /2
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
        Column
        {

            width: parent.width /2
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
    }

}
