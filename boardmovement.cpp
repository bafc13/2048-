#include <boardwithgame.cpp>



void boardWithgame::keyPressEvent(QKeyEvent *e) //рандом в столбце, передаём номер столбца, потом функция рандомит в строке
{
        //stepBackAdd(); //заполнение массива для отката на ход назад
        //setcolor();



        if(e->key() == Qt::Key_Escape){
            close();
        }


        if(e->key() == Qt::Key_A){ //если происходит движение влево
            rearrangmentCounter = 0;
            spawnCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВЛЕВО

            moveLeft();
//            moveLeft(2);
//            moveLeft(3);
//            moveLeft(4);

            //БЛОК
            //ОКОНЧАНИЯ
            //ИГРЫ
            gameEnd();

            //Блок...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

              //БЛОК
              //РАНДОМНОГО
              //СПАВНА

            spawnAllPlates();}


        if(e->key() == Qt::Key_D) { //если происходит движение вправо
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВПРАВО

            moveRight(1);
            moveRight(2);
            moveRight(3);
            moveRight(4);

            //БЛОК
            //ОКОНЧАНИЯ
            //ИГРЫ

            gameEnd();

            //Блок...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

            //БЛОК
            //РАНДОМНОГО
            //СПАВНА
            spawnAllPlates();}


        if(e->key() == Qt::Key_S){ //если происходит движение вниз
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВНИЗ

            moveDown(1);
            moveDown(2);
            moveDown(3);
            moveDown(4);

            //БЛОК
            //ОКОНЧАНИЯ
            //ИГРЫ

            gameEnd();

            //Блок...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

            //БЛОК
            //РАНДОМНОГО
            //СПАВНА
            spawnAllPlates();}


        if(e->key() == Qt::Key_W){ //если происходит движение вверх
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВВЕРХ

            moveUp(1);
            moveUp(2);
            moveUp(3);
            moveUp(4);

            //БЛОК
            //ОКОНЧАНИЯ
            //ИГРЫ

            gameEnd();

            //Блок...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

              //БЛОК
              //РАНДОМНОГО
              //СПАВНА
            spawnAllPlates();}
}
