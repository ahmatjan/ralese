#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465264
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:07:50 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_即时模型频道试探歌曲
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、80后频道（或者流行）
# 2、cookie用户
# 3、近15天内在当前公共频道的完整听歌数为0
# ==== Expect:
# 1、两首歌曲是试探歌曲列表里的歌曲
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case描述}
class RlsChannellistTest < SuperTest
    
    # {测试点}
    def test_me
        #TODO
        param = $FMRLS_G
		param["testdata"]["uid"] = "0"
		param["testdata"]["baiduid"] = "1BCC1EFC518E09BF058BEBC49DB44148"
        param["testdata"]["channel_en"] = "public_shiguang_80hou"
        playlist=channel_cmd_song_list(param)
        assert_equal  playlist["songinfos"].length,200
		
		check_detect_song(param,playlist)
    end

end
