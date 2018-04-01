#!/bin/bash
#http://www.hanshq.net/command-line-android.html

JDK_FILE=jdk-9.0.1_linux-x64_bin.tar.gz

RED='\033[0;31m'
YEL='\033[1;33m'
NC='\033[0m'

if [ ! -e $JDK_FILE ]
then
    echo Файл $JDK_FILE не найден. Положите его сюда и запустите скрипт ещё раз.
    echo Его можно взять здесь: http://www.oracle.com/technetwork/java/javase/downloads/index.html
    exit 1
fi

echo -e "${YEL}Распаковываю jdk${NC}"
tar -xf $JDK_FILE
#export JAVA_HOME=$(pwd)/jdk-9.0.1
#export PATH=${JAVA_HOME}/bin:$PATH

echo -e "${YEL}Скачиваю и распаковываю sdk-tools${NC}"
wget https://dl.google.com/android/repository/sdk-tools-linux-3859397.zip
unzip sdk-tools-linux-3859397.zip

echo -e "${YEL}Скачиваю и распаковываю build-tools${NC}"
wget https://dl.google.com/android/repository/build-tools_r27.0.1-linux.zip
unzip build-tools_r27.0.1-linux.zip
mkdir tools/build-tools
mv android-8.1.0 tools/build-tools/27.0.1

echo -e "${YEL}Скачиваю и распаковываю ndk${NC}"
wget https://dl.google.com/android/repository/android-ndk-r16-linux-x86_64.zip
unzip android-ndk-r16-linux-x86_64.zip

# Запускаем android-studio. Открываем SDK Manager. Appearance&Behaviour -> System Settings --> Android SDK.
# Вкладка SDK Update Sites. По этому адресу можно увидеть XML с перечнем доступных платформ. Выбираем, подменяем в адресе на указанный в XML android-xxxx.zip и скачиваем
# По состоянию на март 2018 года самый свежий - https://dl.google.com/android/repository/repository2-1.xml
# Для разработки в студии и сборки вручную я брал (мог бы взять, кабы не старая версия андроида на моём устройстве) https://dl.google.com/android/repository/platform-26_r02.zip
# Для того, чтобы в студии можно было разрабатывать под моё (старое) устройство, необходимо добавить репозиторий https://dl.google.com/android/repository/repository-11.xml
echo -e "${YEL}Скачиваю и распаковываю платформу android-22${NC}"
wget https://dl.google.com/android/repository/android-22_r02.zip
unzip android-22_r02.zip
mkdir tools/platforms
mv android-5.1.1 tools/platforms/android-22

echo -e "${YEL}Скачиваю и распаковываю инструменты для платформы r26.0.2${NC}"
wget https://dl.google.com/android/repository/platform-tools_r26.0.2-linux.zip
unzip platform-tools_r26.0.2-linux.zip -d tools/

mv tools android-sdk-linux

echo export MYANDROID="$(pwd)" >> ~/.bashrc
cp $(dirname $0)/generates_desktop_home_files_for_desktop_indicator.sh ./
echo export MYANDROID_GEN="$(pwd)/generates_desktop_home_files_for_desktop_indicator.sh" >> ~/.bashrc

#echo export SDK="$(pwd)/android-sdk-linux" >> ~/.bashrc
#echo export BUILD_TOOLS="${SDK}/build-tools/27.0.1" >> ~/.bashrc
#echo export PLATFORM="${SDK}/platforms/android-22" >> ~/.bashrc
#echo export PATH="$SDK/platform-tools":"$SDK/build-tools/27.0.1":"$SDK":"$PATH" >> ~/.bashrc
