
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
#include "base/CControlView.h"
#include "base/CDataPlot.h"
#include "qt/QPortIOSimulator.h"

QFrameWorkElementsFactory::QFrameWorkElementsFactory() {
  DEBUG("Create QFrameWorkElementsFactory");
}

QFrameWorkElementsFactory::~QFrameWorkElementsFactory() {
  DEBUG("Destroy QFrameWorkElementsFactory");
}

CPortIO* QFrameWorkElementsFactory::createPortIO(const CPortIO::portIo_type type) {
  CPortIO* port = NULL;                            
  DEBUG("Create PortIo");                          
  switch( type ) {                                 
  case CPortIO::SIMULATOR_IO :{      
       port = new QPortIOSimulator();                 
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
      CRITICAL( "Can't create QPortIO" );          
  }                                                
  return port;                                     
}

CProtocolPackFactory* QFrameWorkElementsFactory::createProtocol() {
  DEBUG("Create Protocol"); 
  CProtocolPackFactory* protocol = new QProtocolPackFactory(new QProtocolLoader());
  if( 0 == protocol ){
      CRITICAL( "Can't create QProtocolPackFactory" );
  }
  return protocol;
}

CCommandExecutor* QFrameWorkElementsFactory::createCommandExecutor() {
  DEBUG("Create Command Executor");                        
  QCommandExecutor* exec = new QCommandExecutor(NULL);     
  if( 0 != exec ){                                         
      if( NO_ERR != exec->startExecution( true ) ){        
          CRITICAL( "Can't start Executor thread" );       
      }                                                    
  }                                                        
  return ( exec );                                         
}

CPacketCollector* QFrameWorkElementsFactory::createPacketCollector( CFrameWork * cFwk ) {
    DEBUG("Create Packet Collector");                
    QPacketCollector* coll = NULL;//TODO= new QPacketCollector(cFwk)
    if( 0 == coll ){                                 
        CRITICAL( "Can't create QPacketCollector" ); 
    }                                                
    return ( coll ); 
}

CControlView* QFrameWorkElementsFactory::createControlView() {
  DEBUG("Create Control View");
  return NULL;                 
}

CDataPlot* QFrameWorkElementsFactory::createDataPlot() {
  DEBUG("Create Data Plot");
   return NULL;
}

void QFrameWorkElementsFactory::deleteExecutor(CCommandExecutor * executor) {
  if( executor ){
       delete (QCommandExecutor*) executor;
  }
}

void QFrameWorkElementsFactory::deleteProtocol(CProtocolPackFactory * protocol) {
  if( protocol ){                              
      delete (QProtocolPackFactory*) protocol; 
  }                                            
}

void QFrameWorkElementsFactory::deletePortIO(CPortIO * port) {
    if( port ){                 
        DEBUG("Delete PortIo");
        switch( port->type() ) {
        case CPortIO::SIMULATOR_IO :{
  		  delete (QPortIOSimulator*) port;
            break;
        }
        case CPortIO::SERIALPORT_IO :{
            delete (QSerialPortIO*) port;
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
            CRITICAL( "Can't create QPortIO" );
        }
    }
    
}

void QFrameWorkElementsFactory::deleteColector(CPacketCollector * collector) {
  if( collector ){                          
      delete (QPacketCollector*) collector; 
  }                                         
}

void QFrameWorkElementsFactory::deleteControlView(CControlView * ctrlView) {
  DEBUG("TODO: Not implemented %x",(unsigned int)ctrlView );
}

void QFrameWorkElementsFactory::deleteDataPlot(CDataPlot * dataPlot) {
   DEBUG("TODO: Not implemented %x",(unsigned int)dataPlot );
}

