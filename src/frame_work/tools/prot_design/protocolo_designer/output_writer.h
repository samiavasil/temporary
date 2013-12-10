#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H
#include<QList>
#include<QMap>

#include"prot_types.h"


class output_writer
{
public:
    output_writer();
    //int generate_messages( QList<msg_types_t>& msg_list );
    int generate_all( QMap< int, pack_types_t >& pack_list, QMap< int, msg_types_t  > & msg_list );

protected:
//    virtual int generate_message( msg_types_t msg ) = 0;
//    virtual int generate_packet( pack_types_t,  QMap< int, msg_types_t  > & msg_list ) = 0;
};

#endif // OUTPUT_WRITER_H
