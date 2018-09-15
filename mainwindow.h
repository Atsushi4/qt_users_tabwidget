#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private:
    Ui::MainWindow *ui;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
};

#endif // MAINWINDOW_H
