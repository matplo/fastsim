#!/bin/bash

function usage
{
	ex=`basename $BASH_SOURCE`
	echo "[i] usage: $ex [-$1]"
}

cmndargs=$*
function check_for_errors
{
	optstring=$1
	#opts=${@:2}
	#echo "check_for_errors optstring:" $optstring "opts:" $cmndargs
	args=`getopt $optstring $cmndargs 2>&1 > /dev/null` ; errcode=$?; set -- $args
	if [ $errcode != 0 ]; then
		echo "[e] unknown or invalid argument(s) given"
		usage $optstring
		return 2
	fi	
	return $errcode
}

function is_arg_set
{
	pattern=$1
	args=`getopt $optstring $cmndargs` ; errcode=$?; set -- $args
	#echo "[is_arg_set] args found: $args"
	for o in $args
	do
		case $o in
				$pattern )
					#echo "$pattern is set"
					return 0
					;;
				-- )
					break;;
		esac	
	done
	return 1
}

function arg_with
{
	pattern=$1
	args=`getopt $optstring $cmndargs` ; errcode=$?; set -- $args
	#echo "[arg_with] found args are:"$args
	oarg=""
	for o in $args
	do
		case "$o" in
				$pattern )
					#echo "[get_arg] arg for $pattern is" "'"$2"'"; 
					oarg="$2"; shift;
					shift;;
				-- )
					break;;
		esac	
	done
	echo $oarg
}

optstring="ho:"
check_for_errors $optstring "$*"
if [ $? != 0 ]; then exit 2; fi

help=false
if is_arg_set "-h"; then help=true; fi
output=`arg_with "-o"`
echo "[i] output: "$output
if $help; then usage $optstring ; exit 0; fi
