#ifndef MUSICPLAYER_P_H
#define MUSICPLAYER_P_H

#include <QObject>

namespace boris
{

class MusicplayerPrivate : public QObject
{
    Q_OBJECT
public:
    MusicplayerPrivate(QObject *parent = 0);
    static MusicplayerPrivate * newInstance(QObject *parent);
    bool setSourcePath(const QString &newPath);
    QString sourcePath() const;
    virtual void setPosition(qulonglong newPos) = 0;
    virtual qint64 position() const = 0;
    virtual QString lastError() const = 0;
    virtual void setTickInterval(qint64 ms) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void setVolume(qreal val) = 0;
signals:
    void tick(qint64 time_ms);//milliseconds
    void finished();
    void totalTimeChanged(qint64);
protected:
    virtual bool setSourcePathImplement(const QString &newPath) = 0;

public:
    QString sourcePathPrivate;
};

} // namespace boris

#endif // MUSICPLAYER_P_H
