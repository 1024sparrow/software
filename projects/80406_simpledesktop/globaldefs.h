#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

QColor colors[] = {
    //Qt::blue,
    0x4488ff,
    //0xff8800,
    //Qt::green,
    0x004444,
    Qt::yellow,
    Qt::red
};
//QColor colorGray(16,16,16);
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
/*
 * QQQWWWEEERRRTTTYYYUUUIIIOOOPPP
 * .AAASSSDDDFFFGGGHHHJJJKKKLLL
 * ..ZZZXXXCCCVVVBBBNNNMMM
 * x = x * 3 + rowNum, w = 3
 */

PointDescr pointsMutableBase[] = {
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
    {'J',16,6,1,1},
    {'K',17,7,1,1},
    {'L',18,8,1,2},
    {'Z',19,0,2,0},
    {'X',20,1,2,0},
    {'C',21,2,2,3},
    {'V',22,3,2,3},
    {'B',23,4,2,2},
    {'N',24,5,2,2},
    {'M',25,6,2,1}
};
int pointsCount = sizeof(pointsMutableBase) / sizeof(struct PointDescr);
int maxCountInRow = 10;
int rowCount = 3;
#endif // GLOBALDEFS_H
