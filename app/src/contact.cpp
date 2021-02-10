#include "contact.h"

bool operator ==(const Contact &lhs, const Contact &rhs) {
    return lhs.id == rhs.id;
}

bool operator <(const Contact &lhs, const Contact &rhs) {
    return lhs.id < rhs.id;
}