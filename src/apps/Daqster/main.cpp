#include <QtGui/QApplication>
#include "mainwindow.h"
#include "qt/QCommandExecutor.h"
#include "base/CPacket.h"
#include "qt/QCommand.h"

#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"
#include<stdio.h>


#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>

class msg{
public:
    static void myMessageOutput(QtMsgType type, const char *msg)
    {
        switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "%s\n", msg);
            break;
        case QtWarningMsg:
         //TODO:   fprintf(stderr, "%s\n", msg);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "%s\n", msg);
            break;
        case QtFatalMsg:
            fprintf(stderr, "%s\n", msg);
            abort();
        }
    }
};



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


#include<QLayout>

class DataType{

public:
    typedef enum{
        Real,
        Complex
    } Types;

    typedef enum{
        I8,
        I16,
        I32,
        I64,
        U8,
        U16,
        U32,
        FLOAT,
        DOUBLE
    } TypeOrder;
public:
    DataType( Types T, TypeOrder N ):m_Type(T),m_TypeOrder(N){

    }
    Types      type(){return m_Type;}
    TypeOrder  typeOrder(){return m_TypeOrder;}
    int compatible( DataType& other ){
        int ret = -1;
        if( m_Type == other.m_Type )
        {
            if( m_TypeOrder >= other.m_TypeOrder )
            {
                DEBUG << "Full compatible types";
                ret = 0;
            }
            else
            {
                DEBUG << "Truncated not full compatible types";
                ret = 1;
            }
        }
        else
        {
            DEBUG << "Not compatible types";
        }
        return ret;
    }

protected:
    Types     m_Type;
    TypeOrder m_TypeOrder;
};



DataType obj(DataType::Real,     DataType::I64);
DataType obj1(DataType::Real,    DataType::I32);
DataType obj2(DataType::Complex, DataType::I32);


#include "qt/QRegFactory.h"


int main(int argc, char *argv[])
{
    msg m;
    qInstallMsgHandler(m.myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;

    //QObject::connect(QPluginList::Instance(),SIGNAL(pluginsUpdate()),&vv,SLOT(reloadPLuginList()));

    //QDesignerComponents c;
/*
    fact1_t::Registrator<A>  rep( "Alabvala" );

    QSet<QString> outlist;
    fact1_t::GetRegList(outlist);
    qDebug()<<outlist;*/

//if( iface )
//{
//    QWidget* w = iface->topLevel();
//    if(w)
//    w->show();
//}

//    QDesignerFormEditorInterface formEditor;
//    QDesignerObjectInspectorInterface *objectInspector = 0;
//    objectInspector = formEditor.objectInspector();
//formEditor.topLevel()->show();
//    QDesignerFormWindowManagerInterface *manager = 0;
// //   manager = formEditor.formWindowManager();

    //objectInspector->setFormWindow(manager->formWindow(0));

    obj.compatible(obj);
    obj.compatible(obj1);
    obj1.compatible(obj);

    obj1.compatible(obj2);

    w.show();


#ifdef TEST_ENBL_BIT_TEST
    testBits();
#endif
    return a.exec();
}
