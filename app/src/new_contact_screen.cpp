#include "new_contact_screen.h"

NewContactScreen::NewContactScreen(QWidget *parent) : QWidget(parent) {   
    setObjectName("contact_label");
    setMinimumHeight(700);
    layoutOuter = new QGridLayout(this);

    nameField = new QLineEdit(this);
    nameField->setPlaceholderText("Enter name");
    nameField->setMinimumWidth(300);
    nameField->setMinimumHeight(50);

    numberField = new QLineEdit(this);
    numberField->setPlaceholderText("Enter number (10 digits)");
    numberField->setMinimumHeight(50);

    addButton = new QPushButton("Add contact", this);
    addButton->setMinimumHeight(50);

    layoutOuter->addWidget(nameField, 1, 1, 1, 2);
    layoutOuter->addWidget(numberField, 2, 1, 1, 2);
    layoutOuter->addWidget(addButton, 3, 1, 1, 2);

    layoutOuter->setColumnStretch(0, 2);
    layoutOuter->setColumnStretch(layoutOuter->columnCount(), 2);
    layoutOuter->setRowStretch(0, 2);
    layoutOuter->setRowStretch(layoutOuter->rowCount(), 2);
    layoutOuter->setVerticalSpacing(20);

    auto mainwindow = this->parent();

    connect(addButton, SIGNAL(clicked()), SLOT(addContact()));
    connect(this, SIGNAL(addContact(const QString &, const QString &)),
            mainwindow, SLOT(addContact(const QString &, const QString &)));
    connect(this, SIGNAL(failValidation()),
            mainwindow, SLOT(failValidation()));
}

NewContactScreen::~NewContactScreen()
{

}

void NewContactScreen::addContact() {
    QRegularExpression re("[0-9]{10}");
    QRegularExpressionMatch match = re.match(numberField->text());
    bool hasMatch = match.hasMatch();

    if (nameField->text().isEmpty() ||  numberField->text().isEmpty() || !hasMatch) {
        emit failValidation();
        return;
    }
    emit addContact(nameField->text(), numberField->text());
    nameField->clear();
    numberField->clear();
}