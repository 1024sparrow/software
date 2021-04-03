#include "comandlistener.h"
#include <stdio.h>
#include <QDebug>

ComandListener::ComandListener(QObject *parent)
	:QThread(parent)
{

}

/*
 * dA - переключиться на рабочий стол A
 * mf - переключиться на следующую группу рабочих столов (mode forward)
 * mb - переключиться на предыдущую группу рабочих столов (mode backward)
 * c - активация/деактивация детского режима
 */
void ComandListener::run()
{
	FILE *fp;
	fp=fopen("/home/boris/.desktop_indicator.fifo", "r");
	if (fp)
	{
		emit sgnInitialize();
	}
	char command = 0; // 0 - not command ; 1 - change desktop ; 2 - change mode
	while (true)
	{
		int nC = getc(fp);
		if (nC < 0)
		{
			fp=fopen("/home/boris/.desktop_indicator.fifo", "r");
			continue;
		}
		char c = static_cast<char>(nC);
		if (command == 1)
		{
			command = 0;

			emit sgnSwitch(c);
		}
		else if (command == 2)
		{
			command = 0;
			if (c == 'f' )// forward
				emit sgnSwitchModeUp();
			else if (c == 'b') // backward
				emit sgnSwitchModeDown();
		}
		else
		{
			if (c == 'd')
			{
				command = 1;
			}
			else if (c == 'm')
			{
				command = 2;
			}
			else
			{
				command = 0;
			}
		}
	}
	fclose(fp);
}
