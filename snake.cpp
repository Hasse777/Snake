#include "snake.h"

// Код змейки, начальные размеры элементов и длинны змейки

Snake::Snake()
{
    m_snakeBeginSize = 6;
    m_snakeItemSize = 10;
    for(int i = 0; i < m_snakeBeginSize; i++)
    {
        m_snakeBody.insert(0, new SnakeItem(i, 0));
    }
}

Snake::~Snake()
{
    for(int i = 0; i < this->m_snakeBody.size(); i++)
    {
        delete m_snakeBody[i];
    }
}

int Snake::Get_ItemSize() const
{
    return this->m_snakeItemSize;
}





// координаты элементов змейки

SnakeItem::SnakeItem(int x, int y)
{
    this->m_x = x;
    this->m_y = y;
}


