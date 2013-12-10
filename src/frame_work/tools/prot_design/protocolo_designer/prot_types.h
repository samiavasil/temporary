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


typedef struct{
    QString packName;
    QString packetDescription;
    QList<int> mIDs;
}pack_types_t;


#endif // PROT_TYPES_H
