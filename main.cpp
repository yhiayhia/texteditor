#include <QApplication>
#include"sdiwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SdiWindow *window=new SdiWindow();
    window->show();

    return a.exec();
}
