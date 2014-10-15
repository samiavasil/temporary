#include "CProtocolDb.h"
#include "base/CProtocolLoader.h"
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"


int CProtocolDb::getProtocolHeaderLenBits() const {
    return m_hDrLenBits;
}

void CProtocolDb::setProtocolHeaderLenBits(int lenBits) {
    m_hDrLenBits = lenBits;
}

int CProtocolDb::getProtocolPostFixLenBits() const {
    return m_postFixLenBits;
}

void CProtocolDb::setProtocolPostFixLenBits(int lenBits) {
    m_postFixLenBits = lenBits;
}

int CProtocolDb::getMaxPacketLen() {
    return m_maxPacketSize;
}

void CProtocolDb::setMaxPacketLen(int max_size) {
    m_maxPacketSize = max_size;
}

int CProtocolDb::loadProtocolDefinition(CProtocolLoader & protLd ) {
    int errCode = SOME_ERROR;
    int MsgCount  = 0;
    int PackCount = 0;
    pack_id_t packID;
    msg_id_t  msgID;
    int msgLen;
    int i,j;
    clearProtDefinitions();
    errCode = protLd.readProtocolData();
    if( NO_ERR  == errCode ){

        int max_pack_size = protLd.getMaxPacketSize( );
        if( 0 < max_pack_size ){
            setMaxPacketLen( max_pack_size );
        }
        else{
            errCode = WRONG_DATA;
            CRITICAL << "Error[" << errCode << "]: Can't read packet size";
            return errCode;
        }
        int lenBits = protLd.getHeaderLenBits();
        if( 0 < lenBits ){
            setProtocolHeaderLenBits( lenBits );
        }
        else{
            errCode = WRONG_DATA;
            CRITICAL << "Error[" << errCode << "]: Can't read packet header size";
            return errCode;
        }
        lenBits = protLd.getPostFixLenBits();
        if( 0 <= lenBits ){
            setProtocolPostFixLenBits( lenBits );
        }
        else{
            errCode = WRONG_DATA;
            CRITICAL << "Error[" << errCode << "]: Can't read packet post fix size";
            return errCode;
        }
        MsgCount = protLd.getMsgCount();
        for( i=0; i < MsgCount;i++ ){
            msgID  = protLd.getMsgId(i);
            if(  MSG_ID_INVALID != msgID ){
                errCode = protLd.getMsgIdLen(msgID,&msgLen);
                if( NO_ERR == errCode ){
                    errCode =  addMessage( msgID, msgLen );
                    if( NO_ERR != errCode ){
                        CRITICAL << "Error[" << errCode << "]:Can't add message ID[" << msgID << "]";
                        return errCode;
                    }
                }
                else{
                    CRITICAL << "Error[" << errCode << "]:Can't get Len for message ID[" << msgID << "]";
                    return errCode;
                }
            }
            else{
                /*TODO Someting*/
                errCode = WRONG_DATA;
                CRITICAL << "TODO: " << __func__ << " : MSG_ID_INVALID";
                return errCode;
            }
        }
        PackCount = protLd.getPacketCount();

        for( i=0; i < PackCount;i++ ){
            packID = protLd.getPackId(i);
            if( PKT_ID_INVALID != packID ){
                errCode =  addPacket( packID );
                if( NO_ERR != errCode ){
                    CRITICAL << "Error[" << errCode << "]:Can't add packet ID[" << packID << "]";
                    return errCode;
                }

                MsgCount = protLd.getMsgsCountForPack( packID );
                if( ( 0 < MsgCount )&&( max_pack_size > MsgCount ) ){
                    for( j = 0; j < MsgCount; j++ ){
                        msgID = protLd.getMsgIdForPack( packID, j );
                        if( MSG_ID_INVALID != msgID ){
                            errCode =  addMessageToPacket( packID, msgID );
                            if( NO_ERR != errCode ){
                                CRITICAL << "Error[" << errCode << "]:Invalid Message ID[" << msgID << "]";
                                return errCode;
                            }
                        }
                        else{
                            CRITICAL <<  "Error[" << errCode << "]:Invalid Message ID["<< msgID
                                      <<  "] for pack ID[" << packID << "]";
                        }
                    }
                }
                else{
                    /*TODO Someting*/
                    if( 0 >= MsgCount ){
                        CRITICAL << "TODO: " << __func__ << " : Packet without messages";
                    }
                    else{
                        CRITICAL << "TODO: " << __func__ << " : Max messages in packet limit is exceeded";
                    }
                }
            }
        }
    }

    return errCode;
}

