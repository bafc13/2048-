#include <boardwithgame.cpp>



void boardWithgame::keyPressEvent(QKeyEvent *e) //рандом в столбце, передаём номер столбца, потом функция рандомит в строке
{
    if(e->key() == Qt::Key_Backspace)
    {
        on_stepBackButton_clicked();
    }

    if(e->key() == Qt::Key_Escape)
    {
        close();
    }

    if(e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
    {
        rearrangmentCounter = 0;
        spawnCounter = 0;
        stepBackAdd();
        moveLeft();
        gameEnd();
        if(rearrangmentCounter == 0){
            stepBackBack();
        }
        spawnAllPlates();
        setcolor();
    }


    if(e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
    {
        spawnCounter = 0;
        rearrangmentCounter = 0;
        stepBackAdd();
        moveRight();
        gameEnd();
        if(rearrangmentCounter == 0){
            stepBackBack();
        }
        spawnAllPlates();
        setcolor();
    }

    if(e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
    {
        spawnCounter = 0;
        rearrangmentCounter = 0;
        stepBackAdd();
        moveDown();
        gameEnd();
        if(rearrangmentCounter == 0){
            stepBackBack();
        }
        spawnAllPlates();
        setcolor();
    }

    if(e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
    {
        spawnCounter = 0;
        rearrangmentCounter = 0;
        stepBackAdd();
        moveUp();
        gameEnd();
        if(rearrangmentCounter == 0){
            stepBackBack();
        }
        spawnAllPlates();
        setcolor();
    }
}
