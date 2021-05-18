while true
do
time ./std < ../data/$T.in > $T.tmp
diff ../data/$T.ans $T.tmp
done