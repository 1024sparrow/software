#!/bin/bash

apt install -y mc vim synaptic git openbox wmctrl
apt install -y python python-pip python-virtualenv
apt install -y qt5-qmake qt5-doc qt5-default qtmultimedia5-dev
apt install -y qtcreator mplayer gparted cmake
apt install -y libc6:i386 npm

#install nodeJS
apt install curl
curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
apt-get install -y nodejs
apt-get install -y build-essential


#tmp=$(pwd)

cp clone_terminal /usr/local/bin/
#cd /usr/local/bin && ln -s ${tmp}/projects/80215_desktop_indicator/80215_desktop_indicator ./
ln -s "$(pwd)/projects/80215_desktop_indicator/80215_desktop_indicator" /usr/local/bin/80215_desktop_indicator
