#pragma once

#include <QtWidgets>

#include "mediator.h"
#include "component.h"

class Component;
class Mediator;

class MainWindow : public QMainWindow, public Component
{
    Q_OBJECT

private:
    std::unique_ptr<QWidget> central; 
    std::unique_ptr<QStackedLayout> layoutOuter;

    std::unique_ptr<QToolBar> toolBar;
    std::unique_ptr<QAction> actionContacts;
    std::unique_ptr<QAction> actionAdd;

    void initToolbar();

public:
    explicit MainWindow(Mediator *mediator, QWidget *parent = nullptr);
    ~MainWindow();

    QStackedLayout *getLayout();

public slots:
    void setWidget(QWidget *widget);
};
