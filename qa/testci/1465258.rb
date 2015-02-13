#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465258
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:00:47 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_推荐频道黑名单过滤
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、推荐频道（私人、随便听听、80hou、70hou、90hou、流行、华语、欧美）
# 2、登录用户
# 3、cookie用户
#      获取播放列表
# ==== Expect:
# 播放列表过滤
# 1、1个星期听过
# 2、两个星期下一首
# 3、全部垃圾桶歌曲
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case描述}
class RlsfilterlistTest < SuperTest
    
    # {测试点}
    def test_me
        #TODO
        param = $FMRLS_G
		param["testdata"]["channel_en"] = "private"
        playlist=channel_cmd_song_list(param)
		assert_equal  playlist["songinfos"].length,200
		playlist=player_cmd_song_next(param)
        check_song_filter(param,playlist)
    end

end
