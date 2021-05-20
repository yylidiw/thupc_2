while true
do
 python datagen.py > ./data.tmp
 ./plane < ./data.tmp > ./plane.tmp 2> plantd.tmp
 ./std < ./data.tmp > ./std.tmp 2> stdd.tmp
 ./check plantd.tmp stdd.tmp |tee -a 1.tmp
 #diff plane.tmp std.tmp
done