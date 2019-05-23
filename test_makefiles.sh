#!/bin/sh

skip_file=../skip_tests.txt
touch ${skip_file}

find ./examples -name Makefile | sort | while read f
do
        mf=`pwd`
        prj=$(realpath $(dirname ${f}) --relative-to="${mf}")
        if cat ${skip_file} | grep "${prj}" >/dev/null; then
            echo "skipping '${prj}'"
            continue
        fi
        echo
        echo "doing '${prj}'"
        make clean > /dev/null 2>&1
        cd "${prj}"
        make
        ret=$?
        cd "$mf"
        if [ $ret -ne 0 ]; then break; fi
        echo "done '${prj}'"
        echo "${prj}" >> ${skip_file}
done

