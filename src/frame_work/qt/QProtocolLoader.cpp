
#include "qt/QProtocolLoader.h"


#define MAX_PACKET_SIZE_BIT  (100)
#define PROTOCOL_HEADER_SIZE (2+2+1)
#define PROTOCOL_POSTFIX_SIZE (0)

struct msg_desc{
    msg_id_t id;
    const char* description;
    int len;
};

struct pack_desc{
    pack_id_t id;
    const msg_id_t *msg_arrea;
    int msg_num;
};

typedef struct msg_desc  msg_desc_t;
typedef struct pack_desc pack_desc_t;


enum{
#define GEN_MSG_ENUMS
#include"ProtoGen.h"

};


enum{
#define GEN_PKT_ENUMS
#include"ProtoGen.h"

};

const msg_desc_t msgs[]={
    #define GEN_MSGS
    #include"ProtoGen.h"
};

#define GEN_MSGS_PKT_MAPS
#include"ProtoGen.h"

const pack_desc_t packs[]={
    #define GEN_PKTS
    #include"ProtoGen.h"
};

#define PKT_NUM  (sizeof(packs)/sizeof(pack_desc_t))
#define MSGS_NUM (sizeof(msgs)/sizeof(msg_desc_t))

int QProtocolLoader::readProtocolData() {
    return NO_ERR;

}

int QProtocolLoader::getMsgCount() {
    return MSGS_NUM;
}

int QProtocolLoader::getMsgId(int number) {
    if( MSGS_NUM > number ){
        return msgs[ number ].id;
    }
    else{
        return MSG_ID_INVALID;
    }
}

int QProtocolLoader::getMaxPacketSize() {
    return MAX_PACKET_SIZE_BIT;
}

int QProtocolLoader::getPacketCount() {
    return PKT_NUM;
}

pack_id_t QProtocolLoader::getPackId(int number) {
    if( PKT_NUM > number ){
        return packs[number].id;
    }
    else{
        return PKT_ID_INVALID;
    }

}

int QProtocolLoader::getMsgsCountForPack(const pack_id_t packID) {
    int i;
    for( i=0; i < PKT_NUM ;i++ ){
        if( packs[i].id == packID ){
            return packs[i].msg_num;
        }
    }
    return 0;
}

msg_id_t QProtocolLoader::getMsgIdForPack(const pack_id_t packID, int idx) {
    int i;
    for( i=0; i < PKT_NUM ;i++ ){
        if( packs[i].id == packID ){
            if( packs[i].msg_num > idx ){
                return packs[i].msg_arrea[idx];
            }
            else{
                break;
            }
        }
    }
    return MSG_ID_INVALID;
}

int QProtocolLoader::getMsgIdLen(const msg_id_t id,int* len ) {
    int i;
    if( 0 != len ){
        for( i=0; i < MSGS_NUM ;i++ ){
            if( msgs[i].id == id ){
                msgs[i].len;
                return NO_ERR;
            }
        }
    }
    return WRONG_PARAMS;
}

int QProtocolLoader::getHeaderSize() {
    return PROTOCOL_HEADER_SIZE;
}

int QProtocolLoader::getPostFixSize() {
    return PROTOCOL_POSTFIX_SIZE;
}

