#pragma once

#include "basicTypes.h"
#include "laneModel.h"

namespace ncStruct {

enum ReminderType {
    ReminderType_none = 0,
    // guidanceVersion <= 11000ʱ����ʾһ��ֱ�С��������̵�·��ֱ�С�����·����/��ֱ�С�
    // guidanceVersion >= 13000ʱ�ϳ���ϸ��Ϊ ReminderType_passJunction �� ReminderType_passFork.
    ReminderType_goStraight = 1,
    
    // �ظ�·������ʻ
    ReminderType_keepSideRoad = 2,
    
    // 7.0 or above "�뱣�������·��ʻ"���������ڸ���·�Ϳ���·
    ReminderType_keepMainRoad = 3,
    
    // guidanceVersion >= 13000, ��ʾ��ֱ��ͨ��·�ڡ�
    ReminderType_passJunction = 4,
    
    // guidanceVersion >= 13000, ��ʾ����˳�У�T�ֿڻ���Y�ֿڣ��Ա��и��ֲ�
    ReminderType_passFork = 5,
    
    // guidanceVersion >= 14000, ��ʾͨ����һ��·�ڣ�ǰ����ת�򹹳������maneuver 
    ReminderType_passFirstJunction = 6,
    
    // guidanceVersion >= 21000, ���
    ReminderType_enterTunnel = 7,
};

struct Reminder {
    // ������λ��
    std::string pos;

    // ��ʾ��λ�ã�����·����㣩
    int dis;

    // Remidner������. guidanceVersion >= 6000
    // �� ty �ֶΣ���ʾReminderType_goStraight
    ReminderType ty;    // [default = ReminderType_goStraight];

    // ������ʾ���ͣ�ע���� tnTy ��Ĭ��Ϊ TurnType_straight
    TurnType tnTy; // [default = TurnType_straight];

    // �¶���ʾ. �޴��ֶΣ���ʾ SlopeHint_none.
    SlopeHint sH;

    // reminder�¼�ǰ��·����·���е��±�
    int sI;

    // reminder�¼����·����·���е��±�
    int eI;

    // ��ͬguidance�汾ʱ��ʽ��ͬ, (dv >= 2.1.4)
    LaneModel laneModel;

    //  һЩ��ǣ���";"�ָT��ʾ�к��̵ơ� guidanceVersion >= 10000
    // optional string flags = 9;
    std::string flags;

    // ��չ���Բ�����Ԥ�������ƻ�����������������չ�����ã�������������� JSON ����
    // optional google.protobuf.Any exts = 20;
    // void* exts = NULL;
};

}