#ifndef DATAPLOTINTERFACE_H
#define DATAPLOTINTERFACE_H

#include <QDesignerCustomWidgetInterface>

class DesignerTamplatePlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "DesignerTamplatePlugin.json")
#endif
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    DesignerTamplatePlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool initialized;
};

#endif // DATAPLOTINTERFACE_H
