import QtQuick 2.15
import QtQuick.Layouts
import "qrc:/qml/Components/" as Components

Item {
    id: firstPage
    property var mainAppData
    Image {
        id: woodImg
        source: "qrc:/img/wood_cranny.jpg"
        width: parent.width
        height : parent.height
    }
    RowLayout
    {
        anchors.fill: parent
        Components.WeatherForecast{
            Layout.fillWidth: true
            Layout.fillHeight: true
            weather: mainAppData.weather
            color: "transparent"
        }
        Components.BinaryClock
        {
          clock: mainAppData.binClock
          Layout.preferredWidth: parent.width /2
          Layout.fillHeight: true
          color: "transparent"
        }
    }
}
