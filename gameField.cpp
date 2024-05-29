#include "gameField.h"


GameField::GameField(QWidget *parent)
{
    setFixedSize(320, 320);
    setFocusPolicy(Qt::StrongFocus);
    this->NewGame();
}

GameField::~GameField()
{
    delete m_snake;
    delete m_snakeFood;
    delete m_Timer;
}

void GameField::slot_SnakeMove()
{
    if(!this->m_pause)
    {
        SnakeItem* temp = nullptr;
        //отлавливаем нажатие стрелок для того чтобы змейка меняла направление
        if(m_snakeRoute == SnakeRoute::right && m_snakeRoute != SnakeRoute::left)
        {
            temp = new SnakeItem(m_snake->m_snakeBody[0]->m_x + 1, m_snake->m_snakeBody[0]->m_y);
        }
        else if(m_snakeRoute == SnakeRoute::left && m_snakeRoute != SnakeRoute::right)
        {
            temp = new SnakeItem(m_snake->m_snakeBody[0]->m_x - 1, m_snake->m_snakeBody[0]->m_y);
        }
        else if(m_snakeRoute == SnakeRoute::up && m_snakeRoute != SnakeRoute::down)
        {
            temp = new SnakeItem(m_snake->m_snakeBody[0]->m_x, m_snake->m_snakeBody[0]->m_y - 1);
        }
        else if(m_snakeRoute == SnakeRoute::down && m_snakeRoute != SnakeRoute::up)
        {
            temp = new SnakeItem(m_snake->m_snakeBody[0]->m_x, m_snake->m_snakeBody[0]->m_y + 1);
        }
        else throw("Undefined type temp-x");
        //-------------------------------------------------------------------------------------------

        //ограничение игрового поля
        if(temp->m_x  >= this->m_gameFieldSizeWidth)
        {
            temp->m_x = 0;
        }
        else if(temp->m_x < 0)
        {
            temp->m_x = this->m_gameFieldSizeWidth - 1;
        }
        else if(temp->m_y < 0)
        {
            temp->m_y = this->m_gameFieldSizeHeight - 1;
        }
        else if(temp->m_y >= this->m_gameFieldSizeHeight)
        {
            temp->m_y = 0;
        }


        //Проверка на то что не врезалась ли змейка в саму себя

        for(int i = 0; i < m_snake->m_snakeBody.size(); i++)
        {
            bool accident = this->BoundaryChecking(QPair<int, int>(temp->m_x, temp->m_y), QPair<int, int>(m_snake->m_snakeBody[i]->m_x, m_snake->m_snakeBody[i]->m_y));
            if(accident)
            {
                delete temp;
                return;
            }
        }

        //-----------------------------------------------------------------------------
        m_snake->m_snakeBody.insert(0, temp);
        if(temp->m_x == this->m_snakeFood->m_x && temp->m_y == this->m_snakeFood->m_y)
        {
            m_text = "Очки : " + QString::number(++m_score) + "\nПауза - ПРОБЕЛ";
            emit this->ChangeText(m_text);
            GameField::ChangeXY_Food();
        }
        else
        {
            m_snake->m_snakeBody.pop_back();
        }

        repaint();
    }
    else repaint();
}


void GameField::NewGame()
{
    m_gameOver = false;
    m_pause = false;

    // Обнуление набранных очков
    m_score = 0;
    m_text = "Очки : " + QString::number(m_score) + "\nПауза - ПРОБЕЛ";
    emit this->ChangeText(m_text);
    //---------------------------------------------------------------

    m_snake = new Snake();
    m_Timer = new QTimer();
    m_gameFieldSizeWidth = width() / m_snake->Get_ItemSize();
    m_gameFieldSizeHeight = height() / m_snake->Get_ItemSize();
    m_snakeFood = new SnakeItem(m_gameFieldSizeWidth / 2, m_gameFieldSizeHeight / 2);
    m_moveStop = false;
    m_snakeRoute = SnakeRoute::right;
    m_snakeSpeed = 100;
    m_Timer->start(m_snakeSpeed);
    connect(m_Timer, &QTimer::timeout, this, &GameField::slot_SnakeMove);
}

void GameField::GameOver()
{
    this->m_gameOver = true;
    delete m_snake;
    delete m_Timer;
    delete m_snakeFood;
    // Ставим в указатели nullprt т.к если пользователь во время проигрыша закроет
    // программу, то вызовется деструктор, который попытается удалить область, к которой нет доступа
    m_snake = nullptr;
    m_Timer = nullptr;
    m_snakeFood = nullptr;
    //----------------------------------------------------------------------------------
    repaint();
}

void GameField::ChangeXY_Food()
{
    this->m_snakeFood->m_x = QRandomGenerator::global()->bounded(0, this->m_gameFieldSizeWidth - 1);
    this->m_snakeFood->m_y = QRandomGenerator::global()->bounded(0, this->m_gameFieldSizeHeight - 1);
    for(int i = 0; i < this->m_snake->m_snakeBody.size(); i++)
    {
        if(this->m_snakeFood->m_x == this->m_snake->m_snakeBody[i]->m_x && this->m_snakeFood->m_y == this->m_snake->m_snakeBody[i]->m_y)
        {
            return GameField::ChangeXY_Food();
        }
    }
}

bool GameField::BoundaryChecking(QPair<int, int> object_1, QPair<int, int> object_2)
{
    if(object_1.first == object_2.first && object_1.second == object_2.second)
    {
        GameField::GameOver();
        return true;
    }
    return false;
}

void GameField::paintEvent(QPaintEvent *p)
{
    QPainter painter;
    if(this->m_gameOver)
    {
        QString str = "Потрачено\nВы набрали очков: " + QString::number(m_score) + "\nНажмите пробел чтобы продожить";
        painter.begin(this);
        painter.drawRect(0, 0, width() - 1, height() - 1);
        painter.setFont(QFont("Verdana", 10, 700));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, str);
        painter.end();
        m_moveStop = false;
    }
    else
    {
        QBrush snakeBrushBody(QColor(41, 242, 122));
        QBrush snakeBrushHead(QColor(255, 0, 0));
        QBrush snakeBrushFood(QColor(245, 17, 59));
        painter.begin(this);

        painter.drawRect(0, 0, width() - 1, height() - 1);

        //Отрисовка змеи

        int item_size = m_snake->Get_ItemSize();
        painter.setBrush(snakeBrushHead);
        painter.drawEllipse(m_snake->m_snakeBody[0]->m_x * item_size, m_snake->m_snakeBody[0]->m_y * item_size, item_size, item_size);

        painter.setBrush(snakeBrushBody);
        for(int i = 1; i < m_snake->m_snakeBody.size(); i++)
        {
            painter.drawEllipse(m_snake->m_snakeBody[i]->m_x * item_size, m_snake->m_snakeBody[i]->m_y * item_size, item_size, item_size);
        }
        //------------------------------------------------------------------------------------------

        //Отрисовка еды
        painter.setBrush(snakeBrushFood);
        painter.drawRect(m_snakeFood->m_x * item_size , m_snakeFood->m_y * item_size, m_snake->Get_ItemSize(), m_snake->Get_ItemSize());
        //------------------------------------------------------------------------------------------

        painter.end();
        m_moveStop = false;
    }
}

void GameField::keyPressEvent(QKeyEvent *k)
{
    if(m_moveStop == true) return;
    //отлавливаем нажатие стрелок чтобы менять направление змейки
    if(m_gameOver)
    {
        if(k->key() == Qt::Key_Space)
        {
            this->NewGame();
        }
    }
    else
    {
        if(k->key() == Qt::Key_Space)
        {
            if(!m_pause)
            {
                m_text = "Очки : " + QString::number(m_score) + "\nПродолжить - ПРОБЕЛ";
                emit ChangeText(m_text);
                m_pause = true;
            }
            else
            {
                m_text = "Очки : " + QString::number(m_score) + "\nПауза - ПРОБЕЛ";
                emit ChangeText(m_text);
                m_pause = false;
            }
        }
        else if(k->key() == Qt::Key_Up && m_snakeRoute != SnakeRoute::down)
        {
            m_snakeRoute = SnakeRoute::up;
        }
        else if(k->key() == Qt::Key_Down && m_snakeRoute != SnakeRoute::up)
        {
            m_snakeRoute = SnakeRoute::down;
        }
        else if(k->key() == Qt::Key_Left && m_snakeRoute != SnakeRoute::right)
        {
            m_snakeRoute = SnakeRoute::left;
        }
        else if(k->key() == Qt::Key_Right && m_snakeRoute != SnakeRoute::left)
        {
            m_snakeRoute = SnakeRoute::right;
        }
        m_moveStop = true;
    }
}
