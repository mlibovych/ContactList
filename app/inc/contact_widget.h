#pragma once

#include <QtWidgets>

#include "contact.h"

struct Contact;

class ContactWidget : public QWidget
{
    Q_OBJECT

private:
    Contact data;
    QLabel *label;
    QCheckBox *check;
    QHBoxLayout *layout_outer;

public:
    explicit ContactWidget(const Contact &contact, QWidget *parent = nullptr);
    ~ContactWidget();

public slots:
    void updateContactStatus();

signals:
    void updateContactStatus(const Contact &contact);
};
