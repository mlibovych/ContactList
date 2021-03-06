#pragma once

#include <optional>
#include <set>
#include <unordered_set>

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
    std::set<Contact> selectAllContacts() const;
    std::set<Contact> selectContactsLike(const QString &text, bool favourite);

public slots:
    void saveContact(const QString &name, const QString &number);
    void updateContactStatus(const Contact &contact);

signals:
    void showContact(const Contact &contact);
    void fail();
    void success();
};
