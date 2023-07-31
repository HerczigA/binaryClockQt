import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Rectangle{

    id :  rootWateringSystem
    property var wateringSystem
    Row
    {
        ColumnLayout {
            id : columnPart
            spacing: 30
            width: rootWateringSystem.width * 0.2
            height: rootWateringSystem.height
            GreenSwitch {
//                transform :
//                    Rotation
//                    {
//                        origin.x: 25;
//                        origin.y: 25;
//                        angle: 90;
//                    }
            }
//            Text{
//                text:{
//                    qsTr("Watering")

//                }
//            }

        }

        Rectangle
        {
                width : (rootWateringSystem.width - columnPart.width) /2
                height : rootWateringSystem.height
                color : "transparent"
        }
        Rectangle
        {
                width : (rootWateringSystem.width - columnPart.width)/2
                height : rootWateringSystem.height
                color : "transparent"
        }

    }
}
