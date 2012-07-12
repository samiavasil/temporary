
#include "base/CProtocolPackFactory.h"
#include "base/CProtocolLoader.h"
#include "base/CPacket.h"

CProtocolPackFactory::CProtocolPackFactory(CProtocolLoader * pLoader) {
  if(  pLoader ) {
      pLoader->loadProtocolDefinition(this);
  }
}

int CProtocolPackFactory::clearMsgDefinitions() {
}

int CProtocolPackFactory::clearProtDeinfitions() {
}

int CProtocolPackFactory::addPacket(const pack_id_t & id) {
}

int CProtocolPackFactory::addMessage(const msg_id_t & id) {
}

int CProtocolPackFactory::addMessageToPacket(const pack_id_t & packID, const msg_id_t & msgID) {
}

int CProtocolPackFactory::addPacketHeader() {
}

int CProtocolPackFactory::addPacketPostFix() {
}

int CProtocolPackFactory::createPacket() {
}

int CProtocolPackFactory::createPacketFromData() {
}

int CProtocolPackFactory::findPacketStart() {
}

int CProtocolPackFactory::getMaxPacketSize() {
}

int CProtocolPackFactory::getPacketLen() {
}

int CProtocolPackFactory::getPacketType() {
}

int CProtocolPackFactory::getProtocolHeaderSize() {
}

int CProtocolPackFactory::setProtocolHeaderSize() {
}

int CProtocolPackFactory::getProtocolPostFixLen() {
}

int CProtocolPackFactory::setProtolPostFixLen() {
}

int CProtocolPackFactory::setMaxPacketSize(int max_size) {
}

int CProtocolPackFactory::setMessage() {
}

