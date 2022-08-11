#pragma once

#include <string>
#include <vector>
#include <stdint.h>

namespace ncStruct {

enum Sideness
{
    Sideness_unknown = 0, // ·����
    Sideness_left = 1,    // ·�����
    Sideness_right = 2,    // ·���Ҳ�
};

/// @brief ��·���г�����,�������߹涨�Ŀ��������ʻ
/// @sa http://en.wikipedia.org/wiki/Traffic_direction
enum TrafficDirection
{
	TrafficDirection_rightHand = 0,  // ������ʻ
	TrafficDirection_leftHand = 1,   // ������ʻ
};

enum TurnType {
    TurnType_none = 0,                    ///< ��Ч
    TurnType_straight = 1,                ///< ֱ��
    TurnType_left = 2,                    ///< ��ת
    TurnType_right = 3,                   ///< ��ת
    TurnType_slightlyLeft = 4,            ///< ����ǰ����ʻ
    TurnType_slightlyRight = 5,           ///< ����ǰ����ʻ
    TurnType_hardLeft = 6,                ///< �������ʻ
    TurnType_hardRight = 7,               ///< ���Һ���ʻ
    TurnType_keepLeft = 8,                ///< ���������ʻ
    TurnType_keepRight = 9,               ///< �����Ҳ���ʻ
    TurnType_straightKeepLeft = 10,       ///< ֱ����������
    TurnType_straightKeepRight = 11,      ///< ֱ�����Ҳ����
    TurnType_leftKeepLeft = 12,           ///< ��ת��������
    TurnType_leftKeepRight = 13,          ///< ��ת���Ҳ����
    TurnType_rightKeepLeft = 14,          ///< ��ת��������
    TurnType_rightKeepRight = 15,         ///< ��ת���Ҳ����
    TurnType_U = 16,                      ///< ��ͷ
};

/// ·�ε��¶���ʾ����
enum SlopeHint {
	SlopeHint_none = 0,             ///< ���¶���ʾ
	SlopeHint_upElevated = 1,       ///< �ϸ߼�
	SlopeHint_upBridge = 2,         ///< ����
	SlopeHint_upHill = 3,           ///< ����
	SlopeHint_downElevated = 4,     ///< �¸߼�
	SlopeHint_downBridge = 5,       ///< ����
	SlopeHint_downHill = 6,         ///< ����
	SlopeHint_notUpElevated = 7,    ///< ���ϸ߼�
	SlopeHint_notUpBridge = 8,      ///< ������
	SlopeHint_notUpHill = 9,        ///< ������
	SlopeHint_notDownElevated = 10, ///< ���¸߼�
	SlopeHint_notDownBridge = 11,   ///< ������
	SlopeHint_notDownHill = 12,     ///< ������
};

enum Direction {
    Direction_unknown = 0,
    Direction_up = 1,
    Direction_down = 2,
    Direction_left = 3,
    Direction_right = 4,
};

enum RestrictionShapeType {
    RestrictionShapeType_none = 0,
    RestrictionShapeType_polyline = 1,  //�߶�
    RestrictionShapeType_polygon = 2,   //�����
};

/**	@brief ·����Ϣ������,ע�⣺��Ҫ�޸��京��ʹ��� */
enum SignInfoType {
	SignInfoType_none = 0,      ///< ��Ч����,�������в������,�������ڴ�����
	SignInfoType_IC = 1,        ///< ����·��
	SignInfoType_Direction = 2, ///< ����·��
};

}