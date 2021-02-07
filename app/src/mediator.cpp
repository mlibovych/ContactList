#include "mediator.h"

Mediator::Mediator() : QObject() {
    contactListProvider = std::make_unique<ContactListProvider> (this);
    mainWindow = std::make_unique<MainWindow> (this);

    generalScreen = std::make_unique<GeneralScreen> (this);
    newContactScreen = std::make_unique<NewContactScreen> (this);
    mainWindow->getLayout()->addWidget(generalScreen.get());
    mainWindow->getLayout()->addWidget(newContactScreen.get());
    mainWindow->getLayout()->setCurrentWidget(generalScreen.get());

    connect(this, SIGNAL(changeWidget(QWidget *)), mainWindow.get(), SLOT(setWidget(QWidget *)));
    connect(this, SIGNAL(saveContact(const QString &, const QString &)),
            contactListProvider.get(), SLOT(saveContact(const QString &, const QString &)));
    connect(contactListProvider.get(), SIGNAL(showContact(const Contact &)),
            generalScreen.get(), SLOT(showContact(const Contact &)));
    connect(this, SIGNAL(refreshContacts(const std::vector<Contact> &)),
            generalScreen.get(), SLOT(refreshView(const std::vector<Contact> &)));
    connect(this, SIGNAL(setContactStatus(const Contact &)),
            contactListProvider.get(), SLOT(updateContactStatus(const Contact &)));

    emit refreshContacts(contactListProvider->selectAllContacts());
    mainWindow->show();
}

Mediator::~Mediator() {
    //
}

MainWindow *Mediator::getMainWindow() const {
    return mainWindow.get();
}

void Mediator::toContactList() {
    emit changeWidget(generalScreen.get());
}

void Mediator::toNewContact() {
    emit changeWidget(newContactScreen.get());
}

void Mediator::addContact(const QString &name, const QString &number) {
    emit saveContact(name, number);
}

void Mediator::searchContacts(const QString &text, bool favourite) {
    emit refreshContacts(contactListProvider->selectContactsLike(text, favourite));
}


void Mediator::updateContactStatus(const Contact &contact) {
    emit setContactStatus(contact);
}
