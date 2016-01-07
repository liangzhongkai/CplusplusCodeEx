#include <stdafx.h>

//////////////////////////////////////////////////////////
//
//   名字：二阶段提交协议<一致性协议的一种>
//   用途：实现原子性操作，事务等
//   核心：每种角色的状态变化都必须只有一条线，因为事务过程中接收到许多失效的包，状态决定对接收到的包进行怎样的操作，状态记录在日志文件
//             而且每种角色的状态变化不能出现无限等待，超时后必须能结束掉
//   解决办法：超时等于否定
//
//////////////////////////////////////////////////////////

void Actions_Of_Coordinator(){
    write("START_2PC to local log");
    multicast("VOTE_REQUEST to all participants");    //附带一个独一无二的事务ID

    while(not all votes have been collected) {
        waitfor("any incoming vote");
        if(timeout) {
            write("GLOBAL_ABORT to local host");
            multicast("GLOBAL_ABORT to all participants");
            return;
        }
        record(vote);  // 收集投票votes, 直到全部集齐
    }

    if(all participants send VOTE_COMMIT and coordinatorvotes COMMIT) {   // 如果全部都投赞成票
        write("GLOBAL_COMMIT to local log");
        multicast("GLOBAL_COMMIT to all participants");
    } else {                                                                                                        // 有一个或以上参与者投反对票
        write("GLOBAL_ABORT to local log");
        multicast("GLOBAL_ABORT to all participants");
    }
}

void Actions_Of_Participants(){
    write("INIT to local log");
    waitfor("VOTE_REQUEST from coordinator");
    if(timeout) {
        write("VOTE_ABORT to local log");
        return;
    }

    if("participant votes COMMIT") {     // 如果该参与者本地资源可以使用，便返回COMMIT，并锁住资源，直到协调者决定是否真正操作资源，然后解锁
        write("VOTE_COMMIT to local log");
        send("VOTE_COMMIT to coordinator");
        waitfor("DESCISION from coordinator");

        if(timeout) {
            multicast("DECISION_REQUEST to other participants");
            waituntil("DECISION is received"); // 直到其他参与者的回复到来，但是万一没有参与者收到协调者的决定，难道要一直等下去？绝壁不是
            if(timeout) {
                write("GLOBAL_ABORT to local log");
                return;
            }
        }

        write("DECISION to local log");
        if(DECISION == "GLOBAL_COMMIT") {
            write("GLOBAL_COMMIT to local log");
        } else if(DECISION == "GLOBAL_ABORT") {
            write("GLOBAL_ABORT to local log");
        }
    } else {
        write("GLOBAL_ABORT to local log");
        send("GLOBAL_ABORT to coordinator");
    }
}