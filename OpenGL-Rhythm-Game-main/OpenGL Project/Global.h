#pragma once

#define WIDTH 1270
#define HEIGHT 720
#define COLUMS 127
#define ROWS 108
#define JUDGE_HEIGHT 5

#define FPS 60

#define INF 214748364	// �Ϻη� ������ �ڸ� ��

#define LINES 4

#define PI 3.14159265358979323846
#define START_FRAME 5*FPS

// ITEM BLINK
#define BLINK_DURATION 400
#define BLINK_DELAY 20

// ITEM ACCEL
#define ACCEL_DURATION 400
#define ACCEL_INIT_VELOCITY 0
#define ACCEL_CONSTANT 0.0097087		// ���� X: �����ϸ� �������� ��Ʈ�� ���� ����

// ITEM SLOWDOWN
#define SLOW_DOWN_DURATION 400
#define SLOW_DOWN_INIT_VELOCITY 1.5
#define SLOW_DOWN_CONSTANT  -0.004854	// ���� X: �����ϸ� �������� ��Ʈ�� ���� ����

// LieNote
#define LIE_DURATION 400


enum MUSIC {
	CANON,
	REVOLUTIONARY
};

enum JUDGEMENT {
	NONE,
	PERFECT,
	GREAT,
	NORMAL,
	BAD,
	MISS
};

enum UI_SELECTION {
	SINGLE_PLAY,
	ONLINE_PLAY,
	TUTORIAL,
	EXIT
};

enum JUDGEMENT_FRAME {
	PERFECT_FRAME = 5,
	GREAT_FRAME = 10,
	NORMAL_FRAME = 15,
	BAD_FRAME = 20,
	MISS_FRAME = 25

};