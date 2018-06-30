#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"
#include"ctype.h" 
#include<math.h> 
#define PORT 4468
#define BUF_SIZE 2000
#define CLADDR_LEN 100
//-------------crypto
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
//-----------------


int sockfd, len, ret, newsockfd;
struct sockaddr_in addr, cl_addr;


void * receiveMessage(void * socket) {
 int sockfd, ret;
 char buffer[BUF_SIZE];
 sockfd = (int) socket;
 memset(buffer, 0, BUF_SIZE);
 for (;;) {
   memset(buffer, 0, BUF_SIZE);
    ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
    strcpy(buffer,decryp(buffer));
    //printf("af decr %s\n\n",buffer);
    if (ret < 0) {
        printf("Error receiving data!\n");
        }
    else{
    //printf("BUffer rec %s\n\n\n",buffer);
    
        char x[500],method[100];int u=0,i;
    memset(method, 0, 100);
        for(i=0;i<strlen(buffer);i++){
            if(buffer[i]==' '){
                break;
            }
            method[u++]=buffer[i];
                
        }

        printf("\nMethod to implement %s\n",method);
        if(!strcmp(method,"GET")){  //GET
    char t[1000];strcpy(t,buffer);
    //request
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));
printf("\nClient Request\n\n%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));
printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));
printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));
printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));
printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
   
        u=0;i++;
        //printf("\n");
        for(i;i<strlen(t);i++){
        if(t[i]==' '){break;}

                x[u++]=t[i];


            }
    //printf("\ni%d\n\n",i);
        FILE *ptr;
        if((ptr = fopen(x,"r"))==NULL){
             
        strcpy(buffer,"HTTP/1.1 404");
strcpy(buffer,encryp(buffer));
    ret = sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
            if (ret < 0) {
                printf("Error sending data! er404\n");
                exit(1);
            }
        }
        else{
            memset(&buffer, 0, sizeof(buffer));
        strcpy(buffer,"HTTP/1.1 200 OK");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        int s=0;
        fseek(ptr, 0L, SEEK_END);
            s = ftell(ptr);
        rewind(ptr);
        sprintf(buffer,"content-Length: %d",s);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"Content-Type: text");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);

            while (!feof(ptr)) { //sends the file
                fread(&buffer, sizeof(buffer), 1, ptr);strcpy(buffer,encryp(buffer));
                sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
        s=s+strlen(buffer);
                memset(&buffer, 0, sizeof(buffer));
            }

            strcpy(buffer,"finish");
strcpy(buffer,encryp(buffer));
            sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);

            printf("\n\n\nFile sent...\n");
            }
        }   //get ends

    else if(!strcmp(method,"POST")){      //POST
                   char t[1000];strcpy(t,buffer);
    //request
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\nClient Request\n\n%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
   
        u=0;i++;
        //printf("\n");
        for(i;i<strlen(t);i++){
        if(t[i]==' '){break;}

                x[u++]=t[i];


            }
    //printf("\ni%d\n\n",i);
        FILE *ptr,*p1;
        if((ptr = fopen(x,"r"))==NULL){
        recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\n\n%s\n",buffer);
            //sendto(newsockfd, "error 404", sizeof("error 404"), 0, (struct sockaddr *) &cl_addr, len);
        strcpy(buffer,"HTTP/1.1 404");
    strcpy(buffer,encryp(buffer));
    ret = sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
        time_t ti = time(NULL);
        struct tm tm = *localtime(&ti);

        sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
            if (ret < 0) {
                printf("Error sending data! er404\n");
                exit(1);
            }
        }
        else{
            p1=fopen(x,"a");
            recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\n\n\n%s\n",buffer);
            fprintf(p1,"%s",buffer);
            
            strcpy(buffer,"HTTP/1.1 200 OK");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        time_t ti = time(NULL);
        struct tm tm = *localtime(&ti);

        sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        int s=0;
        fseek(p1, 0L, SEEK_END);
            s = ftell(p1);
        rewind(p1);
    fclose(p1);
        sprintf(buffer,"content-Length: %d",s);
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
        strcpy(buffer,"Content-Type: text");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
    strcpy(buffer,"POST done");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"finish");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);        
            }
        }    //POST ends


       else if(!strcmp(method,"DELETE")){
    FILE *ptr,*p1;
    
       char command[500],x[500],t[100];i++;u=0;
        strcpy(t,buffer);
    for(i;i<strlen(t);i++){
            if(t[i]==' '){break;}
                    x[u++]=t[i];
                }
    
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\nClient Request\n\n%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
        
    ptr=fopen(x,"r");
    int s=0;
    
    if(ptr==NULL){
        strcpy(buffer,"HTTP/1.1 404");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    }
    else{
    
        fseek(ptr, 0L, SEEK_END);
            s = ftell(ptr);
        rewind(ptr);
    sprintf(command,"rm -f %s",x);
        system(command);
    

    strcpy(buffer,"HTTP/1.1 200 OK");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    }
        time_t ti = time(NULL);
        struct tm tm = *localtime(&ti);

        sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        
    strcpy(buffer,"Server: terminal");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
        sprintf(buffer,"content-Length: %d",s);
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"Content-Type: text");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
    if(ptr==NULL){
    strcpy(buffer,"File not found");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    }
    else{
    strcpy(buffer,"File deleted");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    }
    strcpy(buffer,"finish");
    strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    }


      else if(!strcmp(method,"PUT")){
        char t[1000];strcpy(t,buffer);
    //request
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\nClient Request\n\n%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);
   
        u=0;i++;
        //printf("\n");
        for(i;i<strlen(t);i++){
        if(t[i]==' '){break;}

                x[u++]=t[i];


            }
    //printf("\ni%d\n\n",i);
        FILE *ptr,*p1;
    p1=fopen(x,"w");
            recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\n\n\n%s\n",buffer);
            fprintf(p1,"%s",buffer);
            
            strcpy(buffer,"HTTP/1.1 200 OK");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        time_t ti = time(NULL);
        struct tm tm = *localtime(&ti);

        sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        int s=0;
        fseek(p1, 0L, SEEK_END);
            s = ftell(p1);
        rewind(p1);
    fclose(p1);
        sprintf(buffer,"content-Length: %d",s);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"Content-Type: text");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"PUT done");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"finish");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
            
        }


       else if(!strcmp(method,"OPTIONS")){
            recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\nClient Request\n\n%s ",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    time_t t = time(NULL);
        struct tm tm = *localtime(&t);

    strcpy(buffer,"HTTP/1.1 200 OK");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);

    sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
    strcpy(buffer,"Server: terminal");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);    

    strcpy(buffer,"Allow: GET,POST,HEAD,PUT,TRACE,OPTIONS");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);

    strcpy(buffer,"Content-Type: text");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        
    strcpy(buffer,"finish");
strcpy(buffer,encryp(buffer));
            sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);

        }


       else if(!strcmp(method,"HEAD")){
        char t[1000];strcpy(t,buffer);
    //request
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\nClient Request\n\n%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);memset(buffer, 0, BUF_SIZE);
   
        u=0;i++;
        //printf("\n");
        for(i;i<strlen(t);i++){
        if(t[i]==' '){break;}

                x[u++]=t[i];


            }
    //printf("\ni%d\n\n",i);
        printf("\nclient requested for: \n");
        printf("%s",x);
        FILE *ptr;
        if((ptr = fopen(x,"r"))==NULL){
    strcpy(buffer,"HTTP/1.1 404");
strcpy(buffer,encryp(buffer));
    ret = sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
           time_t t = time(NULL);
        struct tm tm = *localtime(&t);
    sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);      
            if (ret < 0) {
                printf("Error sending data! er404\n");
                exit(1);
            }
        }
        else{
    memset(buffer, 0, BUF_SIZE);
            time_t t = time(NULL);
        struct tm tm = *localtime(&t);

    strcpy(buffer,"HTTP/1.1 200 OK");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);

        sprintf(buffer,"Date: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        int s=0;
        fseek(ptr, 0L, SEEK_END);
            s = ftell(ptr);
        rewind(ptr);
    fclose(ptr);
        sprintf(buffer,"content-Length: %d",s);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        strcpy(buffer,"Content-Type: text");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"finish");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        }
    }
    else if(!strcmp(method,"TRACE")){
        char t[1000];strcpy(t,buffer);
        char trace[5][1000];
memset(trace[0], 0, BUF_SIZE);
memset(trace[1], 0, BUF_SIZE);
memset(trace[2], 0, BUF_SIZE);
memset(trace[3], 0, BUF_SIZE);
    //request
    //strcpy(trace[0],"~~");
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("\nClient Request\n\n%s \n",buffer);strcpy(trace[0],buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);strcpy(trace[1],buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);strcpy(trace[2],buffer);memset(buffer, 0, BUF_SIZE);
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);strcpy(buffer,decryp(buffer));printf("%s\n",buffer);strcpy(trace[3],buffer);memset(buffer, 0, BUF_SIZE);
   
        u=0;i++;
        //printf("\n");
        for(i;i<strlen(t);i++){
        if(t[i]==' '){break;}

                x[u++]=t[i];


            }
    //printf("\ni%d\n\n",i);
        FILE *ptr;
        if((ptr = fopen(x,"r"))==NULL){
            //ret = sendto(newsockfd, "error 404", sizeof("error 404"), 0, (struct sockaddr *) &cl_addr, len);
        strcpy(buffer,"HTTP/1.1 404");
strcpy(buffer,encryp(buffer));
    ret = sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        sprintf(buffer,"now: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
strcpy(buffer," ");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
            if (ret < 0) {
                printf("Error sending data! er404\n");
                exit(1);
            }
        }
        else{
            memset(&buffer, 0, sizeof(buffer));
        strcpy(buffer,"HTTP/1.1 200 OK");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        sprintf(buffer,"now: %d-%d-%d %d:%d:%d", tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
    strcpy(buffer,"Server: terminal");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);    

    strcpy(buffer,"Connection: close");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);

    int s=0;
        fseek(ptr, 0L, SEEK_END);
            s = ftell(ptr);
        rewind(ptr);
    sprintf(buffer,"Content-Length: %d",s);
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);

    strcpy(buffer,"Content-Type: text");
strcpy(buffer,encryp(buffer));
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);memset(buffer, 0, BUF_SIZE);
    
        


            }
//tracing
memset(buffer, 0, BUF_SIZE);
strcpy(trace[0],encryp(trace[0]));strcpy(buffer,trace[0]);
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
memset(buffer, 0, BUF_SIZE);
strcpy(trace[1],encryp(trace[1]));strcpy(buffer,trace[1]);
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
memset(buffer, 0, BUF_SIZE);
strcpy(trace[2],encryp(trace[2]));strcpy(buffer,trace[2]);
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
memset(buffer, 0, BUF_SIZE);
strcpy(trace[3],encryp(trace[3]));strcpy(buffer,trace[3]);
    sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);
memset(buffer, 0, BUF_SIZE);
    strcpy(buffer,"finish");
strcpy(buffer,encryp(buffer));
            sendto(newsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cl_addr, len);

        }
    
        }
    }
}




void main() {


 char buffer[BUF_SIZE];
 pid_t childpid;
 char clientAddr[CLADDR_LEN];
 pthread_t rThread;

 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Error creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");

 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = INADDR_ANY;
 addr.sin_port = PORT;

 ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) {
  printf("Error binding!\n");
  exit(1);
 }
 printf("Binding done...\n");

 printf("Waiting for a connection...\n");
 listen(sockfd, 5);


 len = sizeof(cl_addr);
 newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
 if (newsockfd < 0) {
  printf("Error accepting connection!\n");
  exit(1);
 }

 inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
 printf("Connection accepted from %s...\n", clientAddr);

 memset(buffer, 0, BUF_SIZE);
 printf("Enter your messages one by one and press return key!\n");

 //creating a new thread for receiving messages from the client
 ret = pthread_create(&rThread, NULL, receiveMessage, (void *) newsockfd);
 if (ret) {
  printf("ERROR: Return Code from pthread_create() is %d\n", ret);
  exit(1);
 }

 while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
  ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, len);
  if (ret < 0) {
   printf("Error sending data!\n");
   exit(1);
  }
 }

 close(newsockfd);
 close(sockfd);

 pthread_exit(NULL);
 return;
}