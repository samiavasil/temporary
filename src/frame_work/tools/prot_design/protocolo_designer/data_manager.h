#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include"prot_types.h"

#include<QList>
#include<QMap>

class data_manager
{
public:
    virtual int get_data( QString& NodeName, QMap< int, pack_types_t >& p_list, QMap< int, msg_types_t  > & m_list ) = 0;

};

#endif // DATA_MANAGER_H
