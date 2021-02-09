#pragma once

#include "contact_list_provider.h"
#include "general_screen.h"
#include "new_contact_screen.h"

#include <QtWidgets>

#ifdef _WIN32
#define DELIM "\\"
#else
#define DELIM "/"
#endif

class ContactListProvider;
class GeneralScreen;
class NewContactScreen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *central; 
    QStackedLayout *layoutOuter;

    QToolBar *toolBar;
    QAction *actionContacts;
    QAction *actionAdd;

    GeneralScreen *generalScreen;
    NewContactScreen *newContactScreen;
    ContactListProvider *contactListProvider;

    void initToolbar();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStackedLayout *getLayout();

public slots:
    void setWidget(QWidget *widget);
    void toContactList();
    void toNewContact();
    void addContact(const QString &name, const QString &number);
    void searchContacts(const QString &text, bool favourite);
    void updateContactStatus(const Contact &contact);
    void failValidation();
    void failAdding();
    void successAdding();

signals:
    void changeWidget(QWidget *widget);
    void saveContact(const QString &name, const QString &number);
    void refreshContacts(const std::vector<Contact> &contacts);
    void setContactStatus(const Contact &contact);
};
