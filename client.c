//client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 15000
 
int main(){
    int sockfd;
    
    int a, b, c;
    
    struct sockaddr_in addr;
    socklen_t  addr_size;
    
    char bufsize[1024];
  
    
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    
    if(sockfd<0){
        perror("Socket error");
        exit(1);
    } 
    
    printf("TCP socket Created \n");
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr=INADDR_ANY;
    
    connect(sockfd,(struct sockaddr*) &addr, sizeof(addr));
    printf("Connected to server\n");
    
     printf("******************************* \n");
    
     printf("Choices include: \n");
      printf("1 - Sum \n");
      printf("2 - Multiply \n");
      printf("3 - Subtract \n");
      printf("4 - Close connection \n");
      
      printf("******************************* \n");
      
   
    printf("Enter Choice: ");
    scanf("%d", &a);
     printf("\n");
    printf("Enter first number: ");
    scanf("%d", &b);
    printf("\n");
    printf("Enter second number: ");
    scanf("%d", &c);
    printf("\n");
    sprintf(bufsize,"%d,%d,%d",a,b,c);
   
   
    send(sockfd, bufsize, strlen(bufsize),0);
  
    
    int msg = read(sockfd, bufsize,1024);
    printf("Server says: %s\n", bufsize);
}
