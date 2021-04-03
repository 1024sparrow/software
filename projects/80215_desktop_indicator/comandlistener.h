#ifndef COMANDLISTENER_H
#define COMANDLISTENER_H

#include <QString>
#include <QThread>

class ComandListener : public QThread
{
	Q_OBJECT
public:
	ComandListener(QObject *parent=0);
	void run();
signals:
	void sgnSwitch(char id);
	void sgnSwitchModeUp();
	void sgnSwitchModeDown();
	void sgnInitialize();
private:
	void setupDesktopCount();
};

#endif // COMANDLISTENER_H
