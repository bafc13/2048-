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
    QMovie *movie = new QMovie(":/new/prefix1/img/4Cb2.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
    ui->setupUi(this);
    setWindowTitle("board");
    ui->liveScore->setText(QString::number(0));//обнуление очков
    ui->label->setStyleSheet("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6); ");
    ui->checkBox->setStyleSheet ("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6); ");
    //qleadd();//добавление плашек в список
    //stepBackAdd();//добавление плашек в список, для восстановления значений на шаг назад
    //qle_list.at(randPlateIndexGenerator(generator))->setText("2");
    //qle_list.at(randPlateIndexGenerator(generator))->setText("2");
    setFrame ();
    qleadd();
    spawnPlate (0);

//    spawnPlate(randPlateIndexGenerator(generator));
//    spawnPlate(1);
//    spawnPlate(2);
//    spawnPlate(0);
//    spawnAllPlates();

    ui->gridLayoutWidget->setGeometry(QRect(298,365,400,400));
//    QLineEdit *plate = new QLineEdit;
//    plate->setText("2");
//    plate->setGeometry(0,0,100,100);
//    ui->gridLayout->addWidget(plate);

//    ui->gridLayout->itemAt(0)->setGeometry(QRect(0,0,100,100));
}

void boardWithgame::plateMoveAnimation(QLineEdit *lineedit)
{
    if(speedMode_toogle == 0){
    animation = new QPropertyAnimation(lineedit, "geometry");
    animation->setDuration(30);
    animation->setStartValue(lineedit->geometry());
    animation->setKeyValueAt(0.5,QRect(lineedit->x()-50, lineedit->y()-50,lineedit->width()-25,lineedit->height()-25));
    animation->setEndValue(lineedit->geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
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
            qf_list.append(frame);
            frame->setGeometry (QRect(0,0,100,100));
            frame->setStyleSheet ("background-color: rgba(100,50,60,200); border: 4mm ridge rgba(211, 220, 50, .6); ");
            ui->gridLayout->addWidget(frame, i, j, 1,1);
            ui->gridLayout->setRowMinimumHeight (i,100);
            ui->gridLayout->setColumnMinimumWidth(j,100);
        }
    }
}

void boardWithgame::spawnPlate(int k)
{

    int text = 0;
    if(randPlateIndexGenerator(generator) < 8){ text = 2; } else { text = 4; }

//    if(qle_list[k] != nullptr){
//        while(qle_list[k] != nullptr){
//            k = randPlateIndexGenerator(generator);
//        }
//    }
    QLineEdit *plate = new QLineEdit; // itematposition возвращает layoutitem...
    plate->setText(QString::number(text));
    plate->setReadOnly(1);
    plate->setStyleSheet("background-color: rgba(0,100,100,170);border-radius: 20px; font-size: 41px;");
    //qle_list[k] = new QLineEdit;
    qle_list[k] = plate;


    int row, column = 0; //column - столбец, row - ряд
//    switch (k + 1 % 4) {
//    case 1:
//        row = k + 1)
//        break;
//    default:
//        break;
//    }
    if((k + 1) % 4 == 0){
        row = ((k + 1) / 4) - 1;
        column = 3;
    } else if((k + 1) % 4 == 1){
        column = 0;
        if((k + 1) / 4 == 0) { row = 0; } else
        if((k + 1) / 4 == 1) { row = 1; } else
        if((k + 1) / 4 == 2) { row = 2; } else
        if((k + 1) / 4 == 3) { row = 3; }
    } else if((k + 1) % 4 == 2){
        column = 1;
        if((k + 1) / 4 == 0) { row = 0; } else
        if((k + 1) / 4 == 1) { row = 1; } else
        if((k + 1) / 4 == 2) { row = 2; } else
        if((k + 1) / 4 == 3) { row = 3; }
    } else if((k + 1) % 4 == 3){
        column = 2;
        if((k + 1) / 4 == 0) { row = 0; } else
        if((k + 1) / 4 == 1) { row = 1; } else
        if((k + 1) / 4 == 2) { row = 2; } else
        if((k + 1) / 4 == 3) { row = 3; }
    }

    //qf_list[1]->set
    ui->gridLayout->addWidget(qle_list.at(k), row, column, Qt::AlignCenter);
    spawnCounter++;
}

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
        qle_list[i] = nullptr;}
    }
    int first, second;
    first = randPlateIndexGenerator(generator);
    second = randPlateIndexGenerator(generator);
    qle_list[first] = new QLineEdit;
    qle_list.at(first)->setText("2");
    qle_list[second] = new QLineEdit;
    qle_list.at(second)->setText("2");
}

void boardWithgame::on_stepBackButton_clicked()
{
    for(int i = 0; i < 16; i++){
        qle_list.at(i)->setText(QString::number(stepBack_list[i]));
        if(stepBack_list[i] == 0){
            qle_list.at(i)->setText("");
        }
    }
}

bool boardWithgame::isEnd()
{
    int k = 0;
    for(int i = 0; i < 16; i++){
        if(qle_list[i] != nullptr){
            k++;}}
    if(k == 16){ return 1; }
    else { return 0; }
}

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
    }
}

void boardWithgame::stepBackAdd()
{
    for(int i = 0; i < 16; i++){
        reserveStepBack_list[i] = stepBack_list[i];
    }
    for(int i = 0; i < 16; i++){
        stepBack_list[i] = qle_list.at(i)->text().toInt();
    }
}

void boardWithgame::stepBackBack()
{
    for(int i = 0; i < 16; i++){
        stepBack_list[i] = reserveStepBack_list[i];
    }
}

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
        }}}
}

void boardWithgame::spawnAllPlates()
{
    if(rearrangmentCounter > 0){
        int k;
        while(spawnCounter == 0){
            k = randPlateIndexGenerator(generator);
            if(qle_list.at(k) == nullptr){
                spawnPlate(k);
            }
        }
    }
}

void boardWithgame::moveWithAddition(int k, int j)
{
    k = k - 1; j = j - 1;
    score += qle_list.at(k)->text().toInt() * 2;
    //qle_list.at(k)->setText(QString::number(qle_list.at(k)->text().toInt() + qle_list.at(j)->text().toInt()));
    //qle_list[k] = QString::number(QString::toInt(qle_list.at(k)->text()) + QString::toInt(qle_list.at(j)->text()));
    qle_list.at(k)->setText(QString::number(qle_list.at(k)->text().toInt() + qle_list.at(j)->text().toInt()));
    qle_list[j] = nullptr;
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k));
}

void boardWithgame::moveWithoutAddition(int k, int j)
{
    k = k - 1; j = j - 1;
    qle_list[k] = new QLineEdit;
    //qle_list.at(k)->setText(qle_list.at(j)->text());
    QLineEdit* bufj = new QLineEdit;
    QLineEdit* bufk = new QLineEdit;
    bufk->text() = qle_list.at(k)->text();
    bufj->text() = qle_list.at(j)->text();
    //qle_list.at(k) = buf;//qle_list.at(j);
    bufk->text()=bufj->text();
    qle_list.at(k)->setText(bufk->text());
    qle_list[j] = nullptr;
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k));
    delete bufk, bufj;
}

void boardWithgame::moveLeft(int k) // 1 строка
{
    if(k == 2){
        k = 5;
    } else if(k == 3){
        k = 9;
    } else if(k == 4){
        k = 13;
    }
    //для первой строки
        if(qle_list[k] != nullptr){
                if(qle_list[k - 1] == nullptr){ //перестановка элементов влево на пустое место
                    moveWithoutAddition(k, k + 1);}
                else if (qle_list.at(k - 1)->text() == qle_list.at(k)->text()){ //перестановка с сложением
                    moveWithAddition(k, k + 1);}}

             if(qle_list[k + 1] != nullptr && qle_list[k] == nullptr){
                if(qle_list[k - 1] == nullptr){ //перестановка на пустое влево
                    moveWithoutAddition(k, k + 2);}
                else if(qle_list.at(k - 1)->text() == qle_list.at(k + 1)->text()){ //перестановка с сложением влево
                     moveWithAddition(k, k + 2);}}

             if(qle_list[k + 1] != nullptr){//перестановка на пустое влево
                 if(qle_list[k] == nullptr){
                     moveWithoutAddition(k + 1, k +2);}
                 else if(qle_list.at(k)->text() == qle_list.at(k + 1)->text()){ //перестановка с сложением влево
                      moveWithAddition(k + 1, k + 2);}}
//////////////
              if(qle_list[k + 2] != nullptr && qle_list[k] == nullptr && qle_list[k + 1] == nullptr){
                  if(qle_list[k - 1] == nullptr){ //перестановка на пустое влево
                    moveWithoutAddition(k, k + 3);}
                  else if(qle_list.at(k - 1)->text() == qle_list.at(k + 2)->text()){//перестановка с сложением влево
                    moveWithAddition(k, k + 3);}}

              if(qle_list[k + 2] != nullptr && qle_list[k + 1] == nullptr){
                  if(qle_list[k] == nullptr){ //перестановка на пустое влево
                     moveWithoutAddition(k + 1, k + 3);}
                  else if(qle_list.at(k)->text() == qle_list.at(k + 2)->text()){ //перестановка с сложением  влево
                     moveWithAddition(k + 1, k + 3);}}

            if(qle_list[k + 2] != nullptr){
                if(qle_list[k + 1] == nullptr){ //перестановка на пустое влево
                    moveWithoutAddition(k + 2, k + 3);}                                 //6 if`ov
                else if(qle_list.at(k + 1)->text() == qle_list.at(k + 2)->text()){ //перестановка с сложение влево
                    moveWithAddition(k + 2, k + 3);}}
}

void boardWithgame::moveRight(int k)
{
    if(k == 2){
        k = 5;
    } else if(k == 3){
        k = 9;
    } else if(k == 4){
        k = 13;
    }
                if(qle_list[k + 1] != nullptr){//для первой строки
                    if(qle_list[k + 2] == nullptr){
                        moveWithoutAddition(k + 3, k + 2);}
                    else if (qle_list.at(k + 2)->text() == qle_list.at(k + 1)->text()){
                        moveWithAddition(k + 3, k + 2);}}

                 if(qle_list[k] != nullptr && qle_list[k + 1] == nullptr){
                    if(qle_list[k + 2] == nullptr){
                        moveWithoutAddition(k + 3, k + 1);}
                    else if(qle_list.at(k + 2)->text() == qle_list.at(k)->text()){
                        moveWithAddition(k + 3, k + 1);}}

                 if(qle_list[k] != nullptr){
                     if(qle_list[k + 1] == nullptr){
                        moveWithoutAddition(k + 2, k + 1);}
                     else if(qle_list.at(k + 1)->text() == qle_list.at(k)->text()){
                        moveWithAddition(k + 2, k + 1);}}

                  if(qle_list[k - 1] != nullptr && qle_list[k] == nullptr && qle_list[k + 1] == nullptr){
                      if(qle_list[k + 2] == nullptr){
                         moveWithoutAddition(k + 3, k);}
                      else if(qle_list.at(k + 2)->text() == qle_list.at(k - 1)->text()){
                          moveWithAddition(k + 3, k);}}

                      if(qle_list[k - 1] != nullptr && qle_list[k] == nullptr){
                          if(qle_list[k + 1] == nullptr){
                             moveWithoutAddition(k + 2, k);}
                          else if(qle_list.at(k + 1)->text() == qle_list.at(k - 1)->text()){
                              moveWithAddition(k + 2, k);}}

                    if(qle_list[k - 1] != nullptr){
                        if(qle_list[k] == nullptr){
                            moveWithoutAddition(k + 1, k);}                                 //6 if`ov
                        else if(qle_list.at(k - 1)->text() == qle_list.at(k)->text()){
                            moveWithAddition(k + 1, k);}}
}

void boardWithgame::moveDown(int k)
{
    if(qle_list[k + 7] != nullptr){//для первого столбца
                    if(qle_list[k + 11] == nullptr){
                        moveWithoutAddition(k + 12, k + 8);}
                    else if (qle_list.at(k + 11)->text() == qle_list.at(k + 7)->text()){
                        moveWithAddition(k + 12, k + 8);}}

                 if(qle_list[k + 3] != nullptr && qle_list[k + 7] == nullptr){
                    if(qle_list[k + 11] == nullptr){
                        moveWithoutAddition(k + 12, k + 4);}
                    else if(qle_list.at(k + 11)->text() == qle_list.at(k + 3)->text()){
                        moveWithAddition(k + 12, k + 4);}}

                 if(qle_list[k + 3] != nullptr){
                     if(qle_list[k + 7] == nullptr){
                        moveWithoutAddition(k + 8, k + 4);}
                     else if(qle_list.at(k + 7)->text() == qle_list.at(k + 3)->text()){
                        moveWithAddition(k + 8, k + 4);}}

                  if(qle_list[k - 1] != nullptr && qle_list[k + 3] == nullptr && qle_list[k + 7] == nullptr){
                      if(qle_list[k + 11] == nullptr){
                        moveWithoutAddition(k + 12, k);}
                      else if(qle_list.at(k - 1)->text() == qle_list.at(k + 11)->text()){
                        moveWithAddition(k + 12, k);}}

                      if(qle_list[k - 1] != nullptr && qle_list[k + 3] == nullptr){
                          if(qle_list[k + 7] == nullptr){
                             moveWithoutAddition(k + 8, k);}
                          else if(qle_list.at(k - 1)->text() == qle_list.at(k + 7)->text()){
                             moveWithAddition(k + 8, k); }}

                if(qle_list[k - 1] != nullptr){
                    if(qle_list[k + 3] == nullptr){
                        moveWithoutAddition(k + 4, k);}                                 //6 if`ov
                    else if(qle_list.at(k + 3)->text() == qle_list.at(k - 1)->text()){
                        moveWithAddition(k + 4, k);}}
}

void boardWithgame::moveUp(int k)
{
    if(qle_list[k + 3] != nullptr){//для первого столбца
                    if(qle_list[k - 1] == nullptr){
                       moveWithoutAddition(k, k + 4);}
                    else if (qle_list.at(k - 1)->text() == qle_list.at(k + 3)->text()){
                       moveWithAddition(k, k + 4);}}

                 if(qle_list[k + 7] != nullptr && qle_list[k + 3] == nullptr){
                    if(qle_list[k - 1] == nullptr){
                        moveWithoutAddition(k, k + 8);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k + 7)->text()){
                        moveWithAddition(k, k + 8);}}

                 if(qle_list[k + 7] != nullptr){
                     if(qle_list[k + 3] == nullptr){
                        moveWithoutAddition(k + 4, k + 8);}
                     else if(qle_list.at(k + 3)->text() == qle_list.at(k + 7)->text()){
                        moveWithAddition(k + 4, k + 8);}}

                  if(qle_list[k + 11] != nullptr && qle_list[k + 7] == nullptr && qle_list[k + 3] == nullptr){
                      if(qle_list[k - 1] == nullptr){
                        moveWithoutAddition(k, k + 12);}
                      else if(qle_list.at(k - 1)->text() == qle_list.at(k + 11)->text()){
                        moveWithAddition(k, k + 12);}}

                      if(qle_list[k + 11] != nullptr && qle_list[k + 7] == nullptr){
                          if(qle_list[k + 3] == nullptr){
                             moveWithoutAddition(k + 4, k + 12);}
                          else if(qle_list.at(k + 3)->text() == qle_list.at(k + 11)->text()){
                             moveWithAddition(k + 4, k + 12);}}

                if(qle_list[k + 11] != nullptr){
                    if(qle_list[k + 7] == nullptr){
                        moveWithoutAddition(k + 8, k + 12);}                                 //6 if`ov
                    else if(qle_list.at(k + 7)->text() == qle_list.at(k + 11)->text()){
                        moveWithAddition(k + 8, k + 12);}}
}

void boardWithgame::setStyleSheet()
{
//    for(int i = 0; i < 16; i++){
//        qle_list.at(i)->setStyleSheet("border-radius: 20px; opacity: 0.5; font-size: 41px;");
//    }
}

void boardWithgame::setcolor()
{
/*    QPalette palette;
    QColor color;
    for(int i = 0; i < 16; i++){
        if(qle_list.at(i)->text() == ""){
            color.setRgb(50,160,168);
            palette.setColor(QPalette::Base, color);
            palette.setColor (QPalette::Text, Qt::black);
            qle_list.at(i)->setPalette(palette);
        }*//*
        if(qle_list.at(i)->text() == "2"){
            color.setRgb(50,93,168);
            palette.setColor(QPalette::Base, color);
            qle_list.at(i)->setPalette(palette);
        }
        if(qle_list.at(i)->text() == "4"){
            color.setRgb(50,68,168);
            palette.setColor(QPalette::Base, color);
            qle_list.at(i)->setPalette(palette);
        }
        if(qle_list.at(i)->text() == "8"){
            color.setRgb(139,50,168);
            palette.setColor(QPalette::Base, color);
            qle_list.at(i)->setPalette(palette);
        }*/}
//        if(qle_list.at(i)->text() == "16"){
//            palette.setColor(QPalette::Base, QColor::setRgb(162, 50, 168));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "32"){
//            palette.setColor(QPalette::Base, QColor::setRgb(168, 50, 137));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "64"){
//            palette.setColor(QPalette::Base, QColor::setRgb(168, 50, 97));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "128"){
//            palette.setColor(QPalette::Base, QColor::setRgb(168, 50, 81));
//            qle_list.at(i)->setPalette(pallete);
//        }
//        if(qle_list.at(i)->text() == "256"){

//        }
//        if(qle_list.at(i)->text() == "512"){

//        }
//        if(qle_list.at(i)->text() == "1024"){

//        }
//        if(qle_list.at(i)->text() == "2048"){

//        }
//        if(qle_list.at(i)->text() == "4096"){

//        }
//        if(qle_list.at(i)->text() == "8192"){

//        }
//        if(qle_list.at(i)->text() == "16384"){

//        }
//    }
//}

void boardWithgame::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        speedMode_toogle = 0;
    } else{
        speedMode_toogle = 1;
    }
}
