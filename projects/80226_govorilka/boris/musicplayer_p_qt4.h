#ifdef  QT4_USING

#ifndef MUSICPLAYER_P_QT4
#define MUSICPLAYER_P_QT4

#include "musicplayer_p.h"

#include <Phonon/AudioOutput>
#include <Phonon/SeekSlider>
#include <Phonon/MediaObject>
#include <Phonon/VolumeSlider>
#include <Phonon/BackendCapabilities>
#include <Phonon/AudioDataOutput>

namespace boris
{

class MusicPlayerPrivateQt4 : public MusicplayerPrivate
{
    Q_OBJECT
public:
    MusicPlayerPrivateQt4(QObject *parent = 0);
    bool setSourcePathImplement(const QString &newPath);
    void setPosition(qulonglong newPos);
    qint64 position() const;
    QString lastError() const;
    void setTickInterval(qint64 ms);
    void play();
    void pause();
    void stop();
    void setVolume(qreal val);
private slots:
    void onTickPrivate(qint64 ms);
    void onFinishedPrivate();
    void onStateChanged(Phonon::State newState,Phonon::State oldState);
    void onD(qint64 p);

private:
    QString lastErrorPrivate;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
};

} // namespace boris

#endif // MUSICPLAYER_P_QT4

#endif // QT4_USING
