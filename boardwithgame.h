#ifndef BOARDWITHGAME_H
#define BOARDWITHGAME_H
#include <iostream>
#include <QDialog>
#include <QLineEdit>
#include <QKeyEvent>
#include <fstream>
#include <QDebug>
#include <QPropertyAnimation>

//������� ������ ������� ������ �����, �� ���� ������ �����, ������� ������� � ��




namespace Ui {
class boardWithgame;
}

class boardWithgame : public QDialog
{
    Q_OBJECT


protected:
    void keyPressEvent(QKeyEvent *e) override; //���������� ����� � ����������

public:
    explicit boardWithgame(QWidget *parent = 0);
    ~boardWithgame();
    bool isEnd();
    void plateMoveAnimation(QLineEdit *lineedit);
    void qleadd();
    void setFrame();
    void winCheck();
    void moveWithoutAddition(int lineGenerator, int j);
    void moveWithAddition(int lineGenerator, int j);
    void spawnPlate(int lineGenerator);
    void spawnAllPlates();
    void gameEnd();
    void stepBackAdd();
    void stepBackBack();
    void moveLeft(int k);
    void moveRight(int k);
    void moveDown(int k);
    void moveUp(int k);
    int speedMode_toogle = 0;
    void setStyleSheet();
    void setcolor();


private slots:
    void on_exitButton_clicked();
    void on_resetButton_clicked();
    void on_stepBackButton_clicked();


    void on_checkBox_stateChanged(int arg1);

private:
    Ui::boardWithgame *ui;
    int score = 0;
    QList<QLineEdit*> qle_list;
    int stepBack_list[16];
    int reserveStepBack_list[16];
    int rearrangmentCounter = 0; //�������, ���������� �� ������������ ������
    int spawnCounter = 0; //�������, ���������� �� ��������� ����� ������
    const QString name = "highscore.txt";  //�������� ����� � ������������ ������
    std::ofstream fout;    //����� ������
    QPropertyAnimation *animation;

};

#endif // BOARDWITHGAME_H
