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
    on_resetButton_clicked();
    ui->gridLayoutWidget->setGeometry(QRect(274,365,440,440));
    setcolor();
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
            frame->setStyleSheet("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6);");
            frame->setGeometry((270 +(100*i)), (370 + (100*j)), 100,100);
            qf_list.push_back(frame);
            ui->gridLayout->addWidget(frame, i, j, 1, 1);
    }}}

void boardWithgame::on_exitButton_clicked()
{
    loadScore();
    close();
}

void boardWithgame::on_resetButton_clicked()
{
    loadScore();
    score = 0;
    ui->liveScore->setText(QString::number(score));
    for(int i = 0; i < 16; i++){
        if(qle_list[i] != nullptr){
            qle_list[i]->hide();
            qle_list[i] = nullptr;}
    }
    int first, second;
    first = randPlateIndexGenerator(generator);
    second = randPlateIndexGenerator(generator);
    while(first == second){second = randPlateIndexGenerator(generator);}
    spawnPlate(first);
    spawnPlate(second);
    setcolor();
}
void boardWithgame::on_stepBackButton_clicked()
{
if(rearrangmentCounter != 0){
    for(int i = 0; i < 16; i++){
        if(stepBack_list[i] != 0){
            if(qle_list[i] != nullptr){
                qle_list[i]->hide();
                qle_list[i] = nullptr;
            }
            spawnPlate(i, stepBack_list[i]);}
        else {
            if(qle_list[i] != nullptr){
                qle_list.at(i)->hide();
                qle_list[i] = nullptr;}
    }}} else {
    for(int i = 0; i < 16; i++){
        if(reserveStepBack_list[i] != 0){
            if(qle_list[i] != nullptr){
                qle_list[i]->hide();
                qle_list[i] = nullptr;
            }
            spawnPlate(i, reserveStepBack_list[i]);}
        else {
            if(qle_list[i] != nullptr){
                qle_list.at(i)->hide();
                qle_list[i] = nullptr;}
    }}
}
setcolor();
}

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
        loadScore();
    }}

void boardWithgame::stepBackAdd()
{
    for(int i = 0; i < 16; i++){
        reserveStepBack_list[i] = stepBack_list[i];
    }
    for(int i = 0; i < 16; i++){
        if(qle_list[i] != nullptr){
            stepBack_list[i] = qle_list.at(i)->text().toInt();
        } else { stepBack_list[i] = 0; }
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
            loadScore();
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

void boardWithgame::spawnPlate(int k, int value)
{
    int text;
    if(value == 0){
        text = 2;
        if(randPlateIndexGenerator(generator) < 8){ text = 2; } else { text = 4; }
    } else { text = value; }
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

    if(column == 0){ tempgeom.setX(0); }
    else if(column == 1){ tempgeom.setX(111); }
    else if(column == 2){ tempgeom.setX(222); }
    else if(column == 3){ tempgeom.setX(333); }

    tempgeom.setWidth(108); tempgeom.setHeight(51);
    qle_list.at(k)->setGeometry(tempgeom);

    spawnCounter++;}

void boardWithgame::plateMoveAnimation(QLineEdit *lineedit, QRect from, QRect to)
{
    count++;
    if(speedMode_toogle == 0){
        animation = new QPropertyAnimation(lineedit, "geometry");
        animation->setDuration(250);
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

    if(column == 0){ to.setX(0); }
    else if(column == 1){ to.setX(111); }
    else if(column == 2){ to.setX(222); }
    else if(column == 3){ to.setX(333); }

    to.setWidth(108); to.setHeight(51);

    qle_list[j]->hide();
    qle_list.at(j)->setText("");

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

    if(column == 0){ to.setX(0); }
    else if(column == 1){ to.setX(111); }
    else if(column == 2){ to.setX(222); }
    else if(column == 3){ to.setX(333); }

    qle_list[j]->hide();
    qle_list.at(j)->setText("");

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

void boardWithgame::loadScore()
{
    fout.open(name.toStdString(),std::ios_base::app);
    fout << score << "\n";
    fout.close();
}

void boardWithgame::setFramePos()
{/*
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            qf_list.at(i)->setGeometry((270 +(100*i)), (370 + (100*j)), 100,100);
            qf_list.at(i)->setStyleSheet("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6);");
    }}*/
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
        for(int j = -1; j < 3; ++j){
            for(int k = 2; k > j; --k){
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
    for(int i = 0; i < 16; ++i){
        if(qle_list[i] != nullptr){
        switch(qle_list.at(i)->text().toInt()){
        case 2:
            qle_list.at(i)->setStyleSheet("background-color: rgb(50,93,168);border-radius: 20px; font-size: 41px;"); break;
        case 4:
            qle_list.at(i)->setStyleSheet("background-color: rgb(100,230,200);border-radius: 20px; font-size: 41px;"); break;
        case 8:
            qle_list.at(i)->setStyleSheet("background-color: rgb(139,50,168);border-radius: 20px; font-size: 41px;"); break;
        case 16:
            qle_list.at(i)->setStyleSheet("background-color: rgb(179,60,178);border-radius: 20px; font-size: 41px;"); break;
        case 32:
            qle_list.at(i)->setStyleSheet("background-color: rgb(199,70,198);border-radius: 20px; font-size: 41px;"); break;
        case 64:
            qle_list.at(i)->setStyleSheet("background-color: rgb(220,85,170);border-radius: 20px; font-size: 41px;"); break;
        case 128:
            qle_list.at(i)->setStyleSheet("background-color: rgb(75,140,198);border-radius: 20px; font-size: 41px;"); break;
        case 256:
            qle_list.at(i)->setStyleSheet("background-color: rgb(139,129,250);border-radius: 20px; font-size: 41px;"); break;
        case 512:
            qle_list.at(i)->setStyleSheet("background-color: rgb(230,110,200);border-radius: 20px; font-size: 41px;"); break;
        case 1024:
            qle_list.at(i)->setStyleSheet("background-color: rgb(230,40,222);border-radius: 20px; font-size: 41px;"); break;
        case 2048:
            qle_list.at(i)->setStyleSheet("background-color: rgb(130,10,250);border-radius: 20px; font-size: 41px;"); break;
        case 4096:
            qle_list.at(i)->setStyleSheet("background-color: rgb(240,160,20);border-radius: 20px; font-size: 41px;"); break;
        case 8192:
            qle_list.at(i)->setStyleSheet("background-color: rgb(130,100,58);border-radius: 20px; font-size: 41px;"); break;
        case 16384:
            qle_list.at(i)->setStyleSheet("background-color: rgb(170,50,201);border-radius: 20px; font-size: 41px;"); break;
        }}
}}


void boardWithgame::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        speedMode_toogle = 0;
    } else{
        speedMode_toogle = 1;
    }}
