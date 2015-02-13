#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465292
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:36:29 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_��½�û���ȡusercounts
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1����¼�û�
# 2����ȡ�û���Ϣusercounts
# ==== Expect:
# 1����鷵���б����Ƿ���������ֶ�
#                         "status"=&gt;"",                       "lovesong_cnt"=&gt;"",                       "hatesong_cnt"=&gt;"",                       "lovesinger_cnt"=&gt;"",                       "hatesinger_cnt"=&gt;"",                       "play_cnt"=&gt;"",
# 2��status=0
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case����}
class RlsChannellistTest < SuperTest
    
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
        res=count_lovesong_total_num(param)
        $FMRLS_G["usercounts"].each_key{|key|assert res.has_key?(key) }
        assert_equal  0,res["status"]
    end

end
