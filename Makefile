#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I./include \
  -I./output \
  -I./output/include
DEP_INCPATH=-I../../../../../app/search/ksarch/store/libmemcached \
  -I../../../../../app/search/ksarch/store/libmemcached/include \
  -I../../../../../app/search/ksarch/store/libmemcached/output \
  -I../../../../../app/search/ksarch/store/libmemcached/output/include \
  -I../../../../../app/search/ksarch/store/mcclient \
  -I../../../../../app/search/ksarch/store/mcclient/include \
  -I../../../../../app/search/ksarch/store/mcclient/output \
  -I../../../../../app/search/ksarch/store/mcclient/output/include \
  -I../../../../../app/search/ksarch/store/neclient \
  -I../../../../../app/search/ksarch/store/neclient/include \
  -I../../../../../app/search/ksarch/store/neclient/output \
  -I../../../../../app/search/ksarch/store/neclient/output/include \
  -I../../../../../app/search/ksarch/store/proxy-lib/redis \
  -I../../../../../app/search/ksarch/store/proxy-lib/redis/include \
  -I../../../../../app/search/ksarch/store/proxy-lib/redis/output \
  -I../../../../../app/search/ksarch/store/proxy-lib/redis/output/include \
  -I../../../../../com/idlcompiler \
  -I../../../../../com/idlcompiler/include \
  -I../../../../../com/idlcompiler/output \
  -I../../../../../com/idlcompiler/output/include \
  -I../../../../../inf/computing/ant \
  -I../../../../../inf/computing/ant/include \
  -I../../../../../inf/computing/ant/output \
  -I../../../../../inf/computing/ant/output/include \
  -I../../../../../inf/computing/java6 \
  -I../../../../../inf/computing/java6/include \
  -I../../../../../inf/computing/java6/output \
  -I../../../../../inf/computing/java6/output/include \
  -I../../../../../inf/computing/zookeeper \
  -I../../../../../inf/computing/zookeeper/include \
  -I../../../../../inf/computing/zookeeper/output \
  -I../../../../../inf/computing/zookeeper/output/include \
  -I../../../../../lib2-64/bsl \
  -I../../../../../lib2-64/bsl/include \
  -I../../../../../lib2-64/bsl/output \
  -I../../../../../lib2-64/bsl/output/include \
  -I../../../../../lib2-64/ccode \
  -I../../../../../lib2-64/ccode/include \
  -I../../../../../lib2-64/ccode/output \
  -I../../../../../lib2-64/ccode/output/include \
  -I../../../../../lib2-64/dict \
  -I../../../../../lib2-64/dict/include \
  -I../../../../../lib2-64/dict/output \
  -I../../../../../lib2-64/dict/output/include \
  -I../../../../../lib2-64/string \
  -I../../../../../lib2-64/string/include \
  -I../../../../../lib2-64/string/output \
  -I../../../../../lib2-64/string/output/include \
  -I../../../../../lib2-64/ullib \
  -I../../../../../lib2-64/ullib/include \
  -I../../../../../lib2-64/ullib/output \
  -I../../../../../lib2-64/ullib/output/include \
  -I../../../../../op/oped/noah/webfoot/naming-lib \
  -I../../../../../op/oped/noah/webfoot/naming-lib/include \
  -I../../../../../op/oped/noah/webfoot/naming-lib/output \
  -I../../../../../op/oped/noah/webfoot/naming-lib/output/include \
  -I../../../../../public/bslext \
  -I../../../../../public/bslext/include \
  -I../../../../../public/bslext/output \
  -I../../../../../public/bslext/output/include \
  -I../../../../../public/comlog-plugin \
  -I../../../../../public/comlog-plugin/include \
  -I../../../../../public/comlog-plugin/output \
  -I../../../../../public/comlog-plugin/output/include \
  -I../../../../../public/configure \
  -I../../../../../public/configure/include \
  -I../../../../../public/configure/output \
  -I../../../../../public/configure/output/include \
  -I../../../../../public/connectpool \
  -I../../../../../public/connectpool/include \
  -I../../../../../public/connectpool/output \
  -I../../../../../public/connectpool/output/include \
  -I../../../../../public/ependingpool \
  -I../../../../../public/ependingpool/include \
  -I../../../../../public/ependingpool/output \
  -I../../../../../public/ependingpool/output/include \
  -I../../../../../public/fcrypt \
  -I../../../../../public/fcrypt/include \
  -I../../../../../public/fcrypt/output \
  -I../../../../../public/fcrypt/output/include \
  -I../../../../../public/gm/galileo \
  -I../../../../../public/gm/galileo/include \
  -I../../../../../public/gm/galileo/output \
  -I../../../../../public/gm/galileo/output/include \
  -I../../../../../public/idlcompiler \
  -I../../../../../public/idlcompiler/include \
  -I../../../../../public/idlcompiler/output \
  -I../../../../../public/idlcompiler/output/include \
  -I../../../../../public/mcpack \
  -I../../../../../public/mcpack/include \
  -I../../../../../public/mcpack/output \
  -I../../../../../public/mcpack/output/include \
  -I../../../../../public/myclient \
  -I../../../../../public/myclient/include \
  -I../../../../../public/myclient/output \
  -I../../../../../public/myclient/output/include \
  -I../../../../../public/ns/buffer \
  -I../../../../../public/ns/buffer/include \
  -I../../../../../public/ns/buffer/output \
  -I../../../../../public/ns/buffer/output/include \
  -I../../../../../public/ns/mynet \
  -I../../../../../public/ns/mynet/include \
  -I../../../../../public/ns/mynet/output \
  -I../../../../../public/ns/mynet/output/include \
  -I../../../../../public/nshead \
  -I../../../../../public/nshead/include \
  -I../../../../../public/nshead/output \
  -I../../../../../public/nshead/output/include \
  -I../../../../../public/odict \
  -I../../../../../public/odict/include \
  -I../../../../../public/odict/output \
  -I../../../../../public/odict/output/include \
  -I../../../../../public/passport/session \
  -I../../../../../public/passport/session/include \
  -I../../../../../public/passport/session/output \
  -I../../../../../public/passport/session/output/include \
  -I../../../../../public/spcache \
  -I../../../../../public/spcache/include \
  -I../../../../../public/spcache/output \
  -I../../../../../public/spcache/output/include \
  -I../../../../../public/spreg \
  -I../../../../../public/spreg/include \
  -I../../../../../public/spreg/output \
  -I../../../../../public/spreg/output/include \
  -I../../../../../public/ub \
  -I../../../../../public/ub/include \
  -I../../../../../public/ub/output \
  -I../../../../../public/ub/output/include \
  -I../../../../../public/uconv \
  -I../../../../../public/uconv/include \
  -I../../../../../public/uconv/output \
  -I../../../../../public/uconv/output/include \
  -I../../../../../third-64/boost \
  -I../../../../../third-64/boost/include \
  -I../../../../../third-64/boost/output \
  -I../../../../../third-64/boost/output/include \
  -I../../../../../third-64/libcurl \
  -I../../../../../third-64/libcurl/include \
  -I../../../../../third-64/libcurl/output \
  -I../../../../../third-64/libcurl/output/include \
  -I../../../../../third-64/mysql \
  -I../../../../../third-64/mysql/include \
  -I../../../../../third-64/mysql/output \
  -I../../../../../third-64/mysql/output/include \
  -I../../../../../third-64/pcre \
  -I../../../../../third-64/pcre/include \
  -I../../../../../third-64/pcre/output \
  -I../../../../../third-64/pcre/output/include \
  -I../../../../../third-64/protobuf \
  -I../../../../../third-64/protobuf/include \
  -I../../../../../third-64/protobuf/output \
  -I../../../../../third-64/protobuf/output/include \
  -I../../../../../third-64/stlport \
  -I../../../../../third-64/stlport/include \
  -I../../../../../third-64/stlport/output \
  -I../../../../../third-64/stlport/output/include \
  -I../../../../../thirdsrc/zookeeper \
  -I../../../../../thirdsrc/zookeeper/include \
  -I../../../../../thirdsrc/zookeeper/output \
  -I../../../../../thirdsrc/zookeeper/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=7e027f52de59f74d11d0fc6620d8fed8  COMAKE


.PHONY:all
all:comake2_makefile_check rls .copy_conf 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf rls
	rm -rf ./output/bin/rls
	rm -rf .copy_conf
	rm -f .copy_conf
	rm -rf output/conf/
	rm -rf rd/src/idl/rls_reload.idl.o
	rm -rf rd/src/idl/rls_rls2.idl.o
	rm -rf rd/src/rls_common.o
	rm -rf rd/src/rls_config.o
	rm -rf rd/src/rls_dao.o
	rm -rf rd/src/rls_mcCache.o
	rm -rf rd/src/rls_mystring.o
	rm -rf rd/src/rls_myubclient_strategy.o
	rm -rf rd/src/rls_networker.o
	rm -rf rd/src/rls_redis.o
	rm -rf rd/src/rls_reload.o
	rm -rf rd/src/rls_rls.o
	rm -rf rd/src/rls_rls_dictseeker.o
	rm -rf rd/src/rls_rls_instant.o
	rm -rf rd/src/rls_rls_piaohandler.o
	rm -rf rd/src/rls_rls_playerhandler.o
	rm -rf rd/src/rls_rls_queryhandler.o
	rm -rf rd/src/rls_rls_ral.o
	rm -rf rd/src/rls_rls_rgen.o
	rm -rf rd/src/rls_rls_rstrategy.o
	rm -rf rd/src/rls_rls_uscchecker.o
	rm -rf rd/src/rls_rls_uscgetter.o
	rm -rf rd/src/rls_rls_y_playerhandler.o
	rm -rf rd/src/rls_shuffle.o
	rm -rf rd/src/rls_userworker.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

rls:rd/src/idl/rls_reload.idl.o \
  rd/src/idl/rls_rls2.idl.o \
  rd/src/rls_common.o \
  rd/src/rls_config.o \
  rd/src/rls_dao.o \
  rd/src/rls_mcCache.o \
  rd/src/rls_mystring.o \
  rd/src/rls_myubclient_strategy.o \
  rd/src/rls_networker.o \
  rd/src/rls_redis.o \
  rd/src/rls_reload.o \
  rd/src/rls_rls.o \
  rd/src/rls_rls_dictseeker.o \
  rd/src/rls_rls_instant.o \
  rd/src/rls_rls_piaohandler.o \
  rd/src/rls_rls_playerhandler.o \
  rd/src/rls_rls_queryhandler.o \
  rd/src/rls_rls_ral.o \
  rd/src/rls_rls_rgen.o \
  rd/src/rls_rls_rstrategy.o \
  rd/src/rls_rls_uscchecker.o \
  rd/src/rls_rls_uscgetter.o \
  rd/src/rls_rls_y_playerhandler.o \
  rd/src/rls_shuffle.o \
  rd/src/rls_userworker.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrls[0m']"
	$(CXX) rd/src/idl/rls_reload.idl.o \
  rd/src/idl/rls_rls2.idl.o \
  rd/src/rls_common.o \
  rd/src/rls_config.o \
  rd/src/rls_dao.o \
  rd/src/rls_mcCache.o \
  rd/src/rls_mystring.o \
  rd/src/rls_myubclient_strategy.o \
  rd/src/rls_networker.o \
  rd/src/rls_redis.o \
  rd/src/rls_reload.o \
  rd/src/rls_rls.o \
  rd/src/rls_rls_dictseeker.o \
  rd/src/rls_rls_instant.o \
  rd/src/rls_rls_piaohandler.o \
  rd/src/rls_rls_playerhandler.o \
  rd/src/rls_rls_queryhandler.o \
  rd/src/rls_rls_ral.o \
  rd/src/rls_rls_rgen.o \
  rd/src/rls_rls_rstrategy.o \
  rd/src/rls_rls_uscchecker.o \
  rd/src/rls_rls_uscgetter.o \
  rd/src/rls_rls_y_playerhandler.o \
  rd/src/rls_shuffle.o \
  rd/src/rls_userworker.o -Xlinker "-("  ../../../../../app/search/ksarch/store/libmemcached/output/lib/libhashkit.a \
  ../../../../../app/search/ksarch/store/libmemcached/output/lib/libmemcached.a \
  ../../../../../app/search/ksarch/store/libmemcached/output/lib/libmemcachedprotocol.a \
  ../../../../../app/search/ksarch/store/libmemcached/output/lib/libmemcachedutil.a \
  ../../../../../app/search/ksarch/store/mcclient/libmcclient.a \
  ../../../../../app/search/ksarch/store/neclient/libneclientadapter.a \
  ../../../../../app/search/ksarch/store/neclient/libneclientcore.a \
  ../../../../../app/search/ksarch/store/neclient/libneclientpool.a \
  ../../../../../app/search/ksarch/store/proxy-lib/redis/libredisclient.a \
  ../../../../../com/idlcompiler/astyle/libastyle.a \
  ../../../../../com/idlcompiler/cxx/libskeleton.a \
  ../../../../../com/idlcompiler/java/libjava_skeleton.a \
  ../../../../../com/idlcompiler/parser/libparser.a \
  ../../../../../com/idlcompiler/php/libphp_skeleton.a \
  ../../../../../inf/computing/zookeeper/output/c_client/lib/libzookeeper_mt.a \
  ../../../../../inf/computing/zookeeper/output/c_client/lib/libzookeeper_st.a \
  ../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../lib2-64/string/lib/libstring.a \
  ../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../op/oped/noah/webfoot/naming-lib/output/lib/libwebfoot_naming.a \
  ../../../../../public/bslext/output/lib/libbsl_bml.a \
  ../../../../../public/bslext/output/lib/libbsl_containers_utils.a \
  ../../../../../public/bslext/output/lib/libbsl_var_scripting.a \
  ../../../../../public/bslext/output/lib/libbsl_var_serializer.a \
  ../../../../../public/bslext/output/lib/libbsl_var_vscript.a \
  ../../../../../public/bslext/output/lib/libbsl_vs.a \
  ../../../../../public/bslext/output/lib/libbslext.a \
  ../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../public/configure/libconfig.a \
  ../../../../../public/connectpool/libconnectpool.a \
  ../../../../../public/ependingpool/libependingpool.a \
  ../../../../../public/fcrypt/libfcrypt.a \
  ../../../../../public/gm/galileo/libgalileo.a \
  ../../../../../public/gm/galileo/output/lib/libzookeeper_mt.a \
  ../../../../../public/idlcompiler/output/lib/libmcpack_idl.a \
  ../../../../../public/mcpack/libmcpack.a \
  ../../../../../public/myclient/libmyclient.a \
  ../../../../../public/ns/buffer/libbuffer.a \
  ../../../../../public/ns/mynet/libmynet.a \
  ../../../../../public/nshead/libnshead.a \
  ../../../../../public/odict/libodict.a \
  ../../../../../public/spcache/libspcache.a \
  ../../../../../public/spreg/libspreg.a \
  ../../../../../public/ub/output/lib/libub.a \
  ../../../../../public/ub/output/lib/libub_aserver.a \
  ../../../../../public/ub/output/lib/libub_client.a \
  ../../../../../public/ub/output/lib/libub_conf.a \
  ../../../../../public/ub/output/lib/libub_galileo.a \
  ../../../../../public/ub/output/lib/libub_log.a \
  ../../../../../public/ub/output/lib/libub_misc.a \
  ../../../../../public/ub/output/lib/libub_monitor.a \
  ../../../../../public/ub/output/lib/libub_naming.a \
  ../../../../../public/ub/output/lib/libub_server.a \
  ../../../../../public/ub/output/lib/libubex.a \
  ../../../../../public/ub/output/lib/libubfw.a \
  ../../../../../public/uconv/libuconv.a \
  ../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../third-64/boost/lib/libboost_iostreams.a \
  ../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../third-64/mysql/lib/libdbug.a \
  ../../../../../third-64/mysql/lib/libheap.a \
  ../../../../../third-64/mysql/lib/libmyisam.a \
  ../../../../../third-64/mysql/lib/libmyisammrg.a \
  ../../../../../third-64/mysql/lib/libmysqlclient.a \
  ../../../../../third-64/mysql/lib/libmysqlclient_r.a \
  ../../../../../third-64/mysql/lib/libmystrings.a \
  ../../../../../third-64/mysql/lib/libmysys.a \
  ../../../../../third-64/mysql/lib/libvio.a \
  ../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../third-64/protobuf/lib/libprotobuf-lite.a \
  ../../../../../third-64/protobuf/lib/libprotobuf.a \
  ../../../../../third-64/protobuf/lib/libprotoc.a \
  ../../../../../thirdsrc/zookeeper/output/lib/libzookeeper_mt.a \
  ../../../../../thirdsrc/zookeeper/output/lib/libzookeeper_st.a -lpthread \
  -lcrypto \
  -lrt \
  -lcurl \
  -lldap \
  -lidn -Xlinker "-)" -o rls
	mkdir -p ./output/bin
	cp -f --link rls ./output/bin

.copy_conf:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m.copy_conf[0m']"
	touch .copy_conf
	cp -R rd/conf output/conf

rd/src/idl/rls_reload.idl.o:rd/src/idl/reload.idl.cpp \
  rd/src/idl/reload.idl.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/idl/rls_reload.idl.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/idl/rls_reload.idl.o rd/src/idl/reload.idl.cpp

rd/src/idl/rls_rls2.idl.o:rd/src/idl/rls2.idl.cpp \
  rd/src/idl/rls2.idl.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/idl/rls_rls2.idl.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/idl/rls_rls2.idl.o rd/src/idl/rls2.idl.cpp

rd/src/rls_common.o:rd/src/common.cpp \
  rd/src/common.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_common.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_common.o rd/src/common.cpp

rd/src/rls_config.o:rd/src/config.cpp \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls.h \
  rd/src/idl/rls2.idl.h \
  rd/src/rls_def.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_config.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_config.o rd/src/config.cpp

rd/src/rls_dao.o:rd/src/dao.cpp \
  rd/src/dao.h \
  rd/src/macro.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/rls_dictseeker.h \
  rd/src/rls_struct.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_dao.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_dao.o rd/src/dao.cpp

rd/src/rls_mcCache.o:rd/src/mcCache.cpp \
  rd/src/mcCache.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/rls_struct.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_dictseeker.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_mcCache.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_mcCache.o rd/src/mcCache.cpp

rd/src/rls_mystring.o:rd/src/mystring.cpp \
  rd/src/mystring.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_mystring.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_mystring.o rd/src/mystring.cpp

rd/src/rls_myubclient_strategy.o:rd/src/myubclient_strategy.cpp \
  rd/src/myubclient_strategy.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_myubclient_strategy.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_myubclient_strategy.o rd/src/myubclient_strategy.cpp

rd/src/rls_networker.o:rd/src/networker.cpp \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/networker.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_networker.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_networker.o rd/src/networker.cpp

rd/src/rls_redis.o:rd/src/redis.cpp \
  rd/src/mcCache.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/rls_struct.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_dictseeker.h \
  rd/src/redis.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_redis.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_redis.o rd/src/redis.cpp

rd/src/rls_reload.o:rd/src/reload.cpp \
  rd/src/reload.h \
  rd/src/common.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/idl/reload.idl.h \
  rd/src/userworker.h \
  rd/src/rls_struct.h \
  rd/src/dao.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_reload.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_reload.o rd/src/reload.cpp

rd/src/rls_rls.o:rd/src/rls.cpp \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/networker.h \
  rd/src/reload.h \
  rd/src/userworker.h \
  rd/src/rls_struct.h \
  rd/src/dao.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_dictseeker.h \
  rd/src/rls_uscchecker.h \
  rd/src/myubclient_strategy.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls.o rd/src/rls.cpp

rd/src/rls_rls_dictseeker.o:rd/src/rls_dictseeker.cpp \
  rd/src/rls_dictseeker.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/rls_struct.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_dictseeker.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_dictseeker.o rd/src/rls_dictseeker.cpp

rd/src/rls_rls_instant.o:rd/src/rls_instant.cpp \
  rd/src/rls_instant.h \
  rd/src/macro.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/rls_struct.h \
  rd/src/userworker.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_instant.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_instant.o rd/src/rls_instant.cpp

rd/src/rls_rls_piaohandler.o:rd/src/rls_piaohandler.cpp \
  rd/src/mcCache.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/rls_struct.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_dictseeker.h \
  rd/src/rls_piaohandler.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_piaohandler.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_piaohandler.o rd/src/rls_piaohandler.cpp

rd/src/rls_rls_playerhandler.o:rd/src/rls_playerhandler.cpp \
  rd/src/mystring.h \
  rd/src/rls_playerhandler.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/common.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/rls_struct.h \
  rd/src/dao.h \
  rd/src/rls_dictseeker.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_rgen.h \
  rd/src/rls_rstrategy.h \
  rd/src/rls_ral.h \
  rd/src/redis.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_playerhandler.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_playerhandler.o rd/src/rls_playerhandler.cpp

rd/src/rls_rls_queryhandler.o:rd/src/rls_queryhandler.cpp \
  rd/src/rls_queryhandler.h \
  rd/src/rls_def.h \
  rd/src/rls_dictseeker.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/rls_struct.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_queryhandler.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_queryhandler.o rd/src/rls_queryhandler.cpp

rd/src/rls_rls_ral.o:rd/src/rls_ral.cpp \
  rd/src/rls_ral.h \
  rd/src/rls_def.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/rls_struct.h \
  rd/src/rls_dictseeker.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/topn.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_ral.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_ral.o rd/src/rls_ral.cpp

rd/src/rls_rls_rgen.o:rd/src/rls_rgen.cpp \
  rd/src/rls_rgen.h \
  rd/src/rls_def.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/idl/rls2.idl.h \
  rd/src/rls_rstrategy.h \
  rd/src/rls_struct.h \
  rd/src/dao.h \
  rd/src/rls_dictseeker.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_ral.h \
  rd/src/redis.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_rgen.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_rgen.o rd/src/rls_rgen.cpp

rd/src/rls_rls_rstrategy.o:rd/src/rls_rstrategy.cpp \
  rd/src/rls_rstrategy.h \
  rd/src/rls_def.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/idl/rls2.idl.h \
  rd/src/rls_struct.h \
  rd/src/dao.h \
  rd/src/rls_dictseeker.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_ral.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_rstrategy.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_rstrategy.o rd/src/rls_rstrategy.cpp

rd/src/rls_rls_uscchecker.o:rd/src/rls_uscchecker.cpp \
  rd/src/rls_uscchecker.h \
  rd/src/rls_struct.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h \
  rd/src/userworker.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_uscchecker.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_uscchecker.o rd/src/rls_uscchecker.cpp

rd/src/rls_rls_uscgetter.o:rd/src/rls_uscgetter.cpp \
  rd/src/rls_uscgetter.h \
  rd/src/rls_struct.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/dao.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_uscgetter.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_uscgetter.o rd/src/rls_uscgetter.cpp

rd/src/rls_rls_y_playerhandler.o:rd/src/rls_y_playerhandler.cpp \
  rd/src/mystring.h \
  rd/src/rls_y_playerhandler.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/common.h \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/rls_struct.h \
  rd/src/dao.h \
  rd/src/rls_dictseeker.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/userworker.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_rgen.h \
  rd/src/rls_rstrategy.h \
  rd/src/rls_ral.h \
  rd/src/redis.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_rls_y_playerhandler.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_rls_y_playerhandler.o rd/src/rls_y_playerhandler.cpp

rd/src/rls_shuffle.o:rd/src/shuffle.cpp \
  rd/src/shuffle.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_shuffle.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_shuffle.o rd/src/shuffle.cpp

rd/src/rls_userworker.o:rd/src/userworker.cpp \
  rd/src/rls.h \
  rd/src/config.h \
  rd/src/macro.h \
  rd/src/common.h \
  rd/src/rls_def.h \
  rd/src/idl/rls2.idl.h \
  rd/src/userworker.h \
  rd/src/rls_struct.h \
  rd/src/dao.h \
  rd/src/rls_piaohandler.h \
  rd/src/rls_dictseeker.h \
  rd/src/mcCache.h \
  rd/src/rls_instant.h \
  rd/src/rls_uscgetter.h \
  rd/src/rls_queryhandler.h \
  rd/src/rls_y_playerhandler.h \
  rd/src/rls_rgen.h \
  rd/src/rls_rstrategy.h \
  rd/src/rls_ral.h \
  rd/src/redis.h \
  rd/src/rls_playerhandler.h \
  rd/src/topn.h \
  rd/src/shuffle.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mrd/src/rls_userworker.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o rd/src/rls_userworker.o rd/src/userworker.cpp

endif #ifeq ($(shell uname -m),x86_64)


