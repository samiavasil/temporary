
#include "qt/QPortIOSimulator.h"
#include <QTimer>

#include <QObject>
#include<QWidget>

QPortIOSimulator::QPortIOSimulator(QObject * parent):QPortIO( parent ) {
  DEBUG("Create QPortIOSimulator");   
  m_PortType = SIMULATOR_IO;          
  qsrand ( qrand() );                 
  m_ReadCounter  = 0;                 
  m_WriteCounter = 0;                 
  m_TaskRuned = false;                
}

QPortIOSimulator::~QPortIOSimulator() {
}

void QPortIOSimulator::showPortConfiguration( QWidget * parent ){
    QWidget* widget = new QWidget(parent);
    widget->setAttribute(Qt::WA_DeleteOnClose, true);
}

int64 QPortIOSimulator::bytesAvailable() {
  int Len;            
  m_Mutex.lock();     
  Len = m_Data.size();
  m_Mutex.unlock();   
  return Len;         
}

int64 QPortIOSimulator::read(char * data, const int64 maxlen) {
  int Len = 0;                                             
  m_Mutex.lock();                                          
  if( 0 != data ){                                         
      if( m_Data.size() < maxlen ){                        
          Len = m_Data.size();                             
      }                                                    
      else{                                                
          Len = maxlen;                                    
      }                                                    
      if( 0 < Len ){                                       
          memcpy( data,m_Data.left(maxlen),Len);           
          m_Data.remove(0,Len);                            
          m_ReadCounter += Len;                            
      }                                                    
  }                                                        
  m_Mutex.unlock();                                        
  return Len;                                              
}

int64 QPortIOSimulator::write(const char * data, const qint64 len) {
  m_Mutex.lock();                   
  m_WriteData.append(data,len);     
  if( false == m_TaskRuned ){       
      reloadSimulatorTask();        
  }                                 
  m_WriteCounter += len;            
  m_Mutex.unlock();                 
  return len;                       
}

int64 QPortIOSimulator::write(const char * data) {
  return write( data, strlen(data) );
}

int QPortIOSimulator::open() {
  return 0;
}

void QPortIOSimulator::close() {
  
}

void QPortIOSimulator::reloadSimulatorTask() {
  int randTime = (qrand()%5);
  QTimer::singleShot( randTime, this, SLOT(simulatorTask()));
  m_TaskRuned = true;          
}

void QPortIOSimulator::simulatorTask() {
  int randSize = (qrand()%10 ) + 1;
  m_Mutex.lock();                                                               
  if(   randSize > m_WriteData.size() ){                                        
      randSize = m_WriteData.size();                                            
  }                                                                             
  if( 0 < randSize ){                                                           
      m_Data.append( m_WriteData.left(randSize) );                              
      m_WriteData.remove( 0, randSize );     
  
  }                                                                             
  if( 0 < m_WriteData.size() ){                                                 
      reloadSimulatorTask();                                                    
  }                                                                             
  else{                                                                         
    //  DEBUG("m_ReadCounter = %d m_WriteCounter = %d",m_ReadCounter,m_WriteCounter);
       m_TaskRuned = false;	 
  }                                                                             
  m_Mutex.unlock();                                                             
  emit readyReadSignal();
}

