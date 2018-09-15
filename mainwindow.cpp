#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTabBar>
#include <QDragMoveEvent>
#include <QEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto index = ui->tabWidget->tabBar()->addTab("");
    ui->tabWidget->tabBar()->setTabEnabled(index, false);
    auto button = new QPushButton("Add");
    connect(button, &QPushButton::clicked, [=]{
        auto index = ui->tabWidget->count() - 1;
        ui->tabWidget->insertTab(index, new QWidget(), QString("Tab_%1").arg(index + 1));
    });
    ui->tabWidget->tabBar()->setTabButton(index, QTabBar::RightSide, button);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() != QEvent::DragMove) return false;
    auto tab = qobject_cast<QTabBar*>(watched);
    if (!tab) return false;
    auto move = static_cast<QDragMoveEvent*>(event);
    auto lastTabCenter = ui->tabWidget->tabBar()->tabRect(ui->tabWidget->count() - 2).center().x();

    qDebug() << move->pos().x() << lastTabCenter;
    return move->pos().x() >= lastTabCenter;
}
