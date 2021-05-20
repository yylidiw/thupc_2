while true
do
time ./plane < ../data/$T.in > $T.tmp
diff ../data/$T.ans $T.tmp
done