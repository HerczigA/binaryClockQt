import QtQuick 2.15

Rectangle {
    id : root
    property var weather
    Column
    {
        width : root.width
        height : root.height
        Rectangle
        {
            width : root.width
            height : root.height /4
            color : "transparent"
            Text{

                height : parent.height
                id : dateSection
                anchors.centerIn: parent
                text : weather.date
                color : "white"
                padding: parent.height/10
                font{
                    bold : true
                    family : "Helvetica"
                    pixelSize : 40
                }

            }

        }
        Rectangle
        {
            color : "transparent"
            height : root.height /2
            width : root.width
        }

        Rectangle
        {
            height : root.height /4
            width : root.width
            color : "transparent"
            Text{
                id :locationSection
                height : parent.height
                width : parent.width
                anchors.centerIn: parent
                text : weather.location
                color : "white"
                font{
                    bold : true
                    pixelSize : 40
                }
            }
        }
    }


}
