#!/bin/sh
shell=$1
if [ x$shell == x ]
then
	echo "You must provide the name of the new shell as arg1." 1>&2
	exit 1
fi
if [ ! -x $shell ]
then
	echo "\"$shell\" is not executable" 1>&2
	exit 1
fi
found=""
for file in *
do
	if [ -f $file ]
	then
		first=`head -1 $file`
		case "$first" in
			\#!/*sh) found="$file $found";;
		esac
	fi
done
for file in $found
do
	echo "#!$shell" > new
	tail +2 $file >> new
	mv new $file
	chmod +x new
done
exit 0
