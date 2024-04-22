#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    board = new boardWithgame(this);
    board->show();
}

void MainWindow::on_scoreButton_clicked()
{
    fin.open(name.toStdString());
    while(std::getline(fin,line)){
        if(std::stoi(line) > maxScore){
            maxScore = std::stoi(line);
        }
    }
    line = std::to_string(maxScore);
    QMessageBox *mes = new QMessageBox;
    mes->setText(QString::fromStdString(line));
    mes->exec();
    fin.close();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}

