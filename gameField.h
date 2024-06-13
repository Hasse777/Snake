#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "snake.h"
#include <QKeyEvent>
#include <QRandomGenerator>

class GameField : public QWidget
{
    Q_OBJECT
private:
    Snake* m_snake;
    SnakeItem* m_snakeFood;
    QTimer* m_Timer;
    int m_gameFieldSizeWidth;
    int m_gameFieldSizeHeight;
    int m_snakeSpeed;
    int m_snakeFoodCounter;
    unsigned short int m_score;
    bool m_moveStop;
    bool m_gameOver;
    bool m_pause;
    QString m_text;
    enum SnakeRoute
    {
        left, right, up, down
    };
    SnakeRoute m_snakeRoute;
    void NewGame();
    void GameOver();
    void ChangeXY_Food();
    bool BoundaryChecking(QPair<int, int> object_1, QPair<int, int> object_2);
protected:
    void paintEvent(QPaintEvent* p) override;
    void keyPressEvent(QKeyEvent* k) override;

public:
    GameField(QWidget* parent = nullptr);
    ~GameField();

public slots:
    void slot_SnakeMove();

signals:
    void ChangeText(QString text);
};


#endif // GAMEFIELD_H
