#!/bin/bash

cd /sys/kernel/debug/tracing

echo 0 > tracing_on
echo function > current_tracer
echo > trace
echo 1 > tracing_on
echo 0 > tracing_on
#cat trace


while getopts 'lp:c:f:' arg;
do
	case $arg in
		l)
			cat trace;;
		p) 
			echo > trace
			echo 0 > tracing_on
			echo "$OPTARG" > current_tracer
			echo 1 > tracing_on
			echo 0 > tracing_on;;
		f)
			echo $OPTARG > set_ftrace_filter;;
		c) 
			cat $OPTARG;;
		?)	
			echo "unkonw command"
			echo "$OPTARG";;
	esac
done

