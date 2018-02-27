#ifndef XMLDELEGATE_H
#define XMLDELEGATE_H

namespace boris
{
    class XmlDelegatePlugin;
    class XmlDelegatePrivate;
}

class QString;

#include <QItemDelegate>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class LIBAPP_API XmlDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    XmlDelegate(QObject *parent = 0);
    void registerPlugin(const QString &tagName, XmlDelegatePlugin *plugin);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    XmlDelegatePrivate *d;
};

} // namespace boris

#endif // XMLDELEGATE_H
