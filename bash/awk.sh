#!bin/sh

awk '{pattern + action}' filename
awk -F 'a' '{commands}' filename

#-F : 域分隔符（可选） 指定特定符号作为分隔符 默认为空格
# -f 加载awk脚本

# commands 真正的命令，对分隔后的数据进行处理 $1 $2 $3    $0表示所有域

awk -F ':' '{print $1}' filename

awk  -F ':'  'BEGIN {print "name,shell"}  {print $1","$7} END {print "blue,/bin/nosh"}'
# 添加列名 name，shell  最后一行添加 blue，/bin/nosh
# 先执行begin，读入文件输出，最后执行end


 awk -F ':' '/root/{print $7}' /etc/passwd
# pattern 为root， action 为{print $7}
# 搜索支持正则表达式： '/^root/'   以root开头



#统计/etc/passwd:文件名，每行的行号，每行的列数，对应的完整行内容:
#awk  -F ':'  '{print "filename:" FILENAME ",linenumber:" NR ",columns:" NF ",linecontent:"$0}' /etc/passwd
#awk  -F ':'  '{printf("filename:%10s,linenumber:%s,columns:%s,linecontent:%s\n",FILENAME,NR,NF,$0)}' /etc/passwd
filename:/etc/passwd,linenumber:1,columns:7,linecontent:root:x:0:0:root:/root:/bin/bash
filename:/etc/passwd,linenumber:2,columns:7,linecontent:daemon:x:1:1:daemon:/usr/sbin:/bin/sh
filename:/etc/passwd,linenumber:3,columns:7,linecontent:bin:x:2:2:bin:/bin:/bin/sh
filename:/etc/passwd,linenumber:4,columns:7,linecontent:sys:x:3:3:sys:/dev:/bin/sh

#ARGC               命令行参数个数
#ARGV               命令行参数排列
#ENVIRON            支持队列中系统环境变量的使用
#FILENAME           awk浏览的文件名
#FNR                浏览文件的记录数
#FS                 设置输入域分隔符，等价于命令行 -F选项
#NF                 浏览记录的域的个数
#NR                 已读的记录数
#OFS                输出域分隔符
#ORS                输出记录分隔符
#RS                 控制记录分隔符


#   http://www.cnblogs.com/ggjucheng/archive/2013/01/13/2858470.html




















