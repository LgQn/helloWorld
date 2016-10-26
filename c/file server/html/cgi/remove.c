#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>
#include<iconv.h>
char fname[512];
int main(){
    char *f="../../server/file/",path[512],*l;
    int a=0;
    int getname(char p[]);

    printf("Content-type:text/html;charset=UTF-8\n\n");
    printf("<html>");
    printf("<head><title>list</title></head>");
    printf("<p>");
    printf("<br/>");

    int len=atoi(getenv("CONTENT_LENGTH"));
    char p[sizeof(char)*len];
    fread(p,1,len,stdin);
    getname(p);
 // printf("size of p:%d",(int)strlen(p));

//    printf("filename:%s",p);
  //  printf("size of p:%d",(int)sizeof(p));
    sprintf(path,"%s%s",f,fname);
    l=path;
  //  printf("l:%s<br/>",l);
   if((a=remove(l))==0)
        printf("文件删除成功");
   else printf("文件删除失败");
   //printf("errno is:%d\n",errno);

    printf("</p>");
    printf("</html>");
    return 0;
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
