/*TODO:
  This file should be moved from frame_work to target app.
  According this there should be updated and QProtocolLoader.
  This is only particlar example for MSG and PACKETS MAPING
*/
#ifdef GEN_MSG_ENUMS
#define ADD_MESSAGE(a,b,c,d)   a = b,
#define PACKET_DESC(a,b)
#define PACKET_DESC_END()
#define ADD_MESSAGE_TO_PACKET(a)
#endif
#ifdef  GEN_PKT_ENUMS
#define ADD_MESSAGE(a,b,c,d)
#define PACKET_DESC(a,b)       a = b,
#define PACKET_DESC_END()
#define ADD_MESSAGE_TO_PACKET(a)
#endif
#ifdef  GEN_MSGS
#define ADD_MESSAGE(a,b,c,d)   {a,c,d},
#define PACKET_DESC(a,b)
#define PACKET_DESC_END()
#define ADD_MESSAGE_TO_PACKET(a)
#endif
#ifdef GEN_MSGS_PKT_MAPS
#define ADD_MESSAGE(a,b,c,d)
#define PACKET_DESC(a,b)           msg_id_t arrea##a[]={
#define PACKET_DESC_END()          };
#define ADD_MESSAGE_TO_PACKET(a)   ((msg_id_t)a),
#endif

#ifdef GEN_PKTS
#define ADD_MESSAGE(a,b,c,d)
#define PACKET_DESC(a,b)        {a,arrea##a,(sizeof(arrea##a)/sizeof(msg_id_t))},
#define PACKET_DESC_END()
#define ADD_MESSAGE_TO_PACKET(a)
#endif

ADD_MESSAGE( MSG1_ID,10,"MSG1 descriptor",6  )
ADD_MESSAGE( MSG2_ID,11,"MSG2 descriptor",7  )
ADD_MESSAGE( MSG3_ID,12,"MSG3 descriptor",11 )
ADD_MESSAGE( MSG4_ID,13,"MSG4 descriptor",4  )
ADD_MESSAGE( MSG5_ID,14,"MSG5 descriptor",12 )
ADD_MESSAGE( MSG6_ID,15,"MSG6 descriptor",9  )
ADD_MESSAGE( MSG7_ID,16,"MSG7 descriptor",4  )
ADD_MESSAGE( MSG8_ID,17,"MSG8 descriptor",5  )

PACKET_DESC(PACK1_ID,2)
ADD_MESSAGE_TO_PACKET(MSG4_ID)
ADD_MESSAGE_TO_PACKET(MSG2_ID)
ADD_MESSAGE_TO_PACKET(MSG3_ID)
ADD_MESSAGE_TO_PACKET(MSG1_ID)
PACKET_DESC_END()
PACKET_DESC(PACK2_ID,3)
ADD_MESSAGE_TO_PACKET(MSG6_ID)
PACKET_DESC_END()
PACKET_DESC(PACK3_ID,4)
ADD_MESSAGE_TO_PACKET(MSG7_ID)
ADD_MESSAGE_TO_PACKET(MSG8_ID)
PACKET_DESC_END()
PACKET_DESC(PACK4_ID,5)
ADD_MESSAGE_TO_PACKET(MSG5_ID)
PACKET_DESC_END()

#undef ADD_MESSAGE
#undef PACKET_DESC
#undef PACKET_DESC_END
#undef ADD_MESSAGE_TO_PACKET
#undef GEN_MSG_ENUMS
#undef GEN_PKT_ENUMS
#undef GEN_MSGS_PKT_MAPS
#undef GEN_MSGS
#undef GEN_PKTS
