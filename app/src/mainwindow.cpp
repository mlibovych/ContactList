#include "mainwindow.h"

MainWindow::MainWindow(Mediator *mediator, QWidget *parent) :
                        QMainWindow(parent), Component(mediator)
{   
    setObjectName("Default");
    setWindowTitle("Contact list viewer");
    central = std::make_unique<QWidget> (this);
    setCentralWidget(central.get());
    layoutOuter = std::make_unique<QStackedLayout> (centralWidget());
    resize(500, 700);
    initToolbar();
}

MainWindow::~MainWindow()
{
    //
}

void MainWindow::setWidget(QWidget *widget) {
    layoutOuter->setCurrentWidget(widget);
}

QStackedLayout *MainWindow::getLayout() {
    return layoutOuter.get();
}

void MainWindow::initToolbar() {
    actionContacts = std::make_unique<QAction>("Contacts");
    actionAdd = std::make_unique<QAction>("Add new");
    toolBar = std::make_unique<QToolBar>(this);

    toolBar->setAllowedAreas(Qt::LeftToolBarArea);
    toolBar->setFloatable(false);
    toolBar->setOrientation(Qt::Vertical);
    toolBar->setMovable(false);
    toolBar->addAction(actionContacts.get());
    toolBar->addAction(actionAdd.get());
    addToolBar(Qt::LeftToolBarArea, toolBar.get());

    connect(actionContacts.get(), SIGNAL(triggered()), mediator, SLOT(toContactList()));
    connect(actionAdd.get(), SIGNAL(triggered()), mediator, SLOT(toNewContact()));
}



