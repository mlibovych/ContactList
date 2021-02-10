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

    tools_widget = new ToolsWidget(this);

    list_widget = new QListWidget();
    list_widget->setSelectionMode(QAbstractItemView::NoSelection);
    list_widget->setSpacing(2);

    separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);

    layout_outer = new QVBoxLayout(this);
    layout_outer->setContentsMargins(0, 0, 0, 0);
    layout_outer->addWidget(tools_widget);
    layout_outer->addWidget(separator);
    layout_outer->addWidget(list_widget);  
}

GeneralScreen::~GeneralScreen()
{

}

void GeneralScreen::addContact(const Contact &contact) {
    QListWidgetItem *item = new QListWidgetItem(list_widget);
    ContactWidget *row = new ContactWidget(contact, this); //init
    
    row->setObjectName("ContactWidget");
    row->setMinimumHeight(50);
    row->setMaximumHeight(50);

    item->setSizeHint({50, 50});

    list_widget->addItem(item);
    list_widget->setItemWidget(item, row);
    contacts.insert(std::move(contact));
}

void GeneralScreen::refreshContacts(const std::set<Contact> &new_contacts) {
    list_widget->clear();
    contacts = std::move(new_contacts);
    for (const auto &contact : new_contacts) {
        addContact(contact);
    }
}

void GeneralScreen::refreshContactsView(const std::set<Contact> &new_contacts) {
    for (int i = 0; i < list_widget->count(); ++i) {
        auto item = list_widget->item(i);
        auto contact_widget = static_cast<ContactWidget*> (list_widget->itemWidget(item));
        if (new_contacts.count(contact_widget->getData())) {
            item->setHidden(0);
        }
        else {
            item->setHidden(1);
        }
    }
}