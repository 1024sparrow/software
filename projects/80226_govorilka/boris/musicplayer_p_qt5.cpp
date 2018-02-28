#ifndef QT4_USING

#include "musicplayer_p_qt5.h"
#include "boris_h/debug.h"

using namespace boris;

MusicPlayerPrivateQt5::MusicPlayerPrivateQt5(QObject *parent)
    :MusicplayerPrivate(parent)
{
    mp = new QMediaPlayer(this);
    connect(mp, SIGNAL(positionChanged(qint64)), this, SLOT(onTickPrivate(qint64)));
    connect(mp, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onStateChanged(QMediaPlayer::State)));
    connect(mp, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
}

bool MusicPlayerPrivateQt5::setSourcePathImplement(const QString &newPath)
{
    mp->stop();
    if (newPath.simplified().isEmpty())
        emit totalTimeChanged(0);
    else
        mp->setMedia(QUrl::fromLocalFile(newPath));
    return true;
}

void MusicPlayerPrivateQt5::setPosition(qulonglong newPos)
{
    mp->setPosition(newPos);
}
qint64 MusicPlayerPrivateQt5::position() const
{
    return mp->position();
}

QString MusicPlayerPrivateQt5::lastError() const
{
    return lastErrorPrivate;
}

void MusicPlayerPrivateQt5::setTickInterval(qint64 ms)
{
    mp->setNotifyInterval(ms);
}

void MusicPlayerPrivateQt5::play()
{
    bool inpause = (mp->state() == QMediaPlayer::PausedState);
    mp->play();
    if (!inpause)
        emit tick(0);
}

void MusicPlayerPrivateQt5::pause()
{
    mp->pause();
}

void MusicPlayerPrivateQt5::stop()
{
    mp->stop();
}

void MusicPlayerPrivateQt5::setVolume(qreal val)
{
    mp->setVolume(val);
}

void MusicPlayerPrivateQt5::onTickPrivate(qint64 ms)
{
    emit tick(ms);
}

void MusicPlayerPrivateQt5::onStateChanged(QMediaPlayer::State s)
{
    if (s == QMediaPlayer::StoppedState)
        emit finished();
}

void MusicPlayerPrivateQt5::onDurationChanged(qint64 dura)
{
    emit totalTimeChanged(dura);
}

#endif
