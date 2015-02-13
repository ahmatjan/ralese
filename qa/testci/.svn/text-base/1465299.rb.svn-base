#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465299
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:44:59 +0800
# Updaters:: 
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_cookie用户完整试听对数据库的影响
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、cookie用户
# 2、完整试听
# ==== Expect:
# 1、完整试听行为写入还数据库
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case描述}
class RlsSongCompletecookieTest < SuperTest
    
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
		param["testdata"]["uid"] = "0"
		param["testdata"]["baiduid"] = "AFA41C180BE16F0375A065AA5D912EE2"
        res=player_cmd_song_complete(param)
        $FMRLS_G["userop"].each_key{|key|assert res.has_key?(key) }
        assert_equal  0,res["status"]
    end

end
