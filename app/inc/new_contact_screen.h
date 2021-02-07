#pragma once

#include <QtWidgets>

#include "mediator.h"
#include "component.h"

class Component;
class Mediator;

class NewContactScreen : public QWidget, public Component
{
    Q_OBJECT

private:
    std::unique_ptr<QGridLayout> layoutOuter;
    std::unique_ptr<QLineEdit> nameField;
    std::unique_ptr<QLineEdit> numberField;
    std::unique_ptr<QPushButton> addButton;

public:
    explicit NewContactScreen(Mediator *mediator, QWidget *parent = nullptr);
    ~NewContactScreen();

public slots:
    void addContact();

signals:
    void addContact(const QString &name, const QString &number);
};
