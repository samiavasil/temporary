#include "PluginDescription.h"
#include "qt/QPluginDescriptor.h"


PluginDescription::PluginDescription(  InterfaceType_t Type,
                                       QString          Location,
                                       QString          Name ,
                                       QString          Category,
                                       QString          Version,
                                       QString          Description,
                                       QIcon            Icon
                                    )
{
    m_Type        =  Type;
    m_Name        =  Name;
    m_Location    =  Location;
    m_Category    =  Category;
    m_Version     =  Version;
    m_Description =  Description;
    m_Icon        =  Icon;
}

PluginDescription::PluginDescription(const PluginDescription& b)
{
    *this = b;
}

PluginDescription::~PluginDescription(){

}

bool  PluginDescription::operator==(const QPluginDescriptor &b)
{
    return ( *this == b.getDescription() );
}

PluginDescription & PluginDescription::operator=(const PluginDescription &b){
     m_Type        = b.m_Type       ;
     m_Name        = b.m_Name       ;
     m_Location    = b.m_Location   ;
     m_Category    = b.m_Category   ;
     m_Version     = b.m_Version    ;
     m_Description = b.m_Description;
     m_Icon        = b.m_Icon       ;

     return *this;
 }

bool  PluginDescription::operator==(const PluginDescription &b){

return(
       ( m_Type == b.m_Type )&&
       (!(
         m_Name.compare(  b.m_Name )||
         m_Location.compare(  b.m_Location )||
         m_Category.compare(  b.m_Category )||
         m_Version.compare(  b.m_Version )||
         m_Description.compare(  b.m_Description )
       ))
      );
}

InterfaceType_t  PluginDescription::type() const{
    return   m_Type;
}

const QString&  PluginDescription::name() const{
    return   m_Name;
}

const QString&  PluginDescription::category() const{
    return   m_Category;
}

const QString&  PluginDescription::version() const{
    return   m_Version;
}

const QString&  PluginDescription::description() const{
    return   m_Description;
}

const QString&  PluginDescription::location() const{
    return m_Location;
}

const QIcon  PluginDescription::icon() const{
    return   m_Icon;
}
