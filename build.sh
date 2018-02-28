#!/bin/bash

tmp=$(pwd)

cp -f .bashrc ~/
cp -rf .gconf ~/
cp -rf .vim ~/
cp -f .vimrc ~/

mkdir openbox
cd openbox
cp config_openbox/* openbox/
mv openbox ~/.config/

bash generates_desktop_home_files_for_desktop_indicator.sh


cd projects/80215_desktop_indicator
qmake && make
cd ../80226_govorilka
qmake && make
