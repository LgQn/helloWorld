#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>   
#include<dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include<time.h>

#define M 1024

int main(){
    char buf[M];char path[1024];
    DIR *mydir;
    struct dirent *myitem;
    struct stat buff;
    time_t time;

    mydir = opendir("../../server/file");
    printf("Content-type:text/html;charset=UTF-8\n\n");
    printf("<html>");
    printf("<head><title>list</title></head>");
    printf("<p>");
    printf("<table border=\"0\" width=100%% >");

    printf("<tr>");
    printf("<td align=\"center\">文件名</td>");
    printf("<td align=\"center\">最近修改日期</td>");
    printf("<td align=\"center\">文件大小</td>");
    printf("</tr>");

    while ((myitem = readdir(mydir)) != NULL)
    {
       if ((strcmp(myitem->d_name, ".") == 0) || (strcmp(myitem->d_name, "..") == 0)) continue;
        strcpy(buf, myitem->d_name);
        sprintf(path,"%s\%s","../../server/file/",buf);
        stat(path,&buff);
        printf("<tr>");
        printf("<td align=\"center\">%s</td>", buf);
        time=buff.st_mtime;
        printf("<td align=\"center\">%s</td>",ctime(&time));
        printf("<td align=\"center\">%ldkb</td>", buff.st_size);
        printf("</tr>");
    }

    closedir(mydir);

printf("</table>");
printf("</p>");
printf("</html>");
return 0;
}
