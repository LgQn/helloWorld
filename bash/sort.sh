#!bin/sh

sort [-bcfMnrtk] [in filename] [out filename]


sort seq.text > result


#
# -b 忽略每行前面开始出现的空格 》从第一个可见字符开始排序
# -c 检查文件是否已经按照顺序排序 》如果乱序输出第一个乱序行的信息并返回1
# -C 检查文件是否已经按照顺序排序 》如果乱序不会输出第一个乱序行的信息仅返回1
# -f 排序时，忽略大小写字母 》将字符转成大写进行比较
# -M 将前面3个字母按照月份的缩写进行排序
# -n 依照数值的大小排序 》防止sort将数值当做字符进行排序
# -o 输出文件，将排序后的结果存入指定文件 》重定向无法输出到源文件而-o可以输出到源文件
# -r 以相反的顺序来排序
# -t 分隔字符 》指定排序时所用的栏位分隔字符将字符串分成区间
# -k 选择以哪个区间进行排序 -k 2
# -u 输出时去除重复行