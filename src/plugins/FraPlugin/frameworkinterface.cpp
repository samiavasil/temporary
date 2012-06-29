#include "frameworkinterface.h"
#include "QFraFrameWork.h"
frameworkinterface::frameworkinterface(QObject* parent ):QObject(parent)
{
    strcpy(nameto,"FrameWorkInterface");
}

frameworkinterface::~frameworkinterface(  )
{
    qDebug("frameworkinterface object removed");
}

QFrameWork* frameworkinterface::getFrameWork(){
    return new QFraFrameWork();
}



Q_EXPORT_PLUGIN2(pnp_graplugin, frameworkinterface)
