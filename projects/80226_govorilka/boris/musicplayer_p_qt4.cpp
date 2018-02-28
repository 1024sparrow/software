#ifdef QT4_USING

#include "musicplayer_p_qt4.h"
#include "boris_h/debug.h"

#include <QTemporaryFile>

using namespace boris;

MusicPlayerPrivateQt4::MusicPlayerPrivateQt4(QObject *parent)
    :MusicplayerPrivate(parent)
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);

    mediaObject->setTickInterval(500);
    connect(mediaObject, SIGNAL(finished()), SLOT(onFinishedPrivate()));
    connect(mediaObject, SIGNAL(tick(qint64)), SLOT(onTickPrivate(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            SLOT(onStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(totalTimeChanged(qint64)), this, SLOT(onD(qint64)));

    Phonon::createPath(mediaObject, audioOutput);
}

bool MusicPlayerPrivateQt4::setSourcePathImplement(const QString &newPath)
{
    mediaObject->stop();
    if (newPath.simplified().isEmpty())
        emit totalTimeChanged(0);
    else
    {
        //mediaObject->setCurrentSource(Phonon::MediaSource(newPath));

        QTemporaryFile tempFileSource;
        if (tempFileSource.open())
        {
            QFile f(newPath);

            f.open(QIODevice::ReadOnly);
            QByteArray data = f.readAll();
            f.close();

            tempFileSource.write(data);
            tempFileSource.close();
        }
        mediaObject->setCurrentSource(Phonon::MediaSource(tempFileSource.fileName()));
    }
    return true;
}

void MusicPlayerPrivateQt4::setPosition(qulonglong newPos)
{
    mediaObject->seek(newPos);
}
qint64 MusicPlayerPrivateQt4::position() const
{
    return mediaObject->currentTime();
}

QString MusicPlayerPrivateQt4::lastError() const
{
    return lastErrorPrivate;
}

void MusicPlayerPrivateQt4::setTickInterval(qint64 ms)
{
    mediaObject->setTickInterval(ms);
}

void MusicPlayerPrivateQt4::play()
{
    bool inpause = (mediaObject->state() == Phonon::PausedState);
    mediaObject->play();
    if (!inpause)
        emit tick(0);
}

void MusicPlayerPrivateQt4::pause()
{
    mediaObject->pause();
}

void MusicPlayerPrivateQt4::stop()
{
    mediaObject->stop();
}

void MusicPlayerPrivateQt4::setVolume(qreal val)
{
    audioOutput->setVolume(qMax(0., qMin(1.,val)));
}

void MusicPlayerPrivateQt4::onTickPrivate(qint64 ms)
{
    emit tick(ms);
}

void MusicPlayerPrivateQt4::onFinishedPrivate()
{
    emit finished();
}

void MusicPlayerPrivateQt4::onStateChanged(Phonon::State newState, Phonon::State oldState)
{
//    bDebug(newState<<oldState);//boris debug 60929
    if (newState == Phonon::ErrorState)
        emit totalTimeChanged(0);
    else if (oldState == Phonon::LoadingState && newState == Phonon::StoppedState)
        emit totalTimeChanged(mediaObject->currentTime() + mediaObject->remainingTime());

    if (newState == Phonon::ErrorState)
    {
        bDebug(mediaObject->errorString());
    }
}

void MusicPlayerPrivateQt4::onD(qint64 p)
{
    bDebug(p);
    emit totalTimeChanged(p);
}

#endif
