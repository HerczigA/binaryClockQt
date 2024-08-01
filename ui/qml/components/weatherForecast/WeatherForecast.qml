import QtQuick 2.15
import QtQuick.Layouts
Rectangle {
    id: weatherForecastRoot
    property var weather
    ColumnLayout
    {
        anchors.fill: weatherForecastRoot
        Text{
            id: dateText
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: weather && weather.date ? weather.date: "--"  
            color: "white"
            font{
                bold: true
                family: "Helvetica"
                pixelSize: 100
            }
        }
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
                source: weather && weather.icon ? weather.icon : ""
                height: weatherIconRectangle.height
                width: weatherIconRectangle.height
            }
        }
        Text{
            id:locationSection
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: weather && weather.location ? weather.location : ""
            color: "white"
            font{
                bold: true
                pixelSize: 70
            }
        }
    }
}
