#ifndef HINTFIELD_H
#define HINTFIELD_H
#include <QWidget>
#include <QPainter>

class HintField : public QWidget
{
    Q_OBJECT
private:
    QString m_text;

public:
    HintField(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* p) override;

public slots:
    void slotСhangeText(QString text);
};



#endif // HINTFIELD_H
