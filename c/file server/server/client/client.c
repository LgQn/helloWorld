/* File Name: client.c */   
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h> 
#include<unistd.h>
#include<errno.h>
#include <fcntl.h>

#define MAXLINE 4096  
#define PORT_M 8888
#define M 1024

void upload(struct sockaddr_in servaddr);      //定义函数
void list(struct sockaddr_in servaddr);
void download(struct sockaddr_in servaddr);
void delete(struct sockaddr_in servaddr);

int main(int argc,char** argv){
    int socket_fd=0;
    struct sockaddr_in servaddr;
    char command;

    socket_fd=socket(AF_INET,SOCK_STREAM,0);     //创建socket
    if(socket_fd==0){
        printf("创建socket失败\n");
        goto error;
    }
    memset(&servaddr,0,sizeof(servaddr));        //初始化 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT_M);
 /*   if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0){     //
        printf("inet_pton error !!!\n");
       goto error;
    }*/
    while(1){
        printf("请输入指令：\n");
        printf("====0：退出\n");
        printf("====1：上传文件\n");
        printf("====2：下载文件\n");
        printf("====3：文件列表\n");
        printf("====4：删除文件\n");
        command=getchar();
        getchar();
        if(command=='0'){
            printf("再见！\n");
            break;
        }else if(command=='1'){
            upload(servaddr);  }               //上传文件
        else if(command=='2')
            download(servaddr);               //下载文件
        else if(command=='3'){
            list(servaddr);
        }                 
        else if(command=='4')
            delete(servaddr);                 //删除文件
    }
error:
    close(socket_fd);
    return 0;
}


//==================函数实现===================

//============================上传服务器文件===========================
void upload(struct sockaddr_in servaddr){
    int socket_fd=0,fp=0,byt=0,x=0;
    char buf[M],*p;

    socket_fd=socket(AF_INET,SOCK_STREAM,0);     //创建socket
    if(socket_fd==0){
        printf("创建socket失败\n");
        goto error;
    }
    if(connect(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        printf("connect failed !!\n");
       goto error;
    }

    buf[0]='u';
    printf("请输入要上传的文件名称：\n");
    fgets(buf+1,32,stdin);
    p=buf+1;
    x=strlen(p);
    p[x-1]='\0';
    fp=open(p,O_RDONLY);       
    if(fp==-1){
        printf("file open error\n");
        return;
    }
    else{
        if(send(socket_fd,buf,M,0)<0){
        printf("send error\n");
        goto error;
        }
    }

    do{
        byt=read(fp,buf,128);
			printf("%d\n",byt);
        send(socket_fd,buf,byt,0);
    }while(byt>0);

error:
    close(socket_fd);
}

//====================删除服务器文件========================
void delete(struct sockaddr_in servaddr){
    int socket_fd=0;
    char buf[M];

        socket_fd=socket(AF_INET,SOCK_STREAM,0);     //创建socket
    if(socket_fd==0){
        printf("创建socket失败\n");
        goto error;
    }
    if(connect(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        printf("connect failed !!\n");
       goto error;
    }
    buf[0]='e';
    printf("请输入要删除的文件名\n");
    fgets(buf+1,32,stdin);
    if(send(socket_fd,buf,M,0)<0){
        printf("send error\n");
    }
 //   buf={0};
    recv(socket_fd,buf,M,0);
    if(buf[0]=='Y'){
        printf("删除成功\n");
    }
    else if(buf[0]=='N'){
        printf("删除失败\n");
    }
    else{
        printf("error");
    }
error:
    close(socket_fd);
}



  //=======================下载文件=====================
void download(struct sockaddr_in servaddr){                 
    int socket_fd=0,file,byt,a;
    char buf[M];
    char *p;

    socket_fd=socket(AF_INET,SOCK_STREAM,0);     //创建socket
    if(socket_fd==0){
        printf("创建socket失败\n");
        goto error;
    }
    if(connect(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        printf("connect failed !!\n");
       goto error;
    }

    buf[0]='d';
   printf("请输入想要下载的文件名：\n");
   fgets(buf+1,32,stdin);
   p=buf+1;
   a=strlen(p);
   p[a-1]='\0';
        if(send(socket_fd,buf,M,0)<0){
        printf("send error\n");
        }

    struct timeval timeout; 
    timeout.tv_sec =2;
    timeout.tv_usec=1000;
    setsockopt(socket_fd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout.tv_sec,sizeof(struct timeval));

    byt=recv(socket_fd,buf,M,0);
    if(byt<0)
    printf("recv fail\n");
    if(buf[0]=='N'){
        printf("can't find files\n");
        return;
    }
    else printf("find file and connecting\n");
        file=open(p,O_WRONLY|O_CREAT,0666);
        if(file<0){
            printf("file open error");
            goto error;
        }
while (1)
{   

    byt=recv(socket_fd,buf,M,0);
  //  printf("%s",buf);
    if(byt>0/*||errno==EAGAIN||errno==EWOULDBLOCK||errno==EINTR*/){ 
        write(file,buf,byt);
 //       printf("%s",buf);
    }
    else break;
}
close(file);
error:
    close(socket_fd);
}


//=====================获取服务器列表函数==========================
void list(struct sockaddr_in servaddr){
    int socket_fd,byt;
   char buf[M];
    socket_fd=socket(AF_INET,SOCK_STREAM,0);     //创建socket
    if(socket_fd==0){
        printf("创建socket失败\n");
        goto error;
    }
    if(connect(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        printf("connect failed !!\n");
       goto error;
    }
    strcpy(buf, "l");
    send(socket_fd, buf, M, 0);
    struct timeval timeout; 
    timeout.tv_sec =1;
    timeout.tv_usec=1000;
    setsockopt(socket_fd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout.tv_sec,sizeof(struct timeval));
while (1)
{
    byt = recv(socket_fd, buf, M, 0);
    if(byt>0)
           printf("%s\n", buf);
        else  break;
}
printf("列表获取完毕\n");
error:
close(socket_fd);
}


void print(){
    printf("qwer\n");
}
