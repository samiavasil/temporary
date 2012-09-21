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

QFrameWork* frameworkinterface::getFrameWork(QWidget* parent){
    return new QFraFrameWork(new QFrameWorkElementsFactory(),parent);
}



Q_EXPORT_PLUGIN2(pnp_graplugin, frameworkinterface)
