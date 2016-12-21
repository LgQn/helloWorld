#!/bin/bash


./test/exitStatus.sh

echo "exitStatus output : $?" # $?输出上一句bash的状态

var1=2     #等号左右不能有空格

echo "last exit status : $?"

echo $var1

#变量字符串替换
test="abcddabc"
echo ${test//"abc"/"e"}























