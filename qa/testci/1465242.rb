#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465242
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 16:44:07 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_获取频道列表
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 检查channel 的rls返回数据包里是否含有指定的字段
# ==== Expect:
# 
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
    
  #    def setup
  #         param=$FMRLS_G
  #        # param["case"]=File.basename(__FILE__,".rb")
  #        # param["case_data"]="#{param["data_path"]}/#{param["case"]}"
  #        # param["dump_response"]=0
  #         setup_rls_pattern($FMRLS_G)
  #         super
  #     end
  #     def teardown
  #         teardown_rls_pattern($FMRLS_G)
  #     end
    # {测试点}
    def test_me
        #TODO
        param = $FMRLS_G
        param["testdata"]["uid"] = "0"
        param["testdata"]["baiduid"]= ""
        param["comdef"]["catename"] = "all"
		p "channel list"
        res=channel_cmd_get_list(param)
        $FMRLS_G["channel"].each_key{|key|assert res.has_key?(key) }
        $FMRLS_G["channel"]["channels"].each_key {|key| assert res["channels"][0].has_key?(key)}
		#  assert_equal  res["channels"].length,37
    end

end
