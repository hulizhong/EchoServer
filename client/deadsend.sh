#!/bin/bash

begtm=`date +%s`
for (( i=0; i<500; i++ ))
do
    /home/hulz/cli &
done
endtm=`date +%s`
let tm=$begtm-$endtm
echo "use $tm second, $begtm -> $endtm"
