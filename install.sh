#!/bin/bash

apt install -y mc vim synaptic git openbox wmctrl
apt install -y python python-pip python-virtualenv
apt install -y qtcreator qt5-qmake qt5-doc qt5-default qtmultimedia5-dev
apt install -y qml qmlscene libqt5qml-graphicaleffects
apt install -y mplayer gparted cmake
apt install -y libc6:i386 npm

# install nodeJS
apt install curl
curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
apt-get install -y nodejs
apt-get install -y build-essential

# install compiler
ln -s $(pwd)/compiler/compile.js /usr/local/bin/compile

cp clone_terminal /usr/local/bin/
ln -s "$(pwd)/projects/80215_desktop_indicator/80215_desktop_indicator" /usr/local/bin/80215_desktop_indicator
