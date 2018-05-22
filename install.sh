#!/bin/bash

if [ ! $(id -u) -eq 0 ]
then
    echo Этот скрипт надо запускат ьпод рутом.
    exit 1
fi

function dep_exit()
{
	echo $1
	exit 1
}

function install()
{
	for i in $1
	do
		echo "Устанавливается пакет $i"
		apt-cache show $i > /dev/null && apt-get install -y $i > /dev/null || dep_exit "Пакет $i не найден в репозитории"
	done
}

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

install "mc vim-console synaptic git"

if [ -z $INSTALL_OPENBOX ];then
    install openbox wmctrl kolourpaint4
    cp -u clone_terminal /usr/local/bin/
    rm /usr/local/bin/80215_desktop_indicator
    ln -s "$(pwd)/projects/80215_desktop_indicator/80215_desktop_indicator" /usr/local/bin/80215_desktop_indicator
fi

install "python python-module-pip python-module-virtualenv"
install "python3 python3-module-pip python3-module-virtualenv"
install "qt-creator qt5-base-devel qt5-base-doc libqt5-multimedia"
install "libqt5-qml qt5-graphicaleffects"
install "gparted cmake"
#install kde4-kolourpaint # какие-то проблемы с установкой в AltLinux-е: наверное, данный пакет битый в локальном зеркале репозитория

if [ -z $INSTALL_TRALIVA_COMPILE ];then
    #install libc6:i386 npm
    # install nodeJS
    #install curl
    #curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash - || dep_exit "fail..."
    #install nodejs
    #install build-essential

    # install compiler
    rm /usr/local/bin/compile
    ln -s $(pwd)/compiler/compile.js /usr/local/bin/compile
fi

rm /usr/local/bin/bash_mode_list
ln -s $(pwd)/bash_mode_list /usr/local/bin/bash_mode_list
