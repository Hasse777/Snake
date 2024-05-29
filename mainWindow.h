#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLayout>
#include "hintField.h"
#include "gameField.h"

class MainWindow : public QMainWindow
{
private:
    GameField* m_game;
    HintField* m_hintField;
    QWidget* m_central_widget;
    QGridLayout * m_gridLayout;
public:
    MainWindow(QWidget* parent = nullptr);
};


#endif // MAINWINDOW_H
