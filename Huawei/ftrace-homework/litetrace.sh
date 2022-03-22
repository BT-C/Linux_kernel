#!/bin/bash

cd /sys/kernel/debug/tracing

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
			echo 1 > tracing_on;;
		f)
			echo > set_ftrace_filter
			echo 0 > tracing_on
			echo > set_ftrace_filter
			echo $OPTARG > set_ftrace_filter
			echo 1 > tracing_on;;
		c) 
			cat $OPTARG;;
		?)	
			echo "unkonw command"
			echo "$OPTARG";;
	esac
done

