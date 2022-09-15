#include "mainwidget.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setWindowTitle("Custom Card");
    w.setWindowIcon(QIcon("C:/Users/Дмитрий/Desktop/Screenshot_2.png"));       //PLACEHOLDER
    w.showMaximized();
    w.show();
    return a.exec();
}
