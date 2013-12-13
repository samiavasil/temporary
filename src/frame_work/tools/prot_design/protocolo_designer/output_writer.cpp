#include "output_writer.h"
#include<QDebug>
output_writer::output_writer()
{
}


int output_writer::generate_all( QMap< int, pack_types_t >& pack_list, QMap< int, msg_types_t  > & msg_list )
{
    qDebug() << "\n\n============================================================================================\n";
    qDebug() << "DUMP ALL NODE MESSAGES:\n";

    QList<int> mIDS = msg_list.keys();
    foreach( int id, mIDS )
    {
        msg_types_t  msg = msg_list[id];
           qDebug() << " \t\t" << "MsgName = " << msg.msgName << "ID: " << id << " Len = " << msg.BitLen << " Default = "<< msg.DefaultValue
                     << "Type= " << msg.Type << "Msg Description:" << msg.msgDescription <<"\n";
    }

    qDebug() << "\n\n============================================================================================\n";
    qDebug() << "DUMP ALL NODE PACKETS:\n";
    foreach( pack_types_t pack, pack_list ) {

        qDebug() << "Packet " << pack.packName << " :\n\t\tDescription: " << pack.packetDescription << "\n";
        qDebug() << " \t\tMessage List: \n";
        foreach( msg_pos mPOS, pack.mIDs )
        {
            msg_types_t msg = msg_list[mPOS.ID];
            qDebug() << " \t\t" << "MsgName = " << msg.msgName << "Position: " << mPOS.pos << " Len = " << msg.BitLen << " Default = "<< msg.DefaultValue
                     << "Type= " << msg.Type << "Msg Description:" << msg.msgDescription <<"\n";
        }
    }
    return 0;
}
