#include "boris_h/dialog.h"

#include <QBoxLayout>
#include <QFrame>
#include <QPushButton>

namespace boris
{

Dialog::Dialog(const QString &okButtonText, const QString &cancelByttonText, QWidget *parent)
    :QDialog(parent)
{
    if (parent)
        setWindowTitle(parent->windowTitle());
    contentContainer = new QFrame(this);
    {
        QHBoxLayout *containerLay = new QHBoxLayout(contentContainer);
        containerLay->setMargin(0);
    }
    QFrame *buttonsWidget = new QFrame(this);
    {
        QPushButton *bnOk = new QPushButton(okButtonText, buttonsWidget);
        QPushButton *bnCancel = 0;
        if (!cancelByttonText.isEmpty())
        {
            bnCancel = new QPushButton(cancelByttonText, buttonsWidget);
            connect(bnCancel, SIGNAL(clicked()), SLOT(reject()));
        }

        connect(bnOk, SIGNAL(clicked()), SLOT(accept()));

        QHBoxLayout *buttonsLay = new QHBoxLayout(buttonsWidget);
        buttonsLay->addStretch();
        buttonsLay->addWidget(bnOk);
        if (bnCancel)
            buttonsLay->addWidget(bnCancel);
    }

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->setMargin(0);
    mainLay->setSpacing(0);
    mainLay->addWidget(contentContainer);
    mainLay->addWidget(buttonsWidget);
}

void Dialog::setContentWidget(QWidget *contentWidget)
{
    //qDeleteAll(contentContainer->children());
    contentContainer->layout()->addWidget(contentWidget);
}

}//monitordocs
