#include <iostream>

#include "mediator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile File(":/qmain.qss");
    QString StyleSheet;
    Mediator *mediator = new Mediator;

    File.open(QFile::ReadOnly);
    StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);

    app.exec();
    delete mediator;
    
    return 0;
}