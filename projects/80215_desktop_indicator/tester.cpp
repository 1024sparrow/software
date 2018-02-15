#include "tester.h"
#include "footer.h"

#include <QBoxLayout>
#include <QPushButton>

Tester::Tester(Footer *footer, QWidget *parent)
    :QWidget(parent), m_footer(footer)
{
    QBoxLayout *lay = new QVBoxLayout(this);
    QPushButton *bnQ = new QPushButton("Q", this);
    QPushButton *bnW = new QPushButton("W", this);
    QPushButton *bnE = new QPushButton("E", this);
    QPushButton *bnMode = new QPushButton("mode", this);
    lay->addWidget(bnQ);
    lay->addWidget(bnW);
    lay->addWidget(bnE);
    lay->addWidget(bnMode);
    connect(bnQ, SIGNAL(clicked()), SLOT(onQ()));
    connect(bnW, SIGNAL(clicked()), SLOT(onW()));
    connect(bnE, SIGNAL(clicked()), SLOT(onE()));
    connect(bnMode, SIGNAL(clicked()), SLOT(onMode()));
    show();
}

void Tester::onQ()
{
    m_footer->onSwitched('Q');
}

void Tester::onW()
{
    m_footer->onSwitched('W');
}

void Tester::onE()
{
    m_footer->onSwitched('E');
}

void Tester::onMode()
{
    m_footer->onModeSwicthed();
}
