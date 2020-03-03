#include "usocket.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    USocket w;
    w.show();

    return a.exec();
}
