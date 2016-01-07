#include <stdafx.h>

//////////////////////////////////////////////////////////
//
//   ���֣����׶��ύЭ��<һ����Э���һ��>
//   ��;��ʵ��ԭ���Բ����������
//   ���ģ�ÿ�ֽ�ɫ��״̬�仯������ֻ��һ���ߣ���Ϊ��������н��յ����ʧЧ�İ���״̬�����Խ��յ��İ����������Ĳ�����״̬��¼����־�ļ�
//             ����ÿ�ֽ�ɫ��״̬�仯���ܳ������޵ȴ�����ʱ������ܽ�����
//   ����취����ʱ���ڷ�
//
//////////////////////////////////////////////////////////

void Actions_Of_Coordinator(){
    write("START_2PC to local log");
    multicast("VOTE_REQUEST to all participants");    //����һ����һ�޶�������ID

    while(not all votes have been collected) {
        waitfor("any incoming vote");
        if(timeout) {
            write("GLOBAL_ABORT to local host");
            multicast("GLOBAL_ABORT to all participants");
            return;
        }
        record(vote);  // �ռ�ͶƱvotes, ֱ��ȫ������
    }

    if(all participants send VOTE_COMMIT and coordinatorvotes COMMIT) {   // ���ȫ����Ͷ�޳�Ʊ
        write("GLOBAL_COMMIT to local log");
        multicast("GLOBAL_COMMIT to all participants");
    } else {                                                                                                        // ��һ�������ϲ�����Ͷ����Ʊ
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

    if("participant votes COMMIT") {     // ����ò����߱�����Դ����ʹ�ã��㷵��COMMIT������ס��Դ��ֱ��Э���߾����Ƿ�����������Դ��Ȼ�����
        write("VOTE_COMMIT to local log");
        send("VOTE_COMMIT to coordinator");
        waitfor("DESCISION from coordinator");

        if(timeout) {
            multicast("DECISION_REQUEST to other participants");
            waituntil("DECISION is received"); // ֱ�����������ߵĻظ�������������һû�в������յ�Э���ߵľ������ѵ�Ҫһֱ����ȥ�����ڲ���
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