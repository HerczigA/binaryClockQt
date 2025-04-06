import QtQuick 2.15
import QtQuick.Layouts
import "qrc:/qml/Components" as Components
import "qrc:/qml/Utilities" as Utilities
import MainApp.qmlcomponents 1.0

Item {
    id: firstPage
    property var mainAppData
    Image {
        id: woodImg
        source: "qrc:/img/wood_surface.jpg"
        width: parent.width
        height: parent.height
    }

    Utilities.SlideDownWindow {
        id: slideDownWindow
        model: mainAppData.binClock
    }

    MouseArea {
        id: firstPageMouseArea
        anchors.fill: parent
        enabled: slideDownWindow.isOpened
        onClicked: {
            if (slideDownWindow.isOpened) {
                slideDownWindow.isOpened = false
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: firstPage.height / 12
            Layout.topMargin: 50
            DateHelper {
                id: dateHelper
            }
            Text {
                id: dateText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: dateHelper
                      && dateHelper.date !== "" ? Qt.formatDate(
                                                      dateHelper.date,
                                                      "yyyy/M/d") : "--"
                color: "white"
                font {
                    bold: true
                    family: "Helvetica"
                    pixelSize: 100
                }
            }
            Components.WeatherForecast {
                Layout.fillWidth: true
                Layout.fillHeight: true
                weather: mainAppData.weather
            }
            Text {
                id: locationSection
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: mainAppData.weather
                      && mainAppData.weather.location ? mainAppData.weather.location : "N/A"
                color: "white"
                font {
                    bold: true
                    pixelSize: 70
                }
            }
        }
        Connections {
            target: mainAppData.binClock
            function onTurnNewDay() {
                dateHelper.updateDate()
            }
        }
    }
}
