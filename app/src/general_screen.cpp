#include "general_screen.h"

ToolsWidget::ToolsWidget(QWidget *parent) : QWidget(parent) {
    setMinimumHeight(80);
    setMaximumHeight(100);
    setMinimumWidth(400);

    layout_outer = new QHBoxLayout(this);
    layout_outer->setContentsMargins(0, 0, 0, 0);

    label1 = new QLabel("contact");
    label1->setAlignment(Qt::AlignCenter);
    label1->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    label1->setObjectName("label_1");

    label2 = new QLabel("list");
    label2->setAlignment(Qt::AlignCenter);
    label2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    label2->setObjectName("label_2");

    check = new QCheckBox("", this);
    check->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    searchField = new QLineEdit(this);
    searchField->setPlaceholderText("Enter name");
    searchField->setMinimumWidth(100);
    searchField->setMinimumHeight(50);
    searchField->setAlignment(Qt::AlignCenter);


    layout_outer->addWidget(label1);
    layout_outer->addWidget(label2);
    layout_outer->addStretch();
    layout_outer->addWidget(searchField);
    layout_outer->addStretch();
    layout_outer->addWidget(check);

    auto mainwindow = this->parent()->parent();

    connect(searchField, SIGNAL(textChanged(const QString &)),
            this, SLOT(searchContacts()));
    connect(check, SIGNAL(stateChanged(int)),
            this, SLOT(searchContacts()));
    connect(this, SIGNAL(searchContacts(const QString &, bool)),
            mainwindow, SLOT(searchContacts(const QString &, bool)));
}

ToolsWidget::~ToolsWidget()
{

}

void ToolsWidget::searchContacts() {
    emit searchContacts(searchField->text(), check->isChecked());
}

GeneralScreen::GeneralScreen(QWidget *parent) : QWidget(parent) {  
    setMinimumHeight(700);
    setObjectName("General");
    scroll_widget = new QScrollArea(this);
    scroll_widget->setMinimumHeight(600);

    tools_widget = new ToolsWidget(this);

    content_widget = new QWidget(scroll_widget);
    content_widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    content_widget->setObjectName("Default");

    scroll_widget->setWidget(content_widget);
    scroll_widget->setWidgetResizable (true);
    scroll_widget->setVerticalScrollBarPolicy (Qt::ScrollBarAsNeeded);
    scroll_widget->setObjectName("Default");

    layout_inner = new QVBoxLayout(content_widget);
    layout_inner->setContentsMargins(0 ,0 ,0, 0);
    layout_inner->setSpacing(2);


    separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);

    layout_outer = new QVBoxLayout(this);
    layout_outer->setContentsMargins(0, 0, 0, 0);
    layout_outer->addWidget(tools_widget);
    layout_outer->addWidget(separator);
    layout_outer->addWidget(scroll_widget);
    
}

GeneralScreen::~GeneralScreen()
{

}

void GeneralScreen::showContact(const Contact &contact) {
    ContactWidget *row = new ContactWidget(contact, this); //init
    
    row->setObjectName("ContactWidget");
    row->setMinimumHeight(50);
    row->setMaximumHeight(50);
    layout_inner->addWidget(row); //insert in area
    contacts.push_back(row);
}

void GeneralScreen::refreshView(const std::vector<Contact> &new_contacts) {
    for (auto contact : contacts) {
        delete contact;
    }
    contacts.clear();

    for (const auto &contact : new_contacts) {
        showContact(contact);
    }
}