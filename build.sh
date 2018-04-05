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

echo; echo Настраиваем git
echo -n "Как вас зовут? "
read git_username
git config --global user.name "$git_username"
echo -n "На какую электронную почту писать в случае вопросов? "
read git_email
git config --global user.email "$git_email"

# install compiler
git clone https://github.com/1024sparrow/compiler.git
cd compiler
npm install
cd ..
