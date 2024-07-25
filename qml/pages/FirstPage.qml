import QtQuick 2.15
import QtQuick.Layouts

Item {
    id: firstPage
    property var mainAppData
    Image {
        id: woodImg
        source: "/img/wood_surface.jpg"
        width: parent.width
        height : parent.height
    }
    RowLayout
    {
        anchors.fill: parent
        WeatherForecast{
            Layout.fillWidth: true
            Layout.fillHeight: true
            weather: mainAppData.weather
            color: "transparent"
        }
        BinaryClock
        {
          clock: mainAppData.binClock
          Layout.preferredWidth: parent.width /2
          Layout.fillHeight: true
        }
    }
}
