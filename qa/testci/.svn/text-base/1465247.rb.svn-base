#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465247
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 16:48:35 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_cookie用户欧美频道完整试听
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# cookie用户欧美频道完整试听
# ==== Expect:
# 歌曲从播放列表中删除
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# test
class RlsPcSongCompleteCO < SuperTest

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
        param["testdata"]["songid"] = "243195"
	param["testdata"]["uid"] = "0"
	param["testdata"]["baiduid"] = "AFA41C180BE16F0375A065AA5D912EE2"
	param["testdata"]["channel_en"] = "public_yuzhong_oumei"
#	param["testdata"]["baiduid"] = ""
	oldlist = channel_cmd_song_list(param)
	oldlist = oldlist["songinfos"]
	    listhead = oldlist.first(2)
		listhead.collect! {|x| x["songid"]}
		param["testdata"]["songid"]=listhead[1].to_s
		p param["testdata"]["songid"]
        newlist=player_cmd_song_complete(param)
		newlist=newlist["songinfos"]
        tmplist = Array.new
        assert_equal(newlist,tmplist)
        newlist=channel_cmd_song_list(param)
		newlist=newlist["songinfos"]
        #从日志中挖掘 删除信息
	check_song_notin_list(param, param["testdata"]["songid"], newlist)
    end

end
