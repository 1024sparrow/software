#include "footer.h"

#include <QImage>
#include <QPixmap>
#include <QProcess>
#include <QSet>
#include <QPainter>
#include <QDebug>//
#include <QTemporaryFile>

QColor colors[] = {
    //Qt::blue,
    0x4488ff,
    //0xff8800,
    //Qt::green,
    //0x004444,
    0x4488ff,
    0xffff80,
    0xff8080
};
QColor bgColors[] = {
    0x000001,
    0x000001,
    0x000001,
    0x404040
};
//QColor colorGray(16,16,16);
//QColor colorGray(32,32,32);
QColor colorGray(64,64,64);

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
    /*{'Q',0,0,0,0},
    {'W',1,1,0,0},
    {'E',2,2,0,3},
    {'R',3,3,0,3},
    {'T',4,5,0,2},
    {'Y',5,6,0,2},
    {'U',6,8,0,3},
    {'I',7,9,0,3},
    {'O',8,10,0,3},
    {'P',9,11,0,3},
    {'A',10,0,1,0},
    {'S',11,1,1,0},
    {'D',12,2,1,3},
    {'F',13,3,1,3},
    {'G',14,5,1,2},
    {'H',15,6,1,2},
    {'J',16,8,1,1},//fixed
    {'K',17,9,1,1},//fixed
    {'L',18,11,1,2},
    {'Z',19,0,2,0},
    {'X',20,1,2,0},
    {'C',21,2,2,3},
    {'V',22,3,2,3},
    {'B',23,5,2,2},
    {'N',24,6,2,2},
    {'M',25,8,2,1},//fixed
    */

    {'Q',0,0,0,0},
    {'W',1,1,0,0},
    {'E',2,2,0,3},
    {'R',3,3,0,3},
    {'T',4,4,0,2},
    {'Y',5,5,0,2},
    {'U',6,6,0,3},
    {'I',7,7,0,3},
    {'O',8,8,0,3},
    {'P',9,9,0,3},
    {'A',10,0,1,0},
    {'S',11,1,1,0},
    {'D',12,2,1,3},
    {'F',13,3,1,3},
    {'G',14,4,1,2},
    {'H',15,5,1,2},
    {'J',16,6,1,1},//fixed
    {'K',17,7,1,1},//fixed
    {'L',18,8,1,2},
    {'Z',19,0,2,0},
    {'X',20,1,2,0},
    {'C',21,2,2,3},
    {'V',22,3,2,3},
    {'B',23,4,2,2},
    {'N',24,5,2,2},
    {'M',25,6,2,1},//fixed
};
int pointsCount = sizeof(pointsMutableBase) / sizeof(struct PointDescr);
//QSet<int> pointsFixed = QSet<int>()<<16<<17<<25;
QSet<int> Footer::pointsFixed = QSet<int>()<<'J'<<'K'<<'M';
/*PointDescr pointsFixed[] = {
    {'J',16,9,1,0},//fixed
    {'K',17,10,1,0},//fixed
    {'M',25,9,2,0}//fixed
};*/

void Footer::updatePixmaps()
{
    if (animationTimerId)
        killTimer(animationTimerId);

    //QSet<int> usingDesktops;
    usingDesktops.clear();
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
                    else if (*p_string == '-')
                    {
                        num = -1;
                        break;
                    }
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
            if (num >= 0)
                usingDesktops.insert(num);
        }
    }
    //qDebug()<<usingDesktops;
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

    QImage imgBlack(w, h, QImage::Format_RGB32);
    imgBlack.fill(Qt::black);
    QImage imgGray = imgBlack;
    for (int iPoint = 0 ; iPoint < pointsCount ; iPoint++)
    {
        struct PointDescr point = pointsMutableBase[iPoint];
        //imgGray.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + (POINT_SIZE/2 ), point.y * POINT_SIZE + (POINT_SIZE/2 ), colorGray.rgb());
        //imgGray.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + (POINT_SIZE/2 ), point.y * POINT_SIZE + (POINT_SIZE/2 ), colors[point.colorIndex].rgb());
        for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
        {
            for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
            {
                //imgGray.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colorGray.rgb());
                imgGray.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, bgColors[point.colorIndex].rgb());
            }
        }
    }
    QImage img;

    for (int iMode = 0 ; iMode < MODE_COUNT ; iMode++)
    {
        img = imgGray;
        for (int iPoint = 0 ; iPoint < pointsCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            if (!pointsFixed.contains(point.id))
                point.id_num += (pointsCount * iMode);
            //if (pointsFixed.contains(point.id_num))
            if (usingDesktops.contains(point.id_num) || (point.id == m_cur && iMode == m_mode))
            {
                for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
                {
                    for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
                    {
                        //img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, qRgb(255,255,255));
                        img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                    }
                }
            }
        }
        painterPix0.drawImage(((iMode + MODE_COUNT / 2) % MODE_COUNT) * w,0,img);

        img = imgGray;
        //img.fill(Qt::red);
        for (int iPoint = 0 ; iPoint < pointsCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            //if (pointsFixed.contains(point.id_num))
            //if (point.id == m_cur && iMode != m_mode)
            if (!pointsFixed.contains(point.id))
                point.id_num += (pointsCount * iMode);
            if (iMode != m_mode)
            {
                if (usingDesktops.contains(point.id_num)){
                    for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
                    {
                        for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
                        {
                            img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                        }
                    }
                }
            }
            //if (point.id == m_cur && iMode == m_mode)
            if (point.id != m_cur && iMode == m_mode)
            {
                if (usingDesktops.contains(point.id_num)){
                    for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
                    {
                        for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
                        {
                            img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                        }
                    }
                }
            }
        }
        painterPix1.drawImage(((iMode + MODE_COUNT / 2) % MODE_COUNT) * w,0,img);

        //img = (iMode == m_mode) ? imgGray : imgBlack;
        img = imgGray;
        for (int iPoint = 0 ; iPoint < pointsCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            if (!pointsFixed.contains(point.id))
                point.id_num += (pointsCount * iMode);
            if (iMode != m_mode)
            {
                if (usingDesktops.contains(point.id_num)){
                    for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
                    {
                        for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
                        {
                            img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                        }
                    }
                }
            }
            //if (pointsFixed.contains(point.id_num))
            if (iMode == m_mode)
            {
                if (usingDesktops.contains(point.id_num) || (point.id == m_cur)){
                    for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
                    {
                        for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
                        {
                            img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                        }
                    }
                }
            }

//            if (usingDesktops.contains(point.id_num)){
//                for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
//                {
//                    for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
//                    {
//                        img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
//                    }
//                }
//            }
        }
        painterPix2.drawImage(((iMode + MODE_COUNT / 2) % MODE_COUNT) * w,0,img);

        //img = (iMode == m_mode) ? imgGray : imgBlack;
        img = imgGray;
        for (int iPoint = 0 ; iPoint < pointsCount ; iPoint++)
        {
            struct PointDescr point = pointsMutableBase[iPoint];
            if (!pointsFixed.contains(point.id))
                point.id_num += (pointsCount * iMode);
            if (iMode != m_mode)
            {
                if (usingDesktops.contains(point.id_num)){
                    for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
                    {
                        for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
                        {
                            img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                        }
                    }
                }
            }
            //if (pointsFixed.contains(point.id_num))
            if (point.id != m_cur && iMode == m_mode)
            {
                if (usingDesktops.contains(point.id_num)){
                    for (int x = POINT_PADDING ; x < POINT_SIZE ; x++)
                    {
                        for (int y = POINT_PADDING ; y < POINT_SIZE ; y++)
                        {
                            img.setPixel(point.x * POINT_SIZE + point.y * (POINT_SIZE/3) + x, point.y * POINT_SIZE + y, colors[point.colorIndex].rgb());
                        }
                    }
                }
            }
        }
        painterPix3.drawImage(((iMode + MODE_COUNT / 2) % MODE_COUNT) * w,0,img);
    }

    if (animationTimerId)
        animationTimerId = startTimer(animDuration);
}

int Footer::desktopNum(char id, char mode)
{
    for (int iPoint = 0 ; iPoint < pointsCount ; iPoint++)
    {
        const struct PointDescr &point = pointsMutableBase[iPoint];
        if (point.id == id)
            return pointsFixed.contains(id) ? point.id_num : point.id_num + mode * pointsCount;
    }
    return -1;
}


















































