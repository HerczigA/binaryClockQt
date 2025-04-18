# binaryClockQt
Hey everbody this is a small sandbox project to learn Qt both on c++ and qml side.
It has been developing for raspberry pi 3B armv7 project with qt6.3.2.
Required packages:
- QtQuick
- QtGui
- QtCore
- QtPositioning
- QtNetwork
- QtLocation
- QtQml
- QtDBus

# qtLocation

Unfortunatelly qtLocation is not building alongside with qtbase from online       installer like the other modules.When you installed every packages what are required you have to build qtLocation from source:
https://code.qt.io/cgit/qt/qtlocation.git/

After downloading, go to qtLocation. Make a build dir then go into.
If necessary do not forget to switch the correct branch (6.3 in case of qtLocation)
- mkdir buid
- cd build

You have to use qt-cmake. Usually qt-cmake located in like user/Qt/6.x.y/macos|gcc_64|other/bin/qt-cmake.
This is a qt specific cmake script which a "smart" cmake. It holds every flags what are needed so you don't have to specify explicitly.
- user/Qt/6.x.y/macos|gcc_64|other/bin/qt-cmake ..
- cmake --build . 
After succesfully build ( without any error)
- cmake --install . 
The last command will copy every cmake files and other dependecies to the proper path to qt to find
qtlocation specific libs. This part is only for developing on host system. Building 
to target device for more information read bellow.

# ini and other necessary files
If you would like to use the program you need the following files:
 - A mainApp.ini config file in /etc/xdg/MainApp
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

# Building to Raspberry
In crossCompileInfo there is a DockerFile which has an ubuntu focal image and every dependecies 
what you need to be able to build for the target device this project. 

This repo does not contain sysroot because it is to big. Perhaps in the future will be part 
of the repo as git lfs or submodule. After docker image build, you have to run the image, 
pull the repo, move into the directory.
First of all create a build folder and move into it. 
Then call 
- /opt/qt6pi/bin/qt-cmake ..
- cmake --build . --parallel ${nproc}

Finally AviCado ( which is a temporary funny name for the project) has been created.
Generally I send the binary to the target via ssh with scp
"scp Avicado pi@ip.address"
At first time you probably have to send every dynamic libs to the target because it works
with dynamic libs instead of as a static one app binary.
Please create a folder in /usr/local/qt6 on the target device and copy the following libs from /opt/qt6pi/
- lib
- qml
- plugins

Yes I know it is really annoying, there is a future task to make a script which will handle this together.

# Use eglfs instead of xcb on device
You may have to update /boot/config.txt on raspberry to use hardware support instead of software rendering.
First of all make a backup ;) 
disable 
Add these lines at the end of the line:
- dtoverlay=vc4-fkms-v3d,disp1_dsi=1
- gpu_mem=256
- max_framebuffers=2

Other dtoverlay please uncomment whihc display specific.

These export will be necessary for eglfs support 
- export QT_QPA_PLATFORM=eglfs
- export QT_QPA_EGLFS_INTEGRATION=eglfs_kms 

Please disable lightdm 
- sudo systemctl disable lightdm   # or gdm3, sddm, etc. depending on your distro

[other future task to handle this with a script]


# Actual state
So far it has a binary clock on the right side of the first page, while on the left side there should be
from up to down the actual date, temperature, a wehater icon and a location.
On the second page there should be a UI for a watering system for plants but this plan for the future. 
Plan: 
Watering sytem
Setting field
Page for your home storage 