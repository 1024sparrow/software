#ifndef QT4_USING

#ifndef MUSICPLAYER_P_QT5
#define MUSICPLAYER_P_QT5

#include "musicplayer_p.h"

#include <QMediaPlayer>

namespace boris
{

class MusicPlayerPrivateQt5 : public MusicplayerPrivate
{
    Q_OBJECT
public:
    MusicPlayerPrivateQt5(QObject *parent = 0);
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
    void onStateChanged(QMediaPlayer::State);
    void onDurationChanged(qint64 dura);
private:
    QString lastErrorPrivate;
    QMediaPlayer *mp;
};

} // namespace boris

#endif // MUSICPLAYER_P_QT5

#endif // QT4_USING
