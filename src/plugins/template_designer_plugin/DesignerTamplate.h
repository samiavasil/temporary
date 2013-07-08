#ifndef DESIGNERTAMPLATE_H
#define DESIGNERTAMPLATE_H

#include<QListWidget>
#include <QtDesigner/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT DesignerTamplate:public QListWidget
{
    Q_OBJECT
public:
    DesignerTamplate(QWidget* parent=NULL);
public slots:
    void Dgd();
signals:
    void blaBla();
};


#endif // DESIGNERTAMPLATE_H
