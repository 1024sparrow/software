#ifndef BTR_H
#define BTR_H

#include <QTextCodec>

#ifndef SOURCE_ENCODING
#define SOURCE_ENCODING "CP1251"
#endif

inline QString btr(const char *str)
{
    QTextCodec *_codec = QTextCodec::codecForName(SOURCE_ENCODING);
    return _codec->toUnicode(str);
}

#endif // BTR_H
