#pragma once

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
    QScrollArea *scroll_widget;
    QWidget *content_widget;
    ToolsWidget *tools_widget;
    QFrame *separator;
    QVBoxLayout *layout_outer;
    QVBoxLayout *layout_inner;

    QVector<ContactWidget *> contacts;

public:
    explicit GeneralScreen(QWidget *parent = nullptr);
    ~GeneralScreen();

public slots:
    void showContact(const Contact &contact);
    void refreshView(const std::vector<Contact> &new_contacts);

};
