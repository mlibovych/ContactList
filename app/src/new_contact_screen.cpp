#include "new_contact_screen.h"

NewContactScreen::NewContactScreen(Mediator *mediator, QWidget *parent) :
                        QWidget(parent), Component(mediator)
{   
    setObjectName("contact_label");
    setMinimumHeight(700);
    layoutOuter = std::make_unique<QGridLayout> (this);

    nameField = std::make_unique<QLineEdit> (this);
    nameField->setPlaceholderText("Enter name");
    nameField->setMinimumWidth(300);
    nameField->setMinimumHeight(50);

    numberField = std::make_unique<QLineEdit> (this);
    numberField->setPlaceholderText("Enter number (10 digits)");
    numberField->setMinimumHeight(50);

    addButton = std::make_unique<QPushButton> ("Add contact", this);
    addButton->setMinimumHeight(50);

    layoutOuter->addWidget(nameField.get(), 1, 1, 1, 2);
    layoutOuter->addWidget(numberField.get(), 2, 1, 1, 2);
    layoutOuter->addWidget(addButton.get(), 3, 1, 1, 2);

    layoutOuter->setColumnStretch(0, 2);
    layoutOuter->setColumnStretch(layoutOuter->columnCount(), 2);
    layoutOuter->setRowStretch(0, 2);
    layoutOuter->setRowStretch(layoutOuter->rowCount(), 2);
    layoutOuter->setVerticalSpacing(20);

    
    connect(addButton.get(), SIGNAL(clicked()), SLOT(addContact()));
    connect(this, SIGNAL(addContact(const QString &, const QString &)),
            mediator, SLOT(addContact(const QString &, const QString &)));
}

NewContactScreen::~NewContactScreen()
{

}

void NewContactScreen::addContact() {
    QRegularExpression re("[0-9]{10}");
    QRegularExpressionMatch match = re.match(numberField->text());
    bool hasMatch = match.hasMatch();

    if (nameField->text().isEmpty() ||  numberField->text().isEmpty() || !hasMatch) {
        QMessageBox::warning(mediator->getMainWindow(), "Alert", "Invalid data.");
        return;
    }
    emit addContact(nameField->text(), numberField->text());
    nameField->clear();
    numberField->clear();
}