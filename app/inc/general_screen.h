#pragma once

#include <QtWidgets>

#include "mediator.h"
#include "component.h"
#include "contact_widget.h"

class Component;
class Mediator;
class ContactWidget;
struct Contact;

class ToolsWidget : public QWidget, public Component
{
    Q_OBJECT

private:
    std::unique_ptr<QHBoxLayout> layout_outer;

    std::unique_ptr<QLabel> label1, label2;
    std::unique_ptr<QCheckBox> check;
    std::unique_ptr<QLineEdit> searchField;

public:
    explicit ToolsWidget(Mediator *mediator, QWidget *parent = nullptr);
    ~ToolsWidget();

public slots:
    void searchContacts();

signals:
    void searchContacts(const QString &text, bool favourite);
};

class GeneralScreen : public QWidget, public Component
{
    Q_OBJECT

private:
    std::unique_ptr<QScrollArea> scroll_widget;
    std::unique_ptr<QWidget> content_widget;
    std::unique_ptr<ToolsWidget> tools_widget;
    std::unique_ptr<QFrame> separator;
    std::unique_ptr<QVBoxLayout> layout_outer;
    std::unique_ptr<QVBoxLayout> layout_inner;

    QVector<std::shared_ptr<ContactWidget>> contacts;

public:
    explicit GeneralScreen(Mediator *mediator, QWidget *parent = nullptr);
    ~GeneralScreen();

public slots:
    void showContact(const Contact &contact);
    void refreshView(const std::vector<Contact> &new_contacts);

};
