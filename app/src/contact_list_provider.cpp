#include "contact_list_provider.h"

ContactListProvider::ContactListProvider(QObject *parent) : QObject(parent), appPath(QDir::homePath() + DELIM + ".contactlist"),
                                        dbPath(appPath + DELIM + "myDb"),
                                        db(QSqlDatabase::addDatabase("QSQLITE", "myDb"))
{
    checkDir();
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Db openind failed";
        exit(1);
    }
    createIfNotExist();

    auto mainwindow = this->parent();

    connect(this, SIGNAL(fail()),
            mainwindow, SLOT(failAdding()));
    connect(this, SIGNAL(success()),
            mainwindow, SLOT(successAdding()));
}

void ContactListProvider::checkDir() {
    if (!QFile::exists(appPath)) {
        QDir appDir;

        appDir.mkpath(appPath);
    }
}

void ContactListProvider::createIfNotExist() {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    if (!query.exec("SELECT * FROM contacts")) {
        query.exec("create table if not exists contacts (id INTEGER PRIMARY KEY AUTOINCREMENT,\
                                                        name VARCHAR(255) NOT NULL,\
                                                        number VARCHAR(255) NOT NULL UNIQUE,\
                                                        favourite INTEGER);\
                    ");
        query.exec("CREATE INDEX song_id_index ON songs (id);");
        for (int i = 0; i < 3; ++i) {
            query.prepare("INSERT INTO contacts (name, number, favourite) VALUES (:name, :number, 0);");
            std::string name = "test_contact" + std::to_string(i);
            std::string number = "55501460" + std::to_string(i);

            query.bindValue(":name", name.c_str());
            query.bindValue(":number", number.c_str());
            query.exec();
        }
        qDebug() << "Creating new Db";
    }
    else {
        qDebug() << "Opening existing Db";
    }
}

std::optional<int> ContactListProvider::createNewContact(const QString &name, const QString &number) const {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    int id;

    //check if exist
    query.prepare("SELECT id FROM contacts WHERE number=:number;");
    query.bindValue(":number", number);
    query.exec();
    if (query.first() && !query.value(0).isNull()) {
        return std::nullopt;
    }
    //try to insert
    query.prepare("INSERT INTO contacts (name, number, favourite) VALUES (:name, :number, 0);");
    query.bindValue(":name", name);
    query.bindValue(":number", number);
    query.exec();
    //get inserted id
    query.prepare("SELECT last_insert_rowid();");
    query.exec();
    if (!query.first()) {
        qDebug() << "Something went wrong";
        return std::nullopt;
    }
    id = query.value(0).toInt();
    return id;
}

std::vector<Contact> ContactListProvider::selectAllContacts() const {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    std::vector<Contact> contacts;

    query.prepare("SELECT * FROM contacts;");
    query.exec();
    while (query.next()) {
        contacts.push_back({
            .id = query.value(0).toInt(),
            .name = query.value(1).toString(),
            .number = query.value(2).toString(),
            .status = query.value(3).toInt()
        });
    }
    return contacts;
}

std::vector<Contact> ContactListProvider::selectContactsLike(const QString &text, bool favourite) {
    QSqlQuery query(QSqlDatabase::database("myDb"));
    std::vector<Contact> contacts;

    if (!favourite) {
        query.prepare("SELECT * FROM contacts WHERE name LIKE :text;");
    
    }
    else {
        query.prepare("SELECT * FROM contacts WHERE name LIKE :text AND favourite=:favourite;");
    
    }
    query.bindValue(":text", "%" + text + "%");
    query.bindValue(":favourite", static_cast<int> (favourite));
    query.exec();
    while (query.next()) {
        contacts.push_back({
            .id = query.value(0).toInt(),
            .name = query.value(1).toString(),
            .number = query.value(2).toString(),
            .status = query.value(3).toInt()
        });
    }
    return contacts;
}

void ContactListProvider::saveContact(const QString &name, const QString &number) {
    if (const auto id = createNewContact(name, number)) {
        Contact contact = {
            .id = *id,
            .name = name,
            .number = number,
            .status = 0
        };
        emit success();
        emit showContact(contact);
        return;
    }
    emit fail();
}

void ContactListProvider::updateContactStatus(const Contact &contact) {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    query.prepare("UPDATE contacts SET favourite=:favourite WHERE id=:id;");
    query.bindValue(":favourite", contact.status);
    query.bindValue(":id", contact.id);
    query.exec();
}