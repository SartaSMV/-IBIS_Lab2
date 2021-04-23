#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rsa.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Restart_A_clicked();

    void on_Restart_B_clicked();

    void on_Code_A_clicked();

    void on_Code_B_clicked();

    void on_Decode_A_clicked();

    void on_Decode_B_clicked();

private:
    RSA A, B;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
