#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class MusicplayerPrivate;
class LIBAPP_API Musicplayer : public QObject
{
    Q_OBJECT
public:
    Musicplayer(QObject *parent = 0);
    bool setSourcePath(const QString &newPath);
    QString sourcePath() const;
    void setPosition(qulonglong newPos);
    qint64 position() const;
    QString lastError() const;
    void setTickInterval(qint64 ms);
public slots:
    void play();
    void pause();
    void stop();
    void setVolume(qreal val);
signals:
    void tick(qint64 time_ms);//milliseconds
    void finished();
    void totalTimeChanged(qint64);
private:
    MusicplayerPrivate *d;
};

} // namespace boris

#endif // MUSICPLAYER_H
