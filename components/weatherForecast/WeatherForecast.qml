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
            id: dateRectangle
            width : root.width
            height : root.height /4
            color : "transparent"
            Text{

                height : parent.height
                id : dateSection
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text : weather.date
                color : "white"
                padding: parent.height/10
                font{
                    bold : true
                    family : "Helvetica"
                    pixelSize : dateRectangle.height/5*3
                }

            }

        }
        Rectangle
        {
            id: temperatureRectangle
            color : "transparent"
            height : root.height /2
            width : root.width
            Text{
                id :temperatureSection
                height : parent.height
                width : parent.width
                anchors.centerIn: temperatureRectangle
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text : qsTr(weather.temperature)
                color : "white"
                font{
                    pixelSize : parent.height/5*3
                }
            }
//            Image {
//                id: name
//                source: weather.icon
//            }
        }

        Rectangle
        {
            id: locationRectangle
            height : root.height /4
            width : root.width
            color : "transparent"
            Text{
                id :locationSection
                height : parent.height
                width : parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text : qsTr(weather.location)
                color : "white"
                font{
                    bold : true
                    pixelSize : parent.height/5*2
                }
            }
        }
    }


}
