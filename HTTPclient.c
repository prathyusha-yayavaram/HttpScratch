#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include"pthread.h" 
#include<math.h> 
#define PORT 4468
#define BUF_SIZE 2000



int type,in=0,index1=0,index2=0,flag1=1;

//-------crypto--------
char* encryp(char emsg[]){
    //char ret[strlen(emsg)];
    //printf("\n En : %s \n",emsg);
    char key[1000],ref[1000];
    strcpy(key,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%^&*()[]/1234567890:.-,");
    strcpy(ref,"asdfghjklmnASDFGTREWQYHJUIKLOPVCBXNZMbvcxzrewqtyuiop123456789,0*()-[]./!:#$%^&");
    int i=0,k=0;
    for(i=0;i<strlen(emsg)-1;i++){
        //printf("%c\n",emsg[i]);
        if(emsg[i]==' '){
            emsg[i]='_';        
        }
        else{
        for(k=0;k<strlen(key);k++){
            
            if(emsg[i]==key[k]){
                break;
            }
        }
        
        emsg[i]=ref[k];}
    }
    //ret[i]=emsg[i];
    return emsg;
}
char* decryp(char dmsg[]){
    char ret[strlen(dmsg)];
    char key[1000],ref[1000];
    strcpy(key,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%^&*()[]/1234567890:.-,");
    strcpy(ref,"asdfghjklmnASDFGTREWQYHJUIKLOPVCBXNZMbvcxzrewqtyuiop123456789,0*()-[]./!:#$%^&");
    int i=0,k=0;
    for(i=0;i<strlen(dmsg)-1;i++){
        if(dmsg[i]=='_'){
            dmsg[i]=' ';        
        }
    else{
        //dmsg[i]=dmsg[i]-6;
        for(k=0;k<strlen(ref);k++){
            if(dmsg[i]==ref[k]){
                break;
            }
        }
        dmsg[i]=key[k];
        }
    }
    return dmsg;
}
//---------
void * receiveMessage(void * socket) {
 int sockfd, ret;
 char buffer[BUF_SIZE];
 char file[BUF_SIZE];
 sockfd = (int) socket;
 memset(buffer, 0, BUF_SIZE);
 for (;;) {
  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
strcpy(buffer,decryp(buffer));
  if (ret < 0) {
   printf("Error receiving data!\n");
  } else {
int ll=strlen(buffer);

if(!strncmp("finish",buffer,ll-2)){
    FILE *f  = fopen("temp","w");
    fprintf(f,"%s\n",file);
    fclose(f);
    char command[100];
    sprintf(command, "gedit %s", "temp");
    system(command);
    //printf("%s",file);
}
else{strcat(file,buffer);
printf("%s\n",buffer);}
if(!strncmp("Content-Type: text",buffer,ll-2)){
printf("\n\n");

}
//fputs(buffer, stdout);
   //printf("\n");
  }
 }
}

int main(int argc, char**argv) {
 struct sockaddr_in addr, cl_addr;
 int sockfd, ret;
 char buffer[BUF_SIZE];
 char * serverAddr;
 pthread_t rThread;

 if (argc < 2) {
  printf("usage: client < ip address >\n");
  exit(1);
 }

 serverAddr = argv[1];

 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Error creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");

 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = inet_addr(serverAddr);
 addr.sin_port = PORT;

 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) {
  printf("Error connecting to the server!\n");
  exit(1);
 }
 printf("Connected to the server...\n");

 memset(buffer, 0, BUF_SIZE);
 
 //creating a new thread for receiving messages from the server
 ret = pthread_create(&rThread, NULL, receiveMessage, (void *) sockfd);
 if (ret) {
  printf("ERROR: Return Code from pthread_create() is %d\n", ret);
  exit(1);
 }

 while (flag1==1) { 
  printf("Enter the method u want to implement! \n1.GET\n2.POST\n3.DELETE\n4.PUT\n5.OPTIONS\n6.HEAD\n7.TRACE\n");
  scanf("%d",&type);
  char req[1000];
  if(type==1){memset(req, 0, sizeof(req));
    //get
    printf("enter url : ");memset(buffer, 0, BUF_SIZE);
    scanf("%s",buffer);
   
    char host[100]={"o"},url[100]={"p"};
    index1=0;index2=0;
    for(in=0;in<strlen(buffer);in++){
        if(buffer[in]=='/'){
            break;
        }
        host[index1++]=buffer[in];
    }
    in++;
    for(in;in<strlen(buffer);in++){
        url[index2++]=buffer[in];
    }
    index1=0;index2=4;
    strcpy(req,"GET ");
    for(index1=0;index1<strlen(buffer);index1++){
       req[index2++]=buffer[index1];
    }
    index1=0;index2=0;
   
   
    memset(buffer, 0, BUF_SIZE);
   
    strcpy(buffer,req);
      //printf("\n\nactual  %s\n\n",req);
    strcpy(buffer,encryp(buffer));
    //printf("\nEncrypted message: %s\n",buffer);
      ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"GET ");strcat(buffer,url);
strcpy(buffer,encryp(buffer));//printf("\n\n%s\n\n",buffer);strcpy(buffer,decryp(buffer));printf("\n\n%s\n\n",buffer);strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HTTP/1.1");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"User-Agent: CS");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HOST : ");strcat(buffer,host);   
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"Accept-Language:en-us");
strcpy(buffer,encryp(buffer)); 
   sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
      if (ret < 0) {
       printf("Error sending data!\n\t-%s", buffer);
      }
    sleep(1);
    int lol;
    printf("\nIf you want to close connection press 0 else 1\n");
    scanf("%d",&lol);
    if(lol==0){  
    exit(0);
    }
   


  }
  if(type==2){memset(req, 0, sizeof(req));
//post
    printf("enter url : ");memset(buffer, 0, BUF_SIZE);
    scanf("%s",buffer);
   
    char host[100]={"o"},url[100]={"p"};
    index1=0;index2=0;
    for(in=0;in<strlen(buffer);in++){
        if(buffer[in]=='/'){
            break;
        }
        host[index1++]=buffer[in];
    }
    in++;
    for(in;in<strlen(buffer);in++){
        url[index2++]=buffer[in];
    }
    index1=0;index2=5;
    strcpy(req,"POST  ");
    for(index1=0;index1<strlen(buffer);index1++){
       req[index2++]=buffer[index1];
    }
    index1=0;index2=0;

    memset(buffer, 0, BUF_SIZE);
       printf("enter the text : ");
    char text[200];
    scanf("%s",text);
//fgets(text,sizeof(text),stdin);
    strcpy(buffer,req);
     // printf("\n\nactual fffff %s\n\n",buffer);
    strcpy(buffer,encryp(buffer));
      ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
        strcpy(buffer,"POST  ");strcat(buffer,url);
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HTTP/1.1");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"User-Agent: CS");
strcpy(buffer,encryp(buffer));   
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HOST : ");strcat(buffer,host); 
strcpy(buffer,encryp(buffer));  
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"Accept-Language:en-us");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
strcpy(text,encryp(text));    
    sendto(sockfd, text, sizeof(text), 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
     
    
    


      if (ret < 0) {
       printf("Error sending data!\n\t-%s", buffer);
      }
    sleep(1);
    int lol;
    printf("\nIf you want to close connection press 0 else 1\n");
    scanf("%d",&lol);
    if(lol==0){  
    exit(0);
    }
   

   //response
  }



  if(type==3){memset(req, 0, sizeof(req));
          printf("enter url : ");memset(buffer, 0, BUF_SIZE);
    scanf("%s",buffer);
   
    char host[100]={"o"},url[100]={"p"};
    index1=0;index2=0;
    for(in=0;in<strlen(buffer);in++){
        if(buffer[in]=='/'){
            break;
        }
        host[index1++]=buffer[in];
    }
    in++;
    for(in;in<strlen(buffer);in++){
        url[index2++]=buffer[in];
    }
    index1=0;index2=7;
    strcpy(req,"DELETE ");
    for(index1=0;index1<strlen(buffer);index1++){
       req[index2++]=buffer[index1];
    }
    index1=0;index2=0;
   
   
    memset(buffer, 0, BUF_SIZE);
   
    strcpy(buffer,req);
      //printf("\n\nactual  %s\n\n",req);
    strcpy(buffer,encryp(buffer));
      ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"DELETE ");strcat(buffer,url);
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HTTP/1.1");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"User-Agent: CS");
strcpy(buffer,encryp(buffer));   
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HOST : ");strcat(buffer,host); 
strcpy(buffer,encryp(buffer));  
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"Accept-Language:en-us");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
      if (ret < 0) {
       printf("Error sending data!\n\t-%s", buffer);
      }
    
    sleep(1);
    int lol;
    printf("\nIf you want to close connection press 0 else 1\n");
    scanf("%d",&lol);
    if(lol==0){  
    exit(0);
    }
   
     memset(buffer, 0, BUF_SIZE);
       //delete
   

  }


  if(type==4){
    //put
    printf("enter url : ");memset(buffer, 0, BUF_SIZE);memset(req, 0, sizeof(req));
    scanf("%s",buffer);
   
    char host[100]={"o"},url[100]={"p"};
    index1=0;index2=0;
    for(in=0;in<strlen(buffer);in++){
        if(buffer[in]=='/'){
            break;
        }
        host[index1++]=buffer[in];
    }
    in++;
    for(in;in<strlen(buffer);in++){
        url[index2++]=buffer[in];
    }
    index1=0;index2=4;
    strcpy(req,"PUT ");
    for(index1=0;index1<strlen(buffer);index1++){
       req[index2++]=buffer[index1];
    }
    index1=0;index2=0;

    memset(buffer, 0, BUF_SIZE);
       printf("enter the text : ");
    char text[200];
    scanf("%s",text);//fgets(text,sizeof(text),stdin);
    strcpy(buffer,req);
     printf("\n\nactual fffff %s\n\n",buffer);
strcpy(buffer,encryp(buffer));
      ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
        strcpy(buffer,"PUT  ");strcat(buffer,url);
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HTTP/1.1");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"User-Agent: CS"); 
strcpy(buffer,encryp(buffer));  
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HOST : ");strcat(buffer,host); 
strcpy(buffer,encryp(buffer));  
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"Accept-Language:en-us");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
strcpy(text,encryp(text));
    sendto(sockfd, text, 200, 0, (struct sockaddr *) &addr, sizeof(addr));memset(text, 0, 200);   //sending text

    


      if (ret < 0) {
       printf("Error sending data!\n\t-%s", buffer);
      }
    sleep(1);
    int lol;
    printf("\nIf you want to close connection press 0 else 1\n");
    scanf("%d",&lol);
    if(lol==0){  
    exit(0);
    }
   

   
  }
  if(type==5){memset(req, 0, sizeof(req));
    //options
    strcpy(buffer,"OPTIONS ");strcat(buffer,"*");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"OPTIONS ");strcat(buffer,"*");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HTTP/1.1");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"User-Agent: CS"); 
strcpy(buffer,encryp(buffer));  
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);

    sleep(1);
      if (ret < 0) {
       printf("Error sending data!\n\t-%s", buffer);
      }
    sleep(1);
    int lol;
    printf("\nIf you want to close connection press 0 else 1\n");
    scanf("%d",&lol);
    if(lol==0){  
    exit(0);
    }
   

  }
  if(type==6){memset(req, 0, sizeof(req));
    //Head
    printf("enter url : ");memset(buffer, 0, BUF_SIZE);
    scanf("%s",buffer);
   
    char host[100]={"o"},url[100]={"p"};
    index1=0;index2=0;
    for(in=0;in<strlen(buffer);in++){
        if(buffer[in]=='/'){
            break;
        }
        host[index1++]=buffer[in];
    }
    in++;
    for(in;in<strlen(buffer);in++){
        url[index2++]=buffer[in];
    }
    index1=0;index2=5;
    strcpy(req,"HEAD ");
    for(index1=0;index1<strlen(buffer);index1++){
       req[index2++]=buffer[index1];
    }
    index1=0;index2=0;
   
   
    memset(buffer, 0, BUF_SIZE);
   
    strcpy(buffer,req);
      //printf("\n\nactual  %s\n\n",req);
strcpy(buffer,encryp(buffer));
      ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"HEAD ");strcat(buffer,url);
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HTTP/1.1");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"User-Agent: CS"); 
strcpy(buffer,encryp(buffer));  
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HOST : ");strcat(buffer,host);
strcpy(buffer,encryp(buffer));   
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"Accept-Language:en-us");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
      if (ret < 0) {
       printf("Error sending data!\n\t-%s", buffer);
      }
    sleep(1);
    int lol;
    printf("\nIf you want to close connection press 0 else 1\n");
    scanf("%d",&lol);
    if(lol==0){  
    exit(0);
    }
   

  }
 if(type==7){memset(req, 0, sizeof(req));
    //trace
    printf("enter url : ");memset(buffer, 0, BUF_SIZE);
    scanf("%s",buffer);
   
    char host[100]={"o"},url[100]={"p"};
    index1=0;index2=0;
    for(in=0;in<strlen(buffer);in++){
        if(buffer[in]=='/'){
            break;
        }
        host[index1++]=buffer[in];
    }
    in++;
    for(in;in<strlen(buffer);in++){
        url[index2++]=buffer[in];
    }
    index1=0;index2=6;
    strcpy(req,"TRACE ");
    for(index1=0;index1<strlen(buffer);index1++){
       req[index2++]=buffer[index1];
    }
    index1=0;index2=0;
   
   
    memset(buffer, 0, BUF_SIZE);
   
    strcpy(buffer,req);
      //printf("\n\nactual  %s\n\n",req);
strcpy(buffer,encryp(buffer));
      ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"TRACE ");strcat(buffer,url);
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HTTP/1.1");
strcpy(buffer,encryp(buffer));
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"User-Agent: CS");
strcpy(buffer,encryp(buffer));   
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"HOST : ");strcat(buffer,host); 
strcpy(buffer,encryp(buffer));  
    sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));memset(buffer, 0, BUF_SIZE);

    sleep(1);
      if (ret < 0) {
       printf("Error sending data!\n\t-%s", buffer);
      }
    
    sleep(1);
    int lol;
    printf("\nIf you want to close connection press 0 else 1\n");
    scanf("%d",&lol);
    if(lol==0){  
    exit(0);
    }
   




    
}



 }

 close(sockfd);
 pthread_exit(NULL);

 return 0;
}