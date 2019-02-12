#include <QApplication>
#include"mdiwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MdiWindow *window=new MdiWindow();
    window->show();

    return a.exec();
}
