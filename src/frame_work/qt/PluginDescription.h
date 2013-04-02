#ifndef PLUGINDESCRIPTION_H
#define PLUGINDESCRIPTION_H

#include "base/global.h"
#include "interfaces.h"//FIX ME
#include<QString>
#include<QIcon>

class QPluginDescriptor;

class PluginDescription{
public:
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

   bool operator==(const QPluginDescriptor &b);

   PluginDescription & operator=(const PluginDescription &b);

   bool  operator==(const PluginDescription &b);

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
