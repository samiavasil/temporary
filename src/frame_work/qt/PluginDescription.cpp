#include "PluginDescription.h"


PluginDescription::PluginDescription(  const InterfaceType_t &Type,
                                       const QString &Location,
                                       const QString &Name ,
                                       const QString &Category,
                                       const QString &Version,
                                       const QString &Description,
                                       QIcon            Icon,
                                       int enabled
                                    )
{
    m_Type        =  Type;
    m_Location    =  Location;
    m_Name        =  Name;
    m_Category    =  Category;
    m_Version     =  Version;
    m_Description =  Description;
    m_Icon        =  Icon;
    m_Enabled     =  enabled;
}

PluginDescription::PluginDescription(const PluginDescription& b)
{
    *this = b;
}

PluginDescription::~PluginDescription(){

}

bool  PluginDescription::IsEmpty()
{
    return ( *this == PluginDescription() );
}

/*Return vaue with PlugDiff bitmask */
unsigned int  PluginDescription::compare( const PluginDescription &b ) const{
    unsigned int diff = THE_SAME;
    if(  m_Type != b.m_Type ){
        diff |= TYPE_DIFF;
    }
    if( m_Location.compare(  b.m_Location ) ){
        diff |= LOC_DIFF;
    }
    if( m_Name.compare(  b.m_Name ) ){
        diff |= NAME_DIFF;
    }
    if( m_Category.compare(  b.m_Category ) ){
        diff |= CATEGORY_DIFF;
    }
    if( m_Version.compare(  b.m_Version ) ){
        diff |= VERS_DIFF;
    }
    if( m_Description.compare(  b.m_Description ) ){
        diff |= DESC_DIFF;
    }
    if( m_Icon.name().compare( b.m_Icon.name() ) ){
        diff |= ICON_DIFF;
    }
    if( m_Enabled !=  b.m_Enabled ){
        diff |= ENABLE_DIFF;
    }
    return diff;
}

/*
   Compare field if the field isn't empty object
*/
bool  PluginDescription::compare_by_valid_fields( const PluginDescription &b ) const{
    bool ret = true;
    if(  m_Type != UNDEFINED && m_Type != b.m_Type ){
        ret = false;
    }else if( !m_Location.isEmpty() && m_Location.compare(  b.m_Location ) ){
        ret = false;
    }else if( !m_Name.isEmpty() && m_Name.compare(  b.m_Name ) ){
        ret = false;
    }else if( !m_Category.isEmpty() && m_Category.compare(  b.m_Category ) ){
        ret = false;
    }else if( !m_Version.isEmpty() && m_Version.compare(  b.m_Version ) ){
        ret = false;
    }else if( !m_Description.isEmpty() && m_Description.compare(  b.m_Description ) ){
        ret = false;
    }else if( m_Icon.isNull() && m_Icon.name().compare( b.m_Icon.name() ) ){
        ret = false;
    }else if( ( m_Enabled != -1 ) && ( m_Enabled != b.m_Enabled ) ){
        ret = false;
    }
    return ret;
}

PluginDescription & PluginDescription::operator=(const PluginDescription &b){
     m_Type        = b.m_Type       ;
     m_Location    = b.m_Location   ;
     m_Name        = b.m_Name       ;
     m_Category    = b.m_Category   ;
     m_Version     = b.m_Version    ;
     m_Description = b.m_Description;
     m_Icon        = b.m_Icon       ;
     m_Enabled     = b.m_Enabled;
     return *this;
 }

bool  PluginDescription::operator==(const PluginDescription &b) const{

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

bool  PluginDescription::is_enabled() const{
    return ( m_Enabled > 0 );
}

void  PluginDescription::enable( bool enbl){
    m_Enabled = enbl;
}
