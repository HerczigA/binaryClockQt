# binaryClockQt
Hey everbody this is a small sandbox project to learn Qt both on c++ and qml side.
It has been developing for raspberry project. 
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