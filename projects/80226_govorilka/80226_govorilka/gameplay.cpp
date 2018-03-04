#include "gameplay.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

#include <string.h>
#include <string.h>

#include <boris_h/xml_driven/xmlpublisher.h>
#include <boris_h/musicplayer.h>
#include "display.h"

//QMap<int, const char *>
//const QMap<char, >
typedef struct{
    const char *nameCapital;
    const char *name;
    //char id;
    int codes[2];
    char glasn;//0 - {'й', 'ъ', 'ь'}, 1 - гласная, -1 - согласная,
} KeyDescr;
KeyDescr keyDescr[] =
{
    {"Ё", "ё", {96, 1025}, 1}, // ё
    {"Й", "й", {81, 1049}, 0}, // й
    {"Ц", "ц", {87, 1062}, -1}, // ц
    {"У", "у", {69, 1059}, 1}, // у
    {"К", "к", {82, 1050}, -1}, // к
    {"Е", "е", {84, 1045}, 1}, // е
    {"Н", "н", {89, 1053}, -1}, // н
    {"Г", "г", {85, 1043}, -1}, // г
    {"Ш", "ш", {73, 1064}, -1}, // ш
    {"Щ", "щ", {79, 1065}, -1}, // щ
    {"З", "з", {80, 1047}, -1}, // з
    {"Х", "х", {91, 1061}, -1}, // х
    {"Ъ", "ъ", {93, 1066}, 0}, // ъ
    {"Ф", "ф", {65, 1060}, -1}, // ф
    {"Ы", "ы", {83, 1067}, 1}, // ы
    {"В", "в", {68, 1042}, -1}, // в
    {"А", "а", {70, 1040}, 1}, // а
    {"П", "п", {71, 1055}, -1}, // п
    {"Р", "р", {72, 1056}, -1}, // р
    {"О", "о", {74, 1054}, 1}, // о
    {"Л", "л", {75, 1051}, -1}, // л
    {"Д", "д", {76, 1044}, -1}, // д
    {"Ж", "ж", {59, 1046}, -1}, // ж
    {"Э", "э", {39, 1069}, -1}, // э
    {"Я", "я", {90, 1071}, 1}, // я
    {"Ч", "ч", {88, 1063}, -1}, // ч
    {"С", "с", {67, 1057}, -1}, // с
    {"М", "м", {86, 1052}, -1}, // м
    {"И", "и", {66, 1048}, 1}, // и
    {"Т", "т", {78, 1058}, -1}, // т
    {"Ь", "ь", {77, 1068}, 0}, // ь
    {"Б", "б", {44, 1041}, -1}, // б
    {"Ю", "ю", {46, 1070}, 1} // ю
};
const int keyDescrCount = sizeof(keyDescr) / sizeof(KeyDescr);

Gameplay::Gameplay()
    :QWidget(0), m_state(STATE__MOL)
{
    strcpy(m_lastPlaying, "");
    m_player = new boris::Musicplayer(this);
    connect(m_player, SIGNAL(finished()), this, SLOT(onPlaybackFinished()));

    boris::XmlPublisher *publisher = new boris::XmlPublisher(this);
    m_display = new Display(publisher, this);
    publisher->registerSubscriber(m_display);
}

void Gameplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::Dense1Pattern);
}

void Gameplay::resizeEvent(QResizeEvent *)
{
    m_display->setFixedSize(size());
}

void Gameplay::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;
    //qDebug() << "pressed "<<event->key()<<" --- "<<event->text();
    int k = event->key();
    const KeyDescr *kd = 0; //({0,0,{0,0},-1});
    for (int i = 0 ; i < keyDescrCount ; i++)
    {
        if ((k == keyDescr[i].codes[0]) || (k == keyDescr[i].codes[1]))
            kd = &keyDescr[i];
    }
    if (!kd)
        return;
    //if (kd->glasn)
    if ((m_state == STATE__MOL) || (m_state == STATE__MOL_GL))
    {
        if ((kd->name[0] == 'ъ') || (kd->name[0] == 'ь'))
        {
            play(0);
            return;
        }
        m_state = (kd->glasn >= 0) ? STATE__ZV_SL : STATE__ZV_SOGL; // 'й' или гласная -- согласная
        play(kd->nameCapital);
    }
    else if (m_state == STATE__MOL_SOGL)
    {
        if (kd->glasn == 0)
        {
            if (kd->name[0] == 'й')
            {
                play(0);
            }
            else if (kd->name[0] == 'ъ')
            {
                m_state = STATE__ZV_SL;
                play(m_lastPlaying);
            }
            else if (kd->name[0] == 'ь')
            {
                m_state = STATE__ZV_SL;
                play(strcat(m_lastPlaying, kd->nameCapital));
            }
        }
        else if (kd->glasn == 1)
        {
            //
        }
        else if (kd->glasn == -1)
        {
            //
        }
    }
    else if (m_state == STATE__MOL_SL)
    {
        if (kd->glasn == 0)
        {
            //
        }
        else if (kd->glasn == 1)
        {
            //
        }
        else if (kd->glasn == -1)
        {
            //
        }
    }
    else if (m_state == STATE__ZV_GL)
    {
        if (kd->glasn == 0)
        {
            //
        }
        else if (kd->glasn == 1)
        {
            //
        }
        else if (kd->glasn == -1)
        {
            //
        }
    }
    else if (m_state == STATE__ZV_SOGL)
    {
        if (kd->glasn == 0)
        {
            //
        }
        else if (kd->glasn == 1)
        {
            //
        }
        else if (kd->glasn == -1)
        {
            //
        }
    }
    else if (m_state == STATE__ZV_SL)
    {
        if (kd->glasn == 0)
        {
            //
        }
        else if (kd->glasn == 1)
        {
            //
        }
        else if (kd->glasn == -1)
        {
            //
        }
    }
}

void Gameplay::keyReleaseEvent(QKeyEvent *event)
{
    /*if (event->isAutoRepeat())
        return;
    qDebug() << "\treleased' "<<event->key();*/
}

void Gameplay::play(const char *str)
{
    m_player->setSourcePath(
                QString("/home/boris/opt/software/projects/80226_govorilka/80226_govorilka/media/allfiles/%1.wav")
                .arg(QString::fromUtf8(str ? str : "пи"))
                );
    strcpy(m_lastPlaying, str);
    m_player->play();
}

void Gameplay::stop()
{
    //
}

void Gameplay::onPlaybackFinished()
{
    //
}
























































