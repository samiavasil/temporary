#include "generator.h"
#include "output_writer.h"
#include "data_manager.h"


generator::generator()
{

}

int generator::generateNodeData( data_manager * mng ,QString& NodeName, output_writer* writer )
{
    if( NULL != mng && NULL != writer )
    {
        QMap< int, pack_types_t >  p_list;
        QMap< int, msg_types_t  >  m_list;
        mng->get_data( NodeName, p_list, m_list );
        ComMatrix matrix(  p_list, m_list );
        writer->build_doc( matrix );
    }
    return 0;
}


