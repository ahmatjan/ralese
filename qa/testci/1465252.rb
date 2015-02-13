#!/usr/bin/env ruby
# coding: gbk
#
# == case    
# Id:: 1465252
# Valid:: 1
# Priority:: 0
# Type:: 0
# Author:: zhouruili01
# Date:: 2012-12-20 16:55:12 +0800
# Updaters:: zhouruili01
# Updated_at:: 2012-12-20 17:55:54 +0800
# ==== Title:
# F_����Ƶ������������
# ==== Description:
# 
# ==== Precondition:
# 
# ==== Steps:
# 1����½�û�
# 2��cookie�û�
# 3������Ƶ��
#       ����Ƶ����С���£���ȡ�����б�
# ==== Expect:
# �����б������û�����Ͱ��ĸ���
# ==== Note:
# 
# End
$CASE_PATH = __FILE__
###########################################
require 'super_test'
require "#{$WORK_ROOT_LIB}/config/fm_rls_config.rb"
include FmRlsPattern

# {case����}
class RlsfilterlistpublicTest < SuperTest
    
    # {���Ե�}
    def test_me
        #TODO
        param = $FMRLS_G
        param["testdata"]["channel_en"] = "public_fengge_xiaoqingxin"
        playlist=channel_cmd_song_list(param)
		assert_equal  playlist["songinfos"].length,200
        check_song_filter_public(param,playlist)
    end

end
