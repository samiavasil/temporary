#ifndef PLUGINDESCRIPTION_H
#define PLUGINDESCRIPTION_H

#include "base/global.h"
#include "interfaces.h"//FIX ME
#include<QString>
#include<QIcon>

class PluginDescription{
public:
   typedef enum{
     THE_SAME     = 0x0,
     TYPE_DIFF    = 0x1,
     NAME_DIFF    = 0x2,
     VERS_DIFF    = 0x4,
     LOC_DIFF     = 0x8,
     DESC_DIFF    = 0x10,
     ICON_DIFF    = 0x11
   }PlugDiff;

   PluginDescription(const PluginDescription& b);

   PluginDescription(  InterfaceType_t  Type        = UNDEFINED,
                        QString          Location    = "",
                        QString          Name        = "" ,
                        QString          Category    = "",
                        QString          Version     = "",
                        QString          Description = "",
                        QIcon            Icon        = QIcon()
                     );

   ~PluginDescription();

   PluginDescription & operator=(const PluginDescription &b);

   bool  operator==(const PluginDescription &b) const;

   PluginDescription::PlugDiff  compare( const PluginDescription &b ) const;

   InterfaceType_t type() const;
   const QString&  name() const;
   const QString&  category() const;
   const QString&  version() const;
   const QString&  description() const;
   const QString&  location() const;
   const QIcon     icon() const;

protected:
    InterfaceType_t  m_Type;
    QString          m_Name;
    QString          m_Location;
    QString          m_Category;
    QString          m_Version;
    QString          m_Description;
    QIcon            m_Icon;
};

#endif // PLUGINDESCRIPTION_H
