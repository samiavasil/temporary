#include "QFraCreator.h"
#include "qt/QFrameWork.h"

QFraCreator::QFraCreator(QObject *parent):QCreator(parent)
{

}

void QFraCreator::Create( CFrameWork * fW)
{
    if( fW )
    {
        QFrameWork* qfW = dynamic_cast<QFrameWork*>(fW);
        if( qfW )
        {
          QList<QObject*> list;
          list = qfW->CreateObjectFromType( );
          for( int i = 0; i < list.count(); i++ ){
              if( list[i] ){
                  QWidget* ptr = dynamic_cast<QWidget*>(list[i]);//DELL ME
                  if(ptr)
                  {
                      ptr->show();
                  }
              }

          }
        }
    }
}

void QFraCreator::Free()
{

}
