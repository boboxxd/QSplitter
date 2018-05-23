#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>
#include "slidingwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SlidingWindow w;
    w.show();
    return a.exec();
}
