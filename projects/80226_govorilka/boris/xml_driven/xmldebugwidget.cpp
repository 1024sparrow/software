#include "boris_h/xml_driven/xmldebugwidget.h"
#include "boris_h/btr.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>

using namespace boris;

XmlDebugWidget::XmlDebugWidget(XmlPublisher *xmlPublisher, QWidget *parent)
    :QWidget(parent), XmlSubscriber(xmlPublisher)
{
    QPushButton *bnApply = new QPushButton(btr("Применить XML"), this);
    connect(bnApply, SIGNAL(clicked()), SLOT(onBnApplyXmlClicked()));

    te = new QTextEdit(this);

    QBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(bnApply);
    lay->addWidget(te);
}

void XmlDebugWidget::processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain)
{
    Q_UNUSED(ifResetXmlChain);
    te->setPlainText(domdoc.toString());
}

void XmlDebugWidget::onBnApplyXmlClicked()
{
    QString xml = te->toPlainText();
    QDomDocument tmpDoc;
    QString errorString;
    int errLine(0), errColumn(0);
    tmpDoc.setContent(xml, &errorString, &errLine, &errColumn);
    if (errorString.isEmpty())
    {
        m_domdoc = tmpDoc;
        registerXmlDataChanges();
    }
    else
    {
        QMessageBox::warning(this,
                             btr("Ошибка."),
                             btr("Некорректный XML. Отказ от применения.\n%1(line %2, column %3)")
                                .arg(errorString)
                                .arg(errLine)
                                .arg(errColumn)
                             );
        xml = m_domdoc.toString();
        te->setPlainText(xml);
    }
}
