/*
 * author VasilyevBP
 * codepage cp1251
 *
 * Тип данных - xml-документ для отображения XmlDelegate-ом
 * Если XmlString установить в QVariant, даваемый моделью, делегат поймёт,
 * что имеет дело с XML, а не с обычным текстом
 *
 * 17 июня 2016г.
 */

#ifndef XMLSTRING_H
#define XMLSTRING_H

#include <QString>
#include <QVariant>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

//typedef QString XmlString;
struct LIBAPP_API XmlString
{
    XmlString(const QString &t = QString())
    {
        text = t;
    }
    QString text;
};

} // namespace boris

Q_DECLARE_METATYPE(boris::XmlString)

#endif // XMLSTRING_H
