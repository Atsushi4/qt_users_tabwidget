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
    auto button = new QPushButton("Add");
    connect(button, &QPushButton::clicked, [=]{
        auto index = ui->tabWidget->count() - 1;
        ui->tabWidget->addTab(new QWidget(), QString("Tab_%1").arg(index + 1));
    });
    ui->tabWidget->setCornerWidget(button, Qt::TopLeftCorner);
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
