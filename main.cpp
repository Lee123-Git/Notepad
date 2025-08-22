#include "notepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);  // 启用高DPI缩放
    QApplication a(argc, argv);
    Notepad w;
    w.show();
    return a.exec();
}
