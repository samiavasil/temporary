#ifndef PLUGINDESCRIPTION_H
#define PLUGINDESCRIPTION_H

#include "base/global.h"
#include "interfaces.h"//FIX ME
#include<QString>
#include<QIcon>

class FRAME_WORKSHARED_EXPORT PluginDescription{
public:
   typedef enum{
     NOTHING_OPT       = 0,
     TYPE_OPT          = 1 << 0,
     LOCATION_OPT      = 1 << 1,
     NAME_OPT          = 1 << 2,
     CATEGORY_OPT      = 1 << 3,
     VERSION_OPT       = 1 << 4,
     DESCRIPTION_OPT   = 1 << 5,
     ICON_OPT          = 1 << 6,
     ENABLE_OPT        = 1 << 7
   }PlugDiff;

   PluginDescription(const PluginDescription& b);

   PluginDescription(   const InterfaceType_t&  Type       = UNDEFINED,
                        const QString&         Location    = QString(),
                        const QString&         Name        = QString(),
                        const QString&         Category    = QString(),
                        const QString&         Version     = QString(),
                        const QString&         Description = QString(),
                        QIcon                  Icon        = QIcon(),
                        int                    enabled     = -1
                     );

   ~PluginDescription();

   PluginDescription & operator=(const PluginDescription &b);

   bool  operator==(const PluginDescription &b) const;

   unsigned int compare( const PluginDescription &b ) const;

   bool         compare_by_valid_fields( const PluginDescription &b ) const;

   bool IsEmpty();

   InterfaceType_t type() const;
   const QString&  name() const;
   const QString&  category() const;
   const QString&  version() const;
   const QString&  description() const;
   const QString&  location() const;
   const QIcon     icon() const;
   bool            is_enabled() const;

   void            enable( bool enbl);

protected:
    InterfaceType_t  m_Type;
    QString          m_Name;
    QString          m_Location;
    QString          m_Category;
    QString          m_Version;
    QString          m_Description;
    QIcon            m_Icon;
    int              m_Enabled;
};

#endif // PLUGINDESCRIPTION_H
