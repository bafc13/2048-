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
//            moveLeft(2);
//            moveLeft(3);
//            moveLeft(4);

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

            moveRight(1);
            moveRight(2);
            moveRight(3);
            moveRight(4);

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

            moveDown(1);
            moveDown(2);
            moveDown(3);
            moveDown(4);

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

            moveUp(1);
            moveUp(2);
            moveUp(3);
            moveUp(4);

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
