#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465290
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:33:01 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_�б���ִ�ɢ
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1����ȡ�������Ƶ���Ĳ����б�
# ==== Expect:
# 1�������б�������5�׸費�����ͬһ�������ݳ��ĸ���
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
        param["testdata"]["uid"]= "0"
        param["testdata"]["username"]= "0"
        param["testdata"]["baiduid"]= "AFA41C180BE16F0375A065AA5D912EE2"
        res=count_lovesong_total_num(param)
        assert_equal  1,res["status"]
    end

end
