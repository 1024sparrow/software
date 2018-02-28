#ifndef LABELTEXTMANUPULATOR_H
#define LABELTEXTMANUPULATOR_H

#include <QObject>
#include <QLabel>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class LIBAPP_API LabelTextManupulator : public QObject
{
    Q_OBJECT
public:
    LabelTextManupulator(QObject *parent);
    void registerSubscriber(QLabel *label, bool hideIfEmpty);
    void setText(const QString &text);
    void clear();
signals:
    void textChanged(const QString &);
    void setVisible(bool);
};

} // namespace boris

#endif // LABELTEXTMANUPULATOR_H
