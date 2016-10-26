 #include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>
#include<iconv.h>
char fname[512];          //存取文件名
int main(){
    char path[1024]="../../server/file/";
    int getname(char *p);
    int flen;
    int getdata(char *p,char data[]);
    FILE *fp;

    printf("Content-type:text/html;charset=UTF-8\n\n");
    printf("<html>");
    printf("<head><title>list</title></head>");
    printf("<p>");
 
    int len=atoi(getenv("CONTENT_LENGTH"));      //获取数据长度
 //   printf("len:%d",len);
    char p[sizeof(char)*len];        //定义数据存储数组

    fread(p,1,len,stdin);            //从标准输入流读取文件
  //  printf("p:%s<br/>",p);
    getname(p);                     //获取文件名
 //   printf("fname:%s  ",fname);
    strcat(path,fname);               //整合文件路径和文件名
 //   printf("path:%s  ",path);
    char data[len];
    flen=getdata(p,data);                      //获取文件内容

    fp=fopen(path,"wb");
    if(fp==NULL){
        printf("文件创建失败！");
        return -1;
    }
    int w=fwrite(data,1,flen,fp);
    if(w<0){
        printf("文件写入失败！");
            return 0;
    }else
        printf("文件上传成功！");

    printf("</p>");
    printf("</html>");
    return 0;
}

//===============获取文件名=======================
int getname(char *p){
  char x[]="filename=";
  char *name=NULL;
  char name1[512];
  int len;

  name=strstr(p,x);            //匹配模式找filename=
  sscanf(name,"filename=\"%s",name1);        //获取文件名
 // printf("name:%s  ",name1);
  len=strlen(name1);
 // printf("len:%d  ",len);
  name1[len-1]='\0';                      //消除文件名后的"
 // printf("name1:%s  <br/>",name1);
  strcpy(fname,name1);
  return 0;
}

//================获取文件数据======================
int getdata(char *p,char data[]){
  char x[]="Content-Type",y[]={0x0d,0x0a,0x0d,0x0a,'\0'},z[]="-----------------";
  char *temp1,*temp2;

  temp1=strstr(p,x);
//  printf("<br/>temp1:%s",temp1);
  temp2=strstr(temp1,y);
//  printf("<br/>temp2:%s",temp2);
  temp1=temp2+4;
//  printf("<br/>temp1:%s",temp1);
  temp2=strstr(temp1,z);
//  printf("<br/>temp2:%s",temp2);
  int tlen2=strlen(temp2);
  int tlen1=strlen(temp1);
  temp1[tlen1-tlen2-2]='\0';
//  printf("<br/>temp1:%s",temp1);
  strcpy(data,temp1);
//  printf("<br/>data:%s",data);
  return (tlen1-tlen2-2);
}
