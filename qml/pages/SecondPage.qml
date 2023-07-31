import QtQuick 2.15
import "../components/wateringSystem"

Item {
    property var mainAppData

    id: rootSecondPage
    /*Image {
        id: woodImg
        source: "/img/wood-grain.jpg"
        width: parent.width
        height : parent.height
    }*/

    WateringSystem{
        wateringSystem: mainAppData
        width : mainAppData.width
        height : mainAppData.height
        color: "#436175"
    }
}
