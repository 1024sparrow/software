#include "gameplay.h"
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QBoxLayout>
#include <QDebug>

#include <string.h>
#include <string.h>
#include <iostream>

#include <boris_h/xml_driven/xmlpublisher.h>
#include <boris_h/musicplayer.h>

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
    {"Э", "э", {39, 1069}, 1}, // э
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
    //m_label = new QLabel(QString::fromUtf8("<h1><span style=\"font-size: 72pt;color:blue\">К</span> <span style=\"color:red\">А</span></h1>"),this);
    m_label = new QLabel(this);
    m_label->setTextFormat(Qt::RichText);
    m_label->setFont(QFont("arial", 144));
    //m_label->setFont(QFont("arial", 288));

    m_debugLabel = new QLabel("DEBUG", this);
    QPalette palette = m_debugLabel->palette();
    palette.setColor(QPalette::Foreground, Qt::green);
    m_debugLabel->setPalette(palette);

    QBoxLayout *lay = new QVBoxLayout(this);
    QBoxLayout *innerLay = new QHBoxLayout(this);
    {
        innerLay->addStretch();
        innerLay->addWidget(m_label);
        innerLay->addStretch();
    }
    lay->addStretch();
    lay->addLayout(innerLay);
    lay->addStretch();
    lay->addWidget(m_debugLabel);

    strcpy(m_lastPlaying, "");
    m_playerPi = new boris::Musicplayer(this);
    m_playerPi->setSourcePath("/home/boris/opt/software/projects/80226_govorilka/80226_govorilka/media/allfiles/пи.wav");
    m_player = new boris::Musicplayer(this);
    connect(m_player, SIGNAL(finished()), this, SLOT(onPlaybackFinished()));
}

void Gameplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    //painter.fillRect(rect(), Qt::Dense1Pattern);
}

void Gameplay::resizeEvent(QResizeEvent *)
{
    //m_label->setFixedSize(size());
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
    if ((m_state == STATE__MOL) || (m_state == STATE__MOL_GL) || (m_state == STATE__ZV_GL) || (m_state == STATE__ZV_SL))
    {
        //if ((kd->name[0] == 'ъ') || (kd->name[0] == 'ь'))
        if ((QString(kd->name)[0] == QString::fromUtf8("ъ")[0]) ||
                (QString(kd->name)[0] == QString::fromUtf8("ь")[0]))
        {
            play(0);
            return;
        }
        m_state = (kd->glasn >= 0) ? STATE__ZV_SL : STATE__ZV_SOGL; // 'й' или гласная -- согласная
        stateChanged();
        play(kd->nameCapital);
    }
    else if ((m_state == STATE__MOL_SOGL) || (m_state == STATE__ZV_SOGL))
    {
        if (kd->glasn == 0)
        {
            //if (kd->name[0] == 'й')
            if (QString(kd->name)[0] == QString::fromUtf8("й")[0])
            {
                play(0);
            }
            //else if (kd->name[0] == 'ъ')
            else if (QString(kd->name)[0] == QString::fromUtf8("ъ")[0])
            {
                m_state = STATE__ZV_SL;
                stateChanged();
                play(m_lastPlaying);
            }
            //else if (kd->name[0] == 'ь')
            else if (QString(kd->name)[0] == QString::fromUtf8("ь")[0])
            {
                m_state = STATE__ZV_SL;
                stateChanged();
                play(strcat(m_lastPlaying, kd->nameCapital));
            }
            else
            {
                m_debugLabel->setText(QString("oops: %1 -- %2").arg(kd->name).arg(QString(kd->name)[0]));
            }
        }
        else if (kd->glasn == 1)
        {
            m_state = STATE__ZV_SL;
            stateChanged();
            play(strcat(m_lastPlaying, kd->nameCapital));
        }
        else if (kd->glasn == -1)
        {
            m_state = STATE__ZV_SOGL;
            stateChanged();
            play(kd->nameCapital);
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
    if (str)
    {
        setLabel(str);
        m_player->setSourcePath(
                    QString("/home/boris/opt/software/projects/80226_govorilka/80226_govorilka/media/allfiles/%1.wav")
                    .arg(QString::fromUtf8(str))
                    );
        strcpy(m_lastPlaying, str);
        m_player->play();
    }
    else
        m_playerPi->play();
}

void Gameplay::stop()
{
    m_player->stop();
}

void Gameplay::onPlaybackFinished()
{
    //
}

void Gameplay::setLabel(const char *s)
{
    if (!s)
    {
        m_label->setText("error");
        return;
    }
    QString cand;
    for (const char *i = s ; *i != '\0'; i++)
    {
        for (int ii = 0 ; ii < keyDescrCount ; ii++)
        {
            const KeyDescr &kd = keyDescr[ii];
            if (QString::fromUtf8(kd.nameCapital)[0] == QString::fromUtf8(i)[0])
            {
                cand += QString("<span style=\"color:%1\">%2</span>")
                        //.arg("blue")
                        .arg(kd.glasn == 0 ? "#444" : (kd.glasn > 0 ? "#f44" : "#048"))
                        .arg(kd.nameCapital);
            }
        }
    }
    cand = "<h1>" + cand + "</h1>";
    m_label->setText(cand);
}

void Gameplay::stateChanged()
{
    QString str = "DEBUG";
    if (m_state == STATE__ZV_GL)
        str = "STATE__ZV_GL";
    else if (m_state == STATE__ZV_SOGL)
        str = "STATE__ZV_SOGL";
    else if (m_state == STATE__ZV_SL)
        str = "STATE__ZV_SL";
    else if (m_state == STATE__MOL)
        str = "STATE__MOL";
    else if (m_state == STATE__MOL_GL)
        str = "STATE__MOL_GL";
    else if (m_state == STATE__MOL_SOGL)
        str = "STATE__MOL_SOGL";
    else if (m_state == STATE__MOL_SL)
        str = "STATE__MOL_SL";
    m_debugLabel->setText(str);
}
























































