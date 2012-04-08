



#include "client.h"
//#include "marshalling.h"
//#include "FTmarshalling.h"




void fork_clients(int client_NUM, uint32_t tkcc)
{

TKCC=tkcc;

intitalize_msgs();
//cout<< "total clients are:"<<client_NUM<<endl;
	for (int i=0; i<client_NUM; i++)
	{
			 int pid= fork();

			if (pid==-1)
			{
				cout<< "not able to fork\n";
			}

			else if (pid==0)
			{

				//pid_t pid_child= getpid();
				//cout <<" in child" << i <<"  pid is "<< pid_child<<"\n";

///////////////////////////////////////////////////////////////////
// get the PORT to connect on through shared memory and populate struct to
	//talk to manager through TCP on: address_client, sockfd_client
///////////////////////////////////////////////////////////////////


				int numbytes_client;
				struct sockaddr_in address_client;
				int  addresslen_client = sizeof(address_client);

				address_client.sin_family = AF_INET;
				address_client.sin_port = PORT;
				address_client.sin_addr.s_addr = INADDR_ANY;
				if ((sockfd_client = socket(AF_INET,SOCK_STREAM,0)) == -1)
				{
					perror("client: socket");
				}
				if (connect(sockfd_client, (struct sockaddr*)&address_client, addresslen_client) == -1)
				{
					close(sockfd_client);
					perror("client: connect");
				}

///////////////////////////////////////////////////////////////////
				//starting to recieve boot info from manager
///////////////////////////////////////////////////////////////////
				getsockname(sockfd_client,(struct sockaddr *)&address_client, (socklen_t*)&addresslen_client);

				// receiving the nonce from manager
				if ((numbytes_client = recv(sockfd_client, NONCE, sizeof NONCE, 0)) == -1)
				{
					perror("recv_NONCE");
					exit(1);
				}
				NONCE[numbytes_client] = '\0';
				//outfile_client<<"received nonce:"<<NONCE<<endl;

				// receiving the client name from manager
				if ((numbytes_client = recv(sockfd_client, CLIENT_NAME, sizeof CLIENT_NAME, 0)) == -1)
				{
					perror("recv_NAME");
					exit(1);
				}
				CLIENT_NAME[numbytes_client] = '\0';
				char client_name[100];
				strcpy(client_name,CLIENT_NAME);
				 MY_TOKEN=nonce_name_hash(uint32_t(htonl(atoi(NONCE))), client_name);
				//c<<"hash is ------------"<<hex<<MY_TOKEN<<endl;

				string file_name= "stage"+STAGE+"."+(string)CLIENT_NAME+".out";
				outfile_client.open(str_to_char(file_name));

				outfile_client<<"client "<<CLIENT_NAME<<" created with hash "<<hex<<MY_TOKEN<<endl;
				//outfile_client<<"received the host name from manager:"<<CLIENT_NAME<<endl;


				// receiving the FP from manager
				if ((numbytes_client = recv(sockfd_client, FP, sizeof FP, 0)) == -1)
				{
					perror("recvFP");
					exit(1);
				}
				FP[numbytes_client] = '\0';
				//outfile_client<<"received FP:"<<dec<<FP<<endl;

				// receiving the FS from manager
				if ((numbytes_client = recv(sockfd_client, FS, sizeof FS, 0)) == -1)
				{
					perror("recvFS");
					exit(1);
				}
				FS[numbytes_client] = '\0';
				//outfile_client<<"received FS:"<<FS<<endl;
				//int client_nonce = atoi(buf_client);


////////////////////////////////////////////////////////////////////
// creating a UDP socket for triad messages- UDP_private
////////////////////////////////////////////////////////////////////
				create_main_udp_port();

////////////////////////////////////////////////////////////////////
// creating a UDP socket for hello messages- UDP_hello
////////////////////////////////////////////////////////////////////
				create_hello_udp_port();
				create_lazy_udp_port();

						//printf("DGRAM port is : %d\n",DGRAM_PORT);
						//outfile_client<< "my udp port is : "<<dec<<DGRAM_PORT<<endl;
//////////////////////////////////////////////
//	finding position in the ring
//////////////////////////////////////////////

						if ((STAGE.compare("2")==0) || (STAGE.compare("3")==0))
						{
							position_in_ring();
						}
						else if((STAGE.compare("6")==0) || (STAGE.compare("7")==0))
						{//cout<<" inside the right intializer"<<endl;
							position_in_ring_FT();
						}

////////////////////////////////////////////////////////////////////////////////////////////
//	sending dgram port and NONCE+Sx to manager through tcp socket - sockfd_client
////////////////////////////////////////////////////////////////////////////////////////////

				sprintf(buf,"%d",DGRAM_PORT);
				if(send(sockfd_client, buf, sizeof(buf), 0) == -1)
					 perror("send");
				//outfile_client<<"dgram port sent is:"<<dec<<DGRAM_PORT<<endl;

				char q[100];
				strcpy (q,NONCE);
				strcat (q,client_name);

				if(send(sockfd_client, q, sizeof(q), 0) == -1)
				perror("send");
				//outfile_client<<"concat nonce+Sx sent is:"<<dec<<q<<endl;



//////////////////////////////////////////////////////////////////////////
				// SELECT between the TCP and UDP sockets
//////////////////////////////////////////////////////////////////////////

				//SELECT();

				TestApp *app;
				app = new TestApp;
					 //Start the timers
					app->start();


				close(sockfd_client);
				outfile_client.close();
				//outfile_client.close();
				exit(0);	//once the child is done sending the info kill the child
			}  // end child code
	}  // end for loop
} // end function




void create_main_udp_port()
{

	int newfd;  // listen on sock_fd, new connection on new_fd
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	struct sockaddr_in address;
	int  addresslen= sizeof(address);

	if ((UDP_private = socket(AF_INET,SOCK_DGRAM,0)) == -1)
			{
				perror("client: dgramsocket");
		    }

			if (setsockopt(UDP_private, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1)
			{
		        perror("setsockopt");
		        exit(1);
		    }

			address.sin_family = AF_INET;
			address.sin_port = htons(0);
			address.sin_addr.s_addr = INADDR_ANY;

			if (bind(UDP_private, (struct sockaddr*)&address, addresslen) == -1)
			{
		        close(UDP_private);
		        perror("server: bind");
			}

			getsockname(UDP_private,(struct sockaddr *)&address, (socklen_t*)&addresslen);
			DGRAM_PORT = (int)htons(address.sin_port);
			cout<< "**** Data port and sock are : "<<DGRAM_PORT<<" "<<UDP_private<<endl;
}

void create_hello_udp_port()
{
	int newfd;  // listen on sock_fd, new connection on new_fd
		struct sockaddr_storage their_addr; // connector's address information
		socklen_t sin_size;
		struct sigaction sa;
		int yes=1;
		struct sockaddr_in address;
		int  addresslen= sizeof(address);

		if ((UDP_hello = socket(AF_INET,SOCK_DGRAM,0)) == -1)
				{
					perror("client: dgramsocket");
			    }

				if (setsockopt(UDP_hello, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1)
				{
			        perror("setsockopt");
			        exit(1);
			    }

				address.sin_family = AF_INET;
				address.sin_port = htons(0);
				address.sin_addr.s_addr = INADDR_ANY;

				if (bind(UDP_hello, (struct sockaddr*)&address, addresslen) == -1)
				{
			        close(UDP_hello);
			        perror("server: bind-hello");
				}

				getsockname(UDP_hello,(struct sockaddr *)&address, (socklen_t*)&addresslen);
				HELLO_PORT = (int)htons(address.sin_port);
				cout<< "**** HELLO port and sock are : "<<HELLO_PORT<<" "<<UDP_hello<<endl;
}

void create_lazy_udp_port()
{
	int newfd;  // listen on sock_fd, new connection on new_fd
		struct sockaddr_storage their_addr; // connector's address information
		socklen_t sin_size;
		struct sigaction sa;
		int yes=1;
		struct sockaddr_in address;
		int  addresslen= sizeof(address);

		if ((UDP_lazy = socket(AF_INET,SOCK_DGRAM,0)) == -1)
				{
					perror("client: dgramsocket");
			    }

				if (setsockopt(UDP_lazy, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1)
				{
			        perror("setsockopt");
			        exit(1);
			    }

				address.sin_family = AF_INET;
				address.sin_port = htons(0);
				address.sin_addr.s_addr = INADDR_ANY;

				if (bind(UDP_lazy, (struct sockaddr*)&address, addresslen) == -1)
				{
			        close(UDP_lazy);
			        perror("server: bind-hello");
				}

				getsockname(UDP_lazy,(struct sockaddr *)&address, (socklen_t*)&addresslen);
				LAZY_PORT = (int)htons(address.sin_port);
				//cout<< "**** LAZY port and sock are : "<<LAZY_PORT<<" "<<UDP_lazy<<endl;
}



int TestTimer1::Expire()
{
	struct timeval tv;
	getTime(&tv);
	fprintf(stderr, "CLIENT : %s ->Timer has expired \n",CLIENT_NAME);

	MARSHALLING_UDP obj;
	obj.data.token= SUCCESSOR;
	obj.SEND((char*)"hello-predecessor-q",SUCCESSOR_port,1);
	int done=obj.RECEIVE(UDP_hello);
	//cout<<"CLIENT: "<<CLIENT_NAME<<"-> DONE is: "<<done<<endl;
	//outfile_client<<"CLIENT: "<<CLIENT_NAME<<"-> DONE is: "<<done<<endl;
	if(done==0 )  /// failed to receive response to hello msg
	{


		lazy_update_ft(SUCCESSOR,DOUBLE_SUCC,DOUBLE_SUCC_PORT);
		cout<<"CLIENT: "<<CLIENT_NAME<<"no response received to hello msg-> updated SUCC to"<<hex<<SUCCESSOR<<endl;
		//outfile_client<<"CLIENT: "<<CLIENT_NAME<<"no response received to hello msg-> updated SUCC to"<<hex<<SUCCESSOR<<endl;


		// updating the double suc to suc of new suc
		MARSHALLING_UDP update;
		update.data.token= SUCCESSOR;
		update.SEND((char*)"successor-q",SUCCESSOR_port,1);
			update.RECEIVE(UDP_hello);
		DOUBLE_SUCC= update.data_recv.id1;
		DOUBLE_SUCC_PORT=update.data_recv.id2;
		//outfile_client<<"updated DOUBKE SUC to -> "<<DOUBLE_SUCC<<" port->"<<dec<<DOUBLE_SUCC_PORT<<endl;
		cout<<"CLIENT: "<<CLIENT_NAME<<" updated DOUBKE SUC to -> "<<DOUBLE_SUCC<<" port->"<<dec<<DOUBLE_SUCC_PORT<<endl;

		/////// updating PRED of double suc to self
		cout<<"CLIENT: "<<CLIENT_NAME<<"-> updated PRED of "<<hex<<SUCCESSOR<<endl;
		//outfile_client<<"CLIENT: "<<CLIENT_NAME<<"-> updated PRED of "<<hex<<SUCCESSOR<<endl;
		MARSHALLING_UDP update_pred;
		update_pred.data.token= SUCCESSOR;
		update_pred.data.id1= MY_TOKEN;
		update_pred.data.id2= DGRAM_PORT;
		update_pred.data.id3= 0;
		update_pred.SEND((char*)"update-q",SUCCESSOR_port,1);
		update_pred.RECEIVE(UDP_hello);
	}

	else if (obj.data_recv.id1== MY_TOKEN)
	{
		cout<<"CLIENT: "<<CLIENT_NAME<<"-> received proper response to hello msg"<<endl;
		//outfile_client<<"CLIENT: "<<CLIENT_NAME<<"-> received proper response to hello msg"<<endl;

		MARSHALLING_UDP update1;
				update1.data.token= SUCCESSOR;
				update1.SEND((char*)"successor-q",SUCCESSOR_port,1);
					update1.RECEIVE(UDP_hello);
				DOUBLE_SUCC= update1.data_recv.id1;
				DOUBLE_SUCC_PORT=update1.data_recv.id2;
				//outfile_client<<"SUC was ALIVE , still updated DOUBKE SUC to -> "<<DOUBLE_SUCC<<" port->"<<dec<<DOUBLE_SUCC_PORT<<endl;
				cout<<"CLIENT: "<<CLIENT_NAME<<"SUC was ALIVE , still  updated DOUBKE SUC to -> "<<DOUBLE_SUCC<<" port->"<<dec<<DOUBLE_SUCC_PORT<<endl;


	}


	fflush(NULL);
	return 0;
}



void TestApp::start()
{
	struct timeval tmv;
	int status;

	fd_set READ_SET;
		fd_set READ_SET_COPY;

		//outfile_client<<"inside seleact"<<endl;
		cout<<"inside select function"<<endl;
			int max_sock;

			if(UDP_private > sockfd_client)
			{
				 max_sock=UDP_private;
			}
			else
			{
				max_sock=sockfd_client;
			}

			int total_timer_events;
			FD_ZERO(&READ_SET);
	// Change while condition to reflect what is required for Project 1
	// ex: Routing table stabalization.
	while (1) {
		//if (total_timer_events >5)
			//exit(1);


		timersManager_->NextTimerTime(&tmv);
		if (tmv.tv_sec == 0 && tmv.tv_usec == 0) {
				//outfile_client<<"timer finished .... calling the function"<<endl;
		        // The timer at the head on the queue has expired
		        timersManager_->ExecuteNextTimer();

			continue;
		}
		if (tmv.tv_sec == MAXVALUE && tmv.tv_usec == 0){
		        // There are no timers in the event queue
		        break;
		}


		/* The select call here will wait for tv seconds before expiring
		 * You need to  modifiy it to listen to multiple sockets and add code for
		 * packet processing. Refer to the select man pages or "Unix Network
		 * Programming" by R. Stevens Pg 156.
		 */




					FD_SET(UDP_private,&READ_SET);
							FD_SET(sockfd_client,&READ_SET);
					status = select(max_sock+1,&READ_SET,NULL,NULL,&tmv);

					if (status<0)
						{perror("select");}


						else if (status == 0){
							//outfile_client<<"select timed out ..... again calling the timers function"<<endl;
									// Timer expired, Hence process it
								        timersManager_->ExecuteNextTimer();
									// Execute all timers that have expired.
									timersManager_->NextTimerTime(&tmv);

									while(tmv.tv_sec == 0 && tmv.tv_usec == 0){
									       // Timer at the head of the queue has expired
									        timersManager_->ExecuteNextTimer();
										timersManager_->NextTimerTime(&tmv);


									}
								}

						else if (status > 0){
					// The socket has received data.
					// Perform packet processing.
							//for(int i=1;i<33;i++)
								//					{
													//	outfile_client<<"client"<<hex<<MY_TOKEN<<"#"<<i<<":"<<hex<<FT[i].NODE_TOKEN<<"->"<<dec<<FT[i].udp_port<<endl;
											//		}
												//outfile_client<<"PREDECESSOR: "<<PREDECESSOR<<endl;
												//outfile_client<<"DOUBLE_SUCC: "<<DOUBLE_SUCC<<"port: "<<DOUBLE_SUCC_PORT<<endl;



						//outfile_client<<"data on socket ---------------"<<endl;
					///////////////////////
					// got msg on UDP port
					///////////////////////


					//cout<<"CLIENT:"<<CLIENT_NAME<<"->"<<" got from port"<<endl;

						if(FD_ISSET(UDP_private,&READ_SET))
										{
											int num_read1;
											outfile_client<<endl;
											//ioctl(UDP_private,FIONREAD,&num_read1);
											//if(num_read1<



											MARSHALLING_UDP obj;
											obj.RECEIVE(UDP_private);
										}
						if(FD_ISSET(sockfd_client,&READ_SET))
										{
											int num_read;
											 ioctl(sockfd_client,FIONREAD,&num_read);
											 if(num_read<=0)
											 {
												 continue;
											 }
											 //recv_tcp();
											 int numbytes_client;
											char RECV[100],RECV1[100];

											if ((numbytes_client = recv(sockfd_client, RECV, sizeof RECV, 0)) == -1)
															{
																perror("recv_TCP_client");
																exit(1);
															}
															//outfile_client<<"received msg from manager:"<<RECV<<endl;


											inst.instruction=strtok(RECV,"-");
											inst.DATA=strtok(NULL,"\0");
											//outfile_client<<"received msg :"<<inst.instruction<<endl;
											//outfile_client<<"received data :"<<inst.DATA<<endl;

											uint32_t data_hash= nonce_name_hash((uint32_t)(htonl(atoi(NONCE))),inst.DATA);



											char DUMMY_store[]="store";
											char DUMMY_search[]="search";
											char DUMMY_end_client[]="end_client";
											char DUMMY_kill_client[]="kill_client";
											int YES;
											uint32_t numbers[]={0,1,2,3};
											uint32_t temp;
											//cout<<"data hash is "<<hex<<data_hash<<endl;
											if (strcmp((char *)inst.instruction,DUMMY_store)==0  )
												{

													if(STAGE.compare("7")==0)
													{
														for (int i=0;i<4;i++)
														{
															data_hash=  (numbers[i]<<30) | (0x3fffffff & data_hash );
															cout<< "DATA_HASH VALUE IS ------->"<<hex<<data_hash<<endl;
															//DATA_HASH=data_hash;   // setting the global value of DATA_HASH
															store_func(data_hash);

														}
													}
													else
													{
														store_func(data_hash);
													}


												}
											else if(strcmp((char *)inst.instruction,DUMMY_search)==0 )
											{
												cout<<"&&&&&&&&&&&&&&&&&&& in SEARCH"<<endl;
												uint32_t min1,min2,temp,temporary;
												min1=0xffffffff;
												uint32_t diff[4];
												map <uint32_t,uint32_t> mapping;

												global_search_counter=0;

												if(STAGE.compare("7")==0)
												{
													for (int i=0;i<4;i++)
													{
														temp=  (numbers[i]<<30) | (0x3fffffff & data_hash );
														//cout<< "DATA_HASH VALUE IS ------->"<<hex<<data_hash<<endl;
														//DATA_HASH=data_hash;   // setting the global value of DATA_HASH
														diff[i] = calculate((uint64_t)temp,(uint64_t)MY_TOKEN,0);
														mapping[diff[i]]= temp;
														cout << diff[i] <<"->"<<hex<<mapping[diff[i]]<<endl;

													}

													for (int j=0;j<4;j++)   // sorting the differences
													{
														for (int k=j+1;k<4;k++)
														{
																if (diff[k]< diff[j] )
																{
																	temporary= diff[j];
																	diff[j]=diff[k];
																	diff[k]=temporary;
																}
														}
													}

													for (int g=0;g<4;g++)
													{
														cout<<"diff is: "<<diff[g]<<endl;
													}
													cout<< "nearest 2 are : "<< hex<<mapping[diff[0]]<<", "<<hex<<mapping[diff[1]]<<endl;

													search_func(mapping[diff[0]]);
													search_func(mapping[diff[1]]);


												}
												else
												{
													search_func(data_hash);
												}
											}

											else if(strcmp((char *)inst.instruction,DUMMY_kill_client)==0 )
												{
													cout<<"CLIENT: "<<CLIENT_NAME<<"-> killing my self ---- got the kill signal from manager"<<endl;
													//outfile_client<<endl;
													exit(1);
												}


										}

					} //end data on socket

	}// end while 1
	return;
}



void store_func(uint32_t data_hash)
{
	details contact;
			//cout<<"CLIENT: "<<CLIENT_NAME<<" hash calculated for data item to be stored "<<hex<<data_hash<<endl;
			//outfile_client<<" hash calculated for data item to be stored/searched: "<<hex<<data_hash<<endl;
			contact= scan_FT(data_hash);
			//cout<< "inside recv func, after scanft "<<inst.instruction<<" "<<inst.DATA<<endl;

			if (contact.node_token==MY_TOKEN)  // if i am myself responsible
			{

					DATA_STORE[data_hash]= new char[100];
					strcpy(DATA_STORE[data_hash],inst.DATA);
					outfile_client<<"add "<<inst.DATA<<" with hash "<<"0x"<<hex<<data_hash<<" to node "<<"0x"<<hex<<MY_TOKEN<<endl;
					cout<<"i am storing and sending OK to manager"<<endl;
					send_ok_manager();
					//continue;

			}


			else
			{

			MARSHALLING_UDP obj;
							obj.data.token= contact.node_token;
							obj.data.id1= data_hash;
				//			cout<< "inside recv func, before sending stores-q "<<inst.instruction<<" "<<inst.DATA<<endl;
							obj.SEND((char*)"stores-q",contact.node_port,0);

			}
}



void search_func(uint32_t data_hash)
{
	details contact;

	cout<<"CLIENT: "<<CLIENT_NAME<<" hash calculated for data item to be stored/searched: "<<hex<<data_hash<<endl;
	//outfile_client<<" hash calculated for data item to be stored/searched: "<<hex<<data_hash<<endl;
	contact= scan_FT(data_hash);
	cout<< "inside recv func, after scanft "<<inst.instruction<<" "<<inst.DATA<<endl;

	if (contact.node_token==MY_TOKEN)  // if i am myself responsible
	{

		if (DATA_STORE.count(data_hash)>0)
		{

			cout<<"------"<<DATA_STORE[data_hash]<<endl;
			outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<MY_TOKEN<<" key PRESENT "<<endl;

			if (global_search_counter==0)
			{
				//outfile_client<<"inside global counter==0,stored "<<endl;
				cout<<"inside global counter==0 in self, stored "<<endl;
				//strcpy(search1_data,DATA_STORE[data_hash]);
				strncpy(search1_data,DATA_STORE[data_hash],strlen(DATA_STORE[data_hash]));

				cout<<"^^^^^^^^^^^^^^^^^^"<<DATA_STORE[data_hash]<<endl;
				search1_node=MY_TOKEN;
				global_search_counter++;
				//outfile_client<<"inside global counter==0,stored "<<search1_data<<endl;
				cout<<"inside global counter==0, stored "<<search1_data<<endl;
			}
			else

			{
				//outfile_client<<"inside global counter==1, searches are"<<DATA_STORE[data_hash]<<" "<<search1_data<<endl;
				cout<<"inside global counter==1 in self, searches are"<<DATA_STORE[data_hash]<<" "<<search1_data<<endl;
				if (strcmp(DATA_STORE[data_hash],search1_data)==0)
				{
					outfile_client<<"search "<<DATA_STORE[data_hash]<<" to node "<<hex<<search1_node<<" and "<<hex<<MY_TOKEN<<" key PRESENT and VERIFIED"<<endl;
					cout<<"search "<<DATA_STORE[data_hash]<<" to node "<<hex<<search1_node<<" and "<<hex<<MY_TOKEN<<" key PRESENT and VERIFIED"<<endl;
				}
				else
				{
					outfile_client<<"search "<<DATA_STORE[data_hash]<<hex<<" to node "<<search1_node<<" and "<<hex<<MY_TOKEN<<" key PRESENT but DISAGREE"<<endl;
					cout<<"search "<<DATA_STORE[data_hash]<<" to node "<<hex<<search1_node<<" and "<<hex<<MY_TOKEN<<" key PRESENT but DISAGREE"<<endl;
				}
				char OK_msg[100];
												strcpy(OK_msg,"OK");
												if(send(sockfd_client, OK_msg, sizeof(OK_msg), 0) == -1)
													perror("send");

					//outfile_client<<"SENT OK to Manager, "<<endl;
			}


		}
		else if (DATA_STORE.count(data_hash)==0)
		{
			outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<MY_TOKEN<<" key ABSENT "<<endl;
			outfile_client<<endl;
		}
			send_ok_manager();
			//continue;

	}


	else
	{

	MARSHALLING_UDP obj;
					obj.data.token= contact.node_token;
					obj.data.id1= data_hash;
					cout<< "inside recv func, before sending stores-q "<<inst.instruction<<" "<<inst.DATA<<endl;
					obj.SEND((char*)"stores-q",contact.node_port,0);

	}
}



void TestApp::recv_tcp()
{
	int numbytes_client;
						char RECV[100],RECV1[100];

						if ((numbytes_client = recv(sockfd_client, RECV, sizeof RECV, 0)) == -1)
										{
											perror("recv_TCP_client");
											exit(1);
										}
										//outfile_client<<"received msg from manager:"<<RECV<<endl;


						inst.instruction=strtok(RECV,"-");
						inst.DATA=strtok(NULL,"\0");
						//outfile_client<<"received msg :"<<inst.instruction<<endl;
						//outfile_client<<"received data :"<<inst.DATA<<endl;

						uint32_t data_hash= nonce_name_hash((uint32_t)(htonl(atoi(NONCE))),inst.DATA);

						char DUMMY_store[]="store";
						char DUMMY_search[]="search";
						char DUMMY_end_client[]="end_client";
						char DUMMY_kill_client[]="kill_client";
						int YES;
						//strcpy(DUMMY_search,"search");
						//strcpy(DUMMY_store,"store");

						//if (((PRE.token<MY_TOKEN) && (data_hash <= MY_TOKEN  &&  data_hash > PRE.token)) || ((PRE.token > MY_TOKEN) && (data_hash < MY_TOKEN)))


	//////////////////////////////////////
	// stage 4/5/6/7


				/*if (LIES_BW(PREDECESSOR,MY_TOKEN,data_hash,(char*)"(]")==1)
									{

										//outfile_client<<"in the if --------------------"<<endl;
										if (strcmp((char *)inst.instruction,DUMMY_store)==0)
										{
											//outfile_client<<"inside store"<<endl;
												DATA_STORE[data_hash]= inst.DATA;
												outfile_client<<"add "<<inst.DATA<<" with hash "<<"0x"<<hex<<data_hash<<" to node "<<"0x"<<hex<<MY_TOKEN<<endl;
												//outfile_client<<"itself 	stored->"<<DATA_STORE[data_hash]<<endl;

												send_ok_manager();
												continue;

										}
										else if(strcmp((char *)inst.instruction,DUMMY_search)==0)
										{
											//outfile_client<<"inside search"<<endl;

											if (DATA_STORE.count(data_hash)>0)
													{

												outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<MY_TOKEN<<" key PRESENT "<<endl;

													}
											else if (DATA_STORE.count(data_hash)==0)
											{
												outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<MY_TOKEN<<" key ABSENT "<<endl;
												outfile_client<<endl;
											}

											send_ok_manager();
											continue;
										}
									}		//end lies_bw

	*/

			if (strcmp((char *)inst.instruction,DUMMY_store)==0 || strcmp((char *)inst.instruction,DUMMY_search)==0  )
				{
					details contact;
					cout<<"CLIENT: "<<CLIENT_NAME<<" hash calculated for data item to be stored/searched: "<<hex<<data_hash<<endl;
					//outfile_client<<" hash calculated for data item to be stored/searched: "<<hex<<data_hash<<endl;
					contact= scan_FT(data_hash);
					cout<< "inside recv func, after scanft "<<inst.instruction<<" "<<inst.DATA<<endl;

					if (contact.node_token==MY_TOKEN)  // if i am myself responsible
					{
						if (strcmp((char *)inst.instruction,DUMMY_store)==0 )
						{
							outfile_client<<"add "<<inst.DATA<<" with hash "<<"0x"<<hex<<data_hash<<" to node "<<"0x"<<hex<<MY_TOKEN<<endl;
							cout<<"i am storing and sending OK to manager"<<endl;
							send_ok_manager();
							//continue;
						}
						else
						{
							outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<MY_TOKEN<<" key PRESENT "<<endl;
							send_ok_manager();
							//continue;
						}
					}


					//else
					{

					MARSHALLING_UDP obj;
									obj.data.token= contact.node_token;
									obj.data.id1= data_hash;
									cout<< "inside recv func, before sending stores-q "<<inst.instruction<<" "<<inst.DATA<<endl;
									obj.SEND((char*)"stores-q",contact.node_port,0);

					}

				}


			else if(strcmp((char *)inst.instruction,DUMMY_kill_client)==0 )
				{
					cout<<"CLIENT: "<<CLIENT_NAME<<"-> killing my self ---- got the kill signal from manager"<<endl;
					//outfile_client<<endl;
					exit(1);
				}



return;

}



TestApp::TestApp()
{
	TimerCallback *tcb;
	struct timeval tv;

	getTime(&tv);

//	fprintf(stderr,"Start time %d.%06d\n",
//		(int)tv.tv_sec, (int)tv.tv_usec);
	// Create the timer event management class
	timersManager_ = new Timers;

	// Create callback classes and set up pointers
	// Add timers to the event queue and specify the timer in ms.
	tcb = new TestTimer1;
	timersManager_->AddTimer(10000, tcb);


}







