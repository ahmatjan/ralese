#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465302
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:46:18 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_登录用户垃圾通对用户中心的影响
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、登陆用户
# 2、垃圾桶
# ==== Expect:
# 1、垃圾桶歌曲写入用户中心
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case描述}
class RlsSonghateTest < SuperTest
    
      def setup
           param=$FMRLS_G
           param["case"]=File.basename(__FILE__,".rb")
           param["case_data"]="#{param["data_path"]}/#{param["case"]}"
          # param["dump_response"]=0
           setup_rls_pattern($FMRLS_G)
           super
       end
       def teardown
           teardown_rls_pattern($FMRLS_G)
       end
    # {测试点}
    def test_me
        #TODO
        param = $FMRLS_G
        res=player_cmd_song_hate(param)
        $FMRLS_G["userop"].each_key{|key|assert res.has_key?(key) }
        assert_equal  0,res["status"]
    end

end
