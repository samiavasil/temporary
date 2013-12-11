#ifndef PROT_TYPES_H
#define PROT_TYPES_H
#include<QString>
#include<QList>

typedef struct{
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


#endif // PROT_TYPES_H
