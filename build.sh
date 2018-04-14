#!/bin/bash

for i in $(cat config)
do
    case "$i" in
        INSTALL_DEFAULT)
            DEST_LIST=".bashrc .bash_modes .gconf .vim .vimrc"
            for i in $DEST_LIST
            do
                rm -rf ~/$i
                ln -s "$(pwd)/$i" ~/$i
            done
        ;;
        INSTALL_OPENBOX)
            rm -rf ~/.config/openbox
            ln -s "$(pwd)"/config_openbox ~/.config/openbox
            bash generates_desktop_home_files_for_desktop_indicator.sh

            cd projects/80215_desktop_indicator
            qmake && make
            cd ../80226_govorilka
            qmake && make
        ;;
        INSTALL_TRALIVA_COMPILE)
            # install compiler
            git clone https://github.com/1024sparrow/compiler.git
            cd compiler
            npm install
            cd ..
        ;;
        SETUP_GIT)
            echo; echo Настраиваем git
            echo -n "Как вас зовут? "
            read git_username
            git config --global user.name "$git_username"
            echo -n "На какую электронную почту писать в случае вопросов? "
            read git_email
            git config --global user.email "$git_email"
        ;;
    esac
done
