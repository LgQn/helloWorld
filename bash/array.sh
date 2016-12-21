#!/bin/bash
print_array()
{
        echo $*
}


# 1
array=()

array[0]="hello"
array[1]="world"
array[2]="!"

echo ${array[@]}
print_array ${array[@]}

# 2
array=("hello" "world" "!")
echo ${array[@]}

# 3    命名执行结果放入数组
array=($(ls))
echo ${array[@]}

#4  从标准输入读取存入数组，空格分隔数组元素
read -a array
echo ${array[@]}



#
#   unset array 清除数组
#   unset array[1] 清除数组指定元素
#   ${#array[@]} 数组长度
#   ${!array[@]} 数组下标
#   ${array[@]} 数组所有元素
#   for i in ${array[@]} ; do 遍历数组i为数组元素
#   for index in ${!array[@]} 遍历数组index为数组下标
#   ${array[@]:n:m} 从数组的n位置开始取m个元素
#
#
#   总结：
#        1)一般#放在变量内部表示长度 eg: ${#chars} 字符串长度；${#array[@]} 数组长度;
#
#
#
#
#
#
#
#
#
#
#
