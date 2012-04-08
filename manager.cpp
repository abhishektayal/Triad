
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
#include <map>
#include<cstdlib>
#include <sys/timeb.h>
#include<unistd.h>



using namespace std;


void accept(int client_num);
void send_instruction(char*,int,int);

char* str_to_char(string);


void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
		return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int c=0;
int PORT;

ofstream outfile ;
string mang_filename;
int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
int j;
struct sockaddr_storage their_addr; // connector's address information
socklen_t sin_size;
struct sigaction sa;
int yes=1;
int FIRST_CLIENT=1;

struct sockaddr_in address;
int  addresslen= sizeof(address);
int NODES_int, NONCE_int;

char client[100][100];
char store_command[100][100];
char search_command[100][100];
char end_command[100][100];
char kill_command[100][100];
char tkcc_command[100][100];
int store_or_search[30];              ////// 0= store   1= search
int client_num=0, store_num=0,search_num=0,end_num=0,kill_num=0,tkcc_num=0;
int store_or_search_index=0;
char UDP1[100];
int inst_index=0,search_index=0,store_index=0,end_index=0,kill_index=0,tkcc_index=0,client_index=0;

map<char*,int> CLIENT_TO_PORT;

int main(int argc, char *argv[]) {

	string NODES, NONCE;



	if (argc !=2 )
	{
		cout<< "enter configuration file path\n";
	}
	else
	{
		int pos;
		string line;
		  ifstream myfile (argv[1]);
		  if (myfile.is_open())
		  {
		    while ( myfile.good() )
		    {
		      getline (myfile,line);
		      //cout << line << endl;
		      if (line.find("#")==0)
		    		  {
		    	  	  	  //cout<<"its a comment\n";
		    		  }
		      else
		      {
		    	  if ((pos=line.find("stage"))==0)
		    	  {
		    		  //cout<<"its the stage tag\n";
		    		   string str3 = line.substr (pos+6);
		    		   //cout<<"the stage is "<< str3<<"\n";
		    		   STAGE=str3;
		    		   mang_filename="stage"+STAGE+"."+"manager.out";
		    		   outfile.open(str_to_char(mang_filename));

		    	  }
		    	  if ((pos=line.find("start_client"))==0)
		    	  		    	  {
		    	  		    		  //cout<<"its the stage tag\n";
		    	  		    		   string str3 = line.substr (pos+13);
		    	  		    		   //cout<<"the stage is "<< str3<<"\n";
		    	  		    		   strcpy(client[client_num],str_to_char(str3));
		    	  		    		 store_or_search[store_or_search_index]=0;
		    	  		    		 store_or_search_index++;
		    	  		    		   client_num++;
		    	  		    	  }
		    	  if ((pos=line.find("start_tkcc"))==0)
		    	  		    	  		    	  {
		    	  		    	  		    		  //cout<<"its the stage tag\n";
		    	  		    	  		    		   string str3 = line.substr (pos+11);
		    	  		    	  		    		   //cout<<"the stage is "<< str3<<"\n";
		    	  		    	  		    		   strcpy(client[client_num],str_to_char(str3));
		    	  		    	  		    		store_or_search[store_or_search_index]=1;
		    	  		    	  		    		store_or_search_index++;
		    	  		    	  		    		   client_num++;
		    	  		    	  		    	  }

		    	  if ((pos=line.find("num_nodes"))==0)
		    	  		    	  {
		    	  		 //   		  cout<<"its the num_nodes tag\n";

		    	  		    		   string str3 = line.substr (pos+10);
		    	  		   // 		   cout<<"no. of nodes are "<< str3<<"\n";
		    	  		    		   NODES= str3;
		    	  		    	  }
		    	  if ((pos=line.find("nonce"))==0)
		    	  		    	  {
		    	  		    //		  cout<<"its the nonce tag\n";

		    	  		    		   string str3 = line.substr (pos+6);
		    	  		    	//	   cout<<"nonce is "<< str3<<"\n";
		    	  		    		   NONCE= str3;
		    	  		    	  }
		    	  if ((pos=line.find("store"))==0)
		    	  		    	  		    	  {
		    	  		    	  		    		   cout<<"its the store tag\n";
		    	  		    	  		    		   string str3 = line.substr (pos+6);
		    	  		    	  		    		   cout<<"the store is "<< str3<<"\n";
		    	  		    	  		    		   strcpy(store_command[store_num],str_to_char(str3));
		    	  		    	  		    		   store_or_search[store_or_search_index]=2;
		    	  		    	  		    		   store_or_search_index++;
		    	  		    	  		    		   store_num++;
		    	  		    	  		    	  }
		    	  if ((pos=line.find("search"))==0)
		    	  		    	  		    	  {
		    	  		    	  		    		   cout<<"its the search tag\n";
		    	  		    	  		    		   string str3 = line.substr (pos+7);
		    	  		    	  		    		   cout<<"the search is "<< str3<<"\n";
		    	  		    	  		    		   strcpy(search_command[search_num],str_to_char(str3));
		    	  		    	  		    		   store_or_search[store_or_search_index]=3;
		    	  		    	  		    		   store_or_search_index++;
		    	  		    	  		    		   search_num++;
		    	  		    	  		    	  }
		    	  if ((pos=line.find("end_client"))==0)
		    	  		    	  		    	  {
		    	  		    	  		    	  	  cout<<"its the end_client tag\n";
		    	  		    	  		    	  	  string str3 = line.substr (pos+11);
		    	  		    	  		    	  	  cout<<"the end_client is "<< str3<<"\n";
		    	  		    	  		    	  	  strcpy(end_command[end_num],str_to_char(str3));
		    	  		    	  		    	  	  store_or_search[store_or_search_index]=4;
		    	  		    	  		    	  	  store_or_search_index++;
		    	  		    	  		    	  	  end_num++;
		    	  		    	  		    	  }
		    	  if ((pos=line.find("kill_client"))==0)
		    	  		    	  		    	  		    	  {
		    	  		    	  		    	  		    	  	  cout<<"its the kill_client tag\n";
		    	  		    	  		    	  		    	  	  string str3 = line.substr (pos+12);
		    	  		    	  		    	  		    	  	  cout<<"the kill_client is "<< str3<<"\n";
		    	  		    	  		    	  		    	  	  strcpy(kill_command[kill_num],str_to_char(str3));
		    	  		    	  		    	  		    	  	  store_or_search[store_or_search_index]=5;
		    	  		    	  		    	  		    	  	  store_or_search_index++;
		    	  		    	  		    	  		    	  	  kill_num++;
		    	  		    	  		    	  		    	  }
		      }
		    }
		    myfile.close();
		  }

	}



	char* n;
			n= new char[NODES.length()];
			for (int i=0;i<=NODES.length();i++)
			{
				n[i]=NODES[i];
			}

			  NODES_int= atoi (n);

			char* a;
				a= new char[NONCE.length()];
				for (int i=0;i<=NONCE.length();i++)
				{
					a[i]=NONCE[i];
				}

				 NONCE_int= atoi (a);

////////////////////////////////////////////////

//creating the tcp socket to communicate with clients
////////////////////////////////////////////////
////////////////////////////////////////////////



	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
		{
			perror("server: socket");
	    }

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1)
		{
	        perror("setsockopt");
	        exit(1);
	    }

		address.sin_family = AF_INET;
		address.sin_port = htons(0);
		address.sin_addr.s_addr = INADDR_ANY;

		if (bind(sockfd, (struct sockaddr*)&address, addresslen) == -1)
		{
	        close(sockfd);
	        perror("server: bind");
		}

		getsockname(sockfd,(struct sockaddr *)&address, (socklen_t*)&addresslen);
		PORT = (int)htons(address.sin_port);
		//printf("Manager Port : %d\n",PORT);


		outfile<<"Manager Port:"<<PORT<<"\n";
		outfile.close();

	    if (listen(sockfd, BACKLOG) == -1)
		{
	        perror("listen");
	        exit(1);
	    }
	    sa.sa_handler = sigchld_handler; // reap all dead processes
	    sigemptyset(&sa.sa_mask);
	    sa.sa_flags = SA_RESTART;

		if (sigaction(SIGCHLD, &sa, NULL) == -1)
		{
	        perror("sigaction");
	        exit(1);
	    }


////////////////////////////////////////////////////////////////////////////////////////////////
// forking all clients one by one
////////////////////////////////////////////////////////////////////////////////////////////////

		//printf("there\n");
		//for (int i=0;i<client_num;i++)
		//{
			//cout<<"in the loop";
			// fork_clients(1);
			 //accept(i);
		//}

		for(int j=0;j<store_or_search_index;j++)
		{
			if (store_or_search[j]==0 )            // the next inst is a start_client
			{
				//outfile<<"inside start - "<<client[client_index]<<endl;
				fork_clients(1,0);
				accept(client_index);
				client_index++;
			}
			else if (store_or_search[j]==1 )            // the next inst is a start_tkcc
						{
							//outfile<<"inside start - "<<client[client_index]<<endl;
							fork_clients(1,1);
							accept(client_index);
							client_index++;
						}

			else if (store_or_search[j]==2)            // the next inst is a store
			{
				//outfile<<"inside store - "<<store_command[store_index]<<endl;
				send_instruction(store_command[store_index],2,0);
				store_index++;
			}
			else if(store_or_search[j]==3)            // the next inst is a search
			{
				//outfile<<"inside search - "<<search_command[search_index]<<endl;
				send_instruction(search_command[search_index],3,0);
				search_index++;
			}
			else if(store_or_search[j]==4)            // the next inst is a end_client
			{
				int client_number;
				for(int i=0;i<client_num;i++)
				{
					if(strcmp(client[i],end_command[end_index])==0)
					{
						 client_number=i;
								break;
					}
				}
				//outfile<<"inside end_client - "<<end_command[end_index]<<" client number is: "<<client_number<<endl;
				send_instruction(end_command[end_index],4,client_number);
				end_index++;
			}
			else if(store_or_search[j]==5)            // the next inst is a kill_client
			{

				int client_number;
								for(int i=0;i<client_num;i++)
								{
									if(strcmp(client[i],kill_command[kill_index])==0)
									{
										 client_number=i;
												break;
									}
								}
				//cout<<"inside kill_client - "<<kill_command[kill_index]<<" client number is: "<<client_number<<"end command is:"<<end_command[end_index]<<endl;
				send_instruction(kill_command[kill_index],5,client_number);
				 struct timeb tp,tp1;
				                         ftime(&tp);

				                 printf(">>>>>>>>>>>>>>>>time start=%ld.%d\n",tp.time,tp.millitm);
				   unsigned long t=1000000000;

				   for(unsigned long e=0;e<10;e++)
				   {
				   for(unsigned long y=0;y<100000000;y++)
				   {
					   while(t>0)
					   {
						   t--;
					   }
				   }
				   }
				ftime(&tp1);
                printf(">>>>>>>>>>>>>>>>>time end=%ld.%d\n",tp1.time,tp1.millitm);
				kill_index++;
			}
		}

		for(int i=0;i<client_num;i++)
		{
			send_instruction((char*)"killing",6,i);
		}




	        close(sockfd);
	        //printf("Manager exiting\n");
return 0;

}





void accept(int client_number)
{
	cout<<"MANAGER:->client_number is"<<client_number<<"name is "<<client[client_number]<<endl;
		int numbytes1;
		 outfile.open (str_to_char(mang_filename),ios::app);
		char buf[MAXDATASIZE],buf1[MAXDATASIZE],buf2[MAXDATASIZE],buf3[MAXDATASIZE],buf4[MAXDATASIZE],buf5[MAXDATASIZE];
		// printf("server: waiting for connections...\n");

		  // main accept()

			sin_size = sizeof their_addr;
			new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if(new_fd == -1)
			{
				perror("accept");
			}

//// storing the tcp communication port associated with each child

		CLIENT_TO_PORT[client[client_number]]=new_fd;
		//cout<<"-------------------------TCP socket connected is: "<<new_fd<<endl;

				int local_client_num=j;
				//cout<<"1-------value of DGRAM socket is: "<<UDP1<<endl;
				outfile<<"1-------value of DGRAM socket is: "<<UDP1<<endl;
				//sending the nonce
				sprintf(buf,"%d",NONCE_int);
				if(send(new_fd, buf, sizeof(buf), 0) == -1)
					perror("send_nonce");
				outfile<< "sent nonce:" << buf<<endl;

				//sending the clients  name

					strcpy(buf1,client[client_number]);

				if(send(new_fd, buf1, sizeof(buf1), 0) == -1)
					perror("send_name");
				outfile<< "sent client name:" << buf1<<endl;

				//sending the FP

					if(client_number==0)
					{
					sprintf(buf2,"%d",0);
					}
					else
					{
					strcpy(buf2,UDP1);
					}
				if(send(new_fd, buf2, sizeof(buf2), 0) == -1)
					perror("send_FP");
				outfile<< "sent the FP:" << buf2<<endl;

				//sending the FS (same as name of first client for everyone)
					strcpy(buf3,client[0]);
				if(send(new_fd, buf3, sizeof(buf3), 0) == -1)
					perror("send_FS");
				outfile<< "sent FS:" << buf3<<endl;

	///////////////////////////////////////
	//receiving DGRAM port and NONCE +Sx from clients
	///////////////////////////////////////

				if ((numbytes1 = recv(new_fd, buf4, sizeof buf4, 0)) == -1)
				{
					perror("recv");
					exit(1);
				}
				buf4[numbytes1] = '\0';
				outfile<<"received Dgram port of  client: "<<buf4<<endl;
				outfile<<"value of FIRST client is: "<<FIRST_CLIENT<<endl;

				if(client_number==0)
				{
				strcpy(UDP1,buf4);
				}


				if ((numbytes1 = recv(new_fd, buf5, sizeof buf5, 0)) == -1)
							{
								perror("recv");
								exit(1);
							}
				buf5[numbytes1] = '\0';
				outfile<<"received NONCE+Sx of  client: "<<buf5<<endl;

				//close(new_fd);
				outfile.close();





}

char* str_to_char(string sample)
{
	char *n;
				n= new char[sample.length()];
				for (int i=0;i<=sample.length();i++)
				{
					n[i]=sample[i];
				}

return n;

}

void send_instruction(char* inst, int type, int client_num)
{
	outfile.open (str_to_char(mang_filename),ios::app);
	int tcp_sock=CLIENT_TO_PORT[client[client_num]];

	char buf[100];
	if(type==2)
	{
		strcpy(buf,"store-");
		strcat(buf,inst);
	}
	else if(type==3)
	{
		strcpy(buf,"search-");
		strcat(buf,inst);
	}
	else if(type==4)
		{
			strcpy(buf,"end_client-");
			strcat(buf,inst);
		}
	else if(type==5)
		{
			strcpy(buf,"kill_client-");
			strcat(buf,inst);
		}
	else if(type==6)
	{
		strcpy(buf,"kill_client-die");
	}


	if(send(tcp_sock, buf, sizeof(buf), 0) == -1)
						perror("send_name");
					outfile<< "sent instruction:" << buf<<"over socket: "<<tcp_sock<< endl;
					cout<< "MANAGER:sent instruction:" << buf<<"over socket: "<<tcp_sock<< endl;
					int numbytes1;
					char buf4[100];

if (type != 5)
{
    if ((numbytes1 = recv(tcp_sock, buf4, sizeof buf4, 0)) == -1)
	{
    	perror("recv:manager inst");
		exit(1);
	}
	buf4[numbytes1] = '\0';
	outfile<<"received reply to instruction sent: "<<buf4<<endl;
}
else   // this is after sending kill to the node
{
	cout<<"MANAGER: this was kill command ..... sleeping "<<endl;

}



	outfile.close();
}



