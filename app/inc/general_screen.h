#pragma once

#include <set>
#include <unordered_set>

#include <QtWidgets>

#include "contact_widget.h"

class ContactWidget;
struct Contact;

class ToolsWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *layout_outer;

    QLabel *label1;
    QLabel *label2;
    QCheckBox *check;
    QLineEdit *searchField;

public:
    explicit ToolsWidget(QWidget *parent = nullptr);
    ~ToolsWidget();

public slots:
    void searchContacts();

signals:
    void searchContacts(const QString &text, bool favourite);
};

class GeneralScreen : public QWidget
{
    Q_OBJECT

private:
    QListWidget *list_widget;

    QListView *list;
    ToolsWidget *tools_widget;
    QFrame *separator;
    QVBoxLayout *layout_outer;

    std::set<Contact> contacts;

public:
    explicit GeneralScreen(QWidget *parent = nullptr);
    ~GeneralScreen();

public slots:
    void addContact(const Contact &contact);
    void refreshContacts(const std::set<Contact> &new_contacts);
    void refreshContactsView(const std::set<Contact> &new_contacts);

};
