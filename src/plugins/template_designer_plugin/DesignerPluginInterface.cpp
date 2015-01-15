#include "DesignerPluginInterface.h"
#include"DesignerTamplate.h"
 #include <QtPlugin>

DesignerTamplatePlugin::DesignerTamplatePlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void DesignerTamplatePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool DesignerTamplatePlugin::isInitialized() const
{
    return initialized;
}

QWidget *DesignerTamplatePlugin::createWidget(QWidget *parent)
{
    return new DesignerTamplate(parent);
}

QString DesignerTamplatePlugin::name() const
{
    return "DesignerTamplate";
}

QString DesignerTamplatePlugin::group() const
{
    return "Vasil Widgets [Examples]";
}

QIcon DesignerTamplatePlugin::icon() const
{
    return QIcon();
}

QString DesignerTamplatePlugin::toolTip() const
{
    return "";
}

QString DesignerTamplatePlugin::whatsThis() const
{
    return "";
}

bool DesignerTamplatePlugin::isContainer() const
{
    return false;
}

QString DesignerTamplatePlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"DesignerTamplate\" name=\"DesignerTamplate\">\n"
           "  <property name=\"sortingEnabled\">\n"
           "  <bool>true</bool>\n"
           "  </property>\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>111</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>The current time</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>The analog clock widget displays the current time.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString DesignerTamplatePlugin::includeFile() const
{
    return "DesignerTamplate.h";
}
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(DesignerTamplateExample, DesignerTamplatePlugin)
#endif
