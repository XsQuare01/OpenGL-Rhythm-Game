#include "Render.h"
#include "RoundScene.h"
#include <vector>
#include <iostream>
#include <random>
#include <bass.h>
#include <stdlib.h>
#include "FireWork.h"
#include "ResultScene.h"

using namespace std;


RoundScene::RoundScene(GameWindow* window, MUSIC id)
{
	this->window = window;

	this->id = id;
	for (int i = 0; i < LINES; i++) {
		line_input[i] = 0;
	}

	switch (this->id)
	{
	case CANON:
		this->name = "Cannon Variation";
		this->artist = "Johan Pachelbel";
		this->musicFile = "./Canon.mp3";
		break;

	case REVOLUTIONARY:
		this->name = "Chopin etude Op.10 No.12 Revolutionary";
		this->artist = "";
		this->musicFile = "./Revolutionary.mp3";

	default:
		break;
	}


	this->init();
	// id를 통해 노래 정보등을 가져오기
}

RoundScene::~RoundScene()
{
	for (int line = 0; line < LINES; line++) {
		for (size_t i = 0; i < this->notes[line].size() - 1; i++) {
			if (this->notes[line][i] != NULL) {
				free(this->notes[line][i]);
			}
		}
	}
}

void RoundScene::init() {

	this->gameInfo = new GameInfo();
	U_Config = new UserConfig();
	BASS_Init(-1, 44100, 0, 0, NULL);

	this->loadMusic();

	int s;
	float t;

	switch (this->id)
	{
	case CANON:
		
		break;
	default:
		break;
	}
}

void RoundScene::loadMusic() {
	this->stream = BASS_StreamCreateFile(FALSE, this->musicFile.c_str(), 0, 0, 0);
	BASS_ChannelPlay(this->stream, FALSE);
	setMVol(U_Config->M_Vol);
	BASS_ChannelPause(this->stream);

	//끝나는 시점 계산
	QWORD len = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
	double time = BASS_ChannelBytes2Seconds(stream, len);
	endFrame = START_FRAME + (time * FPS);
}

void RoundScene::playEffectSound() {
	HSTREAM effect = BASS_StreamCreateFile(FALSE, "./hit_sound.mp3", 0, 0, 0);
	BASS_ChannelSetAttribute(effect, BASS_ATTRIB_VOL, U_Config->E_Vol);
	BASS_ChannelPlay(effect, FALSE);
}

void RoundScene::playSound() {
	if (this->stream) {
		BASS_ChannelPlay(this->stream, FALSE);
	}
}

void RoundScene::pauseSound(bool pause)
{
	if (pause) BASS_ChannelPause(this->stream);
	else {
		if (frame >= START_FRAME) {
			this->playSound();
		}
	}
}

void RoundScene::setMVol(float volume)
{
	bool check = BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
}

void RoundScene::receiveJudgement(int judge, Note* nott)
{
	//(0 = Normal, 1 = Section, 2 = Lie, 3 = LieSection 4 = 하이라이트 5 = Item1, 6 = Item2, 7 = Item3)

	int type = nott->type;

	//miss 아닐때만 확인
	//item1 : 회복, 2판정, up 3상대방 가리기 

	if (type >= 5 && judge < 5) {


		if (type == 5) {
			gameInfo->HP += 30;
		}
		else if (type == 6) {
			//프레임 단위(임시)
			reinforce += 1000;
		}
	}

	//판정 up 아이템 적용
	//퍼펙트 < 해당노트 < miss 해당노트 판정 up
	if (reinforce > 0 && judge > 1 && judge < 5) {
		judge--;
	}
	//lie노트
	//놓쳤을 때가 아닐 때 처리

	// 가짜 노트 - 수정 필수!!!!!!!!!!!!! 가짜 롱노트 부분
	if (type == 2) {
		printf("lie\n");
		if (judge < 6)
			gameInfo->HP -= 30;
	}
	else if (type == 1) {
		calcSectionInfo(judge);
	}
	else if (type == 4)
		calcInfo(judge, 1);
	else calcInfo(judge, 0);

	if (gameInfo->HP > 100)
		gameInfo->HP = 100;

	if (gameInfo->HP <= 0) {
		this->isEnd = true;
	}
}

void RoundScene::calcInfo(int judge, int highlight)
{
	//perfect 1 great 2 normal 3 bad 4 miss : 점수 계산 없음
	//노트 점수 : 기본점수 * 콤보 보너스(100combo당 10% 증가) * 판정 점수(1.3 1.1 1.0 0.5 0)
	int base = 0;
	if (highlight)
		base = 150;
	else
		base = 100;

	int interval = gameInfo->combo / 100;
	float calc = 0;

	switch (judge) {
	case 1:
		gameInfo->HP += 2;
		gameInfo->combo++;
		gameInfo->perfect++;
		gameInfo->recentJudgement = PERFECT;
		calc = base * (1 + (interval * 0.1)) * 1.3;
		break;
	case 2:
		gameInfo->HP += 1;
		gameInfo->combo++;
		gameInfo->great++;
		gameInfo->recentJudgement = GREAT;
		calc = base * (1 + (interval * 0.1)) * 1.1;
		break;
	case 3:
		gameInfo->combo++;
		gameInfo->normal++;
		gameInfo->recentJudgement = NORMAL;
		calc = base * (1 + (interval * 0.1)) * 1;
		break;
	case 4:
		gameInfo->HP -= 5;
		gameInfo->combo = 0;
		gameInfo->bad++;
		gameInfo->recentJudgement = BAD;
		calc = base * 0.5;
		break;
	default:
		gameInfo->HP -= 10;
		gameInfo->combo = 0;
		gameInfo->miss++;
		gameInfo->recentJudgement = MISS;
	}
	if (gameInfo->max_combo < gameInfo->combo) {
		gameInfo->max_combo = gameInfo->combo;
	}
	int tmp = calc;
	gameInfo->score += tmp;
}


void RoundScene::calcSectionInfo(int judge)
{
	//perfect 1 great 2 normal 3 bad 4 miss : 점수 계산 없음
	//노트 점수 : 기본점수 * 콤보 보너스(100combo당 10% 증가) * 판정 점수(1.3 1.1 1.0 0.5 0)
	int base = 100;
	int interval = gameInfo->combo / 100;
	float calc = 0;

	switch (judge) {
	case 1:
		gameInfo->HP += 0.2;
		gameInfo->combo++;
		gameInfo->perfect++;
		gameInfo->recentJudgement = PERFECT;
		calc = base * (1 + (interval * 0.1)) * 1.3;
		break;
	case 2:
		gameInfo->HP += 0.1;
		gameInfo->combo++;
		gameInfo->great++;
		gameInfo->recentJudgement = GREAT;
		calc = base * (1 + (interval * 0.1)) * 1.1;
		break;
	case 3:
		gameInfo->combo++;
		gameInfo->normal++;
		gameInfo->recentJudgement = NORMAL;
		calc = base * (1 + (interval * 0.1)) * 1;
		break;
	case 4:
		gameInfo->HP -= 0.5;
		gameInfo->combo = 0;
		gameInfo->bad++;
		gameInfo->recentJudgement = BAD;
		calc = base * 0.5;
		break;
	default:
		gameInfo->HP -= 10;
		gameInfo->combo = 0;
		gameInfo->miss++;
		gameInfo->recentJudgement = MISS;
	}

	int tmp = calc;
	gameInfo->score += tmp;
}

void RoundScene::setInput(unsigned char key) {
	//cout << key;
	if (key == 'd') {
		this->key[0] = true;
		this->renderKey[0] = true;
		this->playEffectSound();
	}
	else if (key == 'f') {
		this->key[1] = true;
		this->renderKey[1] = true;
		this->playEffectSound();
	}
	else if (key == 'j') {
		this->key[2] = true;
		this->renderKey[2] = true;
		this->playEffectSound();
	}
	else if (key == 'k') {
		this->key[3] = true;
		this->renderKey[3] = true;
		this->playEffectSound();
	}
	else if (key == 'p') {
		pause = !(pause);
		pauseSound(pause);

	}
	else if (key == '[') {
		U_Config->M_Vol -= 0.1;
		if (U_Config->M_Vol < 0) U_Config->M_Vol = 0;
		setMVol(U_Config->M_Vol);
	}
	else if (key == ']') {
		U_Config->M_Vol += 0.1;
		if (U_Config->M_Vol > 1) U_Config->M_Vol = 1;
		setMVol(U_Config->M_Vol);
	}
	//효과음 볼륨조정
	else if (key == ',') {
		U_Config->E_Vol -= 0.1;
		if (U_Config->E_Vol < 0) U_Config->E_Vol = 0;
	}
	else if (key == '.') {
		U_Config->E_Vol += 0.1;
		if (U_Config->E_Vol > 1) U_Config->E_Vol = 1;
	}
	// 아이템 테스트용
	else if (key == 'q') {
		blink();
		printf("Blink On!\n");
	}
	else if (key == 'w') {
		setAccelNote(frame);
		printf("Accel On!\n");
	}
	else if (key == 'e') {
		setSlowNote(frame);
		printf("Slow Down On!\n");
	}
	else if (key == 'r') {
		lieNoteOn();
		printf("Lie Note On!\n");
	}
	else if (key == 't') {
		unsetAutoMode();
		printf("Auto Mode Off!\n");
	}

}
void RoundScene::unsetInput(unsigned char key) {
	if (key == 'd') {
		this->key[0] = false;
		this->renderKey[0] = false;
	}
	else if (key == 'f') {
		this->key[1] = false;
		this->renderKey[1] = false;
	}
	else if (key == 'j') {
		this->key[2] = false;
		this->renderKey[2] = false;
	}
	else if (key == 'k') {
		this->key[3] = false;
		this->renderKey[3] = false;
	}
}


void RoundScene::checkSectionNote()
{
	// 모든 line에 대하여 검사
	for (int i = 0; i < LINES; i++) {

		// 현재 롱노트가 입력 상태일 때,
		if (section_judgement[i] != -1) {

			// 현재 롱노트
			Note* current_section = notes[i][line_input[i]];

			// 손이 떨어지지 않음 - 입력중
			if (this->renderKey[i]) {
				// 입력 길이가 롱노트의 길이보다 짧다면, 
				if (current_section->getNoteLength() > section_input[i]) {
					// 롱노트 판정 반복 전달
					receiveJudgement(section_judgement[i], current_section);

					// input++
					section_input[i] += 1;
				}
				// 둘이 길이가 동일함 -> 이제부턴 롱노트 입력 x
				else if (current_section->getNoteLength() == section_input[i]) {
					// 입력 횟수, 판정 초기화
					section_input[i] = 0;
					section_judgement[i] = -1;
					section_delay[i] = 0;

					// 노트 제거
					this->deleteNote(i, line_input[i]);
					this->setLineInput(i);
				}
			}
			// 손이 떨어짐 - 더 이상 롱노트 입력 X
			else {
				// 마지막 노트와의 판정 구하기
				unsigned int end_frame =
					(current_section->createFrame + current_section->getNoteLength()) + (ROWS - JUDGE_HEIGHT);
				unsigned int unset_delay = end_frame - frame;

				// 노트 삭제
				this->deleteNote(i, line_input[i]);
				this->setLineInput(i);

				// Normal 입력까지는 기존 입력 고수
				if (unset_delay <= NORMAL_FRAME && unset_delay >= -NORMAL_FRAME) {
					receiveJudgement(section_judgement[i], current_section);
				}
				// Bad 이하는 모두 Miss로
				else {
					receiveJudgement(5, current_section);
				}

				// 입력 횟수, 판정 초기화
				section_input[i] = 0;
				section_judgement[i] = -1;
				section_delay[i] = 0;

			}

		}
		else {
			continue;
		}

	}

}

void RoundScene::checkInput()
{
	// Queue가 비어있지 않다면,
	while (!InputQueue.empty()) {
		// 현재 입력
		Input* current_input = InputQueue.front();

		int i_line = current_input->getInputLine();
		unsigned int i_frame = current_input->getInputFrame();

		// 입력 처리
		getNoteDelay(i_line, i_frame);

		// Queue 제거
		InputQueue.pop();
		delete current_input;
	}

}

void RoundScene::addInput(int line)
{
	InputQueue.push(new Input(frame, line));
}

void RoundScene::showTimer()
{
	if (init_timer == NULL) {
		init_timer = clock();
	}
	clock_t passed_time = clock() - init_timer;
	// 1000 : 60 (timer :  frame) -> 16.67 ms per 1 frame
	//cout << "Frame: " << frame << " Seconds: " << double(passed_time) / CLOCKS_PER_SEC << endl;
	clock_delay = double(passed_time) - round(16.667 * frame);
	//cout << "Delay: " << clock_delay << "ms" << endl;
}
void RoundScene::timeCheck()
{
	if (frame % 30 == 0) {
		if (start_timer == NULL) {
			start_timer = clock();
		}
		else {
			end_timer = clock();
			calcTimer();
			start_timer = end_timer;

		}
	}
}

void RoundScene::calcTimer()
{
	// frame이 빠름
	if (clock_delay < 0) {
		Sleep(-double(clock_delay));
	}
	// frame이 늦음
	else if (clock_delay > 0) {
		// .....???
	}

	//cout << timer_count++ << ": 60 Frame -  " << double(clock() - start_timer) / CLOCKS_PER_SEC << " seconds" << endl;
}

void RoundScene::blink()
{
	blink_on = true;
}

void RoundScene::blinkOff()
{
	blink_on = false;
	blink_count = 0;
	//printf("Blink Off..\n");
}

void RoundScene::blinkCountUp()
{
	blink_count++;
}


void RoundScene::setAccelNote(int _frame)
{
	// 모든 라인에 대하여,
	for (int i = 0; i < LINES; i++) {
		int _count = line_input[i];
		while (true) {
			// 이미 만들어진 노트
			if (this->notes[i][_count]->createFrame < _frame) {
				_count++;
				continue;
			}
			// 가속할 노트들
			else if (this->notes[i][_count]->createFrame <= _frame + ACCEL_DURATION) {
				this->notes[i][_count++]->isAccel = true;
				continue;
			}
			// 범위를 넘어가는 것들
			else {
				break;
			}
		}
	}
}

double RoundScene::calcAccelNoteDist(int _time)
{
	if (_time < 0) {
		return 0.0;
	}
	else {
		return ACCEL_INIT_VELOCITY * _time + ACCEL_CONSTANT * _time * _time;

	}
}

void RoundScene::setSlowNote(int _frame)
{
	// 모든 라인에 대하여,
	for (int i = 0; i < LINES; i++) {
		int _count = line_input[i];
		while (true) {
			// 이미 만들어진 노트
			if (this->notes[i][_count]->createFrame < _frame) {
				_count++;
				continue;
			}
			// 가속할 노트들
			else if (this->notes[i][_count]->createFrame <= _frame + SLOW_DOWN_DURATION) {
				this->notes[i][_count++]->isSlow = true;
				continue;
			}
			// 범위를 넘어가는 것들
			else {
				break;
			}
		}
	}
}

double RoundScene::calcSlowNoteDist(int _time)
{
	if (_time < 0) {
		return 0.0;
	}
	else {
		return SLOW_DOWN_INIT_VELOCITY * _time + SLOW_DOWN_CONSTANT * _time * _time;

	}
}

int RoundScene::getNearNote(int line, int current_frame)
{
	int note_start = 0;
	int note_end = this->notes[line].size() - 1;
	int vector_center = 0;	// 임시 초기화

	// 최적의 frame: binary_search
	while (note_start <= note_end) {
		vector_center = (note_start + note_end) / 2;
		if (this->notes[line][vector_center]->createFrame == current_frame) {
			return vector_center;
		}
		// 오른쪽으로
		else if (this->notes[line][vector_center]->createFrame > current_frame) {
			note_end = vector_center - 1;
		}
		// 왼쪽으로
		else {
			note_start = vector_center + 1;
		}
	}

	// 자신보다 아래에 있는 노트 + 맨 끝 노트가 아닐 때,
	if (this->notes[line][vector_center]->createFrame < current_frame && vector_center != this->notes[line].size()) {
		return vector_center + 1;
	}
	else {
		return vector_center;
	}

}

void RoundScene::makeLieNoteData(int current_frame)
{
	// 각 라인별 현재 frame과 가장 가까운 노트 index 찾기
	int nearest_note[LINES];		// 노트 index
	int nearest_note_frame[LINES];	// 노트 생성 frame

	for (int i = 0; i < LINES; i++) {
		// 각 라인별 가장 인접한 노트를 받음 - 해당 노트부터 시작
		nearest_note[i] = getNearNote(i, current_frame);
		nearest_note_frame[i] = this->notes[i][nearest_note[i]]->createFrame;
	}

	for (int i = current_frame; i < current_frame + LIE_DURATION; i++) {
		// 최신 update
		for (int j = 0; j < LINES; j++) {
			// 롱노트일때
			if (this->notes[j][nearest_note[j]]->type == 1) {
				int _length = this->notes[j][nearest_note[j]]->getNoteLength();
				// 롱노트가 현재 프레임보다 아래에 있다면,
				if (nearest_note_frame[j] + _length < i) {
					nearest_note[j]++;
					nearest_note_frame[j] = this->notes[j][nearest_note[j]]->createFrame;
				}
			}
			// 일반노트일때
			else {
				// 해당 노트를 지나왔다면
				if (nearest_note_frame[j] < i) {
					nearest_note[j]++;
					nearest_note_frame[j] = this->notes[j][nearest_note[j]]->createFrame;
				}
			}
		}

		// 가짜 노트 넣을 수 있는지 확인용
		bool is_available[LINES];

		// 해당 프레임에 존재하는 노트 수
		int _count = 0;

		// 거짓노트 가능한 개수
		int lie_count = LINES - 1;

		// 배열 초기화
		for (int k = 0; k < LINES; k++) {

			// 롱노트라면?
			if (this->notes[k][nearest_note[k]]->type == 1) {
				int _length = this->notes[k][nearest_note[k]]->getNoteLength();
				// 롱노트가 사이에 존재한다면, 
				if (nearest_note_frame[k] + _length > i) {
					is_available[k] = false;
				}
			}
			// 아니라면?
			else {
				// 이미 해당 line frame에 진짜 노트가 존재함
				if (nearest_note_frame[k] == i) {
					is_available[k] = false;
					_count++;
				}
				else {
					is_available[k] = true;
				}

			}

		}
		// 만들 수 있는 가짜노트 전부 생성
		for (int l = _count; l > 0; l--) {
			// 임의의 시작 라인
			int rand_line = rand() % 100;
			bool _flag = true;

			for (int m = 0; m < LINES; m++) {

				// 임의의 라인 선택 - 커지지 않도록 mod 연산
				rand_line = rand_line % 4;

				// 가짜 노트 삽입 가능
				if (is_available[rand_line]) {
					lie_notes[rand_line].push_back((Note*) new LieNote(i));
					is_available[rand_line++] = false;
					_flag = false;
					break;
				}
				else {
					rand_line++;
					continue;
				}
			}

			// 더 이상 가짜 노트 추가 불가능
			if (_flag) {
				break;
			}
		}
	}
}

void RoundScene::renderLieNotes()
{
	if (frame + 120 > 10000) return;
	int input_count = 0;
	for (int line = 0; line < LINES; ++line) {
		for (int scope = 0; scope < this->lie_notes[line].size(); ++scope) {
			if (this->lie_notes[line][scope] == nullptr)
				break;
			if (this->lie_notes[line][scope]->IsActive(frame) && this->lie_notes[line][scope]->isAlive) {

				// 노트의 색 지정
				glColor3f(0.96f, 1, 0.98f);

				int height = this->lie_notes[line][scope]->GetHeight(frame);
				int noteLength = this->lie_notes[line][scope]->getNoteLength();

				//printf("%d: line, %d: scope, %d: accel_dist\n", line, scope, frame);

				glRectd(20.f + ((float)line * 4), height, 24.f + ((float)line * 4), height + noteLength);

			}
		}
	}
}

void RoundScene::setLieInput(int line)
{
	lie_input[line]++;
}

void RoundScene::lieNoteOn()
{
	lie_on = true;
	makeLieNoteData(frame);
}

void RoundScene::lieNoteOff()
{
	lie_on = false;
	lie_count = 0;
	// 거짓 노트 입력 횟수 초기화
	for (int i = 0; i < LINES; i++) {
		lie_input[i] = 0;
	}
	//printf("Lie Note Off\n");
}

void RoundScene::lieTimerCheck()
{
	lie_count++;
	if (lie_count > LIE_DURATION + ROWS) {
		lieNoteOff();
		clearLieNoteVector();
	}
}

void RoundScene::clearLieNoteVector()
{
	for (int i = 0; i < LINES; i++) {
		this->lie_notes[i].clear();
		vector<Note*>().swap(this->lie_notes[i]);
	}
}


void RoundScene::autoMode()
{
	for (int i = 0; i < LINES; i++) {
		// 노트가 판정선에 도달함
		if (mirror_flag) {
			i = LINES - (i + 1);
		}

		if (this->notes[i][line_input[i]]->GetHeight(frame) <= JUDGE_HEIGHT) {
			Note* nott = this->notes[i][line_input[i]];

			if (nott->type == 4) {
				ItemNote* itemNote = (ItemNote*)nott;
				itemNote->UseItem(this);
				mirror_flag = !mirror_flag;
			}

			int _result = rand() % 100;
			if (_result <= 90) {
				receiveJudgement(1, nott);
			}
			else if (_result <= 95) {
				receiveJudgement(2, nott);
			}
			else {
				receiveJudgement(3, nott);
			}
			auto_input[i] = 5;
			//cout << "Line: " << i + 1 << " Frame: " << this->notes[i][line_input[i]]->createFrame << endl;
			this->deleteNote(i, this->line_input[i]);
			this->setLineInput(i);
		}
	}

}

void RoundScene::setTempLineInput()
{
	for (int i = 0; i < LINES; i++) {
		// 첫 입력
		if (auto_input[i] != 0) {
			if (auto_input[i] == 5) {
				this->renderKey[i] = true;
			}
			else if (auto_input[i] == 1) {
				this->renderKey[i] = false;
			}
			auto_input[i]--;

		}
	}
}

void RoundScene::unsetAutoMode()
{
	auto_on = false;
}


void RoundScene::update() {
	if (this->isEnd) {
		BASS_Free();
		this->window->scene = new ResultScene(this->window, gameInfo, NULL, 0);
		free(this->gameInfo);
		free(this->U_Config);
		delete(this);
	}

	if (!pause) {
		int former_combo = this->gameInfo->combo;

		this->addTime();

		// x Auto Mode
		if (!auto_on) {
			this->checkInput();
			this->checkSectionNote();
			this->deleteMissNode();
		}
		// Auto Mode
		else {
			autoMode();
			setTempLineInput();
		}

		// frame 보정
		showTimer();
		timeCheck();
		
		if (frame == START_FRAME) {
			this->playSound();	// 5초 뒤 음악 실행
		}
		if (reinforce > 0) reinforce--;

		//for (auto f : this->fireWork) {
		//	if (f) {
		//		f->update();
		//	}
		//}
		//if (former_combo != this->gameInfo->combo && this->gameInfo->combo > 0 && this->gameInfo->combo % 50 == 0) {
		//	for (int i = 0; i < 10; ++i) {
		//		if (this->fireWork[i]) free(this->fireWork[i]);
		//		this->fireWork[i] = new FireWork(new Vector(getRandRage(0, 127), 0), getRandRage(1.1f, 2.f));
		//	}
		//}

		// Blink timer
		if (blink_on && blink_count >= BLINK_DURATION) {
			blinkOff();
		}
		else if (blink_on) {
			blinkCountUp();
		}

		// LieNote timer
		if (lie_on) {
			lieTimerCheck();
		}

	}
}

void RoundScene::render() {
	//glColor4f(1, 0.8f, 0, 0.5f);
	//drawCircle(20, 20, 3);

	for (int i = 0; i < 10; ++i) {
		if (this->fireWork[i]) {
			this->fireWork[i]->render();
		}
	}
	
	// Blink on -> x Draw
	if (!blink_on || (blink_count / BLINK_DELAY) % 2 == 1) {
		this->renderNotes();
	}

	if (lie_on) {
		this->renderLieNotes();
	}
	
	this->renderGrid();
	this->renderInputEffect();

	this->renderCombo();
	this->renderJudgement();
	this->renderScoreAndInfo();

}

void RoundScene::renderCombo() {
	if (this->gameInfo->combo == 0) {
		return;
	}

	float x = 50;
	float y = 50;

	string content = to_string(this->gameInfo->combo) + " COMBO";

	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(0.04, 0.06, 1);
	glColor4f(1, 0.8f, 0, 0.5f);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x + 0.15f, y, 0);
	glColor4f(0, 0.65f, 1, 0.5f);
	glScalef(0.04, 0.06, 1);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x + 0.3f, y, 0);
	glColor4f(0.19f, 0.65f, 0.32f, 0.5f);
	glScalef(0.04, 0.06, 1);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x + 0.45f, y, 0);
	glColor4f(0.9f, 1, 0.15f, 0.5f);
	glScalef(0.04, 0.06, 1);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
}
void RoundScene::renderJudgement() {
	if (this->gameInfo->recentJudgement == NONE) {
		return;
	}

	float x = 50;
	float y = 36;

	string content = "";
	switch (this->gameInfo->recentJudgement) {
	case PERFECT:
		glColor4f(0.64f, 0.05f, 0.6f, 0.5f);
		content = "PERFECT";
		break;
	case GREAT:
		glColor4f(0.9f, 0.55f, 0.15f, 0.5f);
		content = " GREAT ";
		break;
	case NORMAL:
		glColor4f(0.1f, 0.75f, 0.15f, 0.5f);
		content = " NORMAL";
		break;
	case BAD:
		glColor4f(0.3f, 0.75f, 0.74f, 0.5f);
		content = "  BAD  ";
		break;
	case MISS:
		glColor4f(0.4f, 0.4f, 0.4f, 0.5f);
		content = "  MISS  ";
		break;
	}


	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(0.04, 0.06, 1);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x + 0.15f, y, 0);
	glScalef(0.04, 0.06, 1);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x + 0.3f, y, 0);
	glScalef(0.04, 0.06, 1);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x + 0.45f, y, 0);
	glScalef(0.04, 0.06, 1);
	glLineWidth(5);
	for (auto c : content)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
}
void RoundScene::renderScoreAndInfo() {
	float x = 0;
	float y = 105;

	string content = "Score: " + to_string(this->gameInfo->score);
	glColor4f(1, 1, 1, 1);
	glRasterPos2f(x, y);
	for (auto c : content)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	y = 101;
	content = "Life: " + to_string(int(this->gameInfo->HP));
	glColor4f(1, 1, 1, 1);
	glRasterPos2f(x, y);
	for (auto c : content)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	x = 50;
	y = 2;
	content = "Music: " + this->artist + " - " + this->name;
	glRasterPos2f(x, y);
	x = 0;
	y = 0;
	for (auto c : content)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}
void RoundScene::renderGrid() {
	glLineWidth(1);
	glColor3f(1, 1, 1);

	//glBegin(GL_LINE_LOOP);
	//glVertex2f(x, y);
	//glVertex2f(x + 1, y);
	//glVertex2f(x + 1, y + 1);
	//glVertex2f(x, y + 1);
	//glEnd();

	for (int i = 0; i < LINES + 1; ++i) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(20 + (i * 4), 0);
		glVertex2f(20 + (i * 4), ROWS);
		glEnd();
	}

	glColor3f(1, 1, 1);
	glRectd(20, 5, 36, 6);
}


void RoundScene::renderNotes() {
	if (frame + 120 > 10000) return;
	int input_count = 0;
	for (int line = 0; line < LINES; ++line) {
		for (int scope = 0; scope < this->notes[line].size(); ++scope) {
			if (this->notes[line][scope] == nullptr)
				break;
			//cout << "fps: " << frame << " | ";
			if (this->notes[line][scope]->IsActive(frame) && this->notes[line][scope]->isAlive) {
				// 노트의 색 지정
				switch (line)
				{
				case 0:
					glColor3f(1, 0.8f, 0);
					break;
				case 1:
					glColor3f(0, 0.65f, 1);
					break;
				case 2:
					glColor3f(0.19f, 0.65f, 0.32f);
					break;
				case 3:
					glColor3f(0.9f, 1, 0.15f);
				default:
					break;
				}

				// 아이템 노트 색 지정
				if (this->notes[line][scope]->type == 4)
					glColor3f(0.6f, 1, 0.6f);

				// 가속 노트
				if (this->notes[line][scope]->isAccel) {
					int height = this->notes[line][scope]->GetHeight(frame);
					double accel_dist = ROWS - calcAccelNoteDist(ROWS - height);
					//printf("%d: line, %d: scope, %lf: accel_dist\n", line, scope, accel_dist);

					// 롱노트에 대하여
					if (this->notes[line][scope]->type == 1) {
						int bottom = 0;
						int accel_end_dist = ROWS - calcAccelNoteDist((ROWS - height) - this->notes[line][scope]->getNoteLength());

						// 롱노트가 현재 입력 대기중인 노트이고, 그 노트가 입력중일 때
						if (scope == line_input[line] && section_judgement[line] != -1) {
							bottom = JUDGE_HEIGHT;
						}

						// 일부 롱노트가 화면 아래에 있음
						if (height < 2) {
							glRectd(20.f + ((float)line * 4), bottom, 24.f + ((float)line * 4), accel_end_dist);
						}
						else {
							glRectd(20.f + ((float)line * 4), accel_dist, 24.f + ((float)line * 4), accel_end_dist);
						}
					}
					else {
						glRectd(20.f + ((float)line * 4), accel_dist, 24.f + ((float)line * 4), accel_dist + 1);
					}

				}
				// 감속 노트
				else if (this->notes[line][scope]->isSlow) {
					int height = this->notes[line][scope]->GetHeight(frame);
					double slow_dist = ROWS - calcSlowNoteDist(ROWS - height);
					//printf("%d: line, %d: scope, %lf: accel_dist\n", line, scope, slow_dist);

					// 롱노트에 대하여
					if (this->notes[line][scope]->type == 1) {
						int bottom = 0;
						int slow_end_dist = ROWS - calcSlowNoteDist((ROWS - height) - this->notes[line][scope]->getNoteLength());

						// 롱노트가 현재 입력 대기중인 노트이고, 그 노트가 입력중일 때
						if (scope == line_input[line] && section_judgement[line] != -1) {
							bottom = JUDGE_HEIGHT;
						}

						// 일부 롱노트가 화면 아래에 있음
						if (height < 2) {
							glRectd(20.f + ((float)line * 4), bottom, 24.f + ((float)line * 4), slow_end_dist);
						}
						else {
							glRectd(20.f + ((float)line * 4), slow_dist, 24.f + ((float)line * 4), slow_end_dist);
						}
					}
					else {
						glRectd(20.f + ((float)line * 4), slow_dist, 24.f + ((float)line * 4), slow_dist + 1);
					}
				}
				else {
					// 바닥으로부터 노트(바닥)까지의 거리
					int height = this->notes[line][scope]->GetHeight(frame);
					int noteLength = this->notes[line][scope]->getNoteLength();

					// 롱노트에 대하여
					if (this->notes[line][scope]->type == 1) {
						int bottom = 0;
						// 롱노트가 현재 입력 대기중인 노트이고, 그 노트가 입력중일 때
						if (scope == line_input[line] && section_judgement[line] != -1) {
							bottom = JUDGE_HEIGHT;
						}

						// 일부 롱노트가 화면 아래에 있음
						if (height < 2) {
							glRectd(20.f + ((float)line * 4), bottom, 24.f + ((float)line * 4), height + noteLength);
						}
						else {
							glRectd(20.f + ((float)line * 4), height, 24.f + ((float)line * 4), height + noteLength);
						}
					}
					else {
						glRectd(20.f + ((float)line * 4), height, 24.f + ((float)line * 4), height + noteLength);
					}

					//}
					//cout << frame << " | " << line << ":" << height << "\n";

					if (line == 0 && (0 <= height && height <= 10)) {
						//	cout << line << ":" << height << "\n";
					}
				}
			}
		}
	}
}
void RoundScene::renderInputEffect() {
	for (int i = 0; i < LINES; i++) {
		if (!this->renderKey[i]) continue;
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex2f(20 + (i * 4), 5);
		glColor4f(0, 0, 0, 0);
		glVertex2f(20 + (i * 4), 40.f);
		glColor4f(0, 0, 0, 0);
		glVertex2f(24 + (i * 4), 40.f);
		glColor3f(1, 1, 1);
		glVertex2f(24 + (i * 4), 5);
		glEnd();
	}
}

void RoundScene::addTime() {
	frame += 1;
	if (frame == endFrame) {
		this->isEnd = true;
	}
}

void RoundScene::getNoteDelay(int line, unsigned int i_frame)
{
	int n_frame = this->line_input[line];
	int l_frame = this->lie_input[line];

	// 거짓 노트 생성
	if (lie_notes[line].size() > 0) {

		// 거짓 노트 일 때,
		if (this->notes[line][n_frame]->createFrame > this->lie_notes[line][l_frame]->createFrame) {

			LieNote* lie_nott = (LieNote*)this->lie_notes[line][l_frame];

			// 입력과 프레임간 차이
			float n_delay = lie_nott->GetHeight(i_frame) - JUDGE_HEIGHT;
			int noteType = lie_nott->type;
			int judgeType = 5;

			// 일정 범위 내에 노트가 존재함
			if (n_delay <= MISS_FRAME) {
				receiveJudgement(judgeType, lie_nott);

				this->deleteNote(line, n_frame);
				this->setLieInput(line);
			}

			return;
		}


	}


	// 입력과 노트 프레임 사이의 차이
	Note* nott = this->notes[line][n_frame];

	float n_delay = nott->GetHeight(i_frame) - JUDGE_HEIGHT;
	int noteType = nott->type;
	int judgeType = 5;


	// 일정 범위 내에 노트가 존재함
	if (n_delay <= MISS_FRAME) {

		//노트 판정
		if (n_delay <= PERFECT_FRAME && n_delay >= -(PERFECT_FRAME / 2)) {
			judgeType = 1;
		}
		else if (n_delay <= GREAT_FRAME && n_delay >= -(GREAT_FRAME / 2)) {
			judgeType = 2;
		}
		else if (n_delay <= NORMAL_FRAME && n_delay >= -(NORMAL_FRAME / 2)) {
			judgeType = 3;
		}
		else if (n_delay <= BAD_FRAME && n_delay >= -(BAD_FRAME / 2)) {
			judgeType = 4;
		}
		receiveJudgement(judgeType, nott);

		// 롱노트
		if (noteType == 1) {
			section_judgement[line] = judgeType;
			section_delay[line] = n_delay;
			section_input[line] = 1;

		}
		// 아이템 노트
		else if (noteType == 4) {
			ItemNote* itemNote = (ItemNote*)nott;
			
			// 노트 지움
			this->deleteNote(line, n_frame);
			this->setLineInput(line);

			itemNote->UseItem(this);
		}
		// 이외의 노트
		else {
			// 노트 지움
			this->deleteNote(line, n_frame);
			this->setLineInput(line);
		}
	}
}

/*입력된 노트를 삭제하는 함수. 이후 판정선을 넘어간 노트도 지워야 함*/
void RoundScene::deleteNote(int line, int n_frame)
{
	if (this->notes[line][n_frame] != nullptr) {
		this->notes[line][n_frame]->killNote();
		//printf("%d번 note 삭제\n", n_frame);
	}

}

int RoundScene::getLineInput(int line) {
	return this->line_input[line];
}

void RoundScene::setLineInput(int line) {
	this->line_input[line]++;
}

void RoundScene::deleteMissNode() {
	// 1 -> LINES로 바꿔야 함.
	for (int i = 0; i < LINES; i++) {
		// 입력 못한 노트 제거
		if (this->notes[i][line_input[i]]->IsMissNote(frame)) {
			Note* nott = this->notes[i][line_input[i]];
			receiveJudgement(6, nott);
			//printf("%d Miss Note 제거\n", line_input[i]);
			this->notes[i][line_input[i]]->killNote();
			this->setLineInput(i);
		}
	}
}

///*놓치는 노트들을 Miss 처리하는 함수 - 판정을 다른 곳으로 보내주어야 함.*/
//void Round::deleteMissNote() 
//{
//	if (frame >= 50) {
//		if (this->notes[0][frame - 50]) {
//			printf("miss\n");
//			deleteNote(0, frame - 50);
//		}
//
//	}
//}
