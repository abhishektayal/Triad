/*
 * marshalling.h
 *
 *  Created on: Oct 20, 2011
 *      Author: Abhi
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include "manager.h"
#include "sha1.h"
#include <map>
#include "timers/timers.hh"
#include <cmath>
//#include "FTmarshalling.h"

#define SUCCESSOR FT[1].NODE_TOKEN
#define SUCCESSOR_port FT[1].udp_port
extern uint32_t DOUBLE_SUCC;
extern uint32_t DOUBLE_SUCC_PORT;
extern uint32_t PREDECESSOR;
extern uint32_t PREDECESSOR_PORT;

extern uint32_t TKCC;
extern uint32_t SEARCH_DONE;

extern char search1_data[100];
extern uint32_t search1_node;

extern int global_search_counter;


#define MAXDATASIZE 100

typedef struct NODE_DETAILS
{
	uint32_t node_token;
	uint32_t node_port;
}details;

//string STAGE;
using namespace std;

extern ofstream outfile_client;


extern map<int,char*> ID_to_MESSAGE;
extern map<int,char*>::iterator IT;



extern map<uint32_t,char*> DATA_STORE;
extern map<uint32_t,char*>::iterator iterate;


extern char NONCE[MAXDATASIZE], buf[MAXDATASIZE], CLIENT_NAME[MAXDATASIZE], FP[MAXDATASIZE],FS[MAXDATASIZE];

extern struct Neighbours
{
	uint32_t token;
	uint32_t UDP_port;
}SUC,PRE;

extern uint32_t MY_TOKEN;
extern uint32_t nonce_name_hash(uint32_t nonce, char *name);
extern void position_in_ring(void);
extern void intitalize_msgs(void);
extern void send_ok_manager(void);
extern int msg_to_id(char *msg);
extern details verify_FT(uint32_t,uint32_t,uint32_t);
 void lazy_update_ft(uint32_t,uint32_t,uint32_t);

extern int LAZY_PORT;
extern int UDP_lazy;
extern int UDP_private;
extern int UDP_hello;
extern int sockfd_client;
extern int DGRAM_PORT;
extern int HELLO_PORT;

	class MARSHALLING_UDP
{

public:
	 struct DATA
	{
		uint32_t token;  // the hash id of the node to which packet should be sent
		uint32_t id1;
		uint32_t id2;
		uint32_t id3;
		uint32_t id4;
		uint32_t id5;
		char d1[100];    // data:


	}data;

	struct DATA_RECV
		{
			uint32_t token;  // the hash id of the node to which packet should be sent
			uint32_t id1;
			uint32_t id2;
			uint32_t id3;
			uint32_t id4;
			uint32_t id5;
			char d1[100];    // data:


		}data_recv;


	void SEND(char *msg_name, int dest_port,int d_h_l);
	int RECEIVE(int RECV_SOCK);
	char* CODE(char* msg);
	void DECODE(char* msg, int send_to,int RECV_SOCK);


};



extern struct INSTRUCTION
{
	char* instruction;
	char* DATA;
}inst;

//extern char* instruction;
//extern char* DATA;
//extern char* DATA=new char[100];
//extern char* instruction=new char[100];


//char* inst.instruction=new char[100];



extern map < uint32_t,char*> DATA_STORE_FT;
extern map < uint32_t,char*>::iterator iterate;




extern struct finger_table
{
	uint32_t INTERVAL_START_including;
	uint32_t INTERVAL_END;
	uint32_t NODE_TOKEN;
	uint32_t udp_port;
}ft;              //// 33 because we will count from index 1 and go to 32 = total 32 entries  ...0 unused

extern finger_table FT[33];
extern void position_in_ring_FT();
extern details find_successor(uint32_t id);
extern details find_predecessor(uint32_t id);
extern details closest_preceding_finger(uint32_t id);
extern void initialize_fingertable(void);
extern int LIES_BW(uint32_t, uint32_t,uint32_t, char*);
details FIND_NODE_SUCC(uint32_t, int );
extern void populate_fingertable(void);
extern void update_q_FT(uint32_t,uint32_t,uint32_t,uint32_t,int);
extern void update_others();
extern uint32_t calculate_mod(int64_t, int,int);
extern uint32_t calculate(int64_t x,int64_t y , int flag);
extern details scan_FT(uint32_t);
extern void stores_q_ft(uint32_t,uint32_t,int,int);





extern void find_double_succ();







