#include "mainwindow.h"
#include <QApplication>

#define haha 123
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.resize(1800, 800);
    w.setWindowTitle(QWidget::tr("阴影标注"));
    w.show();

    return a.exec();
}
