#ifndef SNAKE_H
#define SNAKE_H
#include <QList>


class SnakeItem;


class Snake
{
private:
    int m_snakeItemSize;
    int m_snakeBeginSize;
public:
    QList <SnakeItem*> m_snakeBody;

    Snake();
    ~Snake();
    int Get_ItemSize() const;
};


class SnakeItem
{
private:

public:
    int m_x;
    int m_y;
    explicit SnakeItem(int x, int y);
};


#endif // SNAKE_H
