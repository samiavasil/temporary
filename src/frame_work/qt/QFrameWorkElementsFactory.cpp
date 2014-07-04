
#include "qt/QFrameWorkElementsFactory.h"
#include "qt/QCommandExecutor.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QPacketCollector.h"
#include "qt/QProtocolLoader.h"
#include "qt/QSerialPortIO.h"
#include "base/CPortIO.h"
#include "base/CProtocolPackFactory.h"
#include "base/CCommandExecutor.h"
#include "base/CPacketCollector.h"
#include "base/CFrameWork.h"
#include "base/CDataPlot.h"



//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFrameWorkElementsFactory::QFrameWorkElementsFactory() {
  DEBUG << "Create QFrameWorkElementsFactory";
}

QFrameWorkElementsFactory::~QFrameWorkElementsFactory() {
  DEBUG << "Destroy QFrameWorkElementsFactory";
}

CPortIO* QFrameWorkElementsFactory::createPortIO(const CPortIO::portIo_type type) {
  CPortIO* port = NULL;                            
  DEBUG << "Create PortIo";
  switch( type ) {                                 
  case CPortIO::SIMULATOR_IO :{      

      break;                                       
  }                                                
  case CPortIO::SERIALPORT_IO :{                   
      port = new QSerialPortIO();                  
      break;                                       
  }                                                
  case CPortIO::USBPORT_IO :{                      
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
CProtocolPackFactory* QFrameWorkElementsFactory::createProtocol() {
  DEBUG << "Create Protocol";
  CProtocolPackFactory* protocol = new QProtocolPackFactory();
  if( 0 == protocol ){
      CRITICAL <<  "Can't create QProtocolPackFactory";
  }
  return protocol;
}

CCommandExecutor* QFrameWorkElementsFactory::createCommandExecutor() {
  DEBUG << "Create Command Executor";
  QCommandExecutor* exec = new QCommandExecutor(NULL);     
  if( 0 != exec ){                                         
      if( NO_ERR != exec->startExecution() ){
          CRITICAL <<  "Can't start Executor thread";
      }                                                    
  }                                                        
  return ( exec );                                         
}

CPacketCollector* QFrameWorkElementsFactory::createPacketCollector( CFrameWork * cFwk ) {
    DEBUG << "Create Packet Collector";
    QPacketCollector* coll = NULL;//TODO= new QPacketCollector(cFwk)
    if( 0 == coll ){                                 
        CRITICAL <<  "Can't create QPacketCollector";
    }                                                
    return ( coll ); 
}

CControlView* QFrameWorkElementsFactory::createControlView() {
  DEBUG << "Create Control View";
  return NULL;                 
}

CDataPlot* QFrameWorkElementsFactory::createDataPlot() {
  DEBUG << "Create Data Plot";
   return NULL;
}


