# Development environment setup guide
This guide is for cross-compiling Qt programs using Boost.\
The host computer is running Ubuntu and the target is a Raspberry Pi 3 with a 7" touchscreen.
### Guides used
* [mechatronicsblog - cross compiling qt for rpi](https://mechatronicsblog.com/cross-compile-and-deploy-qt-5-12-for-raspberry-pi/)
* [wiki.qt.io - cross compiling qt for rpi](https://wiki.qt.io/RaspberryPi2EGLFS)
* [yadoms - cross-compiling for rpi with boost](https://github.com/Yadoms/yadoms/wiki/Cross-compile-for-raspberry-PI)

## Setting up the Rpi
Download [Raspbian Strecth Lite](https://www.raspberrypi.org/downloads/raspbian/)

### Setting up passwordless-ssh and the Rpi firmware
Console commands will be **bold**.\
\
**sudo rpi-update**\
**reboot**\
**sudo raspi-config**
* Set the available GPU memory to 256
* Enable ssh
* Enable console without login

**reboot**\
\
Follow [this guide](https://www.raspberrypi.org/documentation/remote-access/ssh/passwordless.md) to set up passwordless ssh\
\
Uncomment the line beginning with: *deb-src*\
**sudo nano /etc/apt/sources.list**
### Building the required libraries on the Rpi
Run the following commands.

**sudo apt-get update**\
**sudo apt-get build-dep qt4-x11**\
**sudo apt-get build-dep libqt5gui5**\
**sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0**\
**sudo apt-get install gdbserver** < *For debugging.*

### Setting up the target directories on the Rpi
Run the following commands. This will create the directories needed later\
\
**sudo mkdir /usr/local/qt5pi** < *Directory where the Qt libraries will be put*\
**sudo chown pi:pi /usr/local/qt5pi** < *Makes it so the pi user can write to it*\
**mkdir /home/pi/lib_tmp** < *Temporary directory where the boost libs will be put*
