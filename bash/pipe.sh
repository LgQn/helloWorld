#!/bin/sh

echo "pipe :"

#./test/inOut.sh

a=`cat test/inOut.sh | ./test/inOut.sh` # a为最终输出
echo "pipe status : $a"

exit 0
