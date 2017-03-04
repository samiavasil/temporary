#include "qt/QTestFrameWorkElementsFactory.h"
#include "qt/QCommandExecutor.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QPacketCollector.h"
#include "qt/QProtocolLoader.h"
#include "qt/QSerialPortIO.h"
#include "base/QDataPlot.h"



//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

template<typename Element> QTestFrameWorkElementsFactory<Element>::QTestFrameWorkElementsFactory() {
  DEBUG << "Create QFrameWorkElementsFactory";
}

template<typename Element> QTestFrameWorkElementsFactory<Element>::~QTestFrameWorkElementsFactory() {
  DEBUG << "Destroy QFrameWorkElementsFactory";
}

template<typename Element> QPortIO* QTestFrameWorkElementsFactory<Element>::createPortIO(const Element &type) {
  QPortIO* port = NULL;                            
  DEBUG << "Create PortIo";
  switch( type ) {                                 
  case QPortIO::SIMULATOR_IO :{      

      break;                                       
  }                                                
  case QPortIO::SERIALPORT_IO :{                   
      port = new QSerialPortIO();                  
      break;                                       
  }                                                
  case QPortIO::USBPORT_IO :{                      
      break;                                       
  }                                                
  default:{                                        
      break;                                       
  }                                                
  }                                                
  if( 0 == port ){                                 
      CRITICAL <<  "Can't create QPortIO";
  }                                                
  return port;                                     
}

#include"qt/QProtocolDb.h"//TODO
#include"qt/QProtocolLoader.h"//TODO
template<typename Element> QProtocolPackFactory* QTestFrameWorkElementsFactory<Element>::createProtocol(const Element &type) {
  DEBUG << "Create Protocol";
  QProtocolPackFactory* protocol = new QProtocolPackFactory(new QProtocolDb());//TODO FIX ME
  if( 0 == protocol ){
      CRITICAL <<  "Can't create QProtocolPackFactory";
  }
  return protocol;
}

template<typename Element> QCommandExecutor* QTestFrameWorkElementsFactory<Element>::createCommandExecutor(const Element &type) {
  DEBUG << "Create Command Executor";
  QCommandExecutor* exec = new QCommandExecutor(NULL);     
  if( 0 != exec ){                                         
      if( NO_ERR != exec->startExecution() ){
          CRITICAL <<  "Can't start Executor thread";
      }                                                    
  }                                                        
  return ( exec );                                         
}

template<typename Element> QPacketCollector* QTestFrameWorkElementsFactory<Element>::createPacketCollector( QFrameWork * cFwk,const Element& type ) {
    DEBUG << "Create Packet Collector";
    QPacketCollector* coll = NULL;//TODO= new QPacketCollector(cFwk)
    if( 0 == coll ){                                 
        CRITICAL <<  "Can't create QPacketCollector";
    }                                                
    return ( coll ); 
}

template<typename Element> CControlView* QTestFrameWorkElementsFactory<Element>::createControlView(const Element& type) {
  DEBUG << "Create Control View";
  return NULL;                 
}

template<typename Element> QDataPlot* QTestFrameWorkElementsFactory<Element>::createDataPlot(const Element& type) {
  DEBUG << "Create Data Plot";
   return NULL;
}


