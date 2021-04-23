#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    A.restart(), B.restart();
    ui->label_A->setText(A.option());
    ui->label_B->setText(B.option());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Restart_A_clicked()
{
    A.restart();
    ui->label_A->setText(A.option());
}

void MainWindow::on_Restart_B_clicked()
{
    B.restart();
    ui->label_B->setText(B.option());
}

void MainWindow::on_Code_A_clicked()
{
    QVector<BigInt> code_m = A.coding(ui->Client_A->toPlainText(), B.get_N(), B.get_s());
    QString code = "";

    ui->Client_A->clear();
    for (auto i:code_m)
    {
        code = code + " " + QString::fromStdString(i.to_string());
    }

    ui->Client_B->clear();
    ui->Client_B->appendPlainText(code);
}

void MainWindow::on_Code_B_clicked()
{
    QVector<BigInt> code_m = B.coding(ui->Client_B->toPlainText(), A.get_N(), A.get_s());
    QString code = "";

    ui->Client_B->clear();
    for (auto i:code_m)
    {
        code = code + " " + QString::fromStdString(i.to_string());
    }

    ui->Client_A->clear();
    ui->Client_A->appendPlainText(code);
}

void MainWindow::on_Decode_A_clicked()
{
    QString code = ui->Client_A->toPlainText();
    QVector<BigInt> code_m;

    QString s = "";
    for(auto i:code)
    {
        if(i == " ")
        {
            if(s != "") code_m.push_back(BigInt(s.toStdString()));
            s = "";
        }
        else s = s + i;
    }
    code_m.push_back(BigInt(s.toStdString()));

    ui->Client_A->clear();
    ui->Client_A->appendPlainText(A.decoding(code_m));
}

void MainWindow::on_Decode_B_clicked()
{
    QString code = ui->Client_B->toPlainText();
    QVector<BigInt> code_m;

    QString s = "";
    for(auto i:code)
    {
        if(i == " ")
        {
            if(s != "") code_m.push_back(BigInt(s.toStdString()));
            s = "";
        }
        else s = s + i;
    }
    code_m.push_back(BigInt(s.toStdString()));

    ui->Client_B->clear();
    ui->Client_B->appendPlainText(B.decoding(code_m));
}
