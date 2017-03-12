/************************************************************************
                        Daqster/QBasePluginObject.cpp.cpp - Copyright vvasilev
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

#include "QBasePluginObject.h"

namespace Daqster {
// Constructors/Destructors
//  

QBasePluginObject::QBasePluginObject (QObject *Parent):QObject( Parent ) {
    m_InterfaceObject = NULL;
}

QBasePluginObject::~QBasePluginObject () {

}

}
