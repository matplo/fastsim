#!/bin/bash

sdir=$1

module load run2trigger

[ ! -d "$sdir" ] && exit 1

infiles=`find $sdir -name "out-*.root"`

for fn in $infiles
do
	$RUN2EMCTRIGGER/bin/filter_single_entries --in $fn
done

