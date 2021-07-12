#!/bin/bash

mode="r"
origin_wd=`pwd`
wd=`echo ~`
tb="$wd/2017203014_TrashBin"
declare -i selected_page=0
declare -i selected_index=0

declare -a files=()
declare -a files_type=()

declare -i dirs_num=0
declare -i cfiles_num=0
declare -i efiles_num=0
declare -i rfiles_num=0

declare -a tree_files=() #relative path of files
declare -A tree_files_type=() #type of files
declare -A tree_files_expanded=() #stat of directory expanded
declare -a tree_files_depth=() #files depth for drawing
declare -i tree_selected_page=0
declare -i tree_selected_index=0
declare -i tree_index=0

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

	dirs_num=0
	cfiles_num=0
	efiles_num=0
	rfiles_num=0

	read_files
	draw_list
	draw_total
}

draw_list() {
	declare -i index=$selected_page*28
	declare -i max_count=$index+28
	if [ $max_count -gt ${#files[*]} ];then
		max_count=${#files[*]}
	fi

	for((i=0; i<28 && index<max_count; i++, index++))
	do
		name=${files[$index]}
		type=${files_type[$index]}
		if [ ${#name} -gt 28 ];then
			name=${name:0:25}"..."
		fi

		color=""
		case "$type" in
		"d") color="[1m[34m";;
		"t") color="[1m[33m";;
		"c") color="[1m[31m";;
		"e") color="[1m[32m";;
		"r") color="[0m[37m";;
		esac
		echo "$color"

		declare -i pos=$i+2
		if [ $i -eq $selected_index ];then
			case "$type" in
			"d") echo "[44m[37m";;
			"t") echo "[43m[37m";;
			"c") echo "[41m[37m";;
			"e") echo "[42m[37m";;
			"r") echo "[47m[30m";;
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
	path="$wd/$name"
	size=`stat -c "%s" $path`
	size_unit="B"
	stat=`stat -c "%x" $path`
	per=`stat -c "%a" $path`

	if [ $abs_sel_index -eq 0 ];then
		cd $path
		path=`pwd`
		cd $origin_wd
	fi
	if [ ${#name} -gt 107 ];then
		name=${name:0:104}"..."
	fi
	if [ ${#path} -gt 103 ];then
		path=${path:0:100}"..."
	fi
	case "${files_type[$abs_sel_index]}" in
	"d") type="Directory";;
	"t") type="TrashBin";;
	"r") type="Regular File";;
	"e") type="Execute File";;
	"c") type="Compressed File";;
	esac
	if [ $size -ge 1024 ];then
		size=`expr $size / 1024`
		size_unit="K"
		if [ $size -ge 1024 ];then
			size=`expr $size / 1024`
			size_unit="M"
			if [ $size -ge 1024 ];then
				size=`expr $size / 1024`
				size_unit="G"
			fi
		fi
	fi
	case `echo $stat | awk '{print $1}' | awk -F '-' '{print $2}'` in
	01) atime="Jan";;  02) atime="Feb";;  03) atime="Mar";;  04) atime="Apr";;
	05) atime="May";;  06) atime="Jun";;  07) atime="Jul";;  08) atime="Aug";;
	09) atime="Sep";;  10) atime="Oct";;  11) atime="Nov";;  12) atime="Dec";;
	esac
	atime="$atime `echo $stat | awk '{print $1}' | awk -F '-' '{print $3}'`"
	atime="$atime `echo $stat | awk '{print $2}' | awk -F '.' '{print $1}'`"
	atime="$atime `echo $stat | awk '{print $1}' | awk -F '-' '{print $1}'`"

	tput cup 31 1
	echo "File name: $name"

	tput cup 32 1
	echo "File type: $color$type[0m"

	tput cup 33 1
	echo "File size: $size$size_unit"

	tput cup 34 1
	echo "Access time: $atime"

	tput cup 35 1
	echo "Permission: $per"

	tput cup 36 1
	echo "Absolute path: $path$color"
}
draw_total() {
	declare -i dir=$dirs_num
	declare -i Sfile=$cfiles_num+$efiles_num
	declare -i Nfile=$rfiles_num
	declare -i total=$dir+$Sfile+$Nfile
	size=`du -sh $wd | awk '{print $1}'`"B"

	tput cup 38 30
	echo "Total: $total, Directory: $dir, SFile: $Sfile, NFile: $Nfile, Size: $size"

	tput cup 38 2
	declare -i max_page=`expr ${#files[*]} - 1`/28+1
	echo "List: `expr $selected_page + 1`/$max_page"
}
draw_filetext() {
	declare -i line_num=`cat $wd/$1 | wc -l`
	if [ $line_num -gt 28 ];then
		line_num=28
	fi
	for((i=1; i<=line_num; i++))
	do
		text=`cat $wd/$1 | head -n $i | tail -n 1 | sed 's/\t/ /g'`
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
clear_tree() {
	for((i=2; i<30; i++))
	do
		tput cup $i 77
		echo "                                          "
	done
	tput cup 38 109
	echo "         "
}
draw_tree() {
	declare -i index=$tree_selected_page*28
	declare -i max_count=$index+28
	if [ $max_count -gt ${#tree_files[*]} ];then
		max_count=${#tree_files[*]}
	fi

	for((i=0; i<28 && index<max_count; i++, index++))
	do
		name=${tree_files[$index]}
		type=${tree_files_type[$name]}
		expanded=${tree_files_expanded[$name]}
		depth=${tree_files_depth[$index]}
		name=`echo $name | cut -d"/" -f$depth`
		text=""

		for((j=1; j<depth; j++))
		do
			text="...."$text
		done
		if [ $depth -gt 1 ];then
			text=$text" "
		fi
		if [ $type = "d" ];then
			if [ ${#expanded} -gt 0 ];then
				text=$text"-"
			else
				text=$text"+"
			fi
		else
			text=$text" "
		fi
		if [ $i -eq $tree_selected_index ];then
			case "$type" in
			"d") color="[44m[37m";;
			"t") color="[43m[37m";;
			"c") color="[41m[37m";;
			"e") color="[42m[37m";;
			"r") color="[47m[30m";;
			esac
			text=$text"[1m"$color$name
			if [ ${#text} -gt 56 ];then
				text=${text:0:53}"..."
			fi
		else
			case "$type" in
			"d") color="[1m[34m";;
			"t") color="[1m[33m";;
			"c") color="[1m[31m";;
			"e") color="[1m[32m";;
			"r") color="[0m[37m";;
			esac
			text=$text$color$name
			if [ ${#text} -gt 51 ];then
				text=${text:0:48}"..."
			fi
		fi
		text=$text"[0m"

		tput cup `expr $i + 2` 77
		echo "$text"
#		tput cup `expr $i + 2` 122		#debug
#		echo "$name $type $expanded $depth"	#debug
	done

	declare -i max_page=`expr ${#tree_files[*]} - 1`/28+1
	text="Tree: `expr $tree_selected_page + 1`/$max_page"
	tput cup 38 `expr 118 - ${#text}`
	echo $text
}

read_files() {
	files[0]=".."; files_type[0]="d"
	declare -i index=1

	if [ $wd = `echo ~` ];then
		dirs=`ls -l $wd | grep    '^d' | awk '{print $NF}' | grep -v '^2017203014_TrashBin$'`
		files[1]="2017203014_TrashBin"; files_type[1]="t"
		index=$index+1
	else
		dirs=`ls -l $wd | grep    '^d' | awk '{print $NF}'`
	fi
	cfiles=`ls -l $wd | grep -v '^d' | egrep    '(\.zip|\.tar\.gz)$' | awk '{print $NF}'`
	efiles=`ls -l $wd | grep -v '^d' | egrep -v '(\.zip|\.tar\.gz)$' | grep -v '...-..-..-' | tail -n +2 | awk '{print $NF}'`
	rfiles=`ls -l $wd | grep -v '^d' | egrep -v '(\.zip|\.tar\.gz)$' | grep    '...-..-..-' | awk '{print $NF}'`

	for((i=0; i<4; i++))
	do
		declare -a names=()
		case "$i" in
		0)
			names=$dirs
			type="d";;
		1)
			names=$cfiles
			type="c";;
		2)
			names=$efiles
			type="e";;
		3)
			names=$rfiles
			type="r";;
		esac
		for name in $names
		do
			case "$type" in
			"d") dirs_num=$dirs_num+1;;
			"c") cfiles_num=$cfiles_num+1;;
			"e") efiles_num=$efiles_num+1;;
			"r") rfiles_num=$rfiles_num+1;;
			esac
			files[$index]=$name
			files_type[$index]=$type
			index=$index+1
		done
	done
}
read_tree_files() {
	tree_files[$tree_index]=$2
	tree_files_depth[$tree_index]=$1
	tree_index=$tree_index+1

	if [ ${#tree_files_expanded[$2]} -gt 0 ];then
		for name in `ls -l $wd/$2 | grep '^d' | awk '{print $NF}' | grep -v '^2017203014_TrashBin$'`
		do
			tree_files_type["$2/$name"]="d"
			read_tree_files `expr $1 + 1` "$2/$name"
		done

		for name in `ls -l $wd/$2 | grep -v '^d' | egrep '(\.zip|\.tar\.gz)$' | awk '{print $NF}'`
		do
			tree_files_type["$2/$name"]="c"
			read_tree_files `expr $1 + 1` "$2/$name"
		done

		for name in `ls -l $wd/$2 | grep -v '^d' | egrep -v '(\.zip|\.tar\.gz)$' | grep -v '...-..-..-' | tail -n +2 | awk '{print $NF}'`
		do
			tree_files_type["$2/$name"]="e"
			read_tree_files `expr $1 + 1` "$2/$name"
		done

		for name in `ls -l $wd/$2 | grep -v '^d' | egrep -v '(\.zip|\.tar\.gz)$' | grep    '...-..-..-' | awk '{print $NF}'`
		do
			tree_files_type["$2/$name"]="r"
			read_tree_files `expr $1 + 1` "$2/$name"
		done
	fi
}
delete() {
	random_name=`cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w 4 | sed 1q`".tar"
	while [ -f "$tb/$random_name" ]
	do
		random_name=`cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w 4 | sed 1q`".tar"
	done
	declare -i abs_sel_index=$selected_page*28+$selected_index
	tar -C $wd -cf "$tb/$random_name" ${files[$abs_sel_index]}
	tar -C $tb -xf "$tb/$random_name"
	rm -rf "$tb/$random_name"
	rm -rf  "$wd/${files[$abs_sel_index]}"
}

get_key() {
	if [ $mode = "r" ];then
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
			if [ $abs_sel_index -lt `expr ${#files[*]} - 1` ];then
				selected_index=$selected_index+1
				if [ $selected_index -ge 28 ];then
					selected_page=$selected_page+1
					selected_index=0
				fi
				init
			fi;;
		"C")
			declare -i max_page=${#files[*]}-1
			declare -i max_index=$max_page%28
			max_page=$max_page/28
			if [ $selected_page -lt $max_page ];then
				selected_page=$selected_page+1
				if [ $selected_index -gt $max_index ];then
					selected_index=$max_index
				fi
				init
			elif [ $selected_index -lt $max_index ];then
				selected_index=$max_index
				init
			fi;;
		"D")
			if [ $selected_page -gt 0 ];then
				selected_page=$selected_page-1
				init
			elif [ $selected_index -gt 0 ];then
				selected_index=0
				init
			fi;;
		esac
		fi
		elif [ ${#key} -eq 0 ];then
			declare -i abs_sel_index=$selected_page*28+$selected_index
			line=`ls -al | grep " ${fies_type[$abs_sel_index]}$"`
			if [ ${files_type[$abs_sel_index]} = "d" ] || [ ${files_type[$abs_sel_index]} = "t" ];then
				wd=$wd"/"${files[$abs_sel_index]}
				if [ $abs_sel_index -eq 0 ];then
					cd $wd
					wd=`pwd`
					cd $origin_wd
				fi
				selected_page=0
				selected_index=0
				init
			else
				draw_filetext ${files[$abs_sel_index]}
			fi
		elif [ $key = "d" ] || [ $key = "D" ];then
			declare -i abs_sel_index=$selected_page*28+$selected_index
			declare -i home=0
			if [ $wd = `echo ~` ];then
				home=1
			fi
			if [ $abs_sel_index -gt $home ];then
				if [ $wd = $tb ];then
					rm -rf "$tb/${files[$abs_sel_index]}"
				else
					delete
				fi
				if [ `expr $abs_sel_index + 1` -ge ${#files[*]} ];then
					selected_index=$selected_index-1
				fi
				init
			fi
		elif [ $key = "t" ] || [ $key = "T" ];then
			declare -i abs_sel_index=$selected_page*28+$selected_index
			if [ $abs_sel_index -gt 0 ] && [ ${files_type[$abs_sel_index]} = "d" ];then
				mode="t"
				name=${files[$abs_sel_index]}
				short_name=$name
				if [ ${#name} -gt 28 ];then
					short_name=${name:0:25}"..."
				fi
				tput cup `expr $selected_index + 2` 1
				echo "[1m[34m$short_name[0m"

				tree_files=()
				tree_files_type=( [$name]="d" )
				tree_files_expanded=( [$name]="1" )
				tree_files_depth=()
				tree_selected_page=0
				tree_selected_index=0
				tree_index=0
				read_tree_files 1 $name
				clear_tree
				draw_tree
			fi
		fi
	elif [ $mode = "t" ];then
		read -sn 1 key
		case "$key" in
		"A")
			if [ $tree_selected_index -gt 0 ];then
				tree_selected_index=$tree_selected_index-1
				init
				draw_tree
			elif [ $tree_selected_page -gt 0 ];then
				tree_selected_page=$tree_selected_page-1
				tree_selected_index=27
				init
				draw_tree
			fi;;
		"B")
			declare -i abs_sel_index=$tree_selected_page*28+$tree_selected_index
			if [ $abs_sel_index -lt `expr ${#tree_files[*]} - 1` ];then
				tree_selected_index=$tree_selected_index+1
				if [ $tree_selected_index -ge 28 ];then
					tree_elected_page=$tree_selected_page+1
					tree_selected_index=0
				fi
				init
				draw_tree
			fi;;
		"C")
			declare -i max_page=${#tree_files[*]}-1
			declare -i max_index=$max_page%28
			max_page=$max_page/28
			if [ $tree_selected_page -lt $max_page ];then
				tree_selected_page=$tree_selected_page+1
				if [ $tree_selected_index -gt $max_index ];then
					tree_selected_index=$max_index
				fi
				init
				draw_tree
			elif [ $tree_selected_index -lt $max_index ];then
				tree_selected_index=$max_index
				init
				draw_tree
			fi;;
		"D")
			if [ $tree_selected_page -gt 0 ];then
				tree_selected_page=$tree_selected_page-1
				init
				draw_tree
			elif [ $tree_selected_index -gt 0 ];then
				tree_selected_index=0
				init
				draw_tree
			fi;;
		esac
		if [ ${#key} -eq 0 ];then
			declare -i abs_tree_sel_index=$tree_selected_page*28+$tree_selected_index
			if [ ${tree_files_type[${tree_files[$abs_tree_sel_index]}]} = "d" ];then
				if [ ${#tree_files_expanded[${tree_files[$abs_tree_sel_index]}]} -gt 0 ];then
					tree_files_expanded[${tree_files[$abs_tree_sel_index]}]=""
				else
					tree_files_expanded[${tree_files[$abs_tree_sel_index]}]="1"
				fi

				declare -i abs_sel_index=$selected_page*28+$selected_index
				tree_files=()
				tree_files_depth=()
				tree_index=0

				read_tree_files 1 ${files[$abs_sel_index]}
				init
				draw_tree
			fi
		elif [ $key = "r" ] || [ $key = "R" ];then
			mode="r"
			init
		fi
	fi
}

main() {
	if [ ! -d ~/2017203014_TrashBin ];then
		mkdir ~/2017203014_TrashBin
	fi
	init
	while true
	do
		get_key
	done
}

main
