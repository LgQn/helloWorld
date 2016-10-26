/* File Name: server.c */  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<unistd.h>
#include<dirent.h>
#include<netinet/in.h>  
#include<errno.h> 
#include<fcntl.h>

#define DEFAULT_PORT 8888  
#define MAXLINE 4096 
#define M 1024

void list(int connect_fd);
void delete(int connect_fd,char buf[M]);
void download(int connect_fd,char buf[M]);
void upload(int connect_fd,char buf[M]);

int main(){
    int socket_fd,connect_fd;
    struct sockaddr_in  servaddr;
    char buf[M];

    socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd<0){
        printf("fial to socket\n");
       goto error;
    }

     memset(&servaddr, 0, sizeof(servaddr));  
     servaddr.sin_family = AF_INET;  
     servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
     servaddr.sin_port = htons(DEFAULT_PORT);//设置的端口为DEFAULT_PORT 
int optval = 1;
setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
     if(bind(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1){
         printf("bind fail\n");
        goto error;
     }
     if(listen(socket_fd,5)==-1){
         printf("listen fail\n");
        goto error;
     }

     printf("please waiting for connect=======\n");
     while(1){
         connect_fd=accept(socket_fd,NULL,NULL);
         if(connect_fd<0){
             printf("fail to connect\n");
             continue;
         }
         recv(connect_fd,buf,M,0);
         switch(buf[0]){
             case 'l':
                 list(connect_fd);break;
             case 'e':
                 delete(connect_fd,buf);break;
             case 'd':
                 download(connect_fd,buf);break;
             case 'u':
                 upload(connect_fd,buf);break;
             default:
                 printf("error command\n");break;
         }
     }
error:
     close(socket_fd);
     return 0;
}

//================客户端上传文件==================
void upload(int connect_fd,char buf[M]){
    int byt=0,file=0;
    char path[M];
    char *p="../file/";

    sprintf(path,"%s\%s","../file/",buf+1);
    file=open(path,O_WRONLY|O_CREAT,00777);
    if(file<0){
        printf("file open error");
        return;
    }

    struct timeval timeout; 
    timeout.tv_sec =1;
    timeout.tv_usec=1000;
    setsockopt(connect_fd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout.tv_sec,sizeof(struct timeval));

    while(1){
        byt=recv(connect_fd,buf,M,0);
    //    printf("%s",buf);
        if(byt>0||errno==EAGAIN||errno==EWOULDBLOCK||errno==EINTR){
            write(file,buf,byt);
     //       printf("%s",buf);
        }
        else break;
    }

    close(file);
}



//=====================下载服务器文件====================
void download(int connect_fd,char buf[M]){
    int fp,byt,x;
    char *path="../file/";
    char buff[M];
    sprintf(buff,"%s\%s",path,buf+1);
    printf("%s",buff);
  //  x=strlen(buff);
  //  buff[x-1]='\0';
//    printf("%s\n",buff);
    fp=open(buff,O_RDONLY);
    if(fp==-1){
        printf("file open error!\n");
        buf[0]='N';
        if( send(connect_fd,buf,M,0)>0){

        }else{
           printf("send fail\n");
           printf("error is %d",errno);
       }
        return;
    }
    else{
        buf[0]='Y';
        if(send(connect_fd,buf,M,0)>0){}
        else{
            printf("send error");
            printf("errno is %d",errno);
        }
    }
   char bufff[M]={};
 do{
        byt=read(fp,bufff,128);
 //       printf("%s",bufff);
        send(connect_fd,bufff,byt,0);
   //     printf("%s",bufff);
    }while(byt>0);
 printf("文件下载完成\n");
  //  fclose(fp);
 //   closedir(dir);
}


//=====================删除服务器文件=================
void delete(int connect_fd,char buf[M]){
    int x,y;
    char *p;
    char *a="../file/";
    char path[M];
    memset(path,0,sizeof(path));
  //  printf("buf:%s",buf+1);
    sprintf(path,"%s%s",a,buf+1);
//int i = 0;
//for(i=1;i<strlen(buf);i++)
   // printf("%c",buf[i]);
//printf("\n");
    p=path;
    y=(int)strlen(p);
    p[y-1]='\0';
//    printf("%s",p);
    x=remove(p);
//    printf("errno is:%d\n",errno);
    if(x<0){
        buf[0]='N';
        send(connect_fd,buf,M,0);
    }
    else{
        buf[0]='Y';
        send(connect_fd,buf,M,0);
    }
}


//==============传递文件列表函数===================
void list(int connect_fd){
 char buf[M];
DIR *mydir;
struct dirent *myitem;

mydir = opendir("../file");
while ((myitem = readdir(mydir)) != NULL)
{
if ((strcmp(myitem->d_name, ".") == 0) || (strcmp(myitem->d_name, "..") == 0)) continue;
strcpy(buf, myitem->d_name);
send(connect_fd, buf, M, 0);
}
closedir(mydir);

return;
}
