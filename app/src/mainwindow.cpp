#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {  
    setObjectName("MainWindow");
    
    contactListProvider = new ContactListProvider(this); 
    central = new QWidget(this);
    generalScreen = new GeneralScreen(this);
    layoutOuter = new QStackedLayout(central);
    newContactScreen = new NewContactScreen(this);
    layoutOuter->addWidget(generalScreen);
    layoutOuter->addWidget(newContactScreen);
    layoutOuter->setCurrentWidget(generalScreen);

    setWindowTitle("Contact list viewer");
    setCentralWidget(central);
    resize(500, 700);
    initToolbar();

    connect(this, SIGNAL(changeWidget(QWidget *)), SLOT(setWidget(QWidget *)));
    connect(this, SIGNAL(saveContact(const QString &, const QString &)),
            contactListProvider, SLOT(saveContact(const QString &, const QString &)));
    connect(contactListProvider, SIGNAL(showContact(const Contact &)),
            generalScreen, SLOT(showContact(const Contact &)));
    connect(this, SIGNAL(refreshContacts(const std::vector<Contact> &)),
            generalScreen, SLOT(refreshView(const std::vector<Contact> &)));
    connect(this, SIGNAL(setContactStatus(const Contact &)),
            contactListProvider, SLOT(updateContactStatus(const Contact &)));

    emit refreshContacts(contactListProvider->selectAllContacts());
}

MainWindow::~MainWindow()
{
    //
}

void MainWindow::setWidget(QWidget *widget) {
    layoutOuter->setCurrentWidget(widget);
}

QStackedLayout *MainWindow::getLayout() {
    return layoutOuter;
}

void MainWindow::initToolbar() {
    actionContacts = new QAction("Contacts", this);
    actionAdd = new QAction("Add new", this);
    toolBar = new QToolBar(this);

    toolBar->setAllowedAreas(Qt::LeftToolBarArea);
    toolBar->setFloatable(false);
    toolBar->setOrientation(Qt::Vertical);
    toolBar->setMovable(false);
    toolBar->addAction(actionContacts);
    toolBar->addAction(actionAdd);
    addToolBar(Qt::LeftToolBarArea, toolBar);

    connect(actionContacts, SIGNAL(triggered()), this, SLOT(toContactList()));
    connect(actionAdd, SIGNAL(triggered()), this, SLOT(toNewContact()));
}

void MainWindow::toContactList() {
    emit changeWidget(generalScreen);
}

void MainWindow::toNewContact() {
    emit changeWidget(newContactScreen);
}

void MainWindow::addContact(const QString &name, const QString &number) {
    emit saveContact(name, number);
}

void MainWindow::searchContacts(const QString &text, bool favourite) {
    emit refreshContacts(contactListProvider->selectContactsLike(text, favourite));
}


void MainWindow::updateContactStatus(const Contact &contact) {
    emit setContactStatus(contact);
}

void MainWindow::failValidation() {
    QMessageBox::warning(this, "Alert", "Invalid data.");
}

void MainWindow::failAdding() {
    QMessageBox::warning(this, "Alert", "This number is already registred.");
}

void MainWindow::successAdding() {
    QMessageBox::information(this, "Alert", "Contact saved.");
}
