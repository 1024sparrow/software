#include "boris_h/labeltextmanupulator.h"

using namespace boris;

LabelTextManupulator::LabelTextManupulator(QObject *parent)
    :QObject(parent)
{
}

void LabelTextManupulator::registerSubscriber(QLabel *label, bool hideIfEmpty)
{
    connect(this, SIGNAL(textChanged(QString)), label, SLOT(setText(QString)));
    if (hideIfEmpty)
        connect(this, SIGNAL(setVisible(bool)), label, SLOT(setVisible(bool)));
}

void LabelTextManupulator::setText(const QString &text)
{
    emit textChanged(text);
    emit setVisible(!text.isEmpty());
}

void LabelTextManupulator::clear()
{
    emit textChanged(QString());
    emit setVisible(false);
}
