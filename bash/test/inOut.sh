#!/bin/sh

#echo "$#"        #管道数据的输入为stdin，而$*读取的是args

#========通过read读取=========
#read line
#while [ ! -z $line ]
#do
#    echo "from pipe : $line"
#    read line
#done

#=============通过cat读取放入subshell================
echo $(cat) 



exit 0

# $#代表参数个数
# $0代表命令本身
# $0代表第一个参数，后面依次
