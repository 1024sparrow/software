#include "musicplayer_p.h"
#ifdef QT4_USING
    #include "musicplayer_p_qt4.h"
#else
    #include "musicplayer_p_qt5.h"
#endif

#include "boris_h/musicplayer.h"
using namespace boris;

MusicplayerPrivate::MusicplayerPrivate(QObject *parent)
    :QObject(parent)
{
    Musicplayer *player = qobject_cast<Musicplayer *>(parent);
    if (player)
    {
        connect(this, SIGNAL(tick(qint64)), player, SIGNAL(tick(qint64)));
        connect(this, SIGNAL(finished()), player, SIGNAL(finished()));
        connect(this, SIGNAL(totalTimeChanged(qint64)), player, SIGNAL(totalTimeChanged(qint64)));
    }
}

MusicplayerPrivate * MusicplayerPrivate::newInstance(QObject *parent)
{
#ifdef QT4_USING
    return new MusicPlayerPrivateQt4(parent);
#else
    return new MusicPlayerPrivateQt5(parent);
#endif
}

bool MusicplayerPrivate::setSourcePath(const QString &newPath)
{
    if (!setSourcePathImplement(newPath))
        return false;
    sourcePathPrivate = newPath;
    return true;
}

QString MusicplayerPrivate::sourcePath() const
{
    return sourcePathPrivate;
}
