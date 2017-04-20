i=0

for file in $( ls ); do
	echo file: $file , $i
	printf -v j "%04d" $i
	cp $file numbered/$j.jpg
	echo $j
	i=$((i+1))
done
