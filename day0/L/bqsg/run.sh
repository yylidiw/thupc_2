while true
do
 python datagen.py > ./data.tmp
 ./plane < ./data.tmp > ./plane.tmp
 ./std < ./data.tmp > ./std.tmp
 
  if  diff plane.tmp std.tmp; then #比较两个输出文件
    printf AC #结果相同显示AC
  else
    echo WA #结果不同显示WA，并退出
    #cat tmp.out tmp2.out
    exit 0
  fi 
done