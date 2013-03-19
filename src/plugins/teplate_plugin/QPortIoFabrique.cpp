#include "portio/QPortIoFabrique.h"
#include "basic/QPortIO.h"
#include "portio/QSerialPortDevice.h"
#include "portio/QSimulatorDevice.h"

/**
   @brief       

   @param      

   Description:  

   @pre 
   
   @return
     
   @note
   @see         
 */

QPortIO * QPortIoFabrique::createPortIo(const QPortIoFabrique::QPortIoType & type) const {
          QPortIO* portIo = NULL;
          switch( type ){
          case SERIAL:{
                  portIo = new QSerialPortDevice("COM1");//TODO
                  break;
              }
          case USB:{
                  break;
              }
          case SIMULATOR:{
                  portIo = new QSimulatorDevice();
                  break;
              }
          default:{
                  portIo = new QSimulatorDevice();//TODO break;
              }          
          }
          return portIo;
}

