import QtQuick 2.15
import QtQuick.Layouts
import "qrc:/qml/Components/" as Components

Item {
    id: weatherForecastRoot
    property var weather
    ColumnLayout
    {
        anchors.fill: weatherForecastRoot
        Rectangle
        {
            id: temperatureRectangle
            color: "transparent"
            Layout.preferredHeight: weatherForecastRoot.height/20*6
            Layout.preferredWidth: weatherForecastRoot.width
            TapHandler
            {
                onDoubleTapped: weather.requestDataFromUI()
            }
            MouseArea
            {
                id: clickHandler
                onDoubleClicked: weather.requestDataFromUI()
            }
            Text{
                id: temperatureSection
                anchors.centerIn: temperatureRectangle
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text:  weather && weather.temperature && qsTr(weather.temperature) !== "" ?  qsTr(weather.temperature + " °C"): "N/A"
                color: "white"
                font{
                    pixelSize: temperatureRectangle.height /5 * 4
                }
            }
        }
        Rectangle
        {
            id: weatherIconRectangle
            color: "transparent"
            Layout.preferredHeight: weatherForecastRoot.height/20*4
            Layout.preferredWidth: weatherForecastRoot.width
            Image {
                id: weatherIcon
                anchors.centerIn: parent
                source: weather && weather.icon ? weather.icon : "qrc:/img/errorIcon.png"
                height: weatherIconRectangle.height
                width: weatherIconRectangle.height
            }
        }
    }
}
