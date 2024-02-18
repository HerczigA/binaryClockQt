import QtQuick 2.15
import "../components/binaryClock"
import "../components/weatherForecast"

Item {
    property var mainAppData
    id: firstPage
    Image {
        id: woodImg
        source: "/img/wood_surface.jpg"
        width: parent.width
        height : parent.height
    }
    Row
    {
        width : parent.width
        height: parent.height
        WeatherForecast{
            width: parent.width /2
            height: parent.height
            weather: mainAppData.weather
            color: "transparent"
        }

        BinaryClock
        {
          clock: mainAppData.binClock
          width: parent.width /2
          height: parent.height
        }
    }
}
