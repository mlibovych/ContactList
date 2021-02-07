#pragma once

#include <QtWidgets>

#include "mediator.h"
#include "component.h"
#include "contact.h"

class Component;
class Mediator;
struct Contact;

class ContactWidget : public QWidget, public Component
{
    Q_OBJECT

private:
    Contact data;
    std::unique_ptr<QLabel> label;
    std::unique_ptr<QCheckBox> check;
    std::unique_ptr<QHBoxLayout> layout_outer;

public:
    explicit ContactWidget(const Contact &contact,
                           const Mediator *mediator,
                           QWidget *parent = nullptr);
    ~ContactWidget();

public slots:
    void updateContactStatus();

signals:
    void updateContactStatus(const Contact &contact);
};
