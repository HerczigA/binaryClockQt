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
        height : parent.height
    }

    Utilities.SlideDownWindow{
        model: mainAppData.binClock
    }


    RowLayout
    {
        anchors.fill: parent
        ColumnLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: firstPage.height/12
            Layout.topMargin: 50
            DateHelper {
                id: dateHelper
            }
            Text{
                id: dateText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text:dateHelper && dateHelper.date !== "" ? Qt.formatDate(dateHelper.date, "yyyy/M/d") : "--"
                color: "white"
                font{
                    bold: true
                    family: "Helvetica"
                    pixelSize: 100
                }
            }
            Components.WeatherForecast{
                Layout.fillWidth: true
                Layout.fillHeight: true
                weather: mainAppData.weather
            }
            Text
            {
                id:locationSection
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: mainAppData.weather && mainAppData.weather.location ? mainAppData.weather.location : "N/A"
                color: "white"
                font{
                    bold: true
                    pixelSize: 70
                }
            }
        }
        /*Components.BinaryClock
        {
            id: binaryClock
            clock: mainAppData.binClock
            Layout.preferredWidth: parent.width /2
            Layout.fillHeight: true
            color: "transparent"

        }*/
        Connections{
            target: mainAppData.binClock
            function onTurnNewDay(){
                dateHelper.updateDate();
            }
        }
    }



    /*Rectangle {
            id: newRectangle
            width: parent.width/2
            anchors.right:parent.right
            height: parent.height - topButton.height
            color: "#33FFFFFF"  // Transparent white
            border.color: "#88FFFFFF"  // Slightly opaque white border
            border.width: 1


            y: -height

            Rectangle {
                id: topButton
                width: parent.width /20
                height: 50
                color: "grey"

                anchors.top: parent.bottom

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Toggle the rectangle's visibility
                        if (newRectangle.y === 0) {
                            // If rectangle is visible, slide up
                            slideUpAnimation.start()
                        }
                        else {
                            // If rectangle is hidden, slide down
                            slideDownAnimation.start()
                        }
                        //slideDownAnimation.start()
                    }
                }
            }


            // Slide Down Animation
            SequentialAnimation {
                id: slideDownAnimation
                PropertyAnimation {
                    target: newRectangle
                    property: "y"
                    from: -newRectangle.height
                    to: 0
                    duration: 1000
                    easing.type: Easing.InOutQuad
                }
            }

            // Slide Up Animation
            SequentialAnimation {
                id: slideUpAnimation
                PropertyAnimation {
                    target: newRectangle
                    property: "y"
                    from: 0
                    to: -newRectangle.height
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
            }
        }*/
}
