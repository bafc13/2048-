#include <boardwithgame.cpp>



void boardWithgame::keyPressEvent(QKeyEvent *e) //������ � �������, ������� ����� �������, ����� ������� �������� � ������
{
        //stepBackAdd(); //���������� ������� ��� ������ �� ��� �����
        //setcolor();



        if(e->key() == Qt::Key_Escape){
            close();
        }


        if(e->key() == Qt::Key_A){ //���� ���������� �������� �����
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

            spawnAllPlates();}


        if(e->key() == Qt::Key_D) { //���� ���������� �������� ������
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
            spawnAllPlates();}


        if(e->key() == Qt::Key_S){ //���� ���������� �������� ����
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
            spawnAllPlates();}


        if(e->key() == Qt::Key_W){ //���� ���������� �������� �����
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
            spawnAllPlates();}
}
