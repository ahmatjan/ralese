#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465274
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:20:59 +0800
# Updaters:: 
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_cookie�û�ŷ��Ƶ������
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1��cookie�û�
# 2��ŷ��Ƶ��
# 3���������Ĳ���
# ==== Expect:
# 1���˸������б���ɾ��
# 2����������ظ���top10��Ȩ
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# test
class RlsPcSongLoveLo < SuperTest

    def setup
            param=$FMRLS_G
            param["case_name"] = File.basename(__FILE__,".rb")
            param["case_data"] = "#{param["data"]}/#{param["case_name"]}"
            #param["case_data_prepare"] = "build"
            setup_rls_pattern($FMRLS_G)
            super
    end

    def teardown
            teardown_rls_pattern($FMRLS_G)
            super
    end 

    def test_me
        param = $FMRLS_G
    	param["comdef"]["rfmp3"] = 1
        param["testdata"]["songid"] = "602998"
    	param["testdata"]["uid"] = "0"
		param["testdata"]["baiduid"] = "AFA41C180BE16F0375A065AA5D912EE2"
    	param["testdata"]["channel_en"] = "public_yuzhong_oumei"

        oldlist=channel_cmd_song_list(param)
		oldlist=oldlist["songinfos"]
		
        listhead = oldlist.first(2)
        listhead.collect! {|x| x["songid"]}
        param["testdata"]["songid"]=listhead[1].to_s
        newlist =  player_cmd_song_love(param)
		newlist=newlist["songinfos"]
		p "here id the chosen song"
		p newlist[3]["songid"]
       check_song_notin_list(param, param["testdata"]["songid"], newlist)
        check_love_rsong_4(param, param["testdata"]["songid"] , newlist)
		check_love_rsingersong_2(param, param["testdata"]["songid"] , newlist)
	end

end
