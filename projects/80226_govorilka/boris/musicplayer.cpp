#include "boris_h/musicplayer.h"
#include "musicplayer_p.h"
#include "musicplayer_p_qt4.h"
#include "musicplayer_p_qt5.h"
#include "boris_h/debug.h"

using namespace boris;

Musicplayer::Musicplayer(QObject *parent)
    :QObject(parent)
{
    d = MusicplayerPrivate::newInstance(this);
}

bool Musicplayer::setSourcePath(const QString &newPath)
{
    return d->setSourcePath(newPath);
}

QString Musicplayer::sourcePath() const
{
    return d->sourcePath();
}

void Musicplayer::setPosition(qulonglong newPos)
{
    d->setPosition(newPos);
}

qint64 Musicplayer::position() const
{
    return d->position();
}

QString Musicplayer::lastError() const
{
    return d->lastError();
}

void Musicplayer::setTickInterval(qint64 ms)
{
    d->setTickInterval(ms);
}

void Musicplayer::play()
{
    d->play();
}

void Musicplayer::pause()
{
    d->pause();
}

void Musicplayer::stop()
{
    d->stop();
}

void Musicplayer::setVolume(qreal val)
{
    d->setVolume(val);
}
