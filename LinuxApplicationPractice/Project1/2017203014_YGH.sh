#!/bin/bash

origin_rd=`pwd`
rd=$origin_rd
declare -i selected_page=0
declare -i selected_index=0
declare -a files=()
declare -a files_type=()
declare -i files_num=0
declare -i dirs_num=0
declare -i cfiles_num=0
declare -i rfiles_num=0
declare -i efiles_num=0

init() {
	clear
	echo "=============================================== 2017203014 Gyeongho Yang ==============================================="
	echo "========================================================= List ========================================================="
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "|                            |                                              |                                          |"
	echo "====================================================== Information ====================================================="
	echo "|                                                                                                                      |"
	echo "|                                                                                                                      |"
	echo "|                                                                                                                      |"
	echo "|                                                                                                                      |"
	echo "|                                                                                                                      |"
	echo "|                                                                                                                      |"
	echo "========================================================= Total ========================================================"
	echo "|                                                                                                                      |"
	echo "========================================================== END ========================================================="

	files=()
	files_type=()
	files_num=0
	dirs_num=0
	cfiles_num=0
	rfiles_num=0
	efiles_num=0

	draw_list
	draw_total $rd
}

draw_list() {
	read_files

	declare -i index=$selected_page*28
	declare -i max_index=$index+28
	if [ $max_index -gt $files_num ];then
		max_index=$files_num
	fi

	for((i=0 ; i<28 && index<=max_index; i++, index++))
	do
		name=${files[$index]}
		type=${files_type[$index]}
		if [ ${#name} -gt 28 ];then
			name=${name:0:25}"..."
		fi

		color=""
		case "$type" in
		"d") color="[34m[1m";;
		"c") color="[31m[1m";;
		"r") color="[0m[37m";;
		"e") color="[32m[1m";;
		esac
		echo "$color"

		declare -i pos=$i+2
		if [ $i -eq $selected_index ];then
			case "$type" in
			"d") echo "[44m[37m";;
			"c") echo "[41m[37m";;
			"r") echo "[47m[30m";;
			"e") echo "[42m[37m";;
			esac
			tput cup $pos 1
			echo "$name[0m"
			draw_info $color
		else
			tput cup $pos 1
			echo "$name"
		fi
	done
	echo "[0m"
}
draw_info() {
	declare -i abs_sel_index=$selected_page*28+$selected_index
	name=${files[$abs_sel_index]}
	color=$1
	type=""
	path="$rd/$name"
	size=`stat -c "%s" $path`
	atime=`stat -c "%x" $path`
	per=`stat -c "%a" $path`

	if [ ${#name} -gt 106 ];then
		name=${name:0:103}"..."
	fi
	if [ ${#path} -gt 102 ];then
		path=${path:0:99}"..."
	fi
	case "${files_type[$abs_sel_index]}" in
	"d") type="directory";;
	"r") type="regular file";;
	"e") type="execute file";;
	"c") type="compressed file";;
	esac

	tput cup 31 1
	echo "file name : $name"

	tput cup 32 1
	echo "$color""file type : $type[0m"

	tput cup 33 1
	echo "file size : $size"

	tput cup 34 1
	echo "access time : $atime"

	tput cup 35 1
	echo "permission : $per"

	tput cup 36 1
	echo "absolute path : $path$color"
}
draw_total() {
	declare -i total=$files_num-1
	declare -i dir=$dirs_num-1
	declare -i file=$rfiles_num
	declare -i Sfile=$cfiles_num+$efiles_num
	declare -i byte=`du $1 | tail -n 1 | awk '{print $1}'`

	tput cup 38 20
	echo "$files_num total   $dir dir   $file file   $Sfile Sfile   $byte byte"

	tput cup 38 1
	declare -i max_page=$files_num/28+1
	echo "`expr $selected_page + 1`/$max_page page"
}
read_files() {
	dirs=`ls -al $rd | tail -n +3 | grep '^d' | awk '{print $NF}'`
	cfiles=`ls -al $rd | grep -v '^d' | awk '{print $NF}' | egrep '(\.zip$|\.tar\.gz)$'`
	rfiles=`ls -al $rd | tail -n +2 | grep -v '^d' | awk '{print $NF}' | egrep -v '(\.zip|\.tar\.gz|\.sh|\.out)$'`
	efiles=`ls -al $rd | grep -v '^d' | awk '{print $NF}' | egrep '(\.sh$|\.out)$'`

	declare -i index=0
	for((i=0; i<8; i++))
	do
		declare -a names=()
		type=""
		case "$i" in
		0|4)
			names=$dirs
			type="d";;
		1|5)
			names=$cfiles
			type="c";;
		2|6)
			names=$rfiles
			type="r";;
		3|7)
			names=$efiles
			type="e";;
		esac
		for name in $names
		do
			if [ $i -lt 4 ] && [ ${name:0:1} != '.' ];then
				break
			fi
			if [ $i -ge 4 ] && [ ${name:0:1} = '.' ];then
				continue
			fi
			case "$type" in
			"d") dirs_num=$dirs_num+1;;
			"c") cfiles_num=$cfiles_num+1;;
			"r") rfiles_num=$rfiles_num+1;;
			"e") efiles_num=$efiles_num+1;;
			esac
			files[$index]=$name
			files_type[$index]=$type
			index=$index+1
		done
	done
	files_num=$index-1
}
open_file() {
	declare -i line_num=`cat $rd/$1 | wc -l`
	if [ $line_num -gt 28 ];then
		line_num=28
	fi
	for((i=1; i<=line_num; i++))
	do
		text=`cat $rd/$1 | head -n $i | tail -n 1 | sed 's/\t/ /g'`
		if [ ${#text} -gt 41 ];then
			text=${text:0:38}"..."
		fi
		declare -i pos=$i+1
		tput cup $pos 30
		line="$i   "
		echo "${line:0:4} $text"
		pos=$pos+1
	done
}

get_key() {
	read -sn 1 key
	if [ "$key" = "" ];then
	read -sn 1 key
	if [ "$key" = "[" ];then
	read -sn 1 key
	case "$key" in
		"A")
			if [ $selected_index -gt 0 ];then
				selected_index=$selected_index-1
				init
			elif [ $selected_page -gt 0 ];then
				selected_page=$selected_page-1
				selected_index=27
				init
			fi;;
		"B")
			declare -i abs_sel_index=$selected_page*28+$selected_index
			if [ $abs_sel_index -lt $files_num ];then
				selected_index=$selected_index+1
				if [ $selected_index -ge 28 ];then
					selected_page=$selected_page+1
					selected_index=0
				fi
				init
			fi;;
	esac
	fi
	elif [ ${#key} -eq 0 ];then
		declare -i abs_sel_index=$selected_page*28+$selected_index
		line=`ls -al | grep " ${fies_type[$abs_sel_index]}$"`
		if [ ${files_type[$abs_sel_index]} = "d" ];then
			rd=$rd"/"${files[$abs_sel_index]}
			if [ $abs_sel_index -eq 0 ];then
				cd $rd
				rd=`pwd`
				cd $origin_rd
			fi
			selected_page=0
			selected_index=0
			init
		else
			open_file ${files[$abs_sel_index]}
		fi
	fi
}

main() {
	init
	while true
	do
		get_key
	done
}

main
