
#include "base/CFrameWork.h"
#include "base/CFrameWorkElementsFactory.h"

CFrameWork::CFrameWork(CFrameWorkElementsFactory * elementsFactory) {
  DEBUG("Create Frame Work Factory");
  m_ElementsFactory = 0;                   
  m_ControlView = 0;                                     
  m_DataPlot    = 0;                                     
  m_Executor    = 0;                                     
  m_Protocol    = 0;                                     
  m_PortIO      = 0;                                     
  m_Colector    = 0;                                     
  if( NO_ERR != attachElementsFactory(elementsFactory) ){
      /*TODO: throw exception maybe*/                    
      CRITICAL("Can't attach ElementsFactory");          
  }                                                      
}

CFrameWork::~CFrameWork() {
  deattachCurrentElementsFactory();                           
}

CPortIO * CFrameWork::getPortIO() {
  return m_PortIO;
}

CPacketCollector  * CFrameWork::getColector() volatile {
  return m_Colector;
}

CProtocolPackFactory * CFrameWork::getProtocol() {
  return m_Protocol;
}

CCommandExecutor* CFrameWork::geExecutor() {
  return m_Executor;
}

CDataPlot * CFrameWork::getDataPlot() {
  return m_DataPlot;
}

CControlView* CFrameWork::getControlView() {
  return m_ControlView;
}

/**
 * This function attach elements factory for FrameWork. If there allready have a factory,
 * this function make deallocation of all ellements, created with current factory, 
 * deallocate current factory and allocate new elements with new factory.
 */
int CFrameWork::attachElementsFactory(CFrameWorkElementsFactory * elementsFactory) {
  int ret = NO_ERR;                                                  
  if( 0 != m_ElementsFactory ){                                      
      if( NO_ERR != deattachCurrentElementsFactory() ){              
          /*TODO - do someting in error*/                            
          DEBUG("Error when deattach ElementsFactory [%d]" , ret);   
          return ret;                                                
      }                                                              
  }                                                                  
  m_ElementsFactory = elementsFactory;                               
  if( 0 != m_ElementsFactory ){                                      
      m_ControlView = m_ElementsFactory->createControlView();        
      m_DataPlot    = m_ElementsFactory->createDataPlot();           
      m_Executor    = m_ElementsFactory->createCommandExecutor();    
      m_Protocol    = m_ElementsFactory->createProtocol();            
      m_PortIO      = m_ElementsFactory->createPortIO(CPortIO::SIMULATOR_IO);// SERIALPORT_IO TODO FIX ME
      m_Colector    = m_ElementsFactory->createPacketCollector(this);                                                               
  }                                                                  
  else{                                                              
      DEBUG("Attach NULL to  ElementsFactory");                      
  }                                                                  
  return ret;                                                                                                            
}

int CFrameWork::deattachCurrentElementsFactory() {
  int ret = NO_ERR;                                            
  /*TODO - do some check and return error mayby in some cases*/
  if( 0 != m_ElementsFactory ){                                
      if( 0 != m_Executor ){                                   
          m_ElementsFactory->deleteExecutor( m_Executor );     
      }                                                        
      if( 0 != m_Protocol ){                                   
          m_ElementsFactory->deleteProtocol(m_Protocol);       
      }                                                        
      if( 0 != m_PortIO ){                                     
          m_ElementsFactory->deletePortIO(m_PortIO);           
      }                                                        
      if( 0 != m_Colector ){                                   
          m_ElementsFactory->deleteColector(m_Colector);       
      }                                                        
      if( 0 != m_ControlView ){                                
          m_ElementsFactory->deleteControlView(m_ControlView); 
      }                                                        
      if( 0 != m_DataPlot ){                                   
          m_ElementsFactory->deleteDataPlot(m_DataPlot);       
      }                                                        
      delete m_ElementsFactory;                                
  }                                                            
  return ret;                                                  
}

