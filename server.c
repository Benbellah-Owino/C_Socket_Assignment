//server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#define PORT 15000
 

void *handleclient(void *c_sockfd){
char bufsize[1024];
char sum_str[1024];
char res[1024];


      read((long)c_sockfd,bufsize,sizeof(bufsize));
       strcpy(sum_str,bufsize);
       
       char delim[2]=",";
       
       char* ptr = strtok(sum_str, delim) ;
       char *two = strtok(NULL,delim);
       char* three = strtok(NULL,delim);
       printf("'%s'\n", ptr);
       printf("'%s'\n", two);
       printf("'%s'\n", three);
       
       int choice = atoi(ptr);
       int nu1 = atoi(two);
       int nu2 = atoi(three);

        int sum_num;
 int mult_num;
 int sub_num;
       
switch (choice){
  case 1:
       sum_num = nu1 + nu2;
     
       sprintf(res,"%d", sum_num);
       send((long)c_sockfd,res,strlen(bufsize),0);
break;

   case 2:
       mult_num = nu1 * nu2;
     
       sprintf(res,"%d", mult_num);
       send((long)c_sockfd,res,strlen(bufsize),0);
break;

    case 3:
       sub_num = nu1 - nu2;
     
       sprintf(res,"%d", sub_num);
       send((long)c_sockfd,res,strlen(bufsize),0);
break;
    case 4:
        printf("client closed");
       strcpy(res,"bye");
       send((long)c_sockfd,res,strlen(bufsize),0);
       
       close((long)c_sockfd);
       pthread_exit(NULL);
break;
}

}


int main(){
 
   int s_sockfd, c_sockfd, val_read;
   
   
   struct sockaddr_in server_addr, client_addr;
   socklen_t addr_size;
   char* bufsize[1024];
   pthread_t tid;
   
 
   
   s_sockfd = socket(AF_INET, SOCK_STREAM,0);
   
   if(s_sockfd<0){
       perror("Socket error\n");
       exit(1);
   }
   
   printf("Server socket created\n");
   
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(PORT);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   
   int n = bind(s_sockfd,(struct sockaddr*) &server_addr, sizeof(server_addr));
   
   if(n<0){
       perror("bind error");
       exit(1);
   }
   
   printf("Bind to port number %d\n",PORT);
   listen(s_sockfd,5);
   printf("Listening...\n");

   
   while(1){
       addr_size = sizeof(client_addr);
       c_sockfd = accept(s_sockfd, (struct sockaddr*)&client_addr,(socklen_t*)&addr_size);
       printf("Client connected\n");
       printf("Thread execution begins \n");
       
       pthread_create(&tid, NULL, handleclient, (void* )c_sockfd);
       
       pthread_detach(tid);
   }

   close(s_sockfd);
  return 0;
  
     
}
