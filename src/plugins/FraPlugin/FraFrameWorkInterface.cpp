#include "FraFrameWorkInterface.h"
#include "QFraFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"
FraFrameWorkInterface::FraFrameWorkInterface(QObject* parent ):QObject(parent)
{
}

FraFrameWorkInterface::~FraFrameWorkInterface(  )
{
    DEBUG("frameworkinterface object removed");
}

QFrameWork* FraFrameWorkInterface::getFrameWork(QWidget* parent){
    return new QFraFrameWork(new QFrameWorkElementsFactory(),parent);
}



Q_EXPORT_PLUGIN2(pnp_graplugin, FraFrameWorkInterface)
