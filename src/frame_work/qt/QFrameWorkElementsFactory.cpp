
#include "qt/QFrameWorkElementsFactory.h"
#include "base/CPortIO.h"
#include "base/CProtocolPackFactory.h"
#include "base/CCommandExecutor.h"
#include "base/CPacketCollector.h"
#include "base/CControlView.h"
#include "base/CDataPlot.h"
#include "qt/QCommandExecutor.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QPacketCollector.h"
#include "qt/QProtocolLoader.h"

CPortIO* QFrameWorkElementsFactory::createPortIO() {
  DEBUG("Create PortIo");
  return NULL;           
}

CProtocolPackFactory* QFrameWorkElementsFactory::createPrtocol() {
  DEBUG("Create Protocol"); 
  CProtocolPackFactory* protocol = new QProtocolPackFactory(NULL);
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

CPacketCollector* QFrameWorkElementsFactory::createPacketCollector() {
  DEBUG("Create Packet Collector");   
  return NULL;                        
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
  DEBUG("TODO: Not implemented");
}

void QFrameWorkElementsFactory::deletePortIO(CPortIO * port) {
  DEBUG("TODO: Not implemented");
}

void QFrameWorkElementsFactory::deleteColector(CPacketCollector * collector) {
  DEBUG("TODO: Not implemented");
}

void QFrameWorkElementsFactory::deleteControlView(CControlView * ctrlView) {
  DEBUG("TODO: Not implemented");
}

void QFrameWorkElementsFactory::deleteDataPlot(CDataPlot * dataPlot) {
  DEBUG("TODO: Not implemented");
}

