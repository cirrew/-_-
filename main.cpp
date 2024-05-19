#include "camers.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    camers w;
    w.show();
    return a.exec();
}
