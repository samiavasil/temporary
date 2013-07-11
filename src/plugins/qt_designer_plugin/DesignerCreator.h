#ifndef DESIGNERCREATOR_H
#define DESIGNERCREATOR_H

#include "plugin_global.h"
#include"qt/QCreator.h"

class CFrameWork;
namespace qdesigner_internal {
    class QDesignerIntegration;
}
namespace Plugins
{
class PLUGIN_EXPORT DesignerCreator:  public QCreator
{
    Q_OBJECT
public:
    explicit DesignerCreator( QObject * parent = NULL );
    ~DesignerCreator( );
    virtual bool Create(CFrameWork *fW);
public slots:
    virtual void Free();

private:
       qdesigner_internal::QDesignerIntegration * _designer;

};
}
#endif // DESIGNERCREATOR_H
