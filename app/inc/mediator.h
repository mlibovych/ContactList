#pragma once

#include <string>
#include <iostream>
#include <utility>
#include <memory>

#include <QtWidgets>
#include <QSysInfo>

#include "contact.h"
#include "mainwindow.h"
#include "contact_list_provider.h"
#include "general_screen.h"
#include "new_contact_screen.h"

#ifdef _WIN32
#define DELIM "\\"
#else
#define DELIM "/"
#endif

class ContactListProvider;
class MainWindow;
class GeneralScreen;
class NewContactScreen;

class Mediator : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<ContactListProvider> contactListProvider;

    std::unique_ptr<GeneralScreen> generalScreen;
    std::unique_ptr<NewContactScreen> newContactScreen;

public:
    Mediator();
    ~Mediator();

    MainWindow *getMainWindow() const;

public slots:
    void toContactList();
    void toNewContact();
    void addContact(const QString &name, const QString &number);
    void searchContacts(const QString &text, bool favourite);
    void updateContactStatus(const Contact &contact);

signals:
    void changeWidget(QWidget *widget);
    void saveContact(const QString &name, const QString &number);
    void refreshContacts(const std::vector<Contact> &contacts);
    void setContactStatus(const Contact &contact);
};
