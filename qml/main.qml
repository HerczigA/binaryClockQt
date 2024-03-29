import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "./pages"

Window {
    id: mainWindow
    width: mainApp.width
    height: mainApp.height
    visible: true
    visibility: "FullScreen"
    title: qsTr("Do It, YOU can do IT")

    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent

        FirstPage
        {
            mainAppData: mainApp
        }

        Item {
            id: secondPage
        }
        Item {
            id: thirdPage
        }
        onCurrentIndexChanged: {
            if (currentIndex === 0)
                mainApp.weather.requestDataFromUI()
        }
    }

    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }


}
