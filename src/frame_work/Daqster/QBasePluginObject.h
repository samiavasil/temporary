/************************************************************************
                        Daqster/QBasePluginObject.h.h - Copyright vvasilev
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

#ifndef QBASEPLUGINOBJECT_H
#define QBASEPLUGINOBJECT_H
#include <QObject>

namespace Daqster {

class QPluginBaseInterface;
/**
  * class QBasePluginObject
  * 
  */

class QBasePluginObject : public QObject
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  QBasePluginObject (  QObject* Parent = NULL );

  /**
   * Empty Destructor
   */
  virtual ~QBasePluginObject ();

  // Static Public attributes
  //  

  // Public attributes
  //  


protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:

protected:

public:

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  // Pointer to plugin interface object
  const Daqster::QPluginBaseInterface* m_InterfaceObject;
public:

private:

public:



};
} // end of package namespace

#endif // QBASEPLUGINOBJECT_H
