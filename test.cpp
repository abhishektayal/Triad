kill -9 `ps -aux | grep -i .\/projc\ conf.txt | awk '{print $2}'`


