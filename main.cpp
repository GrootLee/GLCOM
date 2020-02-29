#include "serialunion.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialUnion w;

    w.setWindowIcon(QIcon(":/imageFile/font.ico"));
    w.show();

    return a.exec();
}
