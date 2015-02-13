#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465250
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 16:52:51 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_登录用户私人频道完整试听
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 
# 登陆用户私人频道完整试听
# ==== Expect:
# 试听歌曲从返回歌曲列表中删除
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# test
class RlsPcSongComplete < SuperTest

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
        param["testdata"]["songid"] = "1499731"
#	param["testdata"]["uid"] = "523264544"
	param["testdata"]["channel_en"] = "private"
	param["testdata"]["baiduid"] = ""
	oldlist = channel_cmd_song_list(param)
	oldlist=oldlist["songinfos"]
        listhead = oldlist.first(2)
        listhead.collect! {|x| x["songid"]}
        param["testdata"]["songid"]=listhead[1].to_s
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
