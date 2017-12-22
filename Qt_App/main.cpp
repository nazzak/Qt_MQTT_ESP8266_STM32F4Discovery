#include "MyScreen.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyScreen w;
    w.show();

    return a.exec();
}
