# binaryClockQt
Hey everbody this is a small sandbox project to learn Qt both on c++ and qml side.
It has been developing for raspberry project with qt6.3.2.
Required packages:
- QtQuick
- QtGui
- QtCore
- QtPositioning
- QtNetwork
- QtLocation
- QtQml
- QtDBus

Unfortunatelly qtLocation is not building alongside with qtbase from online installer like the other modules.
When you installed every packages what are required you have build qtLocation from source:
https://code.qt.io/cgit/qt/qtlocation.git/

After downloading, go to qtLocation. Make a build dir then go into.
- mkdir buid
- cd build

You have to use qt-cmake. Usually qt-cmake located in like user/Qt/6.x.y/macos|gcc_64|other/bin/qt-cmake.
This is a qt specific cmake script which a "smart" cmake. It holds every flags what is needed so you don't 
have to specify explicitly.
- user/Qt/6.x.y/macos|gcc_64|other/bin/qt-cmake ..
- cmake --build . 
After succesfully build ( without any error)
- cmake --install . 
The last command will copy every cmake files and other dependecies to the proper path to qt to find
qtlocation specific libs.


If you would like to use the program you need the following files:
 - A mainApp.conf config file in /etc/xdg/MainApp
 - An MainApp.desktop file for dbus communication with geoclue2 to get goordinates

So far the conf file should like this:
[WeatherForecast]
url= the url where from you would like to get weather datas
apikey=yourApiKey for the previous link
attribute1=val
attribute2=val2 
these attribute will fill up the rest of the url 
[Position]
type=[DBus | Plugin | GpsDevice | Online]
url= url where from you would like to get position info somehow
apikey=yourApikey


While the .desktop  file should look like:
[Desktop Entry]
Type=Application
Name=MainApp
GenericName=My Location-Aware Application
Comment=An application that uses geolocation services
Exec=path/of/your/executable
Terminal=false
Categories=Utility;
X-Geoclue-Reason=To provide location-based services
X-Geoclue-NotificationLevel=NONE


So far it has a binary clock on the right side of the first page, while on the left side there should be from up to down the actual date, temperature, a wehater icon and a location.
On the second page there should be a UI for a watering system for plants but this plan for the future. 
Plan: 
Watering sytem
Setting field
Page for your home storage 