/*
 * marshalling.cpp
 *
 *  Created on: Oct 20, 2011
 *      Author: Abhi
 */


#include "marshalling.h"



using namespace std;


char buff[100];



////////////////////////////////////////
//UDP API's
////////////////////////////////////////



void MARSHALLING_UDP::SEND(char *msg_name, int dest_port, int d_h_l =0)
	{

		char *buff1 = CODE(msg_name);
        struct sockaddr_in destination;


       destination.sin_family = AF_INET;
       destination.sin_port = htons(dest_port);
       destination.sin_addr.s_addr = htonl(INADDR_ANY);
       //UDP_private is the UDP port of sender node

       if (strcmp(CLIENT_NAME,"logmsg")==0)
       {
    	   outfile_client<<buff1<<endl;
       }

    if (d_h_l == 0)
    {
       if( sendto(UDP_private,buff1,strlen(buff1),0,(struct sockaddr*)&destination,sizeof(destination))==-1)
    	   perror("send:UDP");
       //outfile_client<<"sent command :"<<buff<<" to socket:"<<dec<<UDP_private<<endl;
    }
    else if(d_h_l==1)
    {
    	//outfile_client<<"sending to port "<<dec<<dest_port<<endl;
    	  if( sendto(UDP_hello,buff1,strlen(buff1),0,(struct sockaddr*)&destination,sizeof(destination))==-1)
    	    	   perror("send:UDP");
    }
    else if(d_h_l==2)
       {
       	//outfile_client<<"sending to port "<<dec<<dest_port<<endl;
       	  if( sendto(UDP_lazy,buff1,strlen(buff1),0,(struct sockaddr*)&destination,sizeof(destination))==-1)
       	    	   perror("send:UDP");
       }
    //outfile_client<<"in SEND - sent data on port >>>>"<<dest_port<<endl;
    //cout<<"CLIENT:"<<CLIENT_NAME<<"->in SEND - sent data on port >>>>"<<buff1<<" port " <<dest_port<<endl;

	} // end function SEND


char* MARSHALLING_UDP::CODE(char* msg)
{
	//outfile_client<<"in CODE "<<msg<<endl;
	//char buff[100];
	char buff1[100],buff2[100],buff3[100],buff4[100],buff5[100],buff6[100];

	int msg_code= msg_to_id(msg);


	sprintf(buff,"%d-",msg_code);
	//outfile_client<<"msg code is :"<<msg_code<<" msg is: "<<msg<<endl;
	//outfile_client<<"coding the packet, msg  right now is "<<buff<<endl;
	switch(msg_code)
	{
//successor-q
	case 1: /// picks up value of token

						//outfile_client<<"inside case 1: "<<buff<<endl;

						sprintf(buff1,"%u",data.token);
						//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
						strcat(buff, buff1);
						outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
						//cout<<"CLIENT:"<<CLIENT_NAME<<"->"<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
							break;

//successor-r
	case 2: /// picks up value of token, id1, id2

							sprintf(buff1,"%u,",data.token);
							//outfile_client<<"adding buff1: "<<buff1;
							strcat(buff, buff1);
							sprintf(buff2,"%u,",data.id1);
							//outfile_client<<"adding buff2: "<<buff2;
							strcat(buff, buff2);
							sprintf(buff3,"%u,",data.id2);
							//outfile_client<<"adding buff3: "<<buff3;
							strcat(buff, buff3);
							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<dec<<data.id2<<")"<<endl;
							//cout<<"CLIENT:"<<CLIENT_NAME<<"->"
							break;
// predecessor-q
	case 3: /// picks up value of token

							//outfile_client<<"inside case 1: "<<buff<<endl;

							sprintf(buff1,"%u",data.token);
							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
							strcat(buff, buff1);
							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
								break;

// predecessor-r
	case 4: /// picks up value of token, id1, id2

								sprintf(buff1,"%u,",data.token);
								//outfile_client<<"adding buff1: "<<buff1;
								strcat(buff, buff1);
								sprintf(buff2,"%u,",data.id1);
								//outfile_client<<"adding buff2: "<<buff2;
								strcat(buff, buff2);
								sprintf(buff3,"%u,",data.id2);
								//outfile_client<<"adding buff3: "<<buff3;
								strcat(buff, buff3);
								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<dec<<data.id2<<")"<<endl;
								break;
/// stores-q
	case 5: /// picks up value of token, id1

									sprintf(buff1,"%u,",data.token);
									//outfile_client<<"adding buff1: "<<buff1;
									strcat(buff, buff1);
									sprintf(buff2,"%u,",data.id1);
									//outfile_client<<"adding buff2: "<<buff2;
									strcat(buff, buff2);

									outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<")"<<endl;

									break;

//// stores-r
	case 6: /// picks up value of token, id1, id2,id3,id4

									sprintf(buff1,"%u,",data.token);
									//outfile_client<<"adding buff1: "<<buff1;
									strcat(buff, buff1);
									sprintf(buff2,"%u,",data.id1);
									//outfile_client<<"adding buff2: "<<buff2;
									strcat(buff, buff2);
									sprintf(buff3,"%u,",data.id2);
									//outfile_client<<"adding buff3: "<<buff3;
									strcat(buff, buff3);
									sprintf(buff4,"%u,",data.id3);
									//outfile_client<<"adding buff3: "<<buff3;
									strcat(buff, buff4);
									sprintf(buff5,"%u,",data.id4);
									//outfile_client<<"adding buff3: "<<buff3;
									strcat(buff, buff5);

									outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<"0x"<<hex<<data.id2<<" "<<dec<<data.id3<<" "<<dec<<data.id4<<")"<<endl;
									break;

	case 7: /// picks up value of token, id1, id2

								sprintf(buff1,"%u,",data.token);
								//outfile_client<<"adding buff1: "<<buff1;
								strcat(buff, buff1);
								sprintf(buff2,"%u,",data.id1);
								//outfile_client<<"adding buff2: "<<buff2;
								strcat(buff, buff2);
								sprintf(buff3,"%u,",data.id2);
								//outfile_client<<"adding buff3: "<<buff3;
								strcat(buff, buff3);
								sprintf(buff4,"%u,",data.id3);
								//outfile_client<<"adding buff3: "<<buff3;
								strcat(buff, buff4);

								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<dec<<data.id2<<" "<<dec<<data.id3<<")"<<endl;
								break;

// store-q
	case 8: /// picks up value of token, id1, d1

										sprintf(buff1,"%u,",data.token);
										//outfile_client<<"adding buff1: "<<buff1;
										strcat(buff, buff1);
										sprintf(buff2,"%u,",data.id1); 		// hash of data to be stored
										//outfile_client<<"adding buff2: "<<buff2;
										strcat(buff, buff2);
										sprintf(buff3,"%u,",data.id2); 		// hash of data to be stored
										//outfile_client<<"adding buff2: "<<buff2;
										strcat(buff, buff3);

										strcat(buff, data.d1);

										outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<"0x"<<hex<<data.id2<<" "<<data.d1<<" "<<")"<<endl;
										break;

// store-r
	case 9: /// picks up value of token, id1, id2, d1

											sprintf(buff1,"%u,",data.token);
											//outfile_client<<"adding buff1: "<<buff1;
											strcat(buff, buff1);
											sprintf(buff2,"%u,",data.id1); 		// R
											//outfile_client<<"adding buff2: "<<buff2;
											strcat(buff, buff2);
											sprintf(buff3,"%u,",data.id2); 		// SL
											//outfile_client<<"adding buff2: "<<buff2;
											strcat(buff, buff3);
											sprintf(buff4,"%u,",data.id3); 		// hash of data to be stored
											//outfile_client<<"adding buff2: "<<buff2;
											strcat(buff, buff4);

											strcat(buff, data.d1);

											outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<"0x"<<hex<<data.id2<<" "<<"0x"<<hex<<data.id3<<" "<<data.d1<<" "<<")"<<endl;
											break;





	case 10: /// picks up value of token, id1, id2

								sprintf(buff1,"%u,",data.token);
								//outfile_client<<"adding buff1: "<<buff1;
								strcat(buff, buff1);
								sprintf(buff2,"%u,",data.id1);
								//outfile_client<<"adding buff2: "<<buff2;
								strcat(buff, buff2);
								sprintf(buff3,"%u,",data.id2);
								//outfile_client<<"adding buff3: "<<buff3;
								strcat(buff, buff3);
								sprintf(buff4,"%u,",data.id3);
								//outfile_client<<"adding buff3: "<<buff3;
								strcat(buff, buff4);
								sprintf(buff5,"%u,",data.id4);
								//outfile_client<<"adding buff3: "<<buff3;
								strcat(buff, buff5);

								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<"0x"<<hex<<data.id2<<" "<<dec<<data.id3<<" "<<dec<<data.id4<<")"<<endl;
								break;

//find_successor-q
	case 11: /// picks up value of token

							//outfile_client<<"inside case 1: "<<buff<<endl;

							sprintf(buff1,"%u",data.token);
							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
							strcat(buff, buff1);
							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
								break;
// find-successor-r
	case 12: /// picks up value of token

							//outfile_client<<"inside case 1: "<<buff<<endl;

							sprintf(buff1,"%u,",data.token);
							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
							strcat(buff, buff1);
							sprintf(buff2,"%u",data.id1);
							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
							strcat(buff, buff2);
							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<dec<<data.id1<<")"<<endl;
								break;

// find-predecessor-q
    case 13: /// picks up value of token

								//outfile_client<<"inside case 1: "<<buff<<endl;

								sprintf(buff1,"%u",data.token);
								//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
								strcat(buff, buff1);
								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
									break;

// find-predecessor-r
   case 14: /// picks up value of token

		//outfile_client<<"inside case 1: "<<buff<<endl;

								sprintf(buff1,"%u,",data.token);
								//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
								strcat(buff, buff1);
								sprintf(buff2,"%u",data.id1);
								//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
								strcat(buff, buff2);
								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<dec<<data.id1<<")"<<endl;
									break;


// closest_preceding_finger-q
    case 15: /// picks up value of token

    							//outfile_client<<"inside case 1: "<<buff<<endl;

								sprintf(buff1,"%u",data.token);
								//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
								strcat(buff, buff1);
								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
								break;

// closest_preceding_finger-r
    case 16: /// picks up value of token
    					//outfile_client<<"inside case 1: "<<buff<<endl;

    							sprintf(buff1,"%u,",data.token);
    							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							strcat(buff, buff1);
    							sprintf(buff2,"%u",data.id1);
    							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							strcat(buff, buff2);
    							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<dec<<data.id1<<")"<<endl;
    								break;

// leaving-q
    case 17: /// picks up value of token
    //outfile_client<<"inside case 1: "<<buff<<endl;

    							sprintf(buff1,"%u,",data.token);
    							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							strcat(buff, buff1);
    							sprintf(buff2,"%u",data.id1);
    							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							strcat(buff, buff2);
    							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<dec<<data.id1<<")"<<endl;
    							break;

// leaving-r
    case 18: /// picks up value of token

    							//outfile_client<<"inside case 1: "<<buff<<endl;

    							sprintf(buff1,"%u",data.token);
    							//outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							strcat(buff, buff1);
    							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
    							break;

// next-data-q
    case 19: /// picks up value of token, id1
    							    //outfile_client<<"inside case 1: "<<buff<<endl;

    							 sprintf(buff1,"%u,",data.token);
    							 //outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							 strcat(buff, buff1);
    							 sprintf(buff2,"%u",data.id1);
    							 //outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							 strcat(buff, buff2);
    							 outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<dec<<data.id1<<")"<<endl;
    							 break;

// next-data-r
    case 20: /// picks up value of token, id1, id2,id3, d1

    							 sprintf(buff1,"%u,",data.token);
    							 //outfile_client<<"adding buff1: "<<buff1;
    							 strcat(buff, buff1);
    							 sprintf(buff2,"%u,",data.id1); 		// hash of data to be stored
    							 //outfile_client<<"adding buff2: "<<buff2;
    							 strcat(buff, buff2);
    							 sprintf(buff3,"%u,",data.id2); 		// hash of data to be stored
    							 //outfile_client<<"adding buff2: "<<buff2;
    							 strcat(buff, buff3);
    							 sprintf(buff4,"%u,",data.id3); 		// hash of data to be stored
    							 //outfile_client<<"adding buff2: "<<buff2;
    							 strcat(buff, buff4);

    							 strcat(buff, data.d1);

    							 outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<"0x"<<hex<<data.id2<<" "<<data.d1<<" "<<")"<<endl;
    							 break;

 // hello-predecessor-q
    case 21: /// picks up value of token

    							 //outfile_client<<"inside case 21: "<<buff<<endl;

    							 sprintf(buff1,"%u",data.token);
    							 //outfile_client<<"inside case 1:token appending: "<<buff1<<endl;
    							 strcat(buff, buff1);
    							 outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<")"<<endl;
    							 break;

// hello-predecessor-r
    case 22: /// picks up value of token, id1, id2

    							sprintf(buff1,"%u,",data.token);
    							//outfile_client<<"adding buff1: "<<buff1;
    							strcat(buff, buff1);
    							sprintf(buff2,"%u,",data.id1);
    							//outfile_client<<"adding buff2: "<<buff2;
    							strcat(buff, buff2);
    							sprintf(buff3,"%u,",data.id2);
    							//outfile_client<<"adding buff3: "<<buff3;
    							strcat(buff, buff3);
    							outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<dec<<data.id2<<")"<<endl;
    							break;

// update-double-successor-q
	case 23: /// picks up value of token, id1

								sprintf(buff1,"%u,",data.token);
								//outfile_client<<"adding buff1: "<<buff1;
								strcat(buff, buff1);
								sprintf(buff2,"%u,",data.id1);
								//outfile_client<<"adding buff2: "<<buff2;
								strcat(buff, buff2);
								//outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<")"<<endl;
								break;

// update-double-successor-r
	case 24: /// picks up value of token, id1

								sprintf(buff1,"%u,",data.token);
								//outfile_client<<"adding buff1: "<<buff1;
								strcat(buff, buff1);
								sprintf(buff2,"%u,",data.id1);
								//outfile_client<<"adding buff2: "<<buff2;
								strcat(buff, buff2);
								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<")"<<endl;
								break;


/// ext-stores-q
case 25: /// picks up value of token, id1

								sprintf(buff1,"%u,",data.token);
								//outfile_client<<"adding buff1: "<<buff1;
								strcat(buff, buff1);
								sprintf(buff2,"%u,",data.id1);
								//outfile_client<<"adding buff2: "<<buff2;
								strcat(buff, buff2);

								outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<")"<<endl;

								break;


//// ext-stores-r
	case 26: /// picks up value of token, id1, id2,id3,id4

									sprintf(buff1,"%u,",data.token);
									//outfile_client<<"adding buff1: "<<buff1;
									strcat(buff, buff1);
									sprintf(buff2,"%u,",data.id1);
									//outfile_client<<"adding buff2: "<<buff2;
									strcat(buff, buff2);
									sprintf(buff3,"%u,",data.id2);
									//outfile_client<<"adding buff3: "<<buff3;
									strcat(buff, buff3);
									sprintf(buff4,"%u,",data.id3);
									//outfile_client<<"adding buff3: "<<buff3;
									strcat(buff, buff4);
									sprintf(buff5,"%u,",data.id4);
									//outfile_client<<"adding buff3: "<<buff3;
									strcat(buff, buff5);
									sprintf(buff6,"%u,",data.id5);
									//outfile_client<<"adding buff3: "<<buff3;
									strcat(buff, buff6);
									strcat(buff,data.d1);
									outfile_client<<msg<<" sent ("<<"0x"<<hex<<data.token<<" "<<"0x"<<hex<<data.id1<<" "<<"0x"<<hex<<data.id2<<" "<<dec<<data.id3<<" "<<dec<<data.id4<<" "<<dec<<data.id5<<" "<<data.d1<<")"<<endl;
									break;


	}


	        //outfile_client<<"the string coded to send is:"<<buff<<endl;
	        return buff;

}

int MARSHALLING_UDP::RECEIVE(int RECV_SOCK)
	{

	struct timeval tmv;
		int status;
		tmv.tv_sec=2;
		tmv.tv_usec=0;
		fd_set READ_SET;
			fd_set READ_SET_COPY;
			int max_sock;
			FD_ZERO(&READ_SET);


			if(RECV_SOCK>UDP_private)
				{max_sock=RECV_SOCK;}
			else
			{	max_sock=UDP_private;}


while(1)
{
	int yes=0;
	if(RECV_SOCK != UDP_private)
	{
			FD_SET(RECV_SOCK,&READ_SET);
	}
			FD_SET(UDP_private,&READ_SET);

		//	cout<<"CLIENT:"<<CLIENT_NAME<<"waiting on sockets :"<<RECV_SOCK<<endl;
		status = select(max_sock+1,&READ_SET,NULL,NULL,&tmv);

		if (status<0)
			{perror("ERROR:select");
				//return 0;
			}
		else if (status == 0)
		{
			cout<<"CLIENT:"<<CLIENT_NAME<<" timed out from select inside receive"<<endl;
			//outfile_client<<"CLIENT:"<<CLIENT_NAME<<" timed out from select inside receive"<<endl;
			return 0;
		}
		else if(status>0)
		{
			//outfile_client<<"inside internal receive- data on some socket"<<endl;
			//cout<<"CLIENT:"<<CLIENT_NAME<<" inside internal receive- data on some socket"<<endl;

		       if(FD_ISSET(RECV_SOCK,&READ_SET) ) // for either hello or lazy msgs
		       			{
		    	   if(RECV_SOCK == UDP_hello)
		    	   {
		    	   //outfile_client<<"received data from hello socket"<<endl;
		    	   cout<<"CLIENT:"<<CLIENT_NAME<<"received data from hello socket"<<endl;
		    	   }
		    	   else if(RECV_SOCK == UDP_lazy)
		    	   		    	   {
		    	   		    	   //outfile_client<<"received data from lazy socket"<<endl;
		    	   		    	cout<<"CLIENT:"<<CLIENT_NAME<<"received data from lazy socket"<<endl;
		    	   		    	   }
		    	   //cout<<"CLIENT:"<<CLIENT_NAME<<" received data from hello socket"<<endl;
							//outfile_client<<"inside recv: on port: "<<RECV_SOCK<<endl;
							struct sockaddr_in sender;
							socklen_t sender_size=sizeof(sender);
							char RECV[100];
								   //UDP_private is the UDP port of sender node
							int len1;
							//cout<<"waiting for reply ....!!!"<<endl;
								   if(( (len1= recvfrom(RECV_SOCK,RECV,sizeof(RECV),0,(struct sockaddr*)&sender,&sender_size))==-1) )
									   {

										   cout<<"in recv_error"<<endl;
										   outfile_client<<"in recv_error"<<endl;
										   perror("recv:UDP");
										   return 0;
										 }
								   RECV[len1]='\0';

								   if (strcmp(CLIENT_NAME,"logmsg")==0)
													  {
													   outfile_client<<RECV<<endl;
													  }
								   //cout<<"received command "<<RECV<<endl;
								   //outfile_client<<"received command "<<RECV<<endl;
								   int sender_port=sender.sin_port;
							/////  message code:
								   DECODE( RECV, sender_port,RECV_SOCK);


								   return 1;
		       			}

		       if(FD_ISSET(UDP_private,&READ_SET))
		       {
		    	   //outfile_client<<"received data from DATA socket"<<endl;
		    	   //cout<<"CLIENT:"<<CLIENT_NAME<<" received data from DATA socket"<<endl;
					//outfile_client<<"inside recv: on port: "<<RECV_SOCK<<endl;
					struct sockaddr_in sender;
					socklen_t sender_size=sizeof(sender);
					char RECV[100];
						   //UDP_private is the UDP port of sender node
					int len1;
					//cout<<"waiting for reply ....!!!"<<endl;
						   if(( (len1= recvfrom(UDP_private,RECV,sizeof(RECV),0,(struct sockaddr*)&sender,&sender_size))==-1) )
							   {

								   cout<<"in recv_error"<<endl;
								   outfile_client<<"in recv_error"<<endl;
								   perror("recv:UDP");
								   return 0;
								 }
						   RECV[len1]='\0';

						   if (strcmp(CLIENT_NAME,"logmsg")==0)
											  {
											   outfile_client<<RECV<<endl;
											  }
						   //cout<<"received command "<<RECV<<endl;
						   //outfile_client<<"received command "<<RECV<<endl;
						   int sender_port=sender.sin_port;
					/////  message code:
						   DECODE( RECV, sender_port,UDP_private);

						   if(RECV_SOCK==UDP_private)
						   {
							   return 1;
						   }

		       } // end if (FDSET=UDP_private)

		}//end if status>0

}
			return 1;
}


void MARSHALLING_UDP::DECODE( char*msg, int send_to,int RECV_SOCK)
{
	char *buff1,*buff2,*buff3,*buff4,*buff5,*buff;
	details info;
	uint32_t data_hash,closest;

	int st;
	//char* msg1;
	//strcpy(msg1,msg);
	//cout<<"outside ......................"<<endl;
	//outfile_client<<"inside decode"<<msg<<endl;
	//cout<<" decode msg is"<<msg<<endl;
	char* msg_code=strtok(msg,"-");       // takes out the msg code
	int int_msg_code=atoi(msg_code);

	//outfile_client<<"msg code is"<<dec<<int_msg_code<<endl;





	switch(int_msg_code)
	{


		case 1: 						// replies for successor -q received
			buff=strtok(NULL,"\0");
			data_recv.token=(uint32_t)atoi(buff);
				//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
			outfile_client<<ID_to_MESSAGE[1]<<" received ("<<"0x"<<hex<<data_recv.token<<")"<<endl;
					if(MY_TOKEN==data_recv.token)
						{
							//outfile_client<<"token matches, Msg reached at correct destination"<<endl;
						}
					else
						{
						//outfile_client<<"token reached wrong destination"<<endl;
							return;
						}
/////////////////////////////////////
//sending appropriate reply
/////////////////////////////////////
			if( (STAGE.compare("2")==0) ||(STAGE.compare("3")==0)  )
				{
					data.id1= SUC.token;
					data.id2=SUC.UDP_port;
				}
			if( (STAGE.compare("6")==0) ||(STAGE.compare("7")==0)  )
			{
				data.id1= SUCCESSOR;
				data.id2=SUCCESSOR_port;
			}

				//outfile_client<<"received message 1"<<endl;
				data.token= MY_TOKEN;
				SEND((char*)"successor-r",send_to);
				break;
//successor-r
		case 2:     // decodes the message and stores it in data_received - token,id1,id2 and returns
			buff=strtok(NULL,",");
			data_recv.token=(uint32_t)atoi(buff);
			//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

			buff1=strtok(NULL,",");     // retrieving si
			data_recv.id1=(uint32_t)atoi(buff1);
			//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
			buff2=strtok(NULL,"\0");     // retrieving sp
			data_recv.id2=(uint32_t)atoi(buff2);
			//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
			outfile_client<<ID_to_MESSAGE[2]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<dec<<data_recv.id2<<")"<<endl;
			return;


		case 3: 						// replies for predecessor -q received
					buff=strtok(NULL,"\0");
					data_recv.token=(uint32_t)atoi(buff);
						//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
					outfile_client<<ID_to_MESSAGE[3]<<" received ("<<"0x"<<hex<<data_recv.token<<")"<<endl;
							if(MY_TOKEN==data_recv.token)
								{
									//outfile_client<<"token matches, Msg reached at correct destination"<<endl;
								}
							else
								{
								//outfile_client<<"token reached wrong destination"<<endl;
									return;
								}
		/////////////////////////////////////
		//sending appropriate reply
		/////////////////////////////////////
							if( (STAGE.compare("2")==0) ||(STAGE.compare("3")==0)  )
						{
							data.id1= PRE.token;
							data.id2=PRE.UDP_port;
						}
						  ///  use finger tables

						else if( (STAGE.compare("6")==0) ||(STAGE.compare("7")==0)  )
										{
											data.id1= PREDECESSOR;
											data.id2=PREDECESSOR_PORT;
										}


						//outfile_client<<"received message 1"<<endl;
						data.token= MY_TOKEN;
						SEND((char*)"predecessor-r",send_to);
						break;


		case 4:     // decodes the message and stores it in data_received - token,id1,id2 and returns
					buff=strtok(NULL,",");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

					buff1=strtok(NULL,",");     // retrieving si
					data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
					buff2=strtok(NULL,"\0");     // retrieving sp
					data_recv.id2=(uint32_t)atoi(buff2);
					//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
					outfile_client<<ID_to_MESSAGE[4]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<dec<<data_recv.id2<<")"<<endl;
					return;



///// stores-q
		case 5:     // decodes the message and stores it in data_received - token,id1,id2 and returns
					buff=strtok(NULL,",");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

					buff1=strtok(NULL,"\0");     // retrieving di
					data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;

					outfile_client<<ID_to_MESSAGE[5]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<")"<<endl;
					//outfile_client<<"in stores-QQQ -> "<<inst.instruction<<" "<<inst.DATA<<endl;
///////////////////////////////
//
///////////////////////////////
//sending the appropriate reply
     if( (STAGE.compare("2")==0) ||(STAGE.compare("3")==0)  )
			{
					if (((PRE.token<MY_TOKEN) &&(data_recv.id1 <= MY_TOKEN && data_recv.id1 > PRE.token)) ||((PRE.token > MY_TOKEN) && ((data_recv.id1 <= MY_TOKEN) || ( MY_TOKEN > PRE.token))))// i have to hold the data


					{
						data.token= MY_TOKEN;
						data.id1= data_recv.id1;
						data.id2= MY_TOKEN;
						data.id3= DGRAM_PORT;

						if ( DATA_STORE.count(data_recv.id1) > 0 ) ///// key already exists with the node
						{
							data.id4= 1;
						}
						else 							// node doesn't have the key but can be responsible
						{
							data.id4= 0;
						}

						SEND((char*)"stores-r",send_to);     // reply accordingly
					}

					else
					{
						data.token= MY_TOKEN;
						data.id1= data_recv.id1;
						data.id2= SUC.token;
						data.id3= SUC.UDP_port;
						data.id4= 0;

						SEND((char*)"stores-r",send_to);

					}
			}
     else
     {
    	 //outfile_client<<"data is -> "<<hex<<data_recv.id1<<endl;
    	   stores_q_ft(data_recv.token,data_recv.id1,send_to,0);
     }

					return;

/// stores-r		/////// primary node is the only one ever receiving this msg
		case 6:
			//outfile_client<<"start of stores-r -> "<<inst.instruction<<" "<<inst.DATA<<endl;
			//outfile_client<<"start of stores-r -> "<<inst.instruction<<" "<<inst.DATA<<endl;
								buff=strtok(NULL,",");
								data_recv.token=(uint32_t)atoi(buff);
								//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

								buff1=strtok(NULL,",");     // retrieving di
								data_recv.id1=(uint32_t)atoi(buff1);
								//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
								buff2=strtok(NULL,",");     // retrieving ri
								data_recv.id2=(uint32_t)atoi(buff2);
								//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
								buff3=strtok(NULL,",");     // retrieving rp
								data_recv.id3=(uint32_t)atoi(buff3);
								buff4=strtok(NULL,"\0");     // retrieving has
								data_recv.id4=(uint32_t)atoi(buff4);

						outfile_client<<ID_to_MESSAGE[6]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<"0x"<<hex<<data_recv.id2<<" "<<dec<<data_recv.id3<<" "<<dec<<data_recv.id4<<")"<<endl;
						//outfile_client<<"in stores-r -> "<<inst.instruction<<" "<<inst.DATA<<endl;

///////////////////////////////////
// sending the appropriate reply
///////////////////////////////////
		if(RECV_SOCK != UDP_lazy)    // don't proceed further if it just a reply to the stores-q for lazy-ft verify
		{
			//outfile_client<<"inside not udp lazy.....!!!"<<endl;

    	   	   	   if ( data_recv.id2== MY_TOKEN)  // circle completed, primary is the final estimate
						{


						/// if it is a store inst
							if(strcmp(inst.instruction,"store")==0)
							{
								// store the data itself
								DATA_STORE[data_recv.id1] = inst.DATA;

								///////// send OK to manager on TCP
								send_ok_manager();

								outfile_client<<"add "<<inst.DATA<<" with hash "<<"0x"<<hex<<data_recv.id1<<" to node "<<"0x"<<hex<<MY_TOKEN<<endl;
								//outfile_client<<"SENT OK to Manager, i have myself stored the data"  <<endl;

							}
							else					// it is a search instruction
							{
								if ( DATA_STORE.count(data_recv.id1) > 0 )    ///// key already exists with the node
																			// would only happen if it is a search inst
								{
									///////// send OK to manager on TCP
									send_ok_manager();

									//outfile_client<<"SENT OK to Manager, i have the data already"  <<endl;
									outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<MY_TOKEN<<" key PRESENT "<<endl;
								}
								else										//// no one has the data we are looking for

								{
									///////// send OK to manager on TCP
									char OK_msg[100];
									strcpy(OK_msg,"NOT_OK");
									if(send(sockfd_client, OK_msg, sizeof(OK_msg), 0) == -1)
									perror("send");

									//outfile_client<<"SENT NOT_OK to Manager, NO one has the data to be searched"  <<endl;
									outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<MY_TOKEN<<" key ABSENT "<<endl;
								}
							} /// end it is a search inst
						}  // end circle complete

						else   // circle still not complete
						{
							if(data_recv.id4 == 1)       // the node already has the data stored with it
													// would only be the case if stores-q is replying to a search inst.
							{

								MARSHALLING_UDP ext;
								ext.data.token=data_recv.token;
								ext.data.id1= data_recv.id1;

								ext.SEND((char*)"ext-stores-q",send_to);
								ext.RECEIVE(UDP_private);

								/*
								char OK_msg[100];
								strcpy(OK_msg,"OK");
								if(send(sockfd_client, OK_msg, sizeof(OK_msg), 0) == -1)
									perror("send");
								 */
								//outfile_client<<"SENT OK to Manager, found the data with nodeid:"<< data_recv.token<<endl;
								outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<data_recv.id2<<" key PRESENT "<<endl;

							}
							else		// the replying node doesn't hold the data:
					// two cases possible:
							//	a) it says that it is itself responsible for the data i.e token==id2
							//  b) gives another node which it thinks is responsible
							{
								//case (a):

								 //cout<<"there ......................"<<inst.instruction<<endl;

								if (data_recv.token == data_recv.id2)
								{
									cout<<"22222there ......................"<<inst.instruction<<" "<<inst.DATA<<endl;


								 if(strcmp(inst.instruction,"store")==0)
								{
										data.token = data_recv.token;
										data.id1= strlen(inst.DATA);
										data.id2=  data_recv.id1;
										strcpy(data.d1,inst.DATA);

										SEND((char*)"store-q",send_to);
								}
								 else
								 {

									 char OK_msg[100];
									 									strcpy(OK_msg,"NOT_OK");
									 									if(send(sockfd_client, OK_msg, sizeof(OK_msg), 0) == -1)
									 									perror("send");

									 outfile_client<<"search "<<inst.DATA<<" to node "<<"0x"<<hex<<data_recv.id2<<" key ABSENT "<<endl;
								 }
								}
								//case (b)
								else
								{
									data.token = data_recv.id2;
									data.id1= data_recv.id1;

									SEND((char*)"stores-q",data_recv.id3);

								}
							}// node doesn't have data itself
						}// end circle still not complete
		}
								return;

// update-q
		case 7:


					// decodes the message and updates according to the message
					buff=strtok(NULL,",");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
					if(MY_TOKEN==data_recv.token)
											{
												//outfile_client<<"token matches, Msg reached at correct destination"<<endl;
											}
										else
											{
											//outfile_client<<"token reached wrong destination"<<endl;
												return;
											}

					buff1=strtok(NULL,",");     // retrieving si
					data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
					buff2=strtok(NULL,",");     // retrieving sp
					data_recv.id2=(uint32_t)atoi(buff2);
					//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
					buff3=strtok(NULL,"\0");     // retrieving sp
					data_recv.id3=(uint32_t)atoi(buff3);
					//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;

					outfile_client<<ID_to_MESSAGE[7]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<dec<<data_recv.id2<<" "<<dec<<data_recv.id3<<")"<<endl;
				if( (STAGE.compare("2")==0) ||(STAGE.compare("3")==0)  )
				{
					if(data_recv.id3==0)       // if 0 then update predecessor
					{
						PRE.token=data_recv.id1;
						PRE.UDP_port=data_recv.id2;
						//outfile_client<<"updated pred to:"<<"0x"<<hex<<PRE.token<<"and port:"<<dec<<PRE.UDP_port<<endl;
					}
					if(data_recv.id3==1)	// if 1 then update successor
					{
						SUC.token=data_recv.id1;
						SUC.UDP_port=data_recv.id2;
						//outfile_client<<"updated suc to:"<<"0x"<<hex<<SUC.token<<"and port:"<<dec<<SUC.UDP_port<<endl;
					}


///////////////////////////////////
// replying with a update confirmation
///////////////////////////////////
					data.token=data_recv.token;
					data.id1=1;
					data.id2=data_recv.id1;
					data.id3=data_recv.id2;
					data.id4=data_recv.id3;

					SEND((char*)"update-r",send_to);

				} // end if stage 2 or 3
				else
				{
					// if finger tables
					update_q_FT(data_recv.token, data_recv.id1, data_recv.id2, data_recv.id3,send_to);
				}
				return;

//// store-q
		case 8:
					buff=strtok(NULL,",");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

					buff1=strtok(NULL,",");     // retrieving SL
					data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
					buff2=strtok(NULL,",");     // retrieving hash
					data_recv.id2=(uint32_t)atoi(buff2);
					//outfile_client<<"there ins store-q received case"<<endl;
					buff3=strtok(NULL,"\0");     // retrieving S
					strcpy(data_recv.d1,buff3);
					//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;


					outfile_client<<ID_to_MESSAGE[8]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<" "<<hex<<data_recv.id2<<" "<<data_recv.d1<<" "<<")"<<endl;

///////////////////////////////
//sending reply after storing the data
///////////////////////////////
					if(MY_TOKEN==data_recv.token)
					{
						//outfile_client<<"token matches, Msg reached at correct destination"<<endl;
					}
					else
					{
						//outfile_client<<"token reached wrong destination"<<endl;
						return;
					}



					 data_hash= data_recv.id2;



		if( (STAGE.compare("2")==0) ||(STAGE.compare("3")==0)  )
				{
					st=1;
				}
		else
		{
			st=2;
		}


		if (st==1)
		{
					if (!(((PRE.token<MY_TOKEN) && (data_hash <= MY_TOKEN  &&  data_hash > PRE.token)) || ((PRE.token > MY_TOKEN) && ((data_hash <= MY_TOKEN)|| ( MY_TOKEN > PRE.token)))))  // doesn't belong here

					{
						data.id1=0;
					}
		}

		else if (st==2)
		{
			if(LIES_BW(PREDECESSOR, MY_TOKEN, data_hash, (char*)"(]")==0)
			{
				data.id1=0;
			}
		}
				 if(DATA_STORE.count(data_hash)>0)     // already exists
					{
						data.id1=2;
					}
					else
					{
						data.id1=1;
						if (TKCC==1)			// corrupting the data
						{
							cout<<"^^^^^^^^^^^^!!!!!!!!!!!!!!!!!!!!!!! corrupting data - in "<<CLIENT_NAME<<endl;
							DATA_STORE[data_hash]= (char*)"nyah, nyah";
						}
						else
						{

							DATA_STORE[data_hash]=new char[100];
							strcpy(DATA_STORE[data_hash],data_recv.d1);
							outfile_client<<"stored "<< DATA_STORE[data_hash]<<" : "<<data_recv.d1<<" with hash "<<hex<<data_hash<<endl;
						}

					}

					//outfile_client<<"calculating reply to store-q, status decided is:"<<data.id1<<endl;
					//outfile_client<<"hash calculated is:"<<"0x"<<hex<<data_hash<<" stored:"<<DATA_STORE[data_hash]<<endl;
					data.token= data_recv.token;
					data.id2=data_recv.id1;
					data.id3=data_recv.id2;
					strcpy(data.d1,data_recv.d1);

					for( iterate = DATA_STORE.begin(); iterate != DATA_STORE.end(); iterate++ ) {
							    cout << CLIENT_NAME<<"******* " << hex<<iterate->first << "*******: " << iterate->second << endl;
							  }

					SEND((char*)"store-r",send_to);


					return;


/// store-r
		case 9:    		buff=strtok(NULL,",");
						data_recv.token=(uint32_t)atoi(buff);
						//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

						buff1=strtok(NULL,",");     // retrieving si
						data_recv.id1=(uint32_t)atoi(buff1);
						//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
						buff2=strtok(NULL,",");     // retrieving sp
						data_recv.id2=(uint32_t)atoi(buff2);
						buff3=strtok(NULL,",");     // retrieving sp
						data_recv.id3=(uint32_t)atoi(buff3);
						buff4=strtok(NULL,"\0");
						strcpy(data_recv.d1,buff4);    // string stored

						outfile_client<<ID_to_MESSAGE[9]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<" "<<dec<<data_recv.id2<<" "<<hex<<data_recv.id3<<" "<<data_recv.d1<<" "<<")"<<endl;
						data_hash=nonce_name_hash((uint32_t)(htonl(atoi(NONCE))),inst.DATA);
						outfile_client<<"add "<<inst.DATA<<" with hash "<<"0x"<<hex<<data_recv.id3<<" to node "<<"0x"<<hex<<data_recv.token<<endl;


/////////////////////////
//sending OK to manager
							send_ok_manager();

							//outfile_client<<ID_to_MESSAGE[9]<<" received"<<endl;
							//outfile_client<<"SENT OK to Manager, node : __ stored the data"<< data_recv.token<<endl;
							return;


		case 10:		buff=strtok(NULL,",");
						data_recv.token=(uint32_t)atoi(buff);
						//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

						buff1=strtok(NULL,",");     // retrieving si
						data_recv.id1=(uint32_t)atoi(buff1);
						//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
						buff2=strtok(NULL,",");     // retrieving sp
						data_recv.id2=(uint32_t)atoi(buff2);
						//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
						buff3=strtok(NULL,",");     // retrieving sp
						data_recv.id3=(uint32_t)atoi(buff3);
						buff4=strtok(NULL,"\0");     // retrieving sp
						data_recv.id4=(uint32_t)atoi(buff4);

				outfile_client<<ID_to_MESSAGE[10]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<" "<<"0x"<<hex<<data_recv.id2<<" "<<dec<<data_recv.id3<<" "<<dec<<data_recv.id4<<")"<<endl;
						return;

// replies for find_successor-q
		case 11:
					buff=strtok(NULL,"\0");
					data_recv.token=(uint32_t)atoi(buff);
						//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
					outfile_client<<ID_to_MESSAGE[11]<<" received ("<<"0x"<<hex<<data_recv.token<<")"<<endl;

		/////////////////////////////////////
		//sending appropriate reply
		/////////////////////////////////////


						//outfile_client<<"received message 1"<<endl;

						info= find_successor(data_recv.token);
						data.token= info.node_token;
						data.id1=info.node_port;
						SEND((char*)"find_successor-r",send_to);
						break;


// accepts find_successor-r and stores the returned value
		case 12:
					buff=strtok(NULL,",");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

					buff1=strtok(NULL,"\0");     // retrieving si
					data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
					outfile_client<<ID_to_MESSAGE[12]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<")"<<endl;
					break;


// replies for find_predecessor-q
        case 13:
        			buff=strtok(NULL,"\0");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
					outfile_client<<ID_to_MESSAGE[13]<<" received ("<<"0x"<<hex<<data_recv.token<<")"<<endl;

					//outfile_client<<"received message 1"<<endl;

					info= find_predecessor(data_recv.token);
					data.token= info.node_token;
					data.id1=info.node_port;
					SEND((char*)"find_predecessor-r",send_to);
					break;


// accepts find_predecessor-r and stores the returned value
        case 14:
        			buff=strtok(NULL,",");
        			data_recv.token=(uint32_t)atoi(buff);
        			//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

        			buff1=strtok(NULL,"\0");     // retrieving si
        			data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
        			outfile_client<<ID_to_MESSAGE[14]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<")"<<endl;
					break;

// replies for closest_preceding_finger-q
        case 15:
        			buff=strtok(NULL,"\0");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
					outfile_client<<ID_to_MESSAGE[15]<<" received ("<<"0x"<<hex<<data_recv.token<<")"<<endl;


					//outfile_client<<"received message 1"<<endl;
					info= closest_preceding_finger(data_recv.token);
					data.token= info.node_token;
					data.id1=info.node_port;
					SEND((char*)"closest_preceding_finger-r",send_to);
					break;


// accepts closest_preceding_finger-r and stores the returned value
        case 16:
        			buff=strtok(NULL,",");
        			data_recv.token=(uint32_t)atoi(buff);
        			//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

        			buff1=strtok(NULL,"\0");     // retrieving si
        			data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
        			outfile_client<<ID_to_MESSAGE[16]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<")"<<endl;
					break;


// accepts leaving-q and sends the next-data-q
        case 17:
        			buff=strtok(NULL,",");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

					buff1=strtok(NULL,"\0");     // retrieving si
					data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
					outfile_client<<ID_to_MESSAGE[17]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<")"<<endl;



					data.token= data_recv.id1;
					data.id1= data_recv.id1;
					SEND((char*)"next-data-q",send_to);

					break;

//accepts leaving-r and exits
        case 18:
        			buff=strtok(NULL,"\0");
        			data_recv.token=(uint32_t)atoi(buff);

        			outfile_client<<ID_to_MESSAGE[18]<<" received ("<<"0x"<<hex<<data_recv.token<<")"<<endl;
        			exit(1);

// accepts next-data-q and responds with the closest stored data to received id

        case 19:
        			buff=strtok(NULL,",");
        			data_recv.token=(uint32_t)atoi(buff);
        			//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

        			buff1=strtok(NULL,"\0");     // retrieving id
        			data_recv.id1=(uint32_t)atoi(buff1);
        			//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
        			outfile_client<<ID_to_MESSAGE[19]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<")"<<endl;

        			closest= PREDECESSOR ;
        			for ( iterate=DATA_STORE.begin() ; iterate != DATA_STORE.end(); iterate++ )
        			{
        					    //cout << (*IT).first << " => " << (*IT).second << endl;
        						uint32_t x=calculate((int64_t)data_recv.id1,(int64_t)((*iterate).first ),1);
        						uint32_t y=calculate((int64_t)data_recv.id1,(int64_t) closest,1);
        						if( x < y)
        						{
        							closest = (*iterate).first;
        						}
        			}

        			if (closest==PREDECESSOR)
        			{
        				data.id3= 0;
        				data.id2=PREDECESSOR;
        				strcpy(data.d1,"");
        			}
        			else
        			{
        				data.id2=closest;
        				data.id3=strlen(DATA_STORE[closest]);
        				strcpy(data.d1,DATA_STORE[closest]);
        			}
        			data.token= data_recv.token;
        			data.id1= data_recv.id1;


        			SEND((char*)"next-data-r",send_to);
        			break;


        case 20:

        				buff=strtok(NULL,",");
        				data_recv.token=(uint32_t)atoi(buff);  // di
        				//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

        				buff1=strtok(NULL,",");     // retrieving qid
        				data_recv.id1=(uint32_t)atoi(buff1);
        				//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
        				buff2=strtok(NULL,",");     // retrieving rid
        				data_recv.id2=(uint32_t)atoi(buff2);
        				//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
        				buff3=strtok(NULL,",");     // retrieving SL
        				data_recv.id3=(uint32_t)atoi(buff3);
        				buff4=strtok(NULL,"\0");     // retrieving S
        				strcpy(data_recv.d1,buff4);

        				outfile_client<<ID_to_MESSAGE[10]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<dec<<data_recv.id1<<" "<<"0x"<<hex<<data_recv.id2<<" "<<dec<<data_recv.id3<<" "<<data_recv.d1<<")"<<endl;

        				if (data_recv.id3==0)  //if SL=0
        				{
        					/////// update pred
        					PREDECESSOR = data_recv.id2;

        					/// update the suc of the pred as self



        				}
        				else
        				{
        					data.token= data_recv.token;
        					data.id1=data_recv.id2;
        					SEND((char*)"next-data-q",send_to);
        				}



        						return;

// replies for hello-predecessor -q received
      case 21:
        					buff=strtok(NULL,"\0");
        					data_recv.token=(uint32_t)atoi(buff);
        						//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;
        					outfile_client<<ID_to_MESSAGE[21]<<" received ("<<"0x"<<hex<<data_recv.token<<")"<<endl;
        							if(MY_TOKEN==data_recv.token)
        								{
        									//outfile_client<<"token matches, Msg reached at correct destination"<<endl;
        								}
        							else
        								{
        								//outfile_client<<"token reached wrong destination"<<endl;
        									return;
        								}
        		/////////////////////////////////////
        		//sending appropriate reply
        		/////////////////////////////////////
        							if( (STAGE.compare("2")==0) ||(STAGE.compare("3")==0)  )
        						{
        							data.id1= PRE.token;
        							data.id2=PRE.UDP_port;
        						}
        						  ///  use finger tables

        						else if( (STAGE.compare("6")==0) ||(STAGE.compare("7")==0)  )
        										{
        											data.id1= PREDECESSOR;
        											data.id2=PREDECESSOR_PORT;
        										}


        						//outfile_client<<"received message 1"<<endl;
        						data.token= MY_TOKEN;
        						SEND((char*)"hello-predecessor-r",send_to);
        						break;


// decodes the message and stores it in data_received - token,id1,id2 and returns
  case 22:
        					buff=strtok(NULL,",");
        					data_recv.token=(uint32_t)atoi(buff);
        					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

        					buff1=strtok(NULL,",");     // retrieving si
        					data_recv.id1=(uint32_t)atoi(buff1);
        					//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
        					buff2=strtok(NULL,"\0");     // retrieving sp
        					data_recv.id2=(uint32_t)atoi(buff2);
        					//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
        					outfile_client<<ID_to_MESSAGE[22]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<dec<<data_recv.id2<<")"<<endl;
        					return;


// update-double-successor-q- get .token & .id1
  case 23:
							buff=strtok(NULL,",");
							data_recv.token=(uint32_t)atoi(buff);
							//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

							buff1=strtok(NULL,"\0");     // retrieving si
							data_recv.id1=(uint32_t)atoi(buff1);
							//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;

							outfile_client<<ID_to_MESSAGE[23]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<")"<<endl;

							//// updating the double succ and its port

							DOUBLE_SUCC=data_recv.token;
							DOUBLE_SUCC_PORT=data_recv.id1;

							data.token=data_recv.token;
							data.id1=data_recv.id1;

							SEND((char*)"update-double-successor-r",send_to);
							return;

// update-double-successor-r
  case 24:
  							buff=strtok(NULL,",");
  							data_recv.token=(uint32_t)atoi(buff);
  							//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

  							buff1=strtok(NULL,"\0");     // retrieving si
  							data_recv.id1=(uint32_t)atoi(buff1);
  							//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;

  							outfile_client<<ID_to_MESSAGE[24]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<")"<<endl;
  							return;

///// ext-stores-q
		case 25:     // decodes the message and stores it in data_received - token,id1,id2 and returns
					buff=strtok(NULL,",");
					data_recv.token=(uint32_t)atoi(buff);
					//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

					buff1=strtok(NULL,"\0");     // retrieving di
					data_recv.id1=(uint32_t)atoi(buff1);
					//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;

					outfile_client<<ID_to_MESSAGE[25]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<")"<<endl;
					//outfile_client<<"in stores-QQQ -> "<<inst.instruction<<" "<<inst.DATA<<endl;


					stores_q_ft(data_recv.token,data_recv.id1,send_to,1);



								return;

/// ext-stores-r		/////// primary node is the only one ever receiving this msg
		case 26:

								buff=strtok(NULL,",");
								data_recv.token=(uint32_t)atoi(buff);
								//outfile_client<<"ni received is: "<<"0x"<<hex<<data_recv.token<<endl;

								buff1=strtok(NULL,",");     // retrieving di
								data_recv.id1=(uint32_t)atoi(buff1);
								//outfile_client<<"successor token recvd is:"<<"0x"<<hex<<data_recv.id1;
								buff2=strtok(NULL,",");     // retrieving ri
								data_recv.id2=(uint32_t)atoi(buff2);
								//outfile_client<<"successor PORT recvd is:"<<"0x"<<hex<<data_recv.id2;
								buff3=strtok(NULL,",");     // retrieving rp
								data_recv.id3=(uint32_t)atoi(buff3);
								buff4=strtok(NULL,",");     // retrieving has
								data_recv.id4=(uint32_t)atoi(buff4);
								buff5=strtok(NULL,",");     // retrieving has
								data_recv.id5=(uint32_t)atoi(buff5);
								strcpy(data_recv.d1,strtok(NULL,"\0"));

						outfile_client<<ID_to_MESSAGE[26]<<" received ("<<"0x"<<hex<<data_recv.token<<" "<<"0x"<<hex<<data_recv.id1<<" "<<"0x"<<hex<<data_recv.id2<<" "<<dec<<data_recv.id3<<" "<<dec<<data_recv.id4<<" "<<dec<<data_recv.id5<<" "<<data_recv.d1<<")"<<endl;
						//outfile_client<<"in ext-stores-r -> "<<inst.instruction<<" "<<inst.DATA<<endl;

						if (global_search_counter==0)
						{
							//outfile_client<<"inside global counter==0,stored "<<endl;
							cout<<"inside global counter==0, stored "<<endl;
							strcpy(search1_data,data_recv.d1);
							search1_node=data_recv.token;
							global_search_counter++;
							//outfile_client<<"inside global counter==0,stored "<<search1_data<<endl;
							cout<<"inside global counter==0, stored "<<search1_data<<endl;
						}
						else

						{
							//outfile_client<<"inside global counter==1, searches are"<<data_recv.d1<<" "<<search1_data<<endl;
							cout<<"inside global counter==1, searches are"<<data_recv.d1<<" "<<search1_data<<endl;
							if (strcmp(data_recv.d1,search1_data)==0)
							{
								outfile_client<<"search "<<data_recv.d1<<" to node "<<hex<<search1_node<<" and "<<hex<<data_recv.token<<" key PRESENT and VERIFIED"<<endl;
								cout<<"search "<<data_recv.d1<<" to node "<<hex<<search1_node<<" and "<<hex<<data_recv.token<<" key PRESENT and VERIFIED"<<endl;
							}
							else
							{
								outfile_client<<"search "<<data_recv.d1<<hex<<" to node "<<search1_node<<" and "<<hex<<data_recv.token<<" key PRESENT but DISAGREE"<<endl;
								cout<<"search "<<data_recv.d1<<" to node "<<hex<<search1_node<<" and "<<hex<<data_recv.token<<" key PRESENT but DISAGREE"<<endl;
							}
							char OK_msg[100];
															strcpy(OK_msg,"OK");
															if(send(sockfd_client, OK_msg, sizeof(OK_msg), 0) == -1)
																perror("send");

								//outfile_client<<"SENT OK to Manager, "<<endl;
						}

						return;




}
}





uint32_t nonce_name_hash(uint32_t nonce, char *name)
{

/*
	if (strcmp(name,"alpha")==0)
		{
		return 0;
		}
		else if (strcmp(name,"bravo")==0)
		{
		return 3;
		}
		else if (strcmp(name,"charlie")==0)
		{
		return 0x4fffffff;
		}
		else if (strcmp(name,"echo")==0)
		{
			return 7;
		}
		else if (strcmp(name,"gamma")==0)
		{
			return 0xa9367d92;
		}

		else
		{
*/

	//cout<<nonce<<name<<endl;
	int name_length = strlen(name);
	int buffer_length = sizeof(int) + name_length;
	unsigned char *buffer = (unsigned char *)malloc(buffer_length);

    memcpy(buffer,(void *)&nonce,sizeof(int));
    memcpy(buffer+sizeof(int),name,strlen(name));

	uint32_t result = projb_hash(buffer, buffer_length);
	free(buffer);

	return result;
		//}




}


void position_in_ring()
{


	if (strcmp(CLIENT_NAME,FS)==0)
	{
		SUC.token=0;
		SUC.UDP_port=0;
		PRE.token=0;
		PRE.UDP_port=0;
		//outfile_client<<"i am the first client, succ and pred are set to 0"<<endl;
	}
	else
	{
		uint32_t TOKEN= nonce_name_hash(atoi(NONCE),FS);
		//outfile_client<<"generated token"<<"0x"<<hex<<TOKEN<<" for first node with "<<NONCE<<" and "<<FS<<endl;

		uint32_t previous_token,current_token,previous_port,current_port;

		uint32_t DUMMY_TOKEN= TOKEN;
		uint32_t DUMMY_FP= atoi(FP);




		MARSHALLING_UDP *obj = new MARSHALLING_UDP ;
		obj->data.token=TOKEN;            // token for the first node
		obj->SEND((char*)"successor-q",atoi(FP));
		obj->RECEIVE(UDP_private);

		previous_token=TOKEN;    // the token of first node
		current_token= obj->data_recv.id1; // token of first node's succesor
		previous_port=(uint32_t)atoi(FP);
		current_port=obj->data_recv.id2;
//////////////////////////////////////
// when it is the second node to enter
//////////////////////////////////////

					if (obj->data_recv.id1 ==0)
					{
						//outfile_client<<"no one has joined the first node"<<endl;
						SUC.token=TOKEN;    // making the first node the successor
						PRE.token=TOKEN;	// making the first node the predecessor
						SUC.UDP_port=(uint32_t)atoi(FP);
						PRE.UDP_port=(uint32_t)atoi(FP);
						//outfile_client<<"i am the 2nd node, updated suc and pred: "<<"0x"<<hex<<SUC.token<<dec<<SUC.UDP_port;
						MARSHALLING_UDP *update_suc_pred = new MARSHALLING_UDP ;


						update_suc_pred->data.token= TOKEN;
						update_suc_pred->data.id1= MY_TOKEN;
						update_suc_pred->data.id2= DGRAM_PORT;
						update_suc_pred->data.id3= 0;          // update predecessor
						update_suc_pred->SEND((char*)"update-q",atoi(FP));
						update_suc_pred->RECEIVE(UDP_private);

						update_suc_pred->data.token= TOKEN;
						update_suc_pred->data.id1= MY_TOKEN;
						update_suc_pred->data.id2= DGRAM_PORT;
						update_suc_pred->data.id3= 1;          // update successor
						update_suc_pred->SEND((char*)"update-q",atoi(FP));
						update_suc_pred->RECEIVE(UDP_private);

						//outfile_client<<"settled in  the ring"<<endl;
						return;
					}
//////////////////////////////////////
// other nodes >=3
//////////////////////////////////////
					else
					{
						while(1)
						{
							uint32_t PREVIOUS_token,CURRENT_token,PREVIOUS_port,CURRENT_port;
							MARSHALLING_UDP *obj1 = new MARSHALLING_UDP ;



									obj1->data.token=DUMMY_TOKEN;            // token for the first node
									obj1->SEND((char*)"predecessor-q",DUMMY_FP);
									obj1->RECEIVE(UDP_private);

									CURRENT_token=DUMMY_TOKEN;    // the token of first node
									PREVIOUS_token= obj1->data_recv.id1; // token of first node's predecessor
									CURRENT_port=DUMMY_FP;
									PREVIOUS_port=obj1->data_recv.id2;

									//cout<<"previous:"<<hex<<PREVIOUS_token<<"current: "<<hex<<CURRENT_token<<endl;
									if(CURRENT_token > PREVIOUS_token)
									{
										DUMMY_TOKEN= PREVIOUS_token;
										DUMMY_FP= PREVIOUS_port;

										continue;
									}
									else if (CURRENT_token < PREVIOUS_token)
									{

										previous_token=obj1->data_recv.id1;    // the token of first node
										current_token= TOKEN; // token of first node's succesor
										previous_port=obj1->data_recv.id2;
										current_port=(uint32_t)atoi(FP);
										break;

									}


						}

						for (int w=0;;w++)
						{
							if (((MY_TOKEN > previous_token) && (MY_TOKEN < current_token))|| (current_token<previous_token))  //if found the rite position
							{
								SUC.token=current_token;    // making the first node the successor
								PRE.token=previous_token;	// making the first node the predecessor
								SUC.UDP_port=current_port;
								PRE.UDP_port=previous_port;
								//outfile_client<<"i am one of >=3 node, updated suc :"<<"0x"<<hex<<SUC.token<<dec<<SUC.UDP_port<<endl;
								//outfile_client<<"i am one of >=3 node, updated PRE :"<<"0x"<<hex<<PRE.token<<dec<<PRE.UDP_port<<endl;


								MARSHALLING_UDP *update_suc_pred = new MARSHALLING_UDP ;


								update_suc_pred->data.token= current_token;
								update_suc_pred->data.id1= MY_TOKEN;
								update_suc_pred->data.id2= DGRAM_PORT;
								update_suc_pred->data.id3= 0;          // update predecessor
								update_suc_pred->SEND((char*)"update-q",current_port);
								update_suc_pred->RECEIVE(UDP_private);

								update_suc_pred->data.token= previous_token;
								update_suc_pred->data.id1= MY_TOKEN;
								update_suc_pred->data.id2= DGRAM_PORT;
								update_suc_pred->data.id3= 1;          // update successor
								update_suc_pred->SEND((char*)"update-q",previous_port);
								update_suc_pred->RECEIVE(UDP_private);

								//outfile_client<<"settled in  the ring"<<endl;
								return;
							}

							else             ///// move to next node and update current and previous
							{

								MARSHALLING_UDP *obj = new MARSHALLING_UDP ;
								obj->data.token= current_token;            // token for the first node
								obj->SEND((char*)"successor-q",current_port);
								obj->RECEIVE(UDP_private);
								previous_token=current_token;
								previous_port=current_port;
								current_token=obj->data_recv.id1;
								current_port=obj->data_recv.id2;
							}

						}
					}
	}
}


void send_ok_manager()
{
	char OK_msg[100];
	strcpy(OK_msg,"OK");
	if(send(sockfd_client, OK_msg, sizeof(OK_msg), 0) == -1)
		perror("send");
}

void intitalize_msgs(void)
{

	ID_to_MESSAGE[1]=(char*)"successor-q";
	ID_to_MESSAGE[2]=(char*)"successor-r";
	ID_to_MESSAGE[3]=(char*)"predecessor-q";
	ID_to_MESSAGE[4]=(char*)"predecessor-r";
	ID_to_MESSAGE[5]=(char*)"stores-q";
	ID_to_MESSAGE[6]=(char*)"stores-r";
	ID_to_MESSAGE[7]=(char*)"update-q";
	ID_to_MESSAGE[8]=(char*)"store-q";
	ID_to_MESSAGE[9]=(char*)"store-r";
	ID_to_MESSAGE[10]=(char*)"update-r";
	ID_to_MESSAGE[11]=(char*)"find_successor-q";
	ID_to_MESSAGE[12]=(char*)"find_successor-r";
	ID_to_MESSAGE[13]=(char*)"find_predecessor-q";
	ID_to_MESSAGE[14]=(char*)"find_predecessor-r";
	ID_to_MESSAGE[15]=(char*)"closest_preceding_finger-q";
	ID_to_MESSAGE[16]=(char*)"closest_preceding_finger-r";
	ID_to_MESSAGE[17]=(char*)"leaving-q";
	ID_to_MESSAGE[18]=(char*)"leaving-r";
	ID_to_MESSAGE[19]=(char*)"next-data-q";
	ID_to_MESSAGE[20]=(char*)"next-data-r";
	ID_to_MESSAGE[21]=(char*)"hello-predecessor-q";
	ID_to_MESSAGE[22]=(char*)"hello-predecessor-r";
	ID_to_MESSAGE[23]=(char*)"update-double-successor-q";
	ID_to_MESSAGE[24]=(char*)"update-double-successor-r";
	ID_to_MESSAGE[25]=(char*)"ext-stores-q";
	ID_to_MESSAGE[26]=(char*)"ext-stores-r";


	return;
}


//////////////////////////////////////////
// FINGER TABLES
//////////////////////////////////////////

void position_in_ring_FT()
{
	//outfile_client<<"inside osition_in_ring"<<endl;
	initialize_fingertable();
	if (strcmp(CLIENT_NAME,FS)==0)  // it is the first node
		{
		//outfile_client<<"i am the first client - find positoin"<<endl;
		 	 for (int i=1;i<33;i++)
		 	 {
		 		FT[i].NODE_TOKEN= MY_TOKEN;
		 		FT[i].udp_port= DGRAM_PORT;

		 	 }
		 	PREDECESSOR=MY_TOKEN;
		 	PREDECESSOR_PORT=DGRAM_PORT;
		}
	else
	{
		populate_fingertable();

		update_others();

	}

//outfile_client<<"settled inside the ring"<<endl;

}

//////////////////////////////////////
// ask this node to find id's successor. A random
//////////////////////////////////////
details find_successor(uint32_t id)
{
	//*outfile_client<<"inside find_successor, received: "<<hex<<id<<endl;
	 details info= find_predecessor(id);
	 details info1= FIND_NODE_SUCC(info.node_token,info.node_port);

	 ////////////////////////////////
	 // send succesor -q msg to node -pred and return the answer
	 ////////////////////////////////
	 //*outfile_client<<"returning find_successor, : "<<hex<<info1.node_token<<" "<<dec<<info1.node_port<<endl;
	 return info1;


	// return pred.successor;
}

details find_predecessor(uint32_t id)
{
	//*outfile_client<<"inside find_predecessor, received: "<<hex<<id<<endl;
	 uint32_t DUMMY_TOKEN, DUMMY_TOKEN_SUCC,DUMMY_PORT;

	 DUMMY_TOKEN= MY_TOKEN;

	 DUMMY_TOKEN_SUCC= SUCCESSOR;
	 //*outfile_client<<"--> (]: DUMMY: "<<hex<<DUMMY_TOKEN<<"DUMMY_SUCCE:"<<hex<<DUMMY_TOKEN_SUCC<<" id:"<<hex<<id<<endl;

	 while (LIES_BW(DUMMY_TOKEN,DUMMY_TOKEN_SUCC,id,(char*)"(]")==0)
	 {
		 //*outfile_client<<"inside lies B/W :DUMMY: "<<hex<<DUMMY_TOKEN<<"DUMMY_SUCCE:"<<hex<<DUMMY_TOKEN_SUCC<<" id:"<<hex<<id<<endl;
		 //outfile_client<<"inside liesB/W"<<endl;
		 if(DUMMY_TOKEN==MY_TOKEN)
		 {
			 //*outfile_client<<"calling my own closest_preced_fing,  "<<endl;
			 details info;
			 info=closest_preceding_finger(id);
			 if (info.node_token==DUMMY_TOKEN)
			 {
				 //*outfile_client<<"returning the same node -- returning "<<endl;
				 return info;
			 }
			 else
			 {

			 DUMMY_TOKEN= info.node_token;
			 DUMMY_PORT= info.node_port;
			 //outfile_client<<"inside else 1 of find_pred"<<" DUMMY_TOK: "<<hex<<DUMMY_TOKEN<<" PORT: "<<dec<<DUMMY_PORT<<endl;
			 }

		 }
		 else
		 {
			 //*outfile_client<<"calling closest_preced_fing,on node  "<<hex<<DUMMY_TOKEN<<" on port: "<<DUMMY_PORT<<endl;
			 MARSHALLING_UDP obj;
			 obj.data.token= id;
			 obj.SEND((char*)"closest_preceding_finger-q",DUMMY_PORT);
			 obj.RECEIVE(UDP_private);
			 if (obj.data_recv.token==DUMMY_TOKEN)
						 {
							 //*outfile_client<<"returning the same node -- returning "<<endl;
							 details infor;
							 infor.node_token=obj.data_recv.token;
							 infor.node_port=obj.data_recv.id1;
							 return infor;
						 }
			 else
			 {
			 DUMMY_TOKEN= obj.data_recv.token;
			 DUMMY_PORT=obj.data_recv.id1;
			 }
		 }

	 }

	 details info1;
	 info1.node_token=DUMMY_TOKEN;
	 info1.node_port=DUMMY_PORT;
	 //*outfile_client<<"outside all conditions-returning find_predecessor, : "<<hex<< info1.node_token<<" "<<dec<< info1.node_port<<endl;
	 return info1;
}

details closest_preceding_finger(uint32_t id)
{
	//*outfile_client<<"inside closest_preced_fing, received: "<<hex<<id<<endl;
	 for (int i=32 ; i>=1;i-- )
	 {
		 //outfile_client<<"MY_token: "<<hex<<MY_TOKEN<<"id:"<<hex<<id<<" FT[i].NODE_TOKEN: "<<hex<<FT[i].NODE_TOKEN<<endl;
		 if (LIES_BW(MY_TOKEN, id, FT[i].NODE_TOKEN,(char*)"()")==1)
		 {
			 details info;
			 info.node_token= FT[i].NODE_TOKEN;
			 info.node_port= FT[i].udp_port;
			 //*outfile_client<<"returning from inside closest_preced_fing, returning: "<<hex<<info.node_token<<" "<<dec<<info.node_port<<" from index of FT:"<<dec<<i<<endl;
			 return info;
		 }
	 }
	 details info1;
	 info1.node_token=MY_TOKEN;
	 info1.node_port= DGRAM_PORT;
	 //*outfile_client<<"returning from outside closest_preced_fing, returning: "<<hex<<info1.node_token<<" "<<dec<<info1.node_port<<endl;
	 return info1;
}



void populate_fingertable()
{
	//*outfile_client<<"inside populating table"<<endl;
	MARSHALLING_UDP obj;
	obj.data.token= FT[1].INTERVAL_START_including;
	obj.SEND((char*)"find_successor-q",atoi(FP));
	obj.RECEIVE(UDP_private);

	FT[1].NODE_TOKEN= obj.data_recv.token;
	FT[1].udp_port= obj.data_recv.id1;

	find_double_succ();

	//*outfile_client<<"updated 1st finger: "<<hex<<SUCCESSOR<<" "<<dec<<SUCCESSOR_port<<endl;

	////send predecessor msg to SUCCESSOR node to update its own predecessor
	MARSHALLING_UDP pre;
	pre.data.token= SUCCESSOR;
	pre.SEND((char*)"predecessor-q",SUCCESSOR_port);
	pre.RECEIVE(UDP_private);

	PREDECESSOR= pre.data_recv.id1;
	PREDECESSOR_PORT= pre.data_recv.id2;

	//*outfile_client<<"received pred info from succesor"<<hex<<PREDECESSOR<<" "<<dec<<PREDECESSOR_PORT<<endl;

	//updating the predecessor of the successor node to itself

	MARSHALLING_UDP update_suc;
	update_suc.data.token= SUCCESSOR;
	update_suc.data.id1= MY_TOKEN;
	update_suc.data.id2= DGRAM_PORT;
	update_suc.data.id3=0;
	update_suc.SEND((char*)"update-q",SUCCESSOR_port);
	update_suc.RECEIVE(UDP_private);

	for(int i=1; i< 32; i++)
	{
		//*outfile_client<<"before ENTERING:::: "<<hex<<MY_TOKEN<<"-->"<<hex<<FT[i].NODE_TOKEN<<"  "<<hex<<FT[i+1].INTERVAL_START_including<<endl;


		if (LIES_BW(MY_TOKEN,FT[i].NODE_TOKEN,FT[i+1].INTERVAL_START_including, (char*)"[)")==1)
				{

					FT[i+1].NODE_TOKEN= FT[i].NODE_TOKEN;
					FT[i+1].udp_port= FT[i].udp_port;
					//*outfile_client<<"		1-updated: index"<<dec<<i+1<<" to: "<<hex<<FT[i+1].NODE_TOKEN<<endl;
				}
		else
		{
			//outfile_client<<"in 2nd"<<endl;
			MARSHALLING_UDP pt;
			pt.data.token= FT[i+1].INTERVAL_START_including;
			pt.SEND((char*)"find_successor-q", atoi(FP));
			pt.RECEIVE(UDP_private);

			FT[i+1].NODE_TOKEN= pt.data_recv.token;
			FT[i+1].udp_port= pt.data_recv.id1;
			//*outfile_client<<"		2-updated: index"<<dec<<i+1<<" to: "<<hex<<FT[i+1].NODE_TOKEN<<endl;
		}
	}
	//find_double_succ();
	return;

}

void initialize_fingertable(void)
 {
	//*outfile_client<<"inside initialize table"<<endl;
	 for (int i=1;i<33;i++)
	 {
		 FT[i].INTERVAL_START_including= calculate_mod((int64_t)MY_TOKEN,i-1,1);
		 if (i==32)
		 {
			 FT[i].INTERVAL_END= MY_TOKEN; 	  // all the way back to self
		 }
		 else
		 {
			 FT[i].INTERVAL_END= calculate_mod((int64_t)MY_TOKEN, i,1);   // start of the next finger
		 }

		 FT[i].NODE_TOKEN=0;
		 FT[i].udp_port=0;
		 //*outfile_client<<"index: "<<dec<<i<< " start: "<<hex<<  FT[i].INTERVAL_START_including<<" end: "<<hex<<FT[i].INTERVAL_END<<endl;

	 }
	 //outfile_client<<"returning initialize table"<<endl;
 }

void update_others()

{
	//*outfile_client<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~inside updating others"<<endl;
	for(int i=1;i<33;i++)
	{
		/// find last node p whose ith finger might be n


		uint32_t temp=  calculate_mod((int64_t)MY_TOKEN,i-1,0);
		details p= find_predecessor(temp);


		if(p.node_token== MY_TOKEN)
		{
			//update_q_FT(MY_TOKEN,MY_TOKEN,DGRAM_PORT,i,0);
			return;
		}

		MARSHALLING_UDP prev;
					prev.data.token= p.node_token;
					prev.data.id1= MY_TOKEN;
					prev.data.id2= DGRAM_PORT;
					prev.data.id3= i;
					prev.SEND((char*)"update-q",p.node_port);

					if (i==1)
					{
						MARSHALLING_UDP reply_doublesucc;
						//outfile_client<<"inside update others-> waiting for successor-q so that my pred can update his double suc"<<endl;
						reply_doublesucc.RECEIVE(UDP_private);

						if(p.node_token == SUCCESSOR)
						{
							//outfile_client<<"i am the second node in the ring -> thus waiting for an double suc update from my pred"<<endl;
							MARSHALLING_UDP recv_update_double;
							recv_update_double.RECEIVE(UDP_private);





						}
					}

					prev.RECEIVE(UDP_private);   // one for recursive call back
					//prev.RECEIVE(UDP_private);

	}
	//*outfile_client<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~returning from updating others"<<endl;
}


 int LIES_BW(uint32_t first, uint32_t second, uint32_t test_token, char* brackets)
  {

	 if (strcmp(brackets,"()")==0)
	 {
		// outfile_client<<"in lies_bw()"<<endl;
		  if (((first< second) && (test_token < second  &&  test_token > first)) || ((first > second) && ((test_token < second) || ( test_token > first)) ))
		  {
		//	  outfile_client<<"returning 1"<<endl;
			  return 1;
		  }
		  else
		  {
			//  outfile_client<<"returning 0"<<endl;
			  return 0;
		  }
	 }
	 else if (strcmp(brackets,"(]")==0)
	 {
		 if(first==second && test_token==second)
			 {
			 	 return 1;
			 }

		 //outfile_client<<"in lies_bw(]"<<endl;
		 if (((first< second) && (test_token <= second  &&  test_token > first)) || ((first > second) && ((test_token <= second) || ( test_token > first)) ))
		 		  {
		 //outfile_client<<"returning 1"<<endl;
		 			  return 1;
		 		  }
		 		  else
		 		  {
		 			// outfile_client<<"returning 0"<<endl;
		 			  return 0;
		 		  }
	 }
	 else if (strcmp(brackets,"[)")==0)
	 	 {
		 if(first==second && test_token==first)
		 			 {
		 			 	 return 1;
		 			 }
		 //outfile_client<<"in lies_bw[)"<<endl;
	 		 if (((first< second) && (test_token < second  &&  test_token >= first)) || ((first > second) && ((test_token < second) || ( test_token >= first)) ))
	 		 		  {
	 		 //outfile_client<<"returning 1"<<endl;
	 		 			  return 1;
	 		 		  }
	 		 		  else
	 		 		  {
	 		 	//		 outfile_client<<"returning 0"<<endl;
	 		 			  return 0;
	 		 		  }
	 	 }
return 0;
  }

details FIND_NODE_SUCC(uint32_t NODE, int NODE_port)
 {
	  details info;
	  if(MY_TOKEN==NODE)
	  {
		  //outfile_client<<"this is on the same node"<<endl;
		  info.node_token= MY_TOKEN;
		  info.node_port=DGRAM_PORT;
		  return info;
	  }
	 MARSHALLING_UDP obj;
	 obj.data.token= NODE;
	 obj.SEND((char*)"successor-q",NODE_port);

	 obj.RECEIVE(UDP_private);


	 info.node_token= obj.data_recv.id1;    /// token of the successor;
	 info.node_port= obj.data_recv.id2; 	/// port of successor

	 return info;
 }

void update_q_FT(uint32_t ni, uint32_t si, uint32_t sp, uint32_t i, int send_to)
{
	//*outfile_client<<"INSIDE UPDATE ***********************"<<endl;
	MARSHALLING_UDP obj;
	uint32_t TOKEN= nonce_name_hash(atoi(NONCE),FS);


	if (ni== MY_TOKEN)
	{

	}
	else
	{
		//*outfile_client<<" update-q request sent to the wrong node"<<endl;
		return;
	}



	if (i==0)
	{

		PREDECESSOR= si;
		PREDECESSOR_PORT=sp;

		//outfile_client<<"updated my predecessor to "<<hex<<PREDECESSOR<<" and port: "<<dec<<PREDECESSOR_PORT<<endl;
	}
	else if(i>0)
	{
		//SUCCESSOR= si;
		//SUCCESSOR_port=sp;
		//outfile_client<<" outside ....LIES_BW: "<<hex<<MY_TOKEN<<" ->"<<hex<<FT[i].NODE_TOKEN<<" "<<hex<<si<< endl;


		if ((LIES_BW(MY_TOKEN,FT[i].NODE_TOKEN,si,(char*)"[)")==1) || (MY_TOKEN==FT[i].NODE_TOKEN))
		{
			//*outfile_client<<"updating the finger entry and recursively contacting the previous node"<<endl;
			FT[i].NODE_TOKEN= si;
			FT[i].udp_port=sp;
			//outfile_client<<"updated myfinger!!!!!!!!!!  "<<dec<<i<<"to: "<<hex<<si<<" and port: "<<dec<<sp<<endl;

			///// if going back to the same node which initiated update - return;
			if(i==1)
			{
				//outfile_client << "###################i==1 in update-q-> also updating my double suc"<<endl;
			find_double_succ();

			MARSHALLING_UDP update_d_succ;
			update_d_succ.data.token= SUCCESSOR;
			update_d_succ.data.id1=SUCCESSOR_port;
			//outfile_client<<"#########now updating the double suc of my pred"<<endl;

			update_d_succ.SEND((char*)"update-double-successor-q",PREDECESSOR_PORT);

			update_d_succ.RECEIVE(UDP_private);

			}


			if (PREDECESSOR==si)
				{
					//*outfile_client<<"it has reached me again ^^^^^^^^^^^^^- ABORT!"<<endl;

											obj.data.token= ni;
											obj.data.id1=1;
											obj.data.id2=si;
											obj.data.id3=sp;
											obj.data.id4=i;

											obj.SEND((char*)"update-r",send_to);
											//find_double_succ();
											return;
				}

			if(send_to!=0)
			{
				////// update previous nodes to me recursively
				MARSHALLING_UDP prev;
				prev.data.token= PREDECESSOR;
				prev.data.id1= si;
				prev.data.id2= sp;
				prev.data.id3= i;
				prev.SEND((char*)"update-q",PREDECESSOR_PORT);
				prev.RECEIVE(UDP_private);
			}


		}
	}


	if (i!=0 &&(LIES_BW(MY_TOKEN,FT[i].NODE_TOKEN,si,(char*)"[)")!=1  || (MY_TOKEN!=FT[i].NODE_TOKEN)))
	{
	//*outfile_client<<" just replying without updating the finger entry"<<endl;
	obj.data.id1=0;
	}
	else
	{
		obj.data.id1=1;
	}


	if(send_to!=0)
	{

						obj.data.token= ni;

						obj.data.id2=si;
						obj.data.id3=sp;
						obj.data.id4=i;

						obj.SEND((char*)"update-r",send_to);
	}

	//find_double_succ();
	return;
}

uint32_t calculate_mod(int64_t n, int i, int flag)
{
	int64_t temp;
	if (flag==1)
			{
	 temp= ((int64_t)( n+ ((int64_t)1<<i)) % (int64_t) ( (int64_t)1<<32));
	 if(temp < 0)
	 {
		 temp=temp + (int64_t)( (int64_t)1<<32);
	 }
			}
	else
	{
		temp= ((int64_t)( n- ((int64_t)1<<i)) % (int64_t)( (int64_t)1<<32));
		 if(temp < 0)
			 {
			 temp=temp + (int64_t)( (int64_t)1<<32);
			 }
	}
	//outfile_client<<"------------------returning from inside mod: "<<(uint32_t)temp<<endl;
	return (uint32_t)temp;

}

uint32_t calculate(int64_t x,int64_t y , int flag)
{
	int64_t temp;
	if (flag==1)
			{
	 temp= ((int64_t)( x+ y) % (int64_t) ( (int64_t)1<<32));
	 if(temp < 0)
	 {
		 temp=temp + (int64_t)( (int64_t)1<<32);
	 }
			}
	else
	{
		temp= ((int64_t)( x- y) % (int64_t)( (int64_t)1<<32));
		 if(temp < 0)
			 {
			 temp=temp + (int64_t)( (int64_t)1<<32);
			 }
	}
	//outfile_client<<"------------------returning from inside mod: "<<(uint32_t)temp<<endl;
	return (uint32_t)temp;

}


details scan_FT(uint32_t data_hash)
{
	//outfile_client<<"in scan"<<endl;
	//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$ "<<inst.instruction<<" "<<inst.DATA<<endl;
	//strcpy(instruction,inst.instruction);
	//strcpy(DATA,inst.DATA);
	cout<<"CLIENT: "<<CLIENT_NAME<<"in scan ... received data_hash:"<<hex<<data_hash<<endl;
	details info;
	for(int i=1;i<33;i++)
	{

		if (LIES_BW(FT[i].INTERVAL_START_including,FT[i].INTERVAL_END,data_hash,(char*)"[)")==1)
		{

			info.node_token=FT[i].NODE_TOKEN;
			info.node_port=FT[i].udp_port;
			//outfile_client<<"my estimate: "<< hex<<info.node_token<<" on port: "<<dec<<info.node_port<<endl;
			cout<<"CLIENT: "<<CLIENT_NAME<<" my estimate: "<< hex<<info.node_token<<" on port: "<<dec<<info.node_port<<endl;
			if(info.node_token==MY_TOKEN)
			{
				return info;
			}
			details verified;
			verified=verify_FT(info.node_token,info.node_port,data_hash);
			return verified;
		}
	}
	info.node_token=SUCCESSOR;
	info.node_port=SUCCESSOR_port;
	//outfile_client<<"my estimate: "<< hex<<info.node_token<<" on port: "<<dec<<info.node_port<<endl;
				cout<<"CLIENT: "<<CLIENT_NAME<<" my estimate: "<< hex<<info.node_token<<" on port: "<<dec<<info.node_port<<endl;
	details verified1;
	verified1=verify_FT(info.node_token,info.node_port,data_hash);
	return verified1;

}


/*
details scan_FT(uint32_t data_hash)
{
        //outfile_client<<"in scan"<<endl;
        details info;
        for(int i=1;i<33;i++)
        {
                if (LIES_BW(FT[i].INTERVAL_START_including,FT[i].INTERVAL_END,data_hash,(char*)"[)")==1)
                {

                        info.node_token=FT[i].NODE_TOKEN;
                        info.node_port=FT[i].udp_port;
                        //outfile_client<<"my estimate: "<< hex<<info.node_token<<" on port: "<<dec<<info.node_port<<endl;
                        return info;
                }
        }
        info.node_token=SUCCESSOR;
        info.node_port=SUCCESSOR_port;
        return info;

}
*/

void stores_q_ft(uint32_t my_token, uint32_t data_hash, int send_to,int ext_or_not)
{
	//outfile_client<<" In receive stores-q "<<endl;
	MARSHALLING_UDP obj;
	if (ext_or_not==1)
	{
		for( iterate = DATA_STORE.begin(); iterate != DATA_STORE.end(); iterate++ ) {
		    cout << CLIENT_NAME<<"******* " << hex<<iterate->first << "*******: " << iterate->second << endl;
		  }
	}
	if (LIES_BW(PREDECESSOR,MY_TOKEN,data_hash,(char*)"(]")==1)// i have to hold the data

	{		//outfile_client<<" I am officially responsible for data "<<endl;

							obj.data.token= MY_TOKEN;
							obj.data.id1= data_hash;
							obj.data.id2= MY_TOKEN;
							obj.data.id3= DGRAM_PORT;

							if ( DATA_STORE.count(data_hash) > 0 ) ///// key already exists with the node
							{
								//outfile_client<<"found "<<hex<<data_hash<<" "<<DATA_STORE[data_hash]<<endl;
								obj.data.id4= 1;
								if(ext_or_not==1)
								{
									obj.data.id5=strlen(DATA_STORE[data_hash]);
									strcpy((char*)obj.data.d1,DATA_STORE[data_hash]);
								}
								//outfile_client<<" I already hold the data"<<endl;
							}
							else 							// node doesn't have the key but can be responsible
							{
								obj.data.id4= 0;
								if(ext_or_not==1)
								{
									obj.data.id5=0;
									strcpy(obj.data.d1,"0");
								}
								//outfile_client<<" I >>'DONT'<< already hold the data"<<endl;
							}

							if (ext_or_not==0)
							{
								obj.SEND((char*)"stores-r",send_to);     // reply accordingly
							}
							else
							{
								//outfile_client<<"sending ext-stores with "<< obj.data.d1<<":"<<DATA_STORE[data_hash]<<" data hash is "<<hex<<data_hash<<endl;
								obj.SEND((char*)"ext-stores-r",send_to);
							}
						}

						else
						{
							details info;
							info= scan_FT(data_hash);

							obj.data.token= MY_TOKEN;
							obj.data.id1= data_hash;
							obj.data.id2= info.node_token;
							obj.data.id3= info.node_port;
							obj.data.id4= 0;
							obj.data.id5=0;
							strcpy(obj.data.d1,"0");

							if (ext_or_not==0)
								{
									obj.SEND((char*)"stores-r",send_to);     // reply accordingly
								}
								else
								{
									obj.SEND((char*)"ext-stores-r",send_to);
								}
						}


}

void find_double_succ()
{

		MARSHALLING_UDP obj;
		obj.data.token= SUCCESSOR;
		obj.SEND((char*)"successor-q",SUCCESSOR_port);
		obj.RECEIVE(UDP_private);
		DOUBLE_SUCC= obj.data_recv.id1;
		DOUBLE_SUCC_PORT=obj.data_recv.id2;


}

int msg_to_id(char* msg)
{
	int msg_code;
	if(strcmp(msg,"successor-q")==0)
					{
						msg_code=1;
					}
	else if(strcmp(msg,"successor-r")==0)
						{
							msg_code=2;
						}
	else if(strcmp(msg,"predecessor-q")==0)
						{
							msg_code=3;
						}
	else if(strcmp(msg,"predecessor-r")==0)
							{
								msg_code=4;
							}

	else if(strcmp(msg,"stores-q")==0)
				{
							msg_code=5;
				}
	else if(strcmp(msg,"stores-r")==0)
					{
								msg_code=6;
					}
	else if(strcmp(msg,"update-q")==0)
					{
								msg_code=7;
					}
	else if(strcmp(msg,"store-q")==0)
					{
								msg_code=8;
					}
	else if(strcmp(msg,"store-r")==0)
					{
								msg_code=9;
					}
	else if(strcmp(msg,"update-r")==0)
					{
								msg_code=10;
					}
	else if(strcmp(msg,"find_successor-q")==0)
						{
									msg_code=11;
						}
	else if(strcmp(msg,"find_successor-r")==0)
							{
										msg_code=12;
							}
	else if(strcmp(msg,"find_predecessor-q")==0)
							{
										msg_code=13;
							}
	else if(strcmp(msg,"find_predecessor-r")==0)
							{
										msg_code=14;
							}
	else if(strcmp(msg,"closest_preceding_finger-q")==0)
								{
											msg_code=15;
								}
	else if(strcmp(msg,"closest_preceding_finger-r")==0)
									{
												msg_code=16;
									}
	else if(strcmp(msg,"leaving-q")==0)
									{
												msg_code=17;
									}
	else if(strcmp(msg,"leaving-r")==0)
										{
													msg_code=18;
										}
	else if(strcmp(msg,"next-data-q")==0)
										{
													msg_code=19;
										}
	else if(strcmp(msg,"next-data-r")==0)
											{
														msg_code=20;
											}
	else if(strcmp(msg,"hello-predecessor-q")==0)
		{
			msg_code=21;
		}
	else if(strcmp(msg,"hello-predecessor-r")==0)
			{
				msg_code=22;
			}
	else if(strcmp(msg,"update-double-successor-q")==0)
				{
					msg_code=23;
				}
	else if(strcmp(msg,"update-double-successor-r")==0)
				{
					msg_code=24;
				}
	else if(strcmp(msg,"ext-stores-q")==0)
					{
						msg_code=25;
					}
	else if(strcmp(msg,"ext-stores-r")==0)
					{
						msg_code=26;
					}
	return msg_code;



}


//// returns node if it exists else returns the suc of node
details verify_FT(uint32_t node, uint32_t node_port,uint32_t data_hash)
{
	//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$ "<<inst.instruction<<" "<<inst.DATA<<endl;
	//outfile_client<<"$$$$$$$$$$$$$$$$$$$$$$$$ "<<endl;
	cout<<"CLIENT: VERIFY"<<CLIENT_NAME<<"-> in verify "<<node<<" data hash os: "<<data_hash<<endl;
	//outfile_client<< ": VERIFY: in verify "<<node<<endl;
	details original;
				original.node_token=node;
				original.node_port=node_port;
	details new_node;

	MARSHALLING_UDP obj;
	obj.data.token= node;
	obj.data.id1= data_hash;

	obj.SEND((char*)"stores-q",node_port,2);
	int done_lazy=obj.RECEIVE(UDP_lazy);

	if (done_lazy==1)
	{
		if(obj.data_recv.token== obj.data_recv.id2)  /// ni=ri
		{
			cout<<"CLIENT: : VERIFY"<<CLIENT_NAME<<"-> verified node: "<<node<<endl;
			//outfile_client<< ": VERIFY: verified node: "<<node<<endl;


				return original;
		}
		else
		{
			cout<<"CLIENT:: VERIFY "<<CLIENT_NAME<<"**********************************inside ri!=ni "<<node<<" change to"<<obj.data_recv.id2<<endl;
			//outfile_client<< ": VERIFY***********************************inside ri!=ni"<<node<<" change to"<<obj.data_recv.id2<<endl;
			//exit(1);
			details new_NODE;
			new_NODE.node_token= obj.data_recv.id2;
			new_NODE.node_port= obj.data_recv.id3;
			return new_NODE;
		}

	}
	else  /// timed out
	{
		cout<<"CLIENT: : VERIFY"<<CLIENT_NAME<<"-> request timed out to "<<node<<endl;
					//outfile_client<< ": VERIFY: request timed out to "<<node<<endl;
		uint32_t prev,prev_port;
		for(int i=1;i<33;i++)
		{
			if(FT[i].NODE_TOKEN==node)
			{
				prev=FT[i-1].NODE_TOKEN;
				prev_port=FT[i-1].udp_port;
				break;
			}
		}
		cout<<"CLIENT: : VERIFY"<<CLIENT_NAME<<"-> node prev to dead node is "<<hex<<prev<<endl;
							//outfile_client<< ": VERIFY: node prev to dead node is "<<hex<<prev<<endl;
		details temp;
		temp = verify_FT(prev,prev_port,data_hash);

	/*	if(temp.node_token==prev){   // the previous node exists

			MARSHALLING_UDP OBJ;
			OBJ.data.token= prev;
			OBJ.SEND((char*)"successor-q",prev_port,2);
			OBJ.RECEIVE(UDP_lazy);


			 new_node.node_token= OBJ.data_recv.id1;
			 new_node.node_port= OBJ.data_recv.id2;
			 lazy_update_ft(node,new_node.node_token,new_node.node_port);
			return new_node;
		}*/
		//else   // prev
		{
			lazy_update_ft(node,temp.node_token,temp.node_port);
			return temp;   // returning the node received from the prev

		}
	}



}


void lazy_update_ft(uint32_t original, uint32_t new_node, uint32_t new_port)
{
	cout<<"CLIENT: : VERIFY"<<CLIENT_NAME<<"-> updating FT "<<original<<" to "<<new_node<<endl;
						//outfile_client<< ": VERIFY: -> updating FT "<<original<<" to "<<new_node<<endl;

	for (int i=1;i<33;i++)
	{
		if(FT[i].NODE_TOKEN==original)
		{
			FT[i].NODE_TOKEN=new_node;
			FT[i].udp_port=new_port;
		}
	}
}
