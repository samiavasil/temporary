#include "frameworkinterface.h"
#include "QFraFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"
frameworkinterface::frameworkinterface(QObject* parent ):QObject(parent)
{
    strcpy(nameto,"FrameWorkInterface");
}

frameworkinterface::~frameworkinterface(  )
{
    DEBUG("frameworkinterface object removed");
}

QFrameWork* frameworkinterface::getFrameWork(){
    return new QFraFrameWork(new QFrameWorkElementsFactory());
}



Q_EXPORT_PLUGIN2(pnp_graplugin, frameworkinterface)
