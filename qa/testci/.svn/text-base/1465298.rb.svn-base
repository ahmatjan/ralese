#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465298
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:43:47 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_登陆用户完整试听对数据库的影响
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、登陆用户
# 2、完整试听
# ==== Expect:
# 1、完整试听行为写入数据库
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case描述}
class RlsSongCompleteTest < SuperTest
    
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
        res=player_cmd_song_complete(param)
        $FMRLS_G["userop"].each_key{|key|assert res.has_key?(key) }
        assert_equal  0,res["status"]
    end

end
