#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>

class QPaintEvent;
class QResizeEvent;
class QKeyEvent;
class Display;
namespace boris
{
    class Musicplayer;
}
class Gameplay : public QWidget
{
    Q_OBJECT
public:
    Gameplay();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent (QKeyEvent * event);
    void keyReleaseEvent (QKeyEvent * event);
    void play(const char *str); // если передан нулевой указатель, то сигнализировать о некорректной комбинации букв
    void stop();
private slots:
    void onPlaybackFinished();

private:
    Display *m_display;
    enum
    {
        STATE__ZV_GL, // звучит гласная
        STATE__ZV_SOGL, // звучит согласная
        STATE__ZV_SL, // звучит слог
        STATE__MOL, // не звучит (и ещё ничего не звучало). В это состояние переходить, если ничего на нажималось в течение некоторого времени.
        STATE__MOL_GL, // не звучит, звучала последний раз гласная
        STATE__MOL_SOGL, // не звучит, звучала последний раз согласная
        STATE__MOL_SL // не звучит, звучал последний раз слог
    } m_state;
    char m_lastPlaying[1024];
    boris::Musicplayer *m_player;

};

#endif // GAMEPLAY_H
