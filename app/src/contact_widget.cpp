#include "contact_widget.h"

ContactWidget::ContactWidget(const Contact &contact,
                             const Mediator *mediator,
                             QWidget *parent) :
                             QWidget(parent),
                             Component(mediator),
                             data(contact)
{   
    label = std::make_unique<QLabel> (data.name);
    label->setAlignment(Qt::AlignHCenter);
    label->setObjectName("contact_label");
    
    check = std::make_unique<QCheckBox> ("", this);
    check->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    if (data.status) {
        check->setCheckState(Qt::Checked);
    }
    
    layout_outer = std::make_unique<QHBoxLayout> (this);
    layout_outer->setContentsMargins(0 ,0 ,0, 0);
    layout_outer->addWidget(label.get());
    layout_outer->addWidget(check.get());

    connect(check.get(), SIGNAL(stateChanged(int)),
            this, SLOT(updateContactStatus()));
    connect(this, SIGNAL(updateContactStatus(const Contact &)),
            mediator, SLOT(updateContactStatus(const Contact &)));
}

ContactWidget::~ContactWidget()
{

}

void ContactWidget::updateContactStatus() {
    data.status = check->isChecked();
    emit updateContactStatus(data);
}