echo "Total word count: "
for file in `ls transcriptions`; do cat transcriptions/$file/transcription.txt; done  | wc -w 

