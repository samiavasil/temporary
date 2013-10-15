#ifndef DESIGNERCREATOR_H
#define DESIGNERCREATOR_H


#include"qt/QCreator.h"

class CFrameWork;
namespace qdesigner_internal {
    class QDesignerIntegration;
}

namespace Ui {
class Designer;
}


class QDesignerFormWindowInterface;

class  DesignerCreator:  public QCreator
{
    Q_OBJECT
public:
    explicit DesignerCreator( QObject * parent = NULL );
    virtual ~DesignerCreator( );
    virtual bool Create(CFrameWork *fW);
protected:
    QWidget* loadUiFile(QWidget *parent, QString &file_name);
public slots:
    virtual void Free();
    virtual void save();
private:
       qdesigner_internal::QDesignerIntegration * _designer;
       QObject * _menu;
       QDesignerFormWindowInterface*  form;
       Ui::Designer   *ui;
};

#endif // DESIGNERCREATOR_H
