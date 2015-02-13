#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465286
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 17:28:36 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_��ȡƵ�������б�
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1����½�û��������Ƶ��
# 2����ȡƵ�������б�
# ==== Expect:
# 1����鷵�����ݰ����Ƿ���status\ids\ch_name\ch_sname\songinfos���ֶ�
# 2������ �����б�����200
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
    
    # {���Ե�}
    def test_me
        #TODO
        param = $FMRLS_G
        param["testdata"]["channel_en"] = "public_tuijian_suibiantingting"
        playlist=channel_cmd_song_list(param)
        $FMRLS_G["playlist"].each_key{|key|assert playlist.has_key?(key) }
        $FMRLS_G["playlist"]["songinfos"].each_key {|key| assert playlist["songinfos"][0].has_key?(key)}
        assert_equal  playlist["songinfos"].length,200
    end

end
