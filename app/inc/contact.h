#pragma once

#include <QtWidgets>

struct Contact {
    int id;
    QString name;
    QString number;
    int status;

    bool operator ==(const Contact &other) {
        return id == other.id;
    }
};

struct ContactHasher {
    size_t operator()(const Contact &contact) const {
        return ihash(contact.id);
    }
    std::hash<int> ihash;
};


bool operator ==(const Contact &lhs, const Contact &rhs);

bool operator <(const Contact &lhs, const Contact &rhs);