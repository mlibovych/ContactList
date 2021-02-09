#include "contact_widget.h"

ContactWidget::ContactWidget(const Contact &contact, QWidget *parent) :
                             QWidget(parent), data(contact)
{   
    label = new QLabel(data.name);
    label->setAlignment(Qt::AlignHCenter);
    label->setObjectName("contact_label");
    
    check = new QCheckBox("", this);
    check->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    if (data.status) {
        check->setCheckState(Qt::Checked);
    }
    
    layout_outer = new QHBoxLayout(this);
    layout_outer->setContentsMargins(0 ,0 ,0, 0);
    layout_outer->addWidget(label);
    layout_outer->addWidget(check);

    auto mainwindow = this->parent()->parent()->parent();

    connect(check, SIGNAL(stateChanged(int)),
            this, SLOT(updateContactStatus()));
    connect(this, SIGNAL(updateContactStatus(const Contact &)),
            mainwindow, SLOT(updateContactStatus(const Contact &)));
}

ContactWidget::~ContactWidget()
{

}

void ContactWidget::updateContactStatus() {
    data.status = check->isChecked();
    emit updateContactStatus(data);
}