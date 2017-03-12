/************************************************************************
                        Daqster/QPluginBaseInterface.h - Copyright vvasilev
Daqster software
Copyright (C) 2016, Vasil Vasilev,  Bulgaria

This file is part of Daqster and its software development toolkit.

Daqster is a free software; you can redistribute it and/or modify it
under the terms of the GNU Library General Public Licence as published by
the Free Software Foundation; either version 2 of the Licence, or (at
your option) any later version.

Daqster is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library
General Public Licence for more details.

Initial version of this file was created on нд март 12 2017 at 20:54:50
**************************************************************************/


#ifndef QPLUGINBASESINTERFACE_H
#define QPLUGINBASESINTERFACE_H
#include <QObject>
#include <QIcon>
#include <QString>
#include<QSharedPointer>
#include<QDebug>
#include "base/global.h"
namespace Daqster {

typedef enum{
    SOME_TYME
} PluginType_t;

class QPluginLoader;
class QBasePluginObject;

/**
  * class QPluginBaseInterface
  * 
  */

class FRAME_WORKSHARED_EXPORT QPluginBaseInterface : public QObject
{
    Q_OBJECT
public:

  /**
   * Empty Constructor
   * @param  parent
   */
   QPluginBaseInterface (QObject* Parent = NULL );

  /**
   * Empty Destructor
   */
  virtual ~QPluginBaseInterface ();

  /**
   * Return plugin basic type. If this isn't set to some type you can check typeName
   * string and try to detect type from name.
   * @return Daqster::PluginType_t
   */
  Daqster::PluginType_t getType ();

  /**
   * Return plugin embeded icon.
   * @return const QIcon
   */
  const QIcon getIcon ();


  /**
   * Return plugin name
   * @return const QString
   */
  const QString getName ();


  /**
   * Get plugin type name
   * @return const QString
   */
  const QString getTypeName ();


  /**
   * Get plugin version
   */
  QString getVersion();


  /**
   * Get plugin description
   * @return const QString
   */
  const QString getDescription ();


  /**
   * Get plugin detail description.
   * @return const QString
   */
  const QString getDetailDescription ();


  /**
   * Get plugin license
   * @return const QString
   */
  const QString getLicense ();


  /**
   * Return plugin author
   * @return const QString
   */
  const QString getAuthor ();


  /**
   * Set new plugin loader.
   * When the plugin is loaded on first time we create QPluginLoader and its method
   * instance() returns QPluginBaseInterface*  plugInterface. On this point
   * plugInterface->setPluginLoader() function is called to set pointer to
   * QPluginLoader.
   * @param  Loader New plugin loader
   */
  void setPluginLoader(QSharedPointer<QPluginLoader> &Loader );


  /**
   * Create  new plugin object.
   * @return Daqster::QBasePluginObject*
   * @param  Pointer to parent QObject
   */
  virtual Daqster::QBasePluginObject* createPlugin (QObject* Parrent = NULL);

 protected:
  /**
   * Abstract function wich create  new plugin object.
   * @return Daqster::QBasePluginObject*
   * @param  Parrent Pointer to parent QObject
   */
  virtual Daqster::QBasePluginObject* createPluginInternal(QObject* Parrent = NULL) = 0;

protected:
  // Plugin Embeded Icon
  QIcon m_Icon;
  // Plugin name
  QString m_Name;
  // Plugin type
  Daqster::PluginType_t m_PluginType;
  // Plugin Type Name
  QString m_PluginTypeName;
  // Plugin Version
  QString m_Version;
  // Plugin Description
  QString m_Description;
  // Plugin detailed description 
  QString m_DetailDescription;
  // Plugin License
  QString m_License;
  // Plugin Author
  QString m_Author;
  // Plugin loader
  QSharedPointer<QPluginLoader> m_PluginLoader;
  // List  with currently instantiated plugins
  QList<Daqster::QBasePluginObject *> m_PluginInstList;
};
} // end of package namespace



/*Next declarations insired fom itom project :)*/
#define CREATE_PLUGIN_INTERFACE_VERSION_STR(major,minor,patch) "Daqster.PlugIn.BaseInterface/"#major"."#minor"."#patch
#define CREATE_PLUGIN_INTERFACE_VERSION(major,minor,patch) ((major<<16)|(minor<<8)|(patch))

#define DAQSTER_PLUGIN_INTERFACE_MAJOR 0
#define DAQSTER_PLUGIN_INTERFACE_MINOR 0
#define DAQSTER_PLUGIN_INTERFACE_PATCH 0
#define DAQSTER_PLUGIN_INTERFACE_VERSION CREATE_PLUGIN_INTERFACE_VERSION(DAQSTER_PLUGIN_INTERFACE_MAJOR,DAQSTER_PLUGIN_INTERFACE_MINOR,DAQSTER_PLUGIN_INTERFACE_PATCH)
//###########################################################################################################
//   Interface version:
//###########################################################################################################
//
//
// Please change the interface version, if you made any changes to this interface, files located in the common folder or to the dataObject.
//
// To add a new version, do the following steps
//
// 1. append the string behind the variable daqster_PluginInterface_CurrentVersion (e.g. CREATE_PLUGIN_INTERFACE_VERSION_STR(0,0,0)) to the array daqster_PluginInterface_OldVersions
// 2. change the version number in the string daqster_PluginInterface_CurrentVersion (e.g. CREATE_PLUGIN_INTERFACE_VERSION_STR(0,0,1))
// TODO: DELL ME 3. if the QPluginBaseInterface version number is incremented, the ito.AbstractItomDesignerPlugin number in AbstractItomDesignerPlugin.h must be incremented as well.
//
//
// This helps, that deprecated or "future" plugins, which fit not to the current implementation of the interface will not be loaded
// but a sophisticated error message is shown.

static const char* daqster_PluginObjectInterface_OldVersions[] = {
     CREATE_PLUGIN_INTERFACE_VERSION_STR(-1,-1,-1),//version TODO: DELL ME not real version in moment
     NULL
};
static const char* daqster_PluginInterface_CurrentVersion = DAQSTER_PLUGIN_INTERFACE_VERSION; //results in "Daqster.PlugIn.BaseInterface/x.x.x";
// must be out of namespace
Q_DECLARE_INTERFACE(Daqster::QPluginBaseInterface , daqster_PluginInterface_CurrentVersion )
#endif // QPLUGINBASESINTERFACE_H
