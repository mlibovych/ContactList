#include "general_screen.h"

ToolsWidget::ToolsWidget(Mediator *mediator, QWidget *parent) :
                        QWidget(parent), Component(mediator)
{
    setMinimumHeight(80);
    setMaximumHeight(100);
    setMinimumWidth(400);

    layout_outer = std::make_unique<QHBoxLayout> (this);
    layout_outer->setContentsMargins(0, 0, 0, 0);

    label1 = std::make_unique<QLabel> ("contact");
    label1->setAlignment(Qt::AlignCenter);
    label1->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    label1->setObjectName("label_1");

    label2 = std::make_unique<QLabel> ("list");
    label2->setAlignment(Qt::AlignCenter);
    label2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    label2->setObjectName("label_2");

    check = std::make_unique<QCheckBox> ("", this);
    check->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    searchField = std::make_unique<QLineEdit> (this);
    searchField->setPlaceholderText("Enter name");
    searchField->setMinimumWidth(100);
    searchField->setMinimumHeight(50);
    searchField->setAlignment(Qt::AlignCenter);


    layout_outer->addWidget(label1.get());
    layout_outer->addWidget(label2.get());
    layout_outer->addStretch();
    layout_outer->addWidget(searchField.get());
    layout_outer->addStretch();
    layout_outer->addWidget(check.get());

    connect(searchField.get(), SIGNAL(textChanged(const QString &)),
            this, SLOT(searchContacts()));
    connect(check.get(), SIGNAL(stateChanged(int)),
            this, SLOT(searchContacts()));
    connect(this, SIGNAL(searchContacts(const QString &, bool)),
            mediator, SLOT(searchContacts(const QString &, bool)));
}

ToolsWidget::~ToolsWidget()
{

}

void ToolsWidget::searchContacts() {
    emit searchContacts(searchField->text(), check->isChecked());
}

GeneralScreen::GeneralScreen(Mediator *mediator, QWidget *parent) :
                        QWidget(parent), Component(mediator)
{   
    setMinimumHeight(700);
    scroll_widget = std::make_unique<QScrollArea> (this);
    scroll_widget->setMinimumHeight(600);

    tools_widget = std::make_unique<ToolsWidget> (mediator, this);

    content_widget = std::make_unique<QWidget> (scroll_widget.get());
    content_widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    content_widget->setObjectName("Default");

    scroll_widget->setWidget(content_widget.get());
    scroll_widget->setWidgetResizable (true);
    scroll_widget->setVerticalScrollBarPolicy (Qt::ScrollBarAsNeeded);
    scroll_widget->setObjectName("Default");

    layout_inner = std::make_unique<QVBoxLayout> (content_widget.get());
    layout_inner->setContentsMargins(0 ,0 ,0, 0);
    layout_inner->setSpacing(2);


    separator = std::make_unique<QFrame> (this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);

    layout_outer = std::make_unique<QVBoxLayout> (this);
    layout_outer->setContentsMargins(0, 0, 0, 0);
    layout_outer->addWidget(tools_widget.get());
    layout_outer->addWidget(separator.get());
    layout_outer->addWidget(scroll_widget.get());
    
}

GeneralScreen::~GeneralScreen()
{

}

void GeneralScreen::showContact(const Contact &contact) {
    auto row = std::make_shared<ContactWidget> (contact, mediator, this); //init
    
    row->setObjectName("ContactWidget");
    row->setMinimumHeight(50);
    row->setMaximumHeight(50);
    layout_inner->addWidget(row.get()); //insert in area
    contacts.push_back(row);
}

void GeneralScreen::refreshView(const std::vector<Contact> &new_contacts) {
    contacts.clear();

    for (const auto &contact : new_contacts) {
        showContact(contact);
    }
}