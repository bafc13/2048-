#include <boardwithgame.cpp>



void boardWithgame::keyPressEvent(QKeyEvent *e) //������ � �������, ������� ����� �������, ����� ������� �������� � ������
{
        //stepBackAdd(); //���������� ������� ��� ������ �� ��� �����
        //setcolor();



        if(e->key() == Qt::Key_Escape){
            close();
        }


        if(e->key() == Qt::Key_A || e->key() == Qt::Key_Left){ //���� ���������� �������� �����
            rearrangmentCounter = 0;
            spawnCounter = 0;

            //����
            //��������
            //�����

            moveLeft();

            //����
            //���������
            //����
            gameEnd();

            //����...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

              //����
              //����������
              //������

            spawnAllPlates();


            setcolor();




        }


        if(e->key() == Qt::Key_D || e->key() == Qt::Key_Right) { //���� ���������� �������� ������
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //����
            //��������
            //������

            moveRight();

            //����
            //���������
            //����

            gameEnd();

            //����...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

            //����
            //����������
            //������
            spawnAllPlates();



            setcolor();


        }


        if(e->key() == Qt::Key_S || e->key() == Qt::Key_Down){ //���� ���������� �������� ����
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //����
            //��������
            //����

            moveDown();

            //����
            //���������
            //����

            gameEnd();

            //����...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

            //����
            //����������
            //������
            spawnAllPlates();

            setcolor();
        }


        if(e->key() == Qt::Key_W || e->key() == Qt::Key_Up){ //���� ���������� �������� �����
            spawnCounter = 0;
            rearrangmentCounter = 0;

            //����
            //��������
            //�����

            moveUp();

            //����
            //���������
            //����

            gameEnd();

            //����...

//            if(rearrangmentCounter == 0){
//                stepBackBack();
//            }

              //����
              //����������
              //������
            spawnAllPlates();

            setcolor();}
}
