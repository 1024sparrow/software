#!/bin/bash

#apt install vim synaptic git openbox wmctrl
apt install -y qtcreator mplayer gparted cmake
apt install -y libc6:i386

#install nodeJS
apt install curl
curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
apt-get install -y nodejs
apt-get install -y build-essential


#tmp=$(pwd)

#cp clone_terminal /usr/local/bin/
#cd /usr/local/bin && ln -s ${tmp}/projects/80215_desktop_indicator/80215_desktop_indicator ./
