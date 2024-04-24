#ifndef BOARDWITHGAME_H
#define BOARDWITHGAME_H
#include <iostream>
#include <QDialog>
#include <QLineEdit>
#include <QKeyEvent>
#include <fstream>
#include <QDebug>
#include <QPropertyAnimation>



namespace Ui {
class boardWithgame;
}

class boardWithgame : public QDialog
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *e) override; //управление игрой с клавиатуры
public:
    explicit boardWithgame(QWidget *parent = 0);
    ~boardWithgame();
    bool isEnd();
    void plateMoveAnimation(QLineEdit *lineedit, QRect from, QRect to);
    void qleadd();
    void setFrame();
    void winCheck();
    void moveWithoutAddition(int lineGenerator, int j);
    void moveWithAddition(int lineGenerator, int j);
    void spawnPlate(int lineGenerator, int value = 0);
    void spawnAllPlates();
    void gameEnd();
    void stepBackAdd();
    void stepBackBack();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    int speedMode_toogle = 0;
    void setcolor();
    void tryMove(int k, int j);
    void loadScore();
    void setFramePos();
private slots:
    void on_exitButton_clicked();
    void on_resetButton_clicked();
    void on_stepBackButton_clicked();
    void on_checkBox_stateChanged(int arg1);
private:
    int count = 0;
    Ui::boardWithgame *ui;
    int score = 0;
    QList<QLineEdit*> qle_list;
    QList <QFrame*> qf_list;
    int stepBack_list[16] = {0};
    int reserveStepBack_list[16];
    int rearrangmentCounter = 0; //счётчик, отвечающий за перестановки плашек
    int spawnCounter = 0; //счётчик, отвечающий за рандомный спавн плашек
    const QString name = "highscore.txt";  //название файла с максимальным счётом
    std::ofstream fout;    //поток вывода
    QPropertyAnimation *animation;
    int animateEachPlate = 0;
};

#endif // BOARDWITHGAME_H
