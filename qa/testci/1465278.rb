#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465278
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:26:23 +0800
# Updaters:: 
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_cookie用户欧美频道下一首
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、cookie用户
# 2、欧美频道
# 3、歌曲下一首
# ==== Expect:
# 1、此歌曲从列表中删除
# 2、相关歌曲的top10降权
# 3、此歌曲的歌手的其他歌曲不出现在最近10首中
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# test
class RlsPcSongNextCo < SuperTest

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
	
        param["testdata"]["songid"] = "308496"
	    param["testdata"]["uid"] = "0"
		param["testdata"]["baiduid"] = "AFA41C180BE16F0375A065AA5D912EE2"
	    param["testdata"]["channel_en"] = "public_yuzhong_oumei"
        oldlist = channel_cmd_song_list(param)
	    oldlist=oldlist["songinfos"]
        listhead = oldlist.first(2)
        listhead.collect! {|x| x["songid"]}
        param["testdata"]["songid"]=listhead[1].to_s
        newlist = player_cmd_song_next(param)
		newlist=newlist["songinfos"]
	    check_song_notin_list(param, param["testdata"]["songid"], newlist)
	    check_top20_rsong_delete(param, param["testdata"]["songid"], newlist)
	    check_top20_singersong_delete(param, param["testdata"]["songid"], newlist)
    end

end
