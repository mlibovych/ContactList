#pragma once

#include <optional>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtWidgets>

#include "contact.h"
#include "mainwindow.h"

struct Contact;

class ContactListProvider : public QObject
{
    Q_OBJECT

private:
    const QString appPath;
    const QString dbPath;

    QSqlDatabase db;

    void checkDir();
    void createIfNotExist();
public:
    ContactListProvider(QObject *parent = nullptr);

    std::optional<int> createNewContact(const QString &name, const QString &number) const;
    std::vector<Contact> selectAllContacts() const;
    std::vector<Contact> selectContactsLike(const QString &text, bool favourite);

public slots:
    void saveContact(const QString &name, const QString &number);
    void updateContactStatus(const Contact &contact);

signals:
    void showContact(const Contact &contact);
    void fail(const QString &name, const QString &number);
};
