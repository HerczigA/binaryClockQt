import QtQuick
import QtQuick.Layouts
import "./components/binaryClock"
import "./components/weatherForecast"

Window {
    id: mainWindow
    width: mainApp.width
    height: mainApp.height
    visible: true
    visibility: "FullScreen"
    title: qsTr("Do It, YOU can do IT")
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
            weather: mainApp.weather
            color: "transparent"
        }

        BinaryClock
        {
          clock: mainApp.binClock
          width: parent.width /2
          height: parent.height
        }
    }


}
