#pragma once

#include <QtWidgets>

class NewContactScreen : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *layoutOuter;
    QLineEdit *nameField;
    QLineEdit *numberField;
    QPushButton *addButton;

public:
    explicit NewContactScreen(QWidget *parent = nullptr);
    ~NewContactScreen();

public slots:
    void addContact();

signals:
    void addContact(const QString &name, const QString &number);
};
