#!/bin/bash
# генератор сборочного скрипта для проекта под Android
# copyright 2018, Васильев Борис

appname=""
apppath=""
if [ -e AndroidManifest.xml ]
then
    echo Обнаружен файл AndroidManifest.xml. Беру параметры сборки из него.
    tmp=$(cat AndroidManifest.xml | grep package)
    tmp=$(expr match $tmp 'package=\"\([^\"]*\)')
    set -f
    array=(${tmp//./ })
    #IFS='.' read -r -a array <<< "$tmp"
    for element in "${array[@]}"
    do
        appname=$element
        if [ ! -z "$apppath" ]; then apppath=$apppath/; fi
        apppath=${apppath}${element}
    done

    echo $appname
    echo $apppath
    
    #echo $(expr index $tmp2 '\([^.]*\)')
else
    echo Файл AndroidManifest.xml не обнаружен - будем создавать новый проект
    echo ========================================
    echo Пример:
    echo Название проекта: webandroidapp
    echo Путь проекта: ru/mycompany/webandroidapp
    echo ========================================
    echo -n "Введите название проекта:"
    read appname
    if [[ -z $appname ]]; then exit 0; fi
    echo -n "Введите путь проекта:"
    read apppath
    if [[ -z $apppath ]]; then echo qq; exit 0; fi
fi

echo -n "Название скрипта (build.sh по умолчанию):"
read scriptname
if [[ -z $scriptname ]]; then scriptname=build.sh; fi
if [ -e $scriptname ]
then
    echo -n Файл $scriptname уже существует. Нажмите ENTER для замены. Для прерывания операции введите что-нибудь.
    read answ
    if [[ ! -z $answ ]]; then exit 0; fi
    rm -rf $scriptname
fi
touch $scriptname

#appname=webandroidapp
#apppath=com/org/zl/webandroidapp

#==========================
#export MYANDROID_SDK="$(pwd)/android-sdk-linux" >> ~/.bashrc
#export MYANDROID_BUILD_TOOLS="${MYANDROID_SDK}/build-tools/27.0.1" >> ~/.bashrc
#export MYANDROID_PLATFORM="${MYANDROID_SDK}/platforms/android-22" >> ~/.bashrc
#export MYANDROID_PATH="$MYANDROID_SDK/platform-tools":"$MYANDROID_SDK/build-tools/27.0.1":"$MYANDROID_SDK":"$PATH" >> ~/.bashrc

#==========================
echo "#!/bin/bash" > $scriptname
echo "# скрипт, собирающий проект под Android" >> $scriptname
echo "# Реализация основана на статье, расположенной по адресу http://www.hanshq.net/command-line-android.html" >> $scriptname
echo >> $scriptname
echo "appname=${appname}" >> $scriptname
echo "apppath=${apppath}" >> $scriptname
echo >> $scriptname
echo "export JAVA_HOME=\${MYANDROID}/jdk-9.0.1" >> $scriptname
echo "export PATH=\${JAVA_HOME}/bin:\$PATH" >> $scriptname
echo "export SDK=\"\${MYANDROID}/android-sdk-linux\"" >> $scriptname
echo "export BUILD_TOOLS=\"\${SDK}/build-tools/27.0.1\"" >> $scriptname
echo "export PLATFORM=\"\${SDK}/platforms/android-22\"" >> $scriptname
echo "export PATH=\"\$SDK/platform-tools\":\"\$SDK/build-tools/27.0.1\":\"\$SDK\":\"\$PATH\"" >> $scriptname
echo >> $scriptname
echo "RED='\033[0;31m'" >> $scriptname
echo "YEL='\033[1;33m'" >> $scriptname
echo "NC='\033[0m'" >> $scriptname
echo >> $scriptname

echo "function error_quite {" >> $scriptname
echo "    echo -e \"\${RED}Сборка прервана из-за возникшей ошибки\${NC}\"" >> $scriptname
echo "    exit 1" >> $scriptname
echo "}" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Удаляем build (предыдущую сборку)\${NC}\"" >> $scriptname
echo "rm -rf build" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Создаём директории, куда будет производиться сборка\${NC}\"" >> $scriptname
echo "mkdir -p build/gen build/obj build/apk || error_quite" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Генерируем java-файлы (R.java), отображающие содержимое ресурсов (которые описаны в XML)\${NC}\"" >> $scriptname
echo "\"\${BUILD_TOOLS}/aapt\" package -f -m -J build/gen/ -S res -M AndroidManifest.xml -I \"\${PLATFORM}/android.jar\" || error_quite" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Собираем байт-код для нашего Java-приложения. Делаем байт-код для версии Java 7.\${NC}\"" >> $scriptname
echo "javac -source 1.7 -target 1.7 -bootclasspath \"\${JAVA_HOME}/jre/lib/rt.jar\" -classpath \"\${PLATFORM}/android.jar\" -d build/obj build/gen/\${apppath}/R.java java/\${apppath}/MainActivity.java || error_quite" >> $scriptname
echo "echo \"Вот мы получили байт-код Java (файлы .class). Но Android использует байт-код другого формата - Dalvik (файлы .dex)\"" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Преобразуем стандартный байт-код в Андроидовский (Dalvik) байт-код\${NC}\"" >> $scriptname
echo "\"\${BUILD_TOOLS}/dx\" --dex --output=build/apk/classes.dex build/obj/ || error_quite" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Запаковываем .dex-файлы, манифест и ресурсы в APK\${NC}\"" >> $scriptname
echo "\"\${BUILD_TOOLS}/aapt\" package -f -M AndroidManifest.xml -A assets -S res/ -I \"\${PLATFORM}/android.jar\" -F build/\${appname}.unsigned.apk build/apk/ || error_quite" >> $scriptname
echo "echo \"У нас есть apk-файл, но прежде чем его устанавливать на смартфон, его необходимо подписать...\"" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Делаем так, чтобы после распаковки нашего apk файлы были выровнены по размеру блока 4 байта\${NC}\"" >> $scriptname
echo "\"\${BUILD_TOOLS}/zipalign\" -f -p 4 build/\${appname}.unsigned.apk build/\${appname}.aligned.apk || error_quite" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Генерируем ключ (будут запрашиваться данные у пользователя)\${NC}\"" >> $scriptname
echo "keytool -genkeypair -keystore keystore.jks -alias androidkey -validity 10000 -keyalg RSA -keysize 2048 -storepass android -keypass android || error_quite" >> $scriptname
echo >> $scriptname

echo "echo -e \"\${YEL}Подписываем полученным ключом наш apk\${NC}\"" >> $scriptname
echo "\"\${BUILD_TOOLS}/apksigner\" sign --ks keystore.jks --ks-key-alias androidkey --ks-pass pass:android --key-pass pass:android --out build/\${appname}.apk build/\${appname}.aligned.apk || error_quite" >> $scriptname
echo >> $scriptname

chmod +x $scriptname
