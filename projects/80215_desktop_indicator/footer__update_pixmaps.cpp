#include "footer.h"

#include <QImage>
#include <QPixmap>
#include <QProcess>
#include <QSet>
#include <QPainter>
#include <QDebug>//

QColor colors[] = {
    //Qt::blue,
    0x4488ff,
    Qt::green,
    Qt::yellow,
    Qt::red
};
QColor colorGray(32,32,32);

// Характеристики точки, описывающей рабочий стол
struct PointDescr
{
    char id;
    int id_num;//числовой идентификатор рабочего стола
    char x;
    char y;
    char colorIndex;
};

const int fixedCount = 3; // число рабочих столов, которые не переключаются между группами рабочих столов
const int pointsMutableBaseCount = 23; // 26 - fixedCount
PointDescr pointsMutableBase[] = {
    {'Q',0,0,0,0},
    {'W',1,1,0,0},
    {'E',2,3,0,1},
    {'R',3,4,0,1},
    {'T',4,6,0,2},
    {'Y',5,7,0,2},
    {'U',6,9,0,3},
    {'I',7,10,0,3},
    {'O',8,11,0,3},
    {'P',9,12,0,3},
    {'A',10,0,1,0},
    {'S',11,1,1,0},
    {'D',12,3,1,1},
    {'F',13,4,1,1},
    {'G',14,6,1,2},
    {'H',15,7,1,2},
    //{'J',16,9,1,0},//fixed
    //{'K',17,10,1,0},//fixed
    {'L',18,11,1,1},
    {'Z',19,0,2,0},
    {'X',20,1,2,0},
    {'C',21,3,2,1},
    {'V',22,4,2,1},
    {'B',23,6,2,2},
    {'N',24,7,2,2}
    //{'M',25,9,2,0},//fixed
};
QSet<int> pointsFixed = QSet<int>()<<16<<17<<25;
/*PointDescr pointsFixed[] = {
    {'J',16,9,1,0},//fixed
    {'K',17,10,1,0},//fixed
    {'M',25,9,2,0}//fixed
};*/

void Footer::updatePixmaps()
{
    if (animationTimerId)
        killTimer(animationTimerId);

    QSet<int> usingDesktops;
    {
        QProcess *process = new QProcess(this);
        process->start("wmctrl -l");
        process->waitForFinished();
        char string[4096];
        int bytes;
        int state;
        char *p_string;
        while ((bytes = process->readLine(string, sizeof(string))) > 0)
        {
            p_string = string;
            //qDebug()<<string;
            state = 0;
            /*
             * 0 - до первого пробела
             * 1 - в пробелах между первой и второй цмфрами
             * 2 - в процессе считывания номера рабочего стола
             */
            int num = 0;
            for (int i = 0 ; (i < bytes) ; i++){
                if (state == 0 && *p_string == ' ')
                    state = 1;
                else if (state == 1 && *p_string != ' ')
                    state = 2;
                if (state == 2)
                {
                    if (*p_string == ' ')
                        break;
                    else
                    {
                        int digit = 0;
                        switch(*p_string){
                            case '1':digit = 1;break;
                            case '2':digit = 2;break;
                            case '3':digit = 3;break;
                            case '4':digit = 4;break;
                            case '5':digit = 5;break;
                            case '6':digit = 6;break;
                            case '7':digit = 7;break;
                            case '8':digit = 8;break;
                            case '9':digit = 9;break;
                        }
                        num = 10 * num + digit;
                    }
                }
                ++p_string;
            }
            //qDebug()<<num;
            usingDesktops.insert(num);
        }
    }
    qDebug()<<usingDesktops;
    //return;//

    const int w = 15 * POINT_SIZE;
    const int h = 3 * POINT_SIZE;
    m_pix[0] = QPixmap(MODE_COUNT * w, h);
    m_pix[1] = QPixmap(MODE_COUNT * w, h);
    m_pix[2] = QPixmap(MODE_COUNT * w, h);
    m_pix[3] = QPixmap(MODE_COUNT * w, h);
    QPainter painterPix0(&m_pix[0]);
    QPainter painterPix1(&m_pix[1]);
    QPainter painterPix2(&m_pix[2]);
    QPainter painterPix3(&m_pix[3]);

    QImage imgGray(w, h, QImage::Format_RGB32);
    imgGray.fill(Qt::black);
    for (int iPoint = 0, iPointCount = sizeof(pointsMutableBase) / sizeof(struct PointDescr) ; iPoint < iPointCount ; iPoint++)
    {
        struct PointDescr point = pointsMutableBase[iPoint];
        for (int x = 0 ; x < POINT_SIZE ; x++)
        {
            for (int y = 0 ; y < POINT_SIZE ; y++)
            {
                imgGray.setPixel(point.x * POINT_SIZE + x, point.y * POINT_SIZE + y, colorGray.rgb());
            }
        }
    }
    QImage img;

    for (int iMode = 0 ; iMode < MODE_COUNT ; iMode++)
    {
        img = imgGray;
        qDebug()<<"----";
        for (int iPoint = 0, iPointCount = sizeof(pointsMutableBase) / sizeof(struct PointDescr) ; iPoint < iPointCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            //if (pointsFixed.contains(point.id_num))
            if (usingDesktops.contains(point.id_num)){
                qDebug()<<"x:"<<(int)point.x;
                for (int x = 0 ; x < POINT_SIZE ; x++)
                {
                    for (int y = 0 ; y < POINT_SIZE ; y++)
                    {
                        //img.setPixel(point.x * POINT_SIZE + x, point.y * POINT_SIZE + y, qRgb(255,255,255));
                        img.setPixel(point.x * POINT_SIZE + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                    }
                }
            }
        }
        painterPix0.drawImage(0,0,img);

        img = imgGray;
        //img.fill(Qt::red);
        for (int iPoint = 0, iPointCount = sizeof(pointsMutableBase) / sizeof(struct PointDescr) ; iPoint < iPointCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            //if (pointsFixed.contains(point.id_num))
        }
        painterPix1.drawImage(0,0,img);

        img = imgGray;
        for (int iPoint = 0, iPointCount = sizeof(pointsMutableBase) / sizeof(struct PointDescr) ; iPoint < iPointCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            //if (pointsFixed.contains(point.id_num))
            if (usingDesktops.contains(point.id_num)){
                for (int x = 0 ; x < POINT_SIZE ; x++)
                {
                    for (int y = 0 ; y < POINT_SIZE ; y++)
                    {
                        img.setPixel(point.x * POINT_SIZE + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                    }
                }
            }
        }
        painterPix2.drawImage(0,0,img);

        img = imgGray;
        for (int iPoint = 0, iPointCount = sizeof(pointsMutableBase) / sizeof(struct PointDescr) ; iPoint < iPointCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            //if (pointsFixed.contains(point.id_num))
        }
        painterPix3.drawImage(0,0,img);
    }

    //запускаем утилиту "wmctrl -l" через QProcess
    // когда получаем ответ от того процесса, вот этот нижележащий код выполняем
    /*int w_single = 15 * POINT_SIZE;
    int w = w_single * MODE_COUNT;
    int h = 6 * POINT_SIZE;
    m_pix[0] = QPixmap(w, h);
    m_pix[1] = QPixmap(w, h);
    m_pix[2] = QPixmap(w, h);
    m_pix[3] = QPixmap(w, h);
    m_pix[0].fill(Qt::red);
    m_pix[1].fill(Qt::blue);
    m_pix[2].fill(Qt::white);
    m_pix[3].fill(Qt::blue);*/

    if (animationTimerId)
        animationTimerId = startTimer(animDuration);
}


















































