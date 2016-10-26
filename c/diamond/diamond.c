#include<stdio.h>
void main(){
    int i;char j;
    void diamond(int x,char y);
    error:;
    printf("请输入行数：");
    scanf("%d",&i);
    if(!(i%2)){
        printf("输入不能为偶数！请重新输入\n");
        goto error;
    }
    printf("请继续输入字符号：");
    getchar();      //用于吸收回车符
    scanf("%c",&j);
    diamond(i,j);
}

void diamond(int x,char y){
    int a,c,d,n,t;    //a:行数  c:中行数  d:tab数  n:符号数循环  t:符号数
    c=x/2;
    for(a=1;a<=c+1;a++){       //行循环
               d=c+1-a;
               t=x-2*d;
               for(;d>0;d--){       //打印tab
                   printf("\t");
                    }
                for(n=1;n<=t;n++){
                   printf("%c\t",y);
               }
       printf("\n");
           }
    for(;a<=x;a++){
        d=a-c-1;
        t=x-2*d;
        for(;d>0;d--){
            printf("\t");
        }
        for(n=1;n<=t;n++){
            printf("%c\t",y);
        }
        printf("\n");
    }

}

