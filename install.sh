#!/bin/bash

if [ ! $(id -u) -eq 0 ]
then
    echo Этот скрипт надо запускат ьпод рутом.
    exit 1
fi

echo "Сейчас будут выведены части системы, которые скрипт может установить. Если установку надо пропустить, введите что-нибудь перед тем как нажать ENTER"
echo -n "Настроить git (имя пользователя и e-mail)"
echo "INSTALL_DEFAULT" > config
read SETUP_GIT
if [ -z $SETUP_GIT ]; then
    echo "SETUP_GIT" >> config
fi
echo -n "openbox с 72 рабочими столами"
read INSTALL_OPENBOX
if [ -z $INSTALL_OPENBOX ]; then
    echo "INSTALL_OPENBOX" >> config
fi
echo -n "компилятор compile для работы с фрэймворком Тралива"
read INSTALL_TRALIVA_COMPILE
if [ -z $INSTALL_TRALIVA_COMPILE ]; then
    echo "INSTALL_TRALIVA_COMPILE" >> config
fi

apt install -y mc vim synaptic git

if [ -z $INSTALL_OPENBOX ];then
    apt install -y openbox wmctrl kolourpaint4
    cp -u clone_terminal /usr/local/bin/
    rm /usr/local/bin/80215_desktop_indicator
    ln -s "$(pwd)/projects/80215_desktop_indicator/80215_desktop_indicator" /usr/local/bin/80215_desktop_indicator
fi

apt install -y python python-pip python-virtualenv
apt install -y python3 python3-pip python3-virtualenv
apt install -y qtcreator qt5-qmake qt5-doc qt5-default qtmultimedia5-dev
apt install -y qml qmlscene libqt5qml-graphicaleffects
apt install -y mplayer gparted cmake
apt install kdelibs5-plugins kdelibs5-data oxygen-icon-theme kolourpaint4

if [ -z $INSTALL_TRALIVA_COMPILE ];then
    apt install -y libc6:i386 npm
    # install nodeJS
    apt install curl
    curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
    apt-get install -y nodejs
    apt-get install -y build-essential

    # install compiler
    rm /usr/local/bin/compile
    ln -s $(pwd)/compiler/compile.js /usr/local/bin/compile
fi

rm /usr/local/bin/bash_mode_list
ln -s $(pwd)/bash_mode_list /usr/local/bin/bash_mode_list
