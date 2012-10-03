#include <QtGui/QApplication>
#include "mainwindow.h"
#include "qt/QCommandExecutor.h"
#include "base/CPacket.h"
#include "qt/QCommand.h"

#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"
#include<stdio.h>


//#define TEST_ENBL_BIT_TEST
#ifdef  TEST_ENBL_BIT_TEST

unsigned char data[21]={0x12,0x34,0x56};
unsigned char data1[sizeof(data)];

void testBits(){
    CPacket pack(0,1000);
    int i,j,t;

    for( int num_bits=1;num_bits < (sizeof(data)*8);num_bits++){
    int num_bytes = num_bits/8;
    for(   j=0; j< 11; j++ ){
        fprintf(stderr,"\nOfset[%d] NumBits[%d] Test Data:\n",j,num_bits );

        if(  ( j == 7 )&&( num_bits == 10 ) ){
            num_bits++;
            num_bits--;
        }

        t=0;
        do
        {
          data[t] = qrand();
          data1[t] = 0;
          fprintf(stderr,"%x ",data[t]);
          t++;
        }while( t < (num_bytes + ( (num_bits%8)?1:0) ) );

        fprintf(stderr,"\n");

        pack.setBits( j, num_bits , data);
        pack.getBits( j, num_bits , data1);

        for(   i=0; i < num_bytes ; i++ ){
            if( data[i] != data1[i] ){
                fprintf(stderr,"Error: BufSizeBits[%d], OffsetBits[%d] - Expected data[%x] Out data[%x]\n",
                        num_bits,j,data[i],data1[i]);
                exit(1);
                break;
            }
        }
        if( i == num_bytes ){
            if( num_bits%8 ){

                if(( data[i]&((1<<(num_bits%8)) - 1) )!=( data1[i]&((1<<(num_bits%8)) - 1) )){
                    fprintf(stderr,"Error: BufSizeBits[%d], OffsetBits[%d] - Expected data[%x] Out data[%x]\n",
                            num_bits,j,( data[i]&((1<<(num_bits%8)) - 1)),( data1[i]&((1<<(num_bits%8)) - 1)) );
                    exit(1);
                }
                else{
                    fprintf(stderr,"Test OK!\n");
                }
            }
            else{
                fprintf(stderr,"Test OK!\n");
            }
        }
        else{
            fprintf(stderr,"ERROR!!!\n");
            exit(1);
        }

    }
    }
}
#endif

class base{
public:
    base(){
        fprintf(stderr,"create base");
    }
    ~base(){
        fprintf(stderr,"destroy base");
    }

};

class first_child:public base{
public:
    first_child(){
        fprintf(stderr,"create first_child");
    }
    ~first_child(){
        fprintf(stderr,"destroy first_child");
    }

};

class second_child :public first_child{
public:
    second_child(){
        fprintf(stderr,"create second_child");
    }
    ~second_child(){
        fprintf(stderr,"destroy second_child");
    }

};


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;//,w1;

    base* base_obj;
    second_child* second_child_obj = new second_child;
    base_obj = second_child_obj;

    //delete base_obj;

    delete second_child_obj;


    w.show();
  //  w1.show();
#ifdef TEST_ENBL_BIT_TEST
    testBits();
#endif
  //  QFrameWork frameWork( new QFrameWorkElementsFactory() ,&w );
  //  QCommandExecutor exec;
  //  QCommand* comm = new QCommand(NULL);
  //  exec.appendCommand(comm);
  //  exec.startExecution(true);
    return a.exec();
}
