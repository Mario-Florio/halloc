
OUTPUT=`find ./* -type f -name "*.c"`

gcc $OUTPUT -Wall -o ./main.exe
