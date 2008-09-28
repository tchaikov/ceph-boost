#! /bin/sh

libs='date_time 
filesystem 
graph 
iostreams 
math
program_options 
python 
regex 
serialization
signals
system
test
thread
wave'

for l in $libs; do
    for f in $libs; do
	[ $l = $f ] && continue
	rgrep -q boost/$f /usr/include/boost/$l && echo $l depends on $f
    done
done
