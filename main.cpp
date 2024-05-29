#include <QApplication>
#include "mainWindow.h"

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        MainWindow game;

        game.show();
        return a.exec();
    }
    catch (...)
    {
        qDebug() << "Error";
    }
}
