# Development environment setup guide
This guide is for cross-compiling Qt programs using Boost.\
The host computer is running Ubuntu and the target is a Raspberry Pi 3 with a 7" touchscreen.
### Guides used
* [mechatronicsblog - cross compiling qt for rpi](https://mechatronicsblog.com/cross-compile-and-deploy-qt-5-12-for-raspberry-pi/)
* [wiki.qt.io - cross compiling qt for rpi](https://wiki.qt.io/RaspberryPi2EGLFS)
* [yadoms - cross-compiling for rpi with boost](https://github.com/Yadoms/yadoms/wiki/Cross-compile-for-raspberry-PI)

## Setting up the Rpi
Download [Raspbian Strecth Lite](https://www.raspberrypi.org/downloads/raspbian/)

### Setting up ssh and the Rpi firmware
Console commands will be *italic*.\
\
*sudo rpi-update*\
*reboot*\
*sudo raspi-config*
* Set the available GPU memory to 256
* Enable ssh
* Enable console without login

*reboot*\
> Follow [this guide](https://www.raspberrypi.org/documentation/remote-access/ssh/passwordless.md) to set up passwordless ssh

Uncomment the line beginning with: *deb-src*\
*sudo nano /etc/apt/sources.list*
### Building the required libraries on the Rpi
Run the following commands.

*sudo apt-get update*\
*sudo apt-get build-dep qt4-x11*\
*sudo apt-get build-dep libqt5gui5*\
*sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0*\
*sudo apt-get install gdbserver* < *For debugging.*

### Setting up the target directories on the Rpi
Run the following commands. This will create the directories needed later\
\
*sudo mkdir /usr/local/qt5pi* < *Directory where the Qt libraries will be put*\
*sudo chown pi:pi /usr/local/qt5pi* < *Makes it so the pi user can write to it*\
*mkdir /home/pi/lib_tmp* < *Temporary directory where the boost libs will be put*


## Setting up the Host Computer
### Setting up the build environment
Start out by making all the environment directories. The sysroot folder will be used to mimic the Rpi. It is therefore important that, you make sure that all object-files that are copied onto the Rpi, are compiled with a compiler that is compatible with the Rpi. Use the compilers in the raspberrypi toolset we will clone in this section.\
\
*mkdir ~/raspi ~/raspi/sysroot*\
*cd ~/raspi*\
*git clone https://github.com/raspberrypi/tools* \
*mkdir sysroot sysroot/usr sysroot/opt*
# TODO: Skriv hur vi installerar Qt och ser till att det fungerar och sedan använder samma kompilator för att kompilera boost.
### Installing Boost and exporting the lib-files to the Rpi
*export PATH=$PATH:$HOME/raspberry/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin*
