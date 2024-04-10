#include "boardwithgame.h"
#include "ui_boardwithgame.h"
#include <QMessageBox>
#include <random>
#include <QDebug>
#include <QLineEdit>
#include <QRect>
#include <QMovie>
#include <QPalette>
#include <QColor>
#include <QGridLayout>
#include <QLayout>


std::default_random_engine generator;
std::uniform_int_distribution<int>
randPlateIndexGenerator(0,15);


int winCounter = 0; //счётчик, для контроля выйгрыша(единовременного)

boardWithgame::boardWithgame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::boardWithgame)
{
    this->setAutoFillBackground(true);
    QMovie *movie = new QMovie(":/new/prefix1/img/4Cb2.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
    ui->setupUi(this);
    setWindowTitle("board");
    ui->liveScore->setText(QString::number(0));//обнуление очков
    ui->label->setStyleSheet("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6); ");
    ui->checkBox->setStyleSheet ("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6); ");
    for(int i = 0; i < 4; ++i){
        ui->gridLayout->setRowMinimumHeight(i,110);
        ui->gridLayout->setColumnMinimumWidth(i,110);
    }
    setFrame();
    qleadd();
    spawnPlate(10);
    spawnPlate(4);
    ui->gridLayoutWidget->setGeometry(QRect(274,365,440,440));
}

boardWithgame::~boardWithgame()
{
    delete ui;
}

void boardWithgame::qleadd()
{
    for(int i = 0; i < 16; ++i){
        qle_list.append(nullptr);
    }
}

void boardWithgame::setFrame()
{
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            QFrame *frame = new QFrame;
            frame->setGeometry(QRect(270 +(102*i),370+(102*j),100,100));
            frame->setStyleSheet("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6);");
            frame->setGeometry((270 +(100*i)), (370 + (100*j)), 100,100);
            qf_list.push_back(frame);
            ui->gridLayout->addWidget(frame, i, j, 1, 1);
    }}}

void boardWithgame::on_exitButton_clicked()
{
    close();
}

void boardWithgame::on_resetButton_clicked()
{
    score = 0;
    ui->liveScore->setText(QString::number(score));
    for(int i = 0; i < 16; i++){
        if(qle_list.at(i) != nullptr){
        qle_list[i] = nullptr;
        qle_list[i]->hide();}
    }
    int first, second;
    first = randPlateIndexGenerator(generator);
    second = randPlateIndexGenerator(generator);
    qle_list[first] = new QLineEdit;
    qle_list.at(first)->setText("2");
    qle_list[second] = new QLineEdit;
    qle_list.at(second)->setText("2");}

void boardWithgame::on_stepBackButton_clicked()
{}
//    for(int i = 0; i < 16; i++){
//        qle_list.at(i)->setText(QString::number(stepBack_list[i]));
//        if(stepBack_list[i] == 0){
//            qle_list.at(i)->setText("");
//        }
//    }


bool boardWithgame::isEnd()
{
    int k = 0;
    for(int i = 0; i < 16; i++){
        if(qle_list[i] != nullptr){
            k++;}}
    if(k == 16){ return 1; }
    else { return 0; }}

void boardWithgame::gameEnd()
{
    if(rearrangmentCounter == 0 && boardWithgame::isEnd() == 1){
        for(int i = 0; i < 16; i++){
            stepBack_list[i] = reserveStepBack_list[i];
        }
        QMessageBox *mes = new QMessageBox;
        mes->setText("You lost! Restart da game! Or try the other side ;)");
        mes->exec();
        fout.open(name.toStdString(),std::ios_base::app);
        fout << score << "\n";
        fout.close();
    }}

void boardWithgame::stepBackAdd()
{
    for(int i = 0; i < 16; i++){
        reserveStepBack_list[i] = stepBack_list[i];
    }
    for(int i = 0; i < 16; i++){
        stepBack_list[i] = qle_list.at(i)->text().toInt();
    }}

void boardWithgame::stepBackBack()
{
    for(int i = 0; i < 16; i++){
        stepBack_list[i] = reserveStepBack_list[i];
    }}

void boardWithgame::winCheck()
{
    for(int i = 0; i < 16; i++){
        if(qle_list.at(i) != nullptr){
        ui->liveScore->setText(QString::number(score));
        if(qle_list.at(i)->text() == "2048" && winCounter == 0){
            for(int i = 0; i < 16; i++){
                stepBack_list[i] = reserveStepBack_list[i];
            }
            QMessageBox *mes = new QMessageBox;
            mes->setText("You won! Congratilations! You can continue, u play endless mode");
            mes->exec();winCounter++;
        }}}}

void boardWithgame::spawnAllPlates()
{
    if(rearrangmentCounter > 0){
        int k;
        while(spawnCounter == 0){
            k = randPlateIndexGenerator(generator);
            if(qle_list[k] == nullptr){
                spawnPlate(k);
}}}}

void boardWithgame::spawnPlate(int k)
{
    int text = 2;
    if(randPlateIndexGenerator(generator) < 8){ text = 2; } else { text = 4; }
    qle_list[k] = new QLineEdit;
    qle_list.at(k)->setText(QString::number(text));
    qle_list.at(k)->setReadOnly(true);
    qle_list.at(k)->setAlignment(Qt::AlignCenter);
    qle_list.at(k)->setStyleSheet("background-color: rgba(0,100,100,170);border-radius: 20px; font-size: 41px;");
    int row, column = 0; //column - столбец, row - ряд
    row = k / 4;
    column = k % 4;
    ui->gridLayout->addWidget(qle_list.at(k), row, column, 1, 1, 0);
    QRect tempgeom = qle_list.at(k)->geometry();
    if(row == 0){ tempgeom.setY(28); }
    else if(row == 1){ tempgeom.setY(131); }
    else if(row == 2){ tempgeom.setY(251); }
    else if(row == 3){ tempgeom.setY(362); }
    qle_list.at(k)->setGeometry(tempgeom);

    spawnCounter++;}

void boardWithgame::plateMoveAnimation(QLineEdit *lineedit, QRect from, QRect to)
{
    count++;
    if(speedMode_toogle == 0){
        animation = new QPropertyAnimation(lineedit, "geometry");
//        animation->setEasingCurve(QEasingCurve::Type::InOutQuad);
        animation->setDuration(200);
        animation->setStartValue(from);
        animation->setEndValue(to);
        animation->start(QAbstractAnimation::KeepWhenStopped);
    }
}

void boardWithgame::moveWithAddition(int k, int j)
{
    score += qle_list.at(k)->text().toInt() * 2;
    qle_list.at(k)->setText(QString::number(qle_list.at(k)->text().toInt() + qle_list.at(j)->text().toInt()));
    qle_list.at(k)->setReadOnly(true);
    qle_list.at(k)->setAlignment(Qt::AlignCenter);
    qle_list.at(k)->setStyleSheet("background-color: rgba(0,100,100,170);border-radius: 20px; font-size: 41px;");
    int row, column = 0; //column - столбец, row - ряд
    row = k / 4;
    column = k % 4;
    ui->gridLayout->takeAt(k);
    ui->gridLayout->addWidget(qle_list.at(k), row, column, 1, 1, 0);

    QRect from = qle_list.at(j)->geometry();
    QRect to = qle_list.at(k)->geometry();

    if(row == 0){ to.setY(28); }
    else if(row == 1){ to.setY(131); }
    else if(row == 2){ to.setY(251); }
    else if(row == 3){ to.setY(362); }

    to.setWidth(108); to.setHeight(51);

    qle_list[j]->hide();
    qle_list.at(j)->setText("");

    qDebug() << count;
    qDebug() << "from" << from;
    qDebug() << "to " << to;

    qle_list[j] = nullptr;
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k), from, to);
}

void boardWithgame::moveWithoutAddition(int k, int j)
{
    qle_list[k] = new QLineEdit;
    QString temp = qle_list.at(j)->text();
    qle_list.at(k)->setReadOnly(true);
    qle_list.at(k)->setAlignment(Qt::AlignCenter);
    qle_list.at(k)->setStyleSheet("background-color: rgba(0,100,100,170);border-radius: 20px; font-size: 41px;");
    qle_list.at(k)->setText(temp);
    int roow, column = 0; //column - столбец, row - ряд
    roow = k / 4;
    column = k % 4;
    ui->gridLayout->addWidget(qle_list.at(k), roow,column);

    QRect from = qle_list.at(j)->geometry();
    QRect to = ui->gridLayout->itemAtPosition(roow,column)->geometry();

    if(roow == 0){ to.setY(28); }
    else if(roow == 1){ to.setY(131); }
    else if(roow == 2){ to.setY(251); }
    else if(roow == 3){ to.setY(362); }
    to.setWidth(108); to.setHeight(51);

    qle_list[j]->hide();
    qle_list.at(j)->setText("");

    qDebug() << count;
    qDebug() << "from" << from;
    qDebug() << "to " << to;

    qle_list[j] = nullptr;
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k), from, to);
}


void boardWithgame::tryMove(int k, int j)
{
    if(qle_list[j] != nullptr && qle_list[k] == nullptr){
        moveWithoutAddition(k, j);
    } else if (qle_list[k] != nullptr && qle_list[j] != nullptr &&
               qle_list.at(k)->text() == qle_list.at(j)->text()){
        moveWithAddition(k,j);
    }
}

void boardWithgame::moveLeft()
{
    for(int i = 1; i < 14; i += 4){
        for(int j = 3; j > 0; --j){
            for(int k = 0; k < j; ++k){
               tryMove(i + k - 1, i + k);
            }}}}

void boardWithgame::moveRight()
{
    for(int i = 1; i < 14; i += 4){
        for(int j = 3; j > 0; --j){
            for(int k = 0; k < j; ++k){
               tryMove(i + k, i + k - 1);
            }}}}

void boardWithgame::moveDown()
{
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 12; j = j + 4){
            for(int k = 12; k > j; k = k - 4){
               tryMove(i + k, i + k - 4);
            }}}}

void boardWithgame::moveUp()
{
    for(int i = 0; i < 4; ++i){
        for(int j = 12; j > 0; j = j - 4){
            for(int k = 0; k < j; k = k + 4){
               tryMove(i + k, i + k + 4);
            }}}}

void boardWithgame::setcolor()
{
    QPalette palette;
    for(int i = 0; i < 16; ++i){
        if(qle_list[i] != nullptr){
        if(qle_list.at(i)->text() == "2"){
            palette.setColor(QPalette::Background, QColor(50,93,168));
            qle_list.at(i)->setPalette(palette);
        }
        if(qle_list.at(i)->text() == "4"){
            palette.setColor(QPalette::Background, QColor(100,230,200));
            qle_list.at(i)->setPalette(palette);
        }
        if(qle_list.at(i)->text() == "8"){
            palette.setColor(QPalette::Background, QColor(139,50,168));
            qle_list.at(i)->setPalette(palette);
        }}}
}


void boardWithgame::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        speedMode_toogle = 0;
    } else{
        speedMode_toogle = 1;
    }}
