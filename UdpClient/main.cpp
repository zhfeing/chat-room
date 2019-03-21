#include "udpcilent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    udpcilent w;
    w.show();

    return a.exec();
}
