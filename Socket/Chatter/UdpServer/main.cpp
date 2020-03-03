#include "userver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UServer w;
    w.show();

    return a.exec();
}
