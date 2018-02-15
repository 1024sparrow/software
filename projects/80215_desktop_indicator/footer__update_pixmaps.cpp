#include "footer.h"

#include <QImage>
#include <QPixmap>

QColor colors[] = {Qt::blue, Qt::green, Qt::yellow, Qt::red};

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
PointDescr pointsFixed[] = {
    {'J',16,9,1,0},//fixed
    {'K',17,10,1,0},//fixed
    {'M',25,9,2,0}//fixed
};

/*
 * p_type:
 *   0 - серый
 *   1 - текущий рабочий стол только
 *   2 - все активные рабочие столы
 * p_mode - для которой группы рабочих столов
 */

QPixmap getPixmap(int p_type, int p_mode)
{
    //
}

void Footer::updatePixmaps()
{
    if (animationTimerId)
        killTimer(animationTimerId);

    //запускаем утилиту "wmctrl -l" через QProcess
    // когда получаем ответ от того процесса, вот этот нижележащий код выполняем
    int w_single = 15 * POINT_SIZE;
    int w = w_single * MODE_COUNT;
    int h = 6 * POINT_SIZE;
    m_pix[0] = QPixmap(w, h);
    m_pix[1] = QPixmap(w, h);
    m_pix[2] = QPixmap(w, h);
    m_pix[3] = QPixmap(w, h);
    m_pix[0].fill(Qt::red);
    m_pix[1].fill(Qt::blue);
    m_pix[2].fill(Qt::white);
    m_pix[3].fill(Qt::blue);

    if (animationTimerId)
        animationTimerId = startTimer(animDuration);
}
