#include "generator.h"
#include "output_writer.h"
#include "data_manager.h"


generator::generator()
{

}

int generator::generateNodeData( data_manager * mng ,QString& NodeName, output_writer* writer )
{

    QMap< int, pack_types_t >  p_list;
    QMap< int, msg_types_t  >  msg_list;
    if( NULL != mng && NULL != writer )
    {
        mng->get_data( NodeName, p_list, msg_list );
        writer->generate_all( p_list, msg_list );
    }
    return 0;
}


