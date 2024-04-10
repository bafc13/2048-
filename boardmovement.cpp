#include <boardwithgame.cpp>



void boardWithgame::keyPressEvent(QKeyEvent *e) //рандом в столбце, передаём номер столбца, потом функция рандомит в строке
{
        //stepBackAdd(); //заполнение массива для отката на ход назад
        //setcolor();



        if(e->key() == Qt::Key_Escape){
            close();
        }


        if(e->key() == Qt::Key_A || e->key() == Qt::Key_Left){ //если происходит движение влево
            rearrangmentCounter = 0;
            spawnCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВЛЕВО

            moveLeft();

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

            spawnAllPlates();


            setcolor();




        }


        if(e->key() == Qt::Key_D || e->key() == Qt::Key_Right) { //если происходит движение вправо
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВПРАВО

            moveRight();

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
            spawnAllPlates();



            setcolor();


        }


        if(e->key() == Qt::Key_S || e->key() == Qt::Key_Down){ //если происходит движение вниз
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВНИЗ

            moveDown();

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
            spawnAllPlates();

            setcolor();
        }


        if(e->key() == Qt::Key_W || e->key() == Qt::Key_Up){ //если происходит движение вверх
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //БЛОК
            //СМЕЩЕНИЯ
            //ВВЕРХ

            moveUp();

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
            spawnAllPlates();

            setcolor();}
}
