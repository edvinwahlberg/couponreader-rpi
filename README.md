# Development environment setup guide

## Guides used
* [mechatronicsblog - cross compiling qt for rpi](https://mechatronicsblog.com/cross-compile-and-deploy-qt-5-12-for-raspberry-pi/)
* [wiki.qt.io - cross compiling qt for rpi](https://wiki.qt.io/RaspberryPi2EGLFS)
* [yadoms - cross-compiling for rpi with boost](github.com/Yadoms/yadoms/wiki/Cross-compile-for-raspberry-PI)

# Setting up the Rpi
> [Download Raspbian Strecth Lite](https://www.raspberrypi.org/downloads/raspbian/)

## Setting up passwordless-ssh and the Rpi firmware
Console commands will be **bold**.\
\
**sudo rpi-update**\
**reboot**\
**sudo raspi-config**
* Set the GPU memory to 256
* Enable SSH
* Enable console without login

**reboot**\
\
Follow [this guide](https://www.raspberrypi.org/documentation/remote-access/ssh/passwordless.md) to set up passwordless ssh
## Building the required libraries on the Rpi
> Enter the following

