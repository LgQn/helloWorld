#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

#define MAX_FILE_LEN  (1024*30)
#define DOWNLOAD_FILE_PATH  "../../server/file/"
char fname[512];
int main(){
    FILE *fp=NULL;
    char filebuf[MAX_FILE_LEN];
    char path[1024],*l;
    struct stat sb;
    int getname(char p[]);

 /*   printf("Content-type:text/html;charset=UTF-8\n\n");
    printf("<html>");
    printf("<head><title>list</title></head>");
    printf("<p>");
*/

    int len=atoi(getenv("CONTENT_LENGTH"));
    char p[sizeof(char)*len];
    fread(p,1,len,stdin);
    getname(p);

    sprintf(path,"%s%s",DOWNLOAD_FILE_PATH,fname);
 //   printf("<br/>path:%s",path);
    l=path;
    if(stat(l,&sb)<0){                                        //取待下载文件的大小
        return 1;
    }        

//==============输出HTTP头信息，输出附加下载文件、文件长度以及内容类型==================

    printf("Content-Disposition:attachment;filename=\"%s\"",fname);
    printf("\r\n"); 
    printf("Content-Length:%ld",sb.st_size);
    printf("\r\n");
  //  printf("Accept-Ranges: bytes\r\n");
    printf("Content-Type:application/octet-stream\r\n");
    printf("\r\n");

    if((fp=fopen(l,"r+b"))){            //成功打开文件，读取文件内容
        do{
        int rs=fread(filebuf,1,512,fp);
        fwrite(filebuf,1,rs,stdout);
              }while(!feof(fp));
        fclose(fp);
    }

return 1;
}

int getname(char p[]){
    char x[]="name=\"filename\"",y[]={0x0d,0x0a,0x0d,0x0a,'\0'};
    char *temp1,*temp2;

    temp1=strstr(p,x);
    temp2=strstr(temp1,y);
    temp1=temp2+4;
    sscanf(temp1,"%s",temp2);
//    printf("<br/>temp2:%s",temp2);
    strcpy(fname,temp2);
    return 0;
}
