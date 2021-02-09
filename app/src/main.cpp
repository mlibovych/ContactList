#include <iostream>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    QFile File(":/qmain.qss");

    File.open(QFile::ReadOnly);
    app.setStyleSheet( QLatin1String(File.readAll()));
    window.show();
    
    return app.exec();
}