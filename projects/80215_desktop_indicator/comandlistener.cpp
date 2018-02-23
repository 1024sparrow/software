#include "comandlistener.h"
#include <stdio.h>
#include <QDebug>

ComandListener::ComandListener(QObject *parent)
    :QThread(parent)
{

}

void ComandListener::run()
{
    /*FILE *fp;
    fp=fopen("/home/boris/.desktop_indicator.fifo", "r");
    char c;
    while((c=getc(fp)) != EOF)
    {
        printf("%c",c);
    }
    qDebug()<<"++++++++";
    fclose(fp);*/

    FILE *fp;
    fp=fopen("/home/boris/.desktop_indicator.fifo", "r");
    //bool bCommandTypeDetermined = false;
    //bool bSwitchToDesktop = false;
    //bool bSwitchToMode = false;
    char command = 0;//0 - not command ; 1 - change desktop ; 2 - change mode
    while (true)
    {
        char c = getc(fp);
        if (command == 1)
        {
            command = 0;
            emit sgnSwitch(c);
        }
        else if (command == 2)
        {
            command = 0;
            if (c == 'f')//forward
                emit sgnSwitchModeUp();
            else if (c == 'b')//backward
                emit sgnSwitchModeDown();
        }
        else
        {
            if (c == 'd')
                command = 1;
            else if (c == 'm')
                command = 2;
            else
                command = 0;
        }
        //
    }
    qDebug()<<"++++++++";
    fclose(fp);
}
