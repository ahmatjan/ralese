//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : myubclient_strategy.cpp
// @date        : 25 Apr 2012,15:24:26
// @copyright   : 2012 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 
//============================================================================

#include "myubclient_strategy.h"
#include <ub_log.h>
#include "ubclient_connectserver.h"
    int MyUbClientStrategy :: filterServer(ub::ConnectionRequestex *req, 
                                           bsl::var::IVar & confVar,
                                           ub::ConnectionRes *serverSelectedInfo){
        UB_LOG_DEBUG("%s", __func__);
        //健康Server过滤 
        if (NULL == req || NULL == serverSelectedInfo) {
            return -1;
        }

        int serverNum = _mgr->getServerSize();
        if (serverNum <= 0) {
            UB_LOG_WARNING("getServerSize[%d] error", serverNum);
            return -1;
        }
        int i = 0;
        UB_LOG_DEBUG("server num : [%d]", serverNum);
        //机房过滤策略
        int room_total = 0;
        int good_room_total = 0;
        bool room_filter = false;
        for (i=0; i<serverNum; i++) {
            ub::UbClientServer *svr = dynamic_cast<ub::UbClientServer *>(_mgr->getServerInfo(i));
            if(NULL != svr && svr->getMaster() == 1){
                room_total++;
                if(svr->isEnable() && svr->isHealthy()){
                    good_room_total++;
                }
                else{//有机器有问题
                    UB_LOG_FATAL("service not avalable, ip[%s], port[%d]", svr->getIP(0), svr->getPort());
                }
            }
        }
        if(good_room_total > 0 && good_room_total >= room_total/2){
            room_filter = true;
        }
        for (i=0; i<serverNum; i++) {
            ub::UbClientServer *svr = dynamic_cast<ub::UbClientServer *>(_mgr->getServerInfo(i));
            if(NULL != svr && svr->isEnable() && svr->isHealthy()) {
                int j = 0;
                for (j=0; j<serverSelectedInfo->selectedServerID.size(); j++) {
                    if (serverSelectedInfo->selectedServerID[j] == i) {
                        break;
                    }
                }
                if (j < serverSelectedInfo->selectedServerID.size()) {
                    continue;
                }
                //其它机房过滤
                if(room_filter && svr->getMaster() == 0){
                    continue;
                }
                UB_LOG_DEBUG("push [%d]", i);
                if (serverSelectedInfo->resultServerID.push_back(i) != 0) {
                    UB_LOG_WARNING("reach server list size : %d", ub::UBCLIENT_SELECTEDSERVER_SIZE);
                    return -1;
                }
			}
        }
        return 0;
    }
