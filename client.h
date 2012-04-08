
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
#include <sys/types.h>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include "manager.h"
#include "sha1.h"
#include <map>
#include "marshalling.h"
#include "timers/timers.hh"






//inst.DATA=new char[100];

using namespace std;

INSTRUCTION inst;
uint32_t TKCC;

uint32_t PREDECESSOR;
uint32_t PREDECESSOR_PORT;
uint32_t DOUBLE_SUCC;
uint32_t DOUBLE_SUCC_PORT;
 ofstream outfile_client;


 map<int,char*> ID_to_MESSAGE;
 map<int,char*>::iterator IT;


  map<uint32_t,char*> DATA_STORE;

  map<uint32_t,char*>::iterator iterate;

   char search1_data[100];
   uint32_t search1_node;

   int global_search_counter;

 char NONCE[MAXDATASIZE], buf[MAXDATASIZE], CLIENT_NAME[MAXDATASIZE], FP[MAXDATASIZE],FS[MAXDATASIZE];

 Neighbours SUC, PRE;
 uint32_t MY_TOKEN;

 uint32_t nonce_name_hash(uint32_t nonce, char *name);
 void position_in_ring(void);
 void intitalize_msgs(void);
 void create_main_udp_port();
 void create_hello_udp_port();
 void create_lazy_udp_port();

 void position_in_ring_FT();

 void store_func(uint32_t data_hash);
 void search_func(uint32_t data_hash);


 int UDP_private;
 int UDP_hello;
 int sockfd_client;
 string STAGE;
 int DGRAM_PORT;
 int HELLO_PORT;
 int LAZY_PORT;
 int UDP_lazy;
 uint32_t SEARCH_DONE;

finger_table FT[33];






/*
* test-app.hh    : Test App Include File
* author         : Fabio Silva and Chalermek Intanagonwiwat
*
* Copyright (C) 2000-2001 by the Unversity of Southern California
* $Id: test-app.hh 2163 2007-02-02 23:39:15Z johnh $
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
*
*/



#include "timers/timers.hh"

class TestApp;

/* In TestTimer1 and TestTimer2, we are using a varible count_ to demonstrate
 * the how to associate variable in the event queue.
 * count_ can be replace by any other type of varible/structure
 * ex: a LSA structure
 */
class TestTimer1: public TimerCallback {
public:

        ~TestTimer1() {};

	int Expire();
};

class TestApp{
public:
	TestApp();
	void start();
	void recv_tcp();
protected:
	Timers *timersManager_;
};

