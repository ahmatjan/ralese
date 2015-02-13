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
# F_列表歌手打散
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1、获取随便听听频道的播放列表
# ==== Expect:
# 1、播放列表里相邻5首歌不会出现同一个歌手演唱的歌曲
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
        param["testdata"]["uid"]= "0"
        param["testdata"]["username"]= "0"
        param["testdata"]["baiduid"]= "AFA41C180BE16F0375A065AA5D912EE2"
        res=count_lovesong_total_num(param)
        assert_equal  1,res["status"]
    end

end
