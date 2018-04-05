#!/bin/bash

DEST_LIST=".bashrc .gconf .vim .vimrc"
for i in $DEST_LIST
do
    rm -rf ~/$i
    ln -s "$(pwd)/$i" ~/$i
done

ln -s "$(pwd)"/config_openbox ~/.config/openbox

bash generates_desktop_home_files_for_desktop_indicator.sh


cd projects/80215_desktop_indicator
qmake && make
cd ../80226_govorilka
qmake && make
