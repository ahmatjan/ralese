#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465314
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:54:06 +0800
# Updaters:: 
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_��½�û���һ�׶����ݿ�Ĳ���
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1����½�û���һ��
# ==== Expect:
# 1��������һ�ױ�д�����ݿ�
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case����}
class RlsSongprecookieTest < SuperTest
    
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
    # {���Ե�}
    def test_me
        #TODO
        param = $FMRLS_G
        param["testdata"]["uid"] = "0"
        param["testdata"]["uname"] = "0"
        param["testdata"]["songid"] = "226211"
        param["testdata"]["baiduid"] = "AFA41C180BE16F0375A065AA5D912EE2"
        res=player_cmd_song_prev(param)
       $FMRLS_G["userop"].each_key{|key|assert res.has_key?(key) }
        assert_equal  0,res["status"]
    end

end