#include "hintField.h"



HintField::HintField(QWidget *parent)
{
    setFixedSize(320, 50);
    m_text = "Очки : 0\nПауза - ПРОБЕЛ";
}

void HintField::paintEvent(QPaintEvent *p)
{
    QPainter painter;
    painter.begin(this);
    painter.setFont(QFont("Verdana", 8, 700));
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, m_text);
    painter.end();
}

void HintField::slotСhangeText(QString text)
{
    m_text = text;
    repaint();
}
