#include "mainWindow.h"


MainWindow::MainWindow(QWidget *parent)
{
    setFixedSize(360, 430);
    setWindowIcon(QIcon(":/images/apple.png"));
    m_gridLayout = new QGridLayout;
    m_game = new GameField;
    m_hintField = new HintField();
    m_central_widget = new QWidget;
    connect(m_game, &GameField::ChangeText, m_hintField, &HintField::slotСhangeText);
    m_gridLayout->addWidget(m_hintField, 0, 0);
    m_gridLayout->addWidget(m_game, 1, 0);

    m_central_widget->setLayout(m_gridLayout);
    this->setCentralWidget(m_central_widget);
}
