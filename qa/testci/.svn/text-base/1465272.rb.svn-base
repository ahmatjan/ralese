#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465272
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:18:46 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_登录用户取消加心
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、登录用户
# 2、私人频道
# 3、取消加心
# ==== Expect:
# 
# 无
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# test
class RlsPcSongCancelLove < SuperTest

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

        param["testdata"]["songid"] = "7472364"
	param["testdata"]["channel_en"] = "private"
	oldlist=channel_cmd_song_list(param)
	oldlist=oldlist["songinfos"]
        listhead = oldlist.first(2)
        listhead.collect! {|x| x["songid"]}
        param["testdata"]["songid"]=listhead[1].to_s
        newlist=player_cmd_song_love_cancel(param)
		newlist=newlist["songinfos"]
        tmplist = Array.new
        assert_equal(newlist,tmplist)
    end

end
