#!/bin/sh
#/***************************************************************************
# * 
# * Copyright (c) 2010 Baidu.com, Inc. All Rights Reserved
# * 
# **************************************************************************/
#set -x
source ./local_build/local_build.conf

#/**
# * @file local_build.sh
# * @author miaoxiaoxuan@baidu.com
# * @date 2011/05/09/ 13:31:37
# * @version $Revision: 1.0 $ 
# * @brief  本地提交代码前进行测试的脚本, 包含1.编译，2.覆盖率检查，3.静态代码检查，4.已有自动化脚本的运行
# *  
# **/

#记录不同的构建阶段,
ENV=1
MAKE=2
CCOVER_CHECK=3
VITAMIN_CHECK=4
STATIC_ANALYSIS=5
HUDSON_MOUDLE=6
MINISTYLE=7
RESULT=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
TIME=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
#DETAIL=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
DETAIL=(
[$ENV]=$LOG_PATH"ENV.log"
[$MAKE]=$LOG_PATH"MAKE.log"
[$CCOVER_CHECK]=$LOG_PATH"CCOVER_CHECK.log"
[$VITAMIN_CHECK]=$LOG_PATH"VITAMIN_CHECK.log"
[$STATIC_ANALYSIS]=$LOG_PATH"STATIC_ANALYSIS.log"
[$HUDSON_MOUDLE]=$LOG_PATH"HUDSON_MOUDLE.log"
[$MINISTYLE]=$LOG_PATH"MINISTYLE_CHECK.log"
)


LOG_FATAL=1
LOG_FAIL=1
LOG_WARNING=2
LOG_PASS=2
LOG_NOTICE=4
LOG_TRACE=8
LOG_DEBUG=16
LOG_LEVEL_TEXT=(
	[1]="FATAL"
	[2]="WARNING"
	[4]="NOTICE"
	[8]="TRACE"
	[16]="DEBUG"
)

TTY_FATAL=1
TTY_PASS=2
TTY_TRACE=4
TTY_INFO=8
TTY_MODE_TEXT=(
	[1]="[FAIL ]"
	[2]="[PASS ]"
	[4]="[NOTICE]"
	[8]=""
)

#0  OFF  
#1  高亮显示  
#4  underline  
#5  闪烁  
#7  反白显示  
#8  不可见 

#30  40  黑色
#31  41  红色  
#32  42  绿色  
#33  43  黄色  
#34  44  蓝色  
#35  45  紫红色  
#36  46  青蓝色  
#37  47  白色 
TTY_MODE_COLOR=(
	[1]="1;31"	
	[2]="1;32"
	[4]="0;36"	
	[8]="1;33"
)

#****************************************************************
##! @BRIEF: print info to tty & log file
##! @IN[int]: $1 => tty mode
##! @IN[string]: $2 => message
##! @RETURN: 0 => sucess; 1 => failure
#****************************************************************
function Print()
{
	local tty_mode=$1
	local message="$2"
	local time=`date "+%m-%d %H:%M:%S"`
	if [ $LOG_LEVEL -le $tty_mode ]
	then 
		echo "${LOG_LEVEL_TEXT[$tty_mode]}: $time: ${MODULE_NAME} * $$ $message" >> ${LOG_FILE}
	fi
        echo -e "\e[${TTY_MODE_COLOR[$tty_mode]}m${TTY_MODE_TEXT[$tty_mode]} ${message}\e[m"
	return $?
}

#****************************************************************
##! @BRIEF: 编译环境的搭建，更新编译依赖(comake2 -U),编译依赖库(comake2 -B)
##! @RETURN: 0 => sucess; -1 => failure
#****************************************************************
comake2_env()
{
	Print $LOG_NOTICE "download the dependency lib and generate the makefile"	
	TIME_BEFORE_ENV=`date +%s`
	
	if [ ${IS_MAKE_QUICK:-"0"} = "1" ] ; then
        export make_parallel=100 
    fi

	if [ -d ~/.BullseyeCoverage ] ; then
		rm -rf ~/.BullseyeCoverage
	fi

	# COMAKE文件暂由QA维护，编译前进行拷贝
	if [ ! -f ./COMAKE ] ; then

		if [ -f ./local_build/COMAKE ] ; then
			cp ./local_build/COMAKE ./
		else
			Print $LOG_FATAL "Unable to find COMAKE file, create one first!"
		fi
	
	fi

	
	if [ "$make_parallel" == "" ] ; then 
		comake2 -U >> ${LOG_FILE} 2>&1  \
		&& export MAC=64  2>&1  \
		&& comake2 -B >> ${LOG_FILE} 2>&1  \
		&& comake2  >> ${LOG_FILE} 2>&1
	else
		comake2 -U >> ${LOG_FILE} 2>&1  \
        && export MAC=64 2>&1  \
        && comake2 -B -J $make_parallel >> ${LOG_FILE} 2>&1  \
        && comake2 >> ${LOG_FILE} 2>&1
	fi

	ret=$?			
	TIME_AFTER_ENV=`date +%s`
    ENV_TIME=$(($TIME_AFTER_ENV-$TIME_BEFORE_ENV))
    Print $LOG_NOTICE "make environment time: $ENV_TIME(s) !";
	RESULT[$ENV]=$?
	TIME[$ENV]=$ENV_TIME	
	
	if [ $ret -ne 0 ] ; then
		Print $LOG_FATAL  "build the make environment failed !"; 
        STATUS_LIST="$STATUS_LIST\nbuild the make environment failed"; 
		return -1;
	else
		Print $LOG_PASS "build the make environment success !"; 
        STATUS_LIST="$STATUS_LIST\nbuild the make environment success"; 
		return 0;
	fi
}


#****************************************************************
##! @BRIEF: 主要是完成对代码的vitamin check;  静态检查的check,生成可视化报告,发送邮件
#****************************************************************
report_mail()
{
	Print $LOG_NOTICE "report mail !"

###****************************************************************************

#check if the modules are correct

FILENAME=$1
TABLEDIR=local_build/log

#get the value of report files
report_id=1
report_type=""
report_pos=""
report_level="error"
report_example=""
report_version=""
report_rd=""

#send mail, make the mail text
echo "From: 
To: ${MAIL_LIST_ERRHUNTER}
Subject: MP3产品线${MODULE_ERRHUNTER}：Errhunter静态分析报告
Content-type:text/html;charset=\"gb2312\"
<!-- status=OK -->
<head>
  <style type="text/css">
             table
              {
                  font-family: '微软雅黑', Tahoma, Arial;
                  font-size: 16px;
                  text-align: center;
                  margin: 0 auto;
                  background-color: #E0F0FF;
              }
</style>
<title>Errhunter</title>
</head>   
Hi,all！<br>
静态代码检查工具errhunter 报告 <br>
扫描${MODULE_ERRHUNTER}目录： <b> ${ERRHUNTER_DIR} </b> <br> 
<table class="cq01-testing-mp347.cq01.baidu.com" style="text-align:center" width="100%" cellspacing="0" border="1">
<tr><th colspan="7" bgcolor="#B0E0E6">${MODULE_ERRHUNTER}:Errhunter静态分析报告——" > ${TABLEDIR}/table.htm
`echo date +%Y年%m月%d日%H点%M分%S秒 ` >> ${TABLEDIR}/table.htm
echo "</th></tr>
<TR  bgcolor="#87CEFA">
<th colspan="1">序号</th>
<th colspan="1">Bug级别</th>
<th colspan="1">错误类型</th>
<th colspan="1">代码位置</th>
<th colspan="1">Bug分析</th>
<th colspan="1">文件版本号</th>
<th colspan="1">RD负责人</th></TR>" >> ${TABLEDIR}/table.htm

cat $FILENAME | while read line    # read from the tmp file
do
    report_type=`echo $line | awk -F":" '{print $3}' | awk -F"(" '{print $2}' | awk -F")" '{print $2}'`
    report_pos=`echo $line | awk -F"]" '{print $1}' | awk -F"[" '{print $2}' | awk -F"/" '{print $NF}'`
#    report_pos=`echo $line | awk -F"]" '{print $1}' | awk -F"[" '{print $0}' | awk -F"/" '{if ($NF > 0){print $NF}else {print $0 | sed 's/[ []//g' } }'`
    report_level=`echo $line | awk -F":" '{print $3}' | awk -F"(" '{print $2}' | awk -F")" '{print $1}'`
    report_example=`echo $line | awk -F":" '{print $3}' | awk -F"(" '{print $2}' | awk -F")" '{print $2}'`
    report_error_file=`echo $report_pos | awk -F":" '{print $1}'`
    report_rd=`svn info ${report_error_file} |grep "Last Changed Author"|cut -d ":" -f 2`
    report_version=`svn info ${report_error_file} |grep "Last Changed Rev"|cut -d ":" -f 2`
    echo "<TR>
<td align=center>${report_id}</td>
<td align=center>"	>> ${TABLEDIR}/table.htm
#  if [ ${report_level}x == "error"x ] ;
  if [[ ${report_level} == "error" ]] ;
	then 
	  echo "<font color="red">${report_level}</font>" >> ${TABLEDIR}/table.htm ;
	else
	  echo "${report_level}" >> ${TABLEDIR}/table.htm ;
	fi
echo "</td>
<td align=center>${report_type}</td>
<td align=center>${report_pos}</td>
<td align=center>${report_example}</td>
<td align=center>${report_version}</td>
<td align=center>${report_rd}</td></TR>" >> ${TABLEDIR}/table.htm
let report_id=$report_id+1
#report_id++
done

echo "</TABLE>
<BR><HR>" >> ${TABLEDIR}/table.htm
cat ${TABLEDIR}/table.htm | /usr/lib/sendmail -t
}

#****************************************************************
##! @BRIEF: 执行errHunter检查
#****************************************************************
ccp_check()
{
	#进行静态分析工具errhunter chcek
	Print $LOG_NOTICE "begin  errhunter  check~~"
	TIME_BEFORE_STATIC_ANALYSIS=`date +%s` 

	if [ ${IS_ERRHUNTER:-"0" } = "1" ]
	then
		#通过ftp下载最新版本的静态代码检查工具errHunter
		rm -fr ./local_build/errHunter
		wget ${ERRHUNTER_FTP} -O ./local_build/errHunter >> ${LOG_FILE}
		chmod u+x ./local_build/errHunter

        #执行代码检查
		./local_build/errHunter -j 8 $ERRHUNTER_DIR 2>${DETAIL[$STATIC_ANALYSIS]}
		ret=$?

        #发送代码检查报告
		report_mail ${DETAIL[$STATIC_ANALYSIS]}

        TIME_AFTER_STATIC_ANALYSIS=`date +%s`
        STATIC_ANALYSIS_TIME=$(($TIME_AFTER_STATIC_ANALYSIS-$TIME_BEFORE_STATIC_ANALYSIS))
        Print $LOG_NOTICE "errhunter time: $STATIC_ANALYSIS_TIME(s) !";
        RESULT[$STATIC_ANALYSIS]=$ret
        TIME[$STATIC_ANALYSIS]=$STATIC_ANALYSIS_TIME

		#发送报告给errhunter统计服务器
		lftp img:imgapptest@db-testing-img16.db01.baidu.com <<-EOF
		cd image/`date +%Y-%m-%d`/
		put ${DETAIL[$STATIC_ANALYSIS]} -o "report_mp3_${MODULE_ERRHUNTER}_"`date +%H%M%S`
		close
		bye
		EOF
	fi

	Print $LOG_NOTICE "errhunter check! "	
}


#****************************************************************
##! @BRIEF: 编译,执行编译,在配置文件中设置 是否要进行覆盖率检查
#****************************************************************
project_make()
{
	Print $LOG_NOTICE "project make !"
	TIME_BEFORE_MAKE=`date +%s`

	if [ ${IS_MAKE_QUICK:-"0"} == "1" ] ; then
		export make_parallel=100 
	fi

	if [ ${IS_CCOVER:-"0"} == "1" ]
	then
		echo $IS_CCOVER
		#修改ccover支持覆盖率统计
        #Enable Coverage Build
		export COVFILE=`pwd`/local_build/test.cov
#		cov01 -1
	
		if [ -d ~/.BullseyeCoverage ] ; then
			rm -rf ~/.BullseyeCoverage
		fi

		if [ "$make_parallel" == "" ] ; then
			make clean >> ${LOG_FILE} 2>&1\
			&& make >> ${LOG_FILE} 2>&1
		else
			make clean >> ${LOG_FILE} 2>&1\
            && make -j$make_parallel >> ${LOG_FILE} 2>&1
		fi
	else
        #Disable Coverage Build
#        cov01 -0

		if [ -d ~/.BullseyeCoverage ] ; then
			rm -rf ~/.BullseyeCoverage
		fi

		if [ "$make_parallel" == "" ] ; then
			make clean >> ${LOG_FILE}  2>&1\
			&& make >> ${LOG_FILE}  2>&1
		else
			make clean >> ${LOG_FILE} 2>&1\
            && make -j$make_parallel >> ${LOG_FILE} 2>&1
		fi
	fi

	ret=$?
	TIME_AFTER_MAKE=`date +%s`
    MAKE_TIME=$(($TIME_AFTER_MAKE-$TIME_BEFORE_MAKE))
	Print $LOG_NOTICE "project time is: $MAKE_TIME(s) !"
	RESULT[$MAKE]=$ret
	TIME[$MAKE]=MAKE_TIME

	if [ $ret -ne 0 ] ; then
		Print $LOG_FAIL "project make failed !"; 
                STATUS_LIST="$STATUS_LIST\nproject make failed"; 
		return -1;
	else
		Print $LOG_PASS "project make success !";
                STATUS_LIST="$STATUS_LIST\nproject make success"; 
		return 0;
	fi
}


#****************************************************************
##! @BRIEF: 更新hudson测试环境,运行全部的模块级case
#****************************************************************
hudson_module_test()
{
	#HUDSON module case 运行;
	Print $LOG_NOTICE "hudson module test begin!"
    TIME_BEFORE_HUDSON_MODULE=`date +%s`

	#
    if [ ${SERVER:-"0"} != "0" ]
    then
        Print $LOG_NOTICE "module test is ${SERVER} !";
		sh  "$MODULE_SH"
	fi
	
	ret=$?
	if [ $ret -ne 0 ] ;then
		Print $LOG_FAIL "module test is  failed !";
		TIME_AFTER_HUDSON_MODULE=`date +%s`
		HUDSON_SMOKE_TIME=$(($TIME_AFTER_HUDSON_MODULE-$TIME_BEFORE_HUDSON_MODULE))
		Print $LOG_NOTICE "module test time is: $HUDSON_SMOKE_TIME(s) !"
		RESULT[$HUDSON_MODULE]=$ret
		TIME[$HUDSON_MODULE]=$HUDSON_MODULE_TIME
                STATUS_LIST="$STATUS_LIST\nmodule test is failed"
		return -1
	fi
}



#****************************************************************
##! @BRIEF: 打印帮助信息
#****************************************************************
print_help()
{
    echo "samples:"
    echo "-----------------------------------------------------------------------------------"
    echo "local_build.sh make_all        :      env + make + ccp_check "
    echo "-----------------------------------------------------------------------------------"
    echo "local_build.sh env             :      download the dependency libs and generate the makefile"
    echo "local_build.sh make            :      make clean & make for project"
    echo "local_build.sh ccp_check       :      errhunter"
    #echo "local_build.sh hudson_module   :      env + make + ccp_check + module test"
    echo "local_build.sh cluster_make    :      make clean & make for project on compile cluster"
    echo "local_build.sh localbuild name :      excute localbuild for rd, include env/make/style_check/ccp_check/supertest case"
    echo "-----------------------------------------------------------------------------------"
}

#****************************************************************
##! @BRIEF: 编译依赖更新、编译、代码检查
#****************************************************************
make_all()
{
    comake2_env &&
    project_make &&
    ccp_check 
}

#****************************************************************
##! @BRIEF: 编译依赖更新、编译、代码检查、hudson运行case
#****************************************************************
hudson_module()
{
    comake2_env &&
    project_make &&
    ccp_check &&
    hudson_module_test
}

#****************************************************************
##! @BRIEF: 集群编译程序
#****************************************************************
cluster_compile()
{
    #包括环境依赖更新，编译，代码检查
    Print $LOG_NOTICE "Make project on compile clusters, please wait a minute..."
    #build_submitter.py -u $SOURCE_PATH -c "cd app/search/mp3/ls/code/rd/src && export MAC=64 && export make_parallel=100 && source /home/mp3/tools/scmtools/usr/bin/scmtools --enable-shared-ccache --enable-dynamic-distcc && source /home/mp3/tools/scmtools/usr/bin/scmtools -c && sh ./local_build/local_build.sh env && sh ./local_build/local_build.sh make && sh ./local_build/local_build.sh ccp_check"
#    build_submitter.py -u $SOURCE_PATH -c "cd app/search/mp3/ls/code/rd/src && export MAC=64 && export make_parallel=100 && sh ./local_build/local_build.sh env && sh ./local_build/local_build.sh make && sh ./local_build/local_build.sh ccp_check"
#    build_submitter.py -x -u $SVN_PATH -c "cd app/search/mp3/rls/code/qa && export MAC=64 && sh ./local_build/local_build.sh make_all" --login 
#     build_submitter.py -x -u "http://svn.baidu.com/app/search/mp3/trunk/rls/code" -c " export MAC=64&&cd app/search/mp3/rls/code/qa && comake2 -U -B &&comake2 && make clean && make"  
    build_submitter.py -u $SVN_PATH  -c "cd app/search/mp3/rls/code/rd/src &&export MAC=64 && cp -rf ../../qa/local_build ./ && sh ./local_build/local_build.sh make_all"
    if [ $? -eq 0 ]; then
    	Print $LOG_PASS "Make project success!"
        STATUS_LIST="$STATUS_LIST\nMake project success"
        ret=0
    else
	Print $LOG_FAIL "Make project failed!"
        STATUS_LIST="$STATUS_LIST\nMake project failed"
        ret=-1
    fi
    #编译完的文件会放在$SOURCE_PATH/output下

    #清理本次编译的文件
    Print $LOG_NOTICE "删除本次编译产生的log"
    rm -fr $SOURCE_PATH/build_submitter.log*
    return $ret
}

#****************************************************************
##! @BRIEF: 本地发起localbuild自动化case验证
#****************************************************************
localbuild()
{
    #根据rd的名字启动相应的localbuild job
    rd_name=$1
    if [ "$rd_name" = "" ]; then
        Print $LOG_FATAL "Localbuild need rd_name as input parameter!"
    fi

    #集群编译版本
    cluster_compile
	#make_all


    #判断编译结果是否正确
    if [ $? -ne 0 ]; then
        return -1
    fi

    #将编译完的版本部署到测试机上的备份目录下
    ssh $LOCALBUILD_SERVER "rm -fr $LOCALBUILD_PATH/$rd_name/output"

    Print $LOG_NOTICE "Scp files new compiled to localbuild server: $LOCALBUILD_SERVER:$LOCALBUILD_PATH/$rd_name"
    ssh $LOCALBUILD_SERVER "mkdir -p $LOCALBUILD_PATH/$rd_name"
    scp -r $SOURCE_PATH/output $LOCALBUILD_SERVER:$LOCALBUILD_PATH/$rd_name

    #启动自动化测试hudson job
    Print $LOG_NOTICE "Trigger the localbuild for $rd_name"
    curl "http://db-testing-mp327.db01.baidu.com:8235/hudson/job/local_build_rls_${rd_name}/build?token=${rd_name}"

    if [ $? -eq 0 ]; then
    	Print $LOG_PASS "Localbuild job start success! Open the webpage to see details:\nhttp://db-testing-mp327.db01.baidu.com:8235/hudson/job/local_build_rls_$rd_name"
        STATUS_LIST="$STATUS_LIST\nLocalbuild job start success"
        return 0
    else
    	Print $LOG_FAIL "Localbuild job start failed!"
        STATUS_LIST="$STATUS_LIST\nLocalbuild job start failed"
        return -1
    fi
}

#****************************************************************
##! @BRIEF: 本地发起localbuild自动化case验证
#****************************************************************
function print_status_list
{
    if [[ "$STATUS_LIST" = "" ]]; then
        return 0
    fi
    echo -e $STATUS_LIST | grep -v ^$ > .status_list

    Print $LOG_NOTICE "\n\n=================================================="
    Print $LOG_NOTICE "The status of localbuild >>"
    Print $LOG_NOTICE "=================================================="

    log_index=1
    while read line; do
        success=`echo $line | grep success`
        if [[ "$success" = "" ]]; then
	    Print $LOG_FAIL "$log_index. $line!"
        else
            Print $LOG_PASS "$log_index. $line!"
        fi
        log_index=`expr $log_index + 1`
    done < .status_list
    rm -fr .status_list
}

#****************************************************************
##! @BRIEF: 参数解析，功能调度
#****************************************************************
Main() 
{
    #写死的函数覆盖率和条件覆盖率
    func_cov=55
    condi_cov=33
    if [ "$1" == "-h" ]; then
        print_help
    elif [ "$1" == "env" ]; then
        comake2_env
    elif [ "$1" == "make" ]; then
        project_make
    elif [ "$1" == "ccp_check" ]; then
        ccp_check
    elif [ "$1" == "cluster_make" ]; then
        cluster_compile
    elif [ "$1" == "localbuild" ]; then
        localbuild $2
    elif [ "$1" == "make_all" ]; then
        make_all
    #elif [ "$1" == "module_test" ]; then
    #    hudson_module
    else
        print_help
    fi
}
		
#执行localbuild
SOURCE_PATH=`pwd`
echo "source path"
echo $SOURCE_PATH
SVN_PATH=${SOURCE_PATH%rd*}
echo "svn path"
echo $SVN_PATH
Main "$@" 

print_status_list
