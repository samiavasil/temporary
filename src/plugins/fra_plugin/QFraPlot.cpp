
#include "QFraPlot.h"
#include <QWidget>


/**
   @brief       

   @param      

   Description:  

   @pre 
   
   @return
     
   @note
   @see         
 */

QFraPlot::QFraPlot(QWidget * parent):QDataPlot(parent),ui(new Ui::QFraPlot)  {
  
}

QFraPlot::~QFraPlot() {
}

/**
   @brief       

   @param      

   Description:  

   @pre 
   
   @return
     
   @note
   @see         
 */

void QFraPlot::InitUI() {
  ui->setupUi(this);
}

