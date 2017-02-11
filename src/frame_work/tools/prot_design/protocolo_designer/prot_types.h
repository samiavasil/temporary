#ifndef PROT_TYPES_H
#define PROT_TYPES_H
#include<QString>
#include<QList>
#include<QMap>
#include<QPair>

typedef struct alabala{
    QString msgName;
    int     BitLen;
    int     DefaultValue;
    int     Type;
    QString msgDescription;
}msg_types_t;

typedef struct
{
    int ID;
    int pos;
}msg_pos;

typedef struct{
    QString packName;
    QString packetDescription;
    QList<msg_pos> mIDs;
}pack_types_t;

typedef struct{
    QMap< int, pack_types_t > pack_list;
    QMap< int, msg_types_t  > msg_list;
}matrix_type_t;

class ComMatrix{
    public:
    ComMatrix( QMap< int, pack_types_t > plist, QMap< int, msg_types_t  > mlist )
    {
        pack_list = plist;
        msg_list  = mlist;
    }

    bool  getPkgPairs( int PackId, QList< QPair<QString,QList<QString>> >& list ) const
    {

        QList<QString> mIDs;
        QList<QString> bitPositions;

        foreach( auto id, pack_list[PackId].mIDs ) {
            mIDs.append( QString("%1").arg( id.ID ) );
            bitPositions.append( QString("%1").arg(id.pos) );
        }
        list.append( qMakePair(QString("Msg ID"),mIDs) );
        list.append( qMakePair(QString("Position [bits]"),bitPositions) );
        return true;
    }

    bool  getMsgPairs( QList< QPair<QString,QList<QString>> >& list ) const
    {
        QList<QString> ID;
        QList<QString> msgName;
        QList<QString> BitLen;
        QList<QString> DefaultValue;
        QList<QString> Type;
        QList<QString> msgDescription;

        foreach( auto key, msg_list.keys() ) {
          ID.append( QString("%1").arg(key) );
          msgName.append( QString("%1").arg(msg_list[key].msgName) );
          BitLen.append( QString("%1").arg(msg_list[key].BitLen) );
          DefaultValue.append( QString("%1").arg(msg_list[key].DefaultValue) );
          Type.append( QString("%1").arg(msg_list[key].Type) );
          msgDescription.append( QString("%1").arg(msg_list[key].msgDescription) );
        }
        list.append( qMakePair(QString("ID"),ID) );
        list.append( qMakePair(QString("msgName"),msgName) );
        list.append( qMakePair(QString("BitLen"),BitLen) );
        list.append( qMakePair(QString("DefaultValue"),DefaultValue) );
        list.append( qMakePair(QString("Type"),Type) );
        list.append( qMakePair(QString("msgDescription"),msgDescription) );
        return true;
    }

    inline const QMap< int, pack_types_t >& packetsList() const
    {
        return pack_list;
    }

    inline const QMap< int, msg_types_t  >& msgList() const
    {
        return msg_list;
    }

private:
    QMap< int, pack_types_t > pack_list;
    QMap< int, msg_types_t  > msg_list;
};

#endif // PROT_TYPES_H
