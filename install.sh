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

if [[ $(which yum) ]]
then
	IS_RHEL=1
	# not supported
elif [[ $(which apt) ]]
then
	IS_UBUNTU=1
	source packet_aliases/ubuntu
elif [[ $(which apk) ]]
then
	IS_ALPINE=1
	source packet_aliases/alpine
else
	IS_UNKNOWN=1
fi

function install()
{
	pacname=packet_$1
	echo "instaling packet: $pacname"
	if [ -z "$pacname" ]
	then
		echo "no such package registered: $1"
		return
	fi

	for iPacket in ${!pacname}
	do
		echo "Устанавливается пакет $iPacket"

		if [[ ! -z $IS_UBUNTU ]]
		then
			apt-cache show $i > /dev/null && apt-get install -y $i > /dev/null || dep_exit "Пакет $i не найден в репозитории"
			#apt-cache show $i && apt-get install $i || dep_exit "Пакет $i не найден в репозитории"
			echo UBUNTU
		fi

		if [[ ! -z IS_ALPINE ]]
		then
			apk add $iPacket
		fi
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

#install "mc vim synaptic git"

if [ -z $INSTALL_OPENBOX ];then
    install openbox
    install wmctrl
    cp -u clone_terminal /usr/local/bin/
    rm /usr/local/bin/80215_desktop_indicator
    ln -s "$(pwd)/projects/80215_desktop_indicator/80215_desktop_indicator" /usr/local/bin/80215_desktop_indicator
fi

install gcc
#install python2
install python3
install qtSdk
#install mplayer
install gparted
install cmake
install feh
install gimp
#install kolourpaint

if [ -z $INSTALL_TRALIVA_COMPILE ];then
	install nodejs

	# install compiler
	rm /usr/local/bin/compile
	ln -s $(pwd)/compiler/compile.js /usr/local/bin/compile
fi

rm /usr/local/bin/bash_mode_list
ln -s $(pwd)/bash_mode_list /usr/local/bin/bash_mode_list
