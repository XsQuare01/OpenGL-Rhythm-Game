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
		// 노드 수작업 부분
		// 오류 확인용 여러 케이스
		//this->notes[2].push_back((Note*)new SectionNote(300, 373));
		this->notes[2].push_back((Note*)new ItemNote(300, SWITCHLINE));
		this->notes[2].push_back((Note*)new NormalNote(322));
		this->notes[2].push_back((Note*)new NormalNote(345));
		this->notes[2].push_back((Note*)new NormalNote(373));

		this->notes[3].push_back((Note*)new NormalNote(390));
		this->notes[3].push_back((Note*)new NormalNote(412));
		this->notes[1].push_back((Note*)new NormalNote(435));
		this->notes[1].push_back((Note*)new NormalNote(457));

		//this->notes[2].push_back((Note*)new SectionNote(480, 553));
		this->notes[2].push_back((Note*)new NormalNote(480));
		this->notes[2].push_back((Note*)new NormalNote(502));
		this->notes[2].push_back((Note*)new NormalNote(525));
		this->notes[2].push_back((Note*)new ItemNote(547, SWITCHLINE));


		this->notes[1].push_back((Note*)new NormalNote(570));
		this->notes[1].push_back((Note*)new NormalNote(592));
		this->notes[0].push_back((Note*)new NormalNote(615));
		this->notes[0].push_back((Note*)new NormalNote(637));

		//this->notes[1].push_back((Note*)new SectionNote(660, 733));
		this->notes[1].push_back((Note*)new NormalNote(660));
		this->notes[1].push_back((Note*)new NormalNote(682));
		this->notes[1].push_back((Note*)new NormalNote(705));
		this->notes[1].push_back((Note*)new NormalNote(727));


		this->notes[3].push_back((Note*)new NormalNote(750));
		this->notes[2].push_back((Note*)new NormalNote(795));

		//this->notes[3].push_back((Note*)new SectionNote(840, 913));
		this->notes[3].push_back((Note*)new NormalNote(840));
		this->notes[3].push_back((Note*)new NormalNote(862));
		this->notes[3].push_back((Note*)new NormalNote(885));
		this->notes[3].push_back((Note*)new NormalNote(907));

		this->notes[0].push_back((Note*)new NormalNote(930));
		this->notes[2].push_back((Note*)new NormalNote(936));
		this->notes[0].push_back((Note*)new NormalNote(941));
		this->notes[2].push_back((Note*)new NormalNote(947));
		this->notes[0].push_back((Note*)new NormalNote(953));
		this->notes[2].push_back((Note*)new NormalNote(958));
		this->notes[0].push_back((Note*)new NormalNote(964));
		this->notes[2].push_back((Note*)new NormalNote(969));
		this->notes[1].push_back((Note*)new NormalNote(975));
		this->notes[3].push_back((Note*)new NormalNote(981));
		this->notes[1].push_back((Note*)new NormalNote(986));
		this->notes[3].push_back((Note*)new NormalNote(992));
		this->notes[1].push_back((Note*)new NormalNote(998));
		this->notes[3].push_back((Note*)new NormalNote(1003));
		this->notes[1].push_back((Note*)new NormalNote(1009));
		this->notes[3].push_back((Note*)new NormalNote(1014));

		this->notes[0].push_back((Note*)new NormalNote(1020));
		this->notes[1].push_back((Note*)new NormalNote(1043));
		this->notes[3].push_back((Note*)new NormalNote(1065));

		this->notes[2].push_back((Note*)new NormalNote(1110));
		this->notes[1].push_back((Note*)new NormalNote(1155));

		this->notes[0].push_back((Note*)new NormalNote(1200));
		this->notes[1].push_back((Note*)new NormalNote(1245));

		this->notes[2].push_back((Note*)new NormalNote(1290));

		this->notes[1].push_back((Note*)new NormalNote(1380));
		this->notes[0].push_back((Note*)new NormalNote(1425));

		this->notes[2].push_back((Note*)new NormalNote(1470));
		this->notes[1].push_back((Note*)new NormalNote(1515));

		this->notes[0].push_back((Note*)new NormalNote(1560));
		this->notes[3].push_back((Note*)new NormalNote(1605));

		this->notes[1].push_back((Note*)new NormalNote(1650));
		this->notes[0].push_back((Note*)new NormalNote(1695));
		this->notes[3].push_back((Note*)new NormalNote(1718));

		this->notes[0].push_back((Note*)new NormalNote(1740));
		this->notes[1].push_back((Note*)new NormalNote(1763));
		this->notes[2].push_back((Note*)new NormalNote(1785));
		this->notes[3].push_back((Note*)new NormalNote(1808));

		this->notes[1].push_back((Note*)new NormalNote(1830));
		this->notes[3].push_back((Note*)new NormalNote(1853));
		this->notes[0].push_back((Note*)new NormalNote(1875));
		this->notes[3].push_back((Note*)new NormalNote(1898));

		this->notes[1].push_back((Note*)new NormalNote(1920));
		this->notes[3].push_back((Note*)new NormalNote(1943));
		this->notes[2].push_back((Note*)new NormalNote(1965));
		this->notes[3].push_back((Note*)new NormalNote(1988));

		this->notes[2].push_back((Note*)new NormalNote(2010));
		this->notes[3].push_back((Note*)new NormalNote(2033));
		this->notes[2].push_back((Note*)new NormalNote(2055));
		this->notes[3].push_back((Note*)new NormalNote(2078));

		this->notes[1].push_back((Note*)new NormalNote(2100));
		this->notes[3].push_back((Note*)new NormalNote(2123));
		this->notes[2].push_back((Note*)new NormalNote(2145));
		this->notes[3].push_back((Note*)new NormalNote(2168));

		this->notes[1].push_back((Note*)new NormalNote(2190));
		this->notes[3].push_back((Note*)new NormalNote(2213));
		this->notes[2].push_back((Note*)new NormalNote(2235));
		this->notes[1].push_back((Note*)new NormalNote(2258));

		this->notes[0].push_back((Note*)new NormalNote(2280));
		this->notes[1].push_back((Note*)new NormalNote(2303));
		this->notes[3].push_back((Note*)new NormalNote(2325));

		this->notes[3].push_back((Note*)new NormalNote(2370));
		this->notes[3].push_back((Note*)new NormalNote(2393));
		this->notes[3].push_back((Note*)new NormalNote(2409));
		this->notes[2].push_back((Note*)new NormalNote(2415));
		this->notes[3].push_back((Note*)new NormalNote(2426));
		this->notes[3].push_back((Note*)new NormalNote(2438));
		this->notes[3].push_back((Note*)new NormalNote(2449));

		this->notes[2].push_back((Note*)new NormalNote(2460));
		this->notes[1].push_back((Note*)new NormalNote(2483));
		this->notes[2].push_back((Note*)new NormalNote(2505));
		this->notes[0].push_back((Note*)new NormalNote(2528));

		this->notes[1].push_back((Note*)new NormalNote(2550));
		this->notes[0].push_back((Note*)new NormalNote(2573));
		this->notes[3].push_back((Note*)new NormalNote(2595));
		this->notes[2].push_back((Note*)new NormalNote(2618));

		this->notes[1].push_back((Note*)new NormalNote(2640));
		this->notes[2].push_back((Note*)new NormalNote(2685));
		this->notes[3].push_back((Note*)new NormalNote(2708));

		this->notes[0].push_back((Note*)new NormalNote(2730));
		this->notes[1].push_back((Note*)new NormalNote(2753));
		this->notes[2].push_back((Note*)new NormalNote(2775));
		this->notes[3].push_back((Note*)new NormalNote(2798));

		this->notes[1].push_back((Note*)new NormalNote(2820));
		this->notes[2].push_back((Note*)new NormalNote(2843));
		this->notes[0].push_back((Note*)new NormalNote(2865));
		this->notes[3].push_back((Note*)new NormalNote(2888));

		this->notes[2].push_back((Note*)new NormalNote(2910));
		this->notes[1].push_back((Note*)new NormalNote(2933));
		this->notes[0].push_back((Note*)new NormalNote(2955));
		this->notes[3].push_back((Note*)new NormalNote(2978));

		this->notes[2].push_back((Note*)new NormalNote(3000));
		this->notes[1].push_back((Note*)new NormalNote(3023));
		this->notes[2].push_back((Note*)new NormalNote(3045));
		this->notes[3].push_back((Note*)new NormalNote(3068));

		this->notes[1].push_back((Note*)new NormalNote(3090));
		this->notes[0].push_back((Note*)new NormalNote(3124));
		this->notes[1].push_back((Note*)new NormalNote(3135));
		this->notes[2].push_back((Note*)new NormalNote(3158));
		this->notes[1].push_back((Note*)new NormalNote(3169));

		this->notes[3].push_back((Note*)new NormalNote(3180));
		this->notes[0].push_back((Note*)new NormalNote(3214));
		this->notes[2].push_back((Note*)new NormalNote(3225));
		this->notes[1].push_back((Note*)new NormalNote(3236));
		this->notes[2].push_back((Note*)new NormalNote(3248));
		this->notes[1].push_back((Note*)new NormalNote(3259));

		this->notes[1].push_back((Note*)new NormalNote(3304));
		this->notes[3].push_back((Note*)new NormalNote(3315));
		this->notes[2].push_back((Note*)new NormalNote(3326));
		this->notes[1].push_back((Note*)new NormalNote(3338));
		this->notes[2].push_back((Note*)new NormalNote(3349));

		this->notes[0].push_back((Note*)new NormalNote(3360));
		this->notes[3].push_back((Note*)new NormalNote(3394));
		this->notes[1].push_back((Note*)new NormalNote(3428));
		this->notes[2].push_back((Note*)new NormalNote(3439));

		this->notes[1].push_back((Note*)new NormalNote(3450));
		this->notes[1].push_back((Note*)new NormalNote(3473));
		this->notes[0].push_back((Note*)new NormalNote(3484));
		this->notes[2].push_back((Note*)new NormalNote(3506));
		this->notes[0].push_back((Note*)new NormalNote(3529));

		this->notes[1].push_back((Note*)new NormalNote(3540));
		this->notes[2].push_back((Note*)new NormalNote(3551));
		this->notes[1].push_back((Note*)new NormalNote(3574));
		this->notes[2].push_back((Note*)new NormalNote(3596));
		this->notes[3].push_back((Note*)new NormalNote(3608));
		this->notes[2].push_back((Note*)new NormalNote(3619));

		this->notes[2].push_back((Note*)new NormalNote(3630));
		this->notes[0].push_back((Note*)new NormalNote(3641));
		this->notes[1].push_back((Note*)new NormalNote(3653));
		this->notes[0].push_back((Note*)new NormalNote(3664));
		this->notes[0].push_back((Note*)new NormalNote(3709));

		this->notes[1].push_back((Note*)new NormalNote(3720));
		this->notes[2].push_back((Note*)new NormalNote(3731));
		this->notes[1].push_back((Note*)new NormalNote(3754));
		this->notes[0].push_back((Note*)new NormalNote(3765));
		this->notes[1].push_back((Note*)new NormalNote(3776));
		this->notes[2].push_back((Note*)new NormalNote(3788));
		this->notes[0].push_back((Note*)new NormalNote(3799));

		this->notes[0].push_back((Note*)new NormalNote(3810));
		this->notes[1].push_back((Note*)new NormalNote(3816));
		this->notes[0].push_back((Note*)new NormalNote(3821));
		this->notes[1].push_back((Note*)new NormalNote(3827));
		this->notes[0].push_back((Note*)new NormalNote(3833));
		this->notes[2].push_back((Note*)new NormalNote(3838));
		this->notes[0].push_back((Note*)new NormalNote(3844));
		this->notes[2].push_back((Note*)new NormalNote(3849));
		this->notes[1].push_back((Note*)new NormalNote(3855));
		this->notes[2].push_back((Note*)new NormalNote(3861));
		this->notes[1].push_back((Note*)new NormalNote(3866));
		this->notes[2].push_back((Note*)new NormalNote(3872));
		this->notes[3].push_back((Note*)new NormalNote(3878));
		this->notes[2].push_back((Note*)new NormalNote(3883));
		this->notes[3].push_back((Note*)new NormalNote(3889));
		this->notes[2].push_back((Note*)new NormalNote(3894));

		this->notes[0].push_back((Note*)new NormalNote(3900));
		this->notes[0].push_back((Note*)new NormalNote(3923));
		this->notes[1].push_back((Note*)new NormalNote(3934));
		this->notes[2].push_back((Note*)new NormalNote(3945));
		this->notes[0].push_back((Note*)new NormalNote(3968));
		this->notes[1].push_back((Note*)new NormalNote(3979));

		this->notes[3].push_back((Note*)new NormalNote(3990));
		this->notes[2].push_back((Note*)new NormalNote(4001));
		this->notes[1].push_back((Note*)new NormalNote(4013));
		this->notes[2].push_back((Note*)new NormalNote(4024));
		this->notes[0].push_back((Note*)new NormalNote(4035));
		this->notes[1].push_back((Note*)new NormalNote(4046));
		this->notes[2].push_back((Note*)new NormalNote(4058));
		this->notes[3].push_back((Note*)new NormalNote(4069));

		this->notes[1].push_back((Note*)new NormalNote(4080));
		this->notes[0].push_back((Note*)new NormalNote(4103));
		this->notes[2].push_back((Note*)new NormalNote(4114));
		this->notes[3].push_back((Note*)new NormalNote(4125));
		this->notes[0].push_back((Note*)new NormalNote(4148));
		this->notes[1].push_back((Note*)new NormalNote(4159));

		this->notes[0].push_back((Note*)new NormalNote(4170));
		this->notes[2].push_back((Note*)new NormalNote(4181));
		this->notes[1].push_back((Note*)new NormalNote(4193));
		this->notes[0].push_back((Note*)new NormalNote(4204));
		this->notes[1].push_back((Note*)new NormalNote(4215));
		this->notes[3].push_back((Note*)new NormalNote(4226));
		this->notes[2].push_back((Note*)new NormalNote(4238));
		this->notes[3].push_back((Note*)new NormalNote(4249));

		this->notes[0].push_back((Note*)new NormalNote(4260));
		this->notes[2].push_back((Note*)new NormalNote(4283));
		this->notes[1].push_back((Note*)new NormalNote(4294));
		this->notes[0].push_back((Note*)new NormalNote(4305));
		this->notes[3].push_back((Note*)new NormalNote(4328));
		this->notes[2].push_back((Note*)new NormalNote(4339));

		this->notes[1].push_back((Note*)new NormalNote(4350));
		this->notes[0].push_back((Note*)new NormalNote(4361));
		this->notes[1].push_back((Note*)new NormalNote(4373));
		this->notes[2].push_back((Note*)new NormalNote(4384));
		this->notes[0].push_back((Note*)new NormalNote(4395));
		this->notes[1].push_back((Note*)new NormalNote(4406));
		this->notes[2].push_back((Note*)new NormalNote(4418));
		this->notes[3].push_back((Note*)new NormalNote(4429));

		this->notes[1].push_back((Note*)new NormalNote(4440));
		this->notes[3].push_back((Note*)new NormalNote(4463));
		this->notes[1].push_back((Note*)new NormalNote(4474));
		this->notes[2].push_back((Note*)new NormalNote(4485));
		this->notes[1].push_back((Note*)new NormalNote(4508));
		this->notes[3].push_back((Note*)new NormalNote(4519));

		this->notes[1].push_back((Note*)new NormalNote(4530));
		this->notes[0].push_back((Note*)new NormalNote(4541));
		this->notes[1].push_back((Note*)new NormalNote(4553));
		this->notes[2].push_back((Note*)new NormalNote(4564));
		this->notes[0].push_back((Note*)new NormalNote(4575));
		this->notes[1].push_back((Note*)new NormalNote(4586));
		this->notes[2].push_back((Note*)new NormalNote(4598));
		this->notes[3].push_back((Note*)new NormalNote(4609));

		this->notes[0].push_back((Note*)new NormalNote(4620));
		this->notes[1].push_back((Note*)new NormalNote(4643));
		this->notes[2].push_back((Note*)new NormalNote(4654));
		this->notes[3].push_back((Note*)new NormalNote(4665));
		this->notes[1].push_back((Note*)new NormalNote(4688));
		this->notes[2].push_back((Note*)new NormalNote(4699));

		this->notes[3].push_back((Note*)new NormalNote(4710));
		this->notes[2].push_back((Note*)new NormalNote(4721));
		this->notes[1].push_back((Note*)new NormalNote(4733));
		this->notes[2].push_back((Note*)new NormalNote(4744));
		this->notes[0].push_back((Note*)new NormalNote(4755));
		this->notes[1].push_back((Note*)new NormalNote(4766));
		this->notes[2].push_back((Note*)new NormalNote(4778));
		this->notes[3].push_back((Note*)new NormalNote(4789));

		this->notes[1].push_back((Note*)new NormalNote(4800));
		this->notes[0].push_back((Note*)new NormalNote(4823));
		this->notes[1].push_back((Note*)new NormalNote(4834));
		this->notes[2].push_back((Note*)new NormalNote(4845));
		this->notes[0].push_back((Note*)new NormalNote(4868));
		this->notes[1].push_back((Note*)new NormalNote(4879));

		this->notes[1].push_back((Note*)new NormalNote(4890));
		this->notes[3].push_back((Note*)new NormalNote(4901));
		this->notes[2].push_back((Note*)new NormalNote(4913));
		this->notes[1].push_back((Note*)new NormalNote(4924));
		this->notes[2].push_back((Note*)new NormalNote(4935));
		this->notes[3].push_back((Note*)new NormalNote(4946));
		this->notes[1].push_back((Note*)new NormalNote(4958));
		this->notes[3].push_back((Note*)new NormalNote(4969));

		this->notes[1].push_back((Note*)new NormalNote(4980));
		this->notes[2].push_back((Note*)new NormalNote(5003));
		this->notes[1].push_back((Note*)new NormalNote(5014));
		this->notes[0].push_back((Note*)new NormalNote(5025));
		this->notes[1].push_back((Note*)new NormalNote(5048));
		this->notes[0].push_back((Note*)new NormalNote(5059));

		this->notes[2].push_back((Note*)new NormalNote(5070));
		this->notes[1].push_back((Note*)new NormalNote(5081));
		this->notes[0].push_back((Note*)new NormalNote(5093));
		this->notes[1].push_back((Note*)new NormalNote(5104));
		this->notes[0].push_back((Note*)new NormalNote(5115));
		this->notes[1].push_back((Note*)new NormalNote(5126));
		this->notes[2].push_back((Note*)new NormalNote(5138));
		this->notes[3].push_back((Note*)new NormalNote(5149));

		this->notes[0].push_back((Note*)new NormalNote(5160));
		this->notes[2].push_back((Note*)new NormalNote(5183));
		this->notes[0].push_back((Note*)new NormalNote(5194));
		this->notes[1].push_back((Note*)new NormalNote(5205));
		this->notes[0].push_back((Note*)new NormalNote(5228));
		this->notes[1].push_back((Note*)new NormalNote(5239));

		this->notes[2].push_back((Note*)new NormalNote(5250));
		this->notes[3].push_back((Note*)new NormalNote(5256));
		this->notes[2].push_back((Note*)new NormalNote(5261));
		this->notes[3].push_back((Note*)new NormalNote(5267));
		this->notes[2].push_back((Note*)new NormalNote(5273));
		this->notes[3].push_back((Note*)new NormalNote(5278));
		this->notes[2].push_back((Note*)new NormalNote(5284));
		this->notes[3].push_back((Note*)new NormalNote(5289));
		this->notes[0].push_back((Note*)new NormalNote(5295));
		this->notes[1].push_back((Note*)new NormalNote(5301));
		this->notes[0].push_back((Note*)new NormalNote(5306));
		this->notes[1].push_back((Note*)new NormalNote(5312));
		this->notes[0].push_back((Note*)new NormalNote(5318));
		this->notes[2].push_back((Note*)new NormalNote(5323));
		this->notes[0].push_back((Note*)new NormalNote(5329));
		this->notes[2].push_back((Note*)new NormalNote(5334));

		this->notes[1].push_back((Note*)new NormalNote(5340));
		this->notes[2].push_back((Note*)new NormalNote(5385));
		this->notes[0].push_back((Note*)new NormalNote(5396));
		this->notes[1].push_back((Note*)new NormalNote(5408));

		this->notes[2].push_back((Note*)new NormalNote(5430));
		this->notes[3].push_back((Note*)new NormalNote(5453));
		this->notes[2].push_back((Note*)new NormalNote(5475));
		this->notes[1].push_back((Note*)new NormalNote(5498));

		this->notes[0].push_back((Note*)new NormalNote(5520));
		this->notes[1].push_back((Note*)new NormalNote(5531));
		this->notes[1].push_back((Note*)new NormalNote(5554));
		this->notes[2].push_back((Note*)new NormalNote(5565));
		this->notes[0].push_back((Note*)new NormalNote(5576));
		this->notes[3].push_back((Note*)new NormalNote(5588));
		this->notes[2].push_back((Note*)new NormalNote(5599));

		this->notes[1].push_back((Note*)new NormalNote(5610));
		this->notes[2].push_back((Note*)new NormalNote(5633));
		this->notes[1].push_back((Note*)new NormalNote(5655));
		this->notes[0].push_back((Note*)new NormalNote(5678));

		this->notes[1].push_back((Note*)new SectionNote(5700, 5728));
		this->notes[0].push_back((Note*)new NormalNote(5745));
		this->notes[1].push_back((Note*)new NormalNote(5756));
		this->notes[2].push_back((Note*)new NormalNote(5768));
		this->notes[3].push_back((Note*)new NormalNote(5779));

		this->notes[3].push_back((Note*)new NormalNote(5801));
		this->notes[2].push_back((Note*)new NormalNote(5813));
		this->notes[3].push_back((Note*)new NormalNote(5824));
		this->notes[1].push_back((Note*)new NormalNote(5835));
		this->notes[3].push_back((Note*)new NormalNote(5846));
		this->notes[2].push_back((Note*)new NormalNote(5858));
		this->notes[3].push_back((Note*)new NormalNote(5869));

		this->notes[1].push_back((Note*)new NormalNote(5880));
		this->notes[3].push_back((Note*)new NormalNote(5891));
		this->notes[2].push_back((Note*)new NormalNote(5903));
		this->notes[3].push_back((Note*)new NormalNote(5914));
		this->notes[1].push_back((Note*)new NormalNote(5925));
		this->notes[3].push_back((Note*)new NormalNote(5936));
		this->notes[2].push_back((Note*)new NormalNote(5948));
		this->notes[3].push_back((Note*)new NormalNote(5959));

		this->notes[2].push_back((Note*)new NormalNote(5970));
		this->notes[1].push_back((Note*)new NormalNote(5981));
		this->notes[0].push_back((Note*)new NormalNote(5993));
		this->notes[2].push_back((Note*)new NormalNote(6004));
		this->notes[3].push_back((Note*)new NormalNote(6026));
		this->notes[2].push_back((Note*)new NormalNote(6038));
		this->notes[3].push_back((Note*)new NormalNote(6049));

		this->notes[2].push_back((Note*)new NormalNote(6060));
		this->notes[1].push_back((Note*)new NormalNote(6071));
		this->notes[0].push_back((Note*)new NormalNote(6083));
		this->notes[0].push_back((Note*)new NormalNote(6094));
		this->notes[1].push_back((Note*)new NormalNote(6105));
		this->notes[3].push_back((Note*)new NormalNote(6128));

		this->notes[2].push_back((Note*)new NormalNote(6150));
		this->notes[3].push_back((Note*)new NormalNote(6173));
		this->notes[1].push_back((Note*)new NormalNote(6195));
		this->notes[0].push_back((Note*)new NormalNote(6218));

		this->notes[1].push_back((Note*)new SectionNote(6240, 6268));
		this->notes[0].push_back((Note*)new NormalNote(6285));
		this->notes[0].push_back((Note*)new NormalNote(6296));
		this->notes[1].push_back((Note*)new NormalNote(6308));

		this->notes[2].push_back((Note*)new NormalNote(6330));
		this->notes[3].push_back((Note*)new NormalNote(6353));
		this->notes[2].push_back((Note*)new NormalNote(6375));
		this->notes[1].push_back((Note*)new NormalNote(6398));

		this->notes[2].push_back((Note*)new NormalNote(6420));
		this->notes[0].push_back((Note*)new NormalNote(6431));
		this->notes[1].push_back((Note*)new NormalNote(6454));
		this->notes[0].push_back((Note*)new NormalNote(6465));
		this->notes[1].push_back((Note*)new NormalNote(6476));
		this->notes[2].push_back((Note*)new NormalNote(6488));
		this->notes[3].push_back((Note*)new NormalNote(6499));

		this->notes[2].push_back((Note*)new NormalNote(6521));
		this->notes[1].push_back((Note*)new NormalNote(6533));
		this->notes[2].push_back((Note*)new NormalNote(6544));
		this->notes[0].push_back((Note*)new NormalNote(6555));
		this->notes[2].push_back((Note*)new NormalNote(6566));
		this->notes[1].push_back((Note*)new NormalNote(6578));
		this->notes[2].push_back((Note*)new NormalNote(6589));

		this->notes[0].push_back((Note*)new NormalNote(6600));
		this->notes[3].push_back((Note*)new NormalNote(6611));
		this->notes[2].push_back((Note*)new NormalNote(6623));
		this->notes[3].push_back((Note*)new NormalNote(6634));
		this->notes[1].push_back((Note*)new NormalNote(6645));
		this->notes[3].push_back((Note*)new NormalNote(6656));
		this->notes[2].push_back((Note*)new NormalNote(6668));
		this->notes[3].push_back((Note*)new NormalNote(6679));

		this->notes[1].push_back((Note*)new NormalNote(6690));
		this->notes[2].push_back((Note*)new NormalNote(6696));
		this->notes[1].push_back((Note*)new NormalNote(6701));
		this->notes[2].push_back((Note*)new NormalNote(6707));
		this->notes[0].push_back((Note*)new NormalNote(6713));
		this->notes[2].push_back((Note*)new NormalNote(6718));
		this->notes[0].push_back((Note*)new NormalNote(6724));
		this->notes[2].push_back((Note*)new NormalNote(6729));
		this->notes[2].push_back((Note*)new NormalNote(6735));
		this->notes[3].push_back((Note*)new NormalNote(6741));
		this->notes[2].push_back((Note*)new NormalNote(6746));
		this->notes[3].push_back((Note*)new NormalNote(6752));
		this->notes[2].push_back((Note*)new NormalNote(6758));
		this->notes[1].push_back((Note*)new NormalNote(6763));
		this->notes[2].push_back((Note*)new NormalNote(6769));
		this->notes[1].push_back((Note*)new NormalNote(6774));

		this->notes[0].push_back((Note*)new SectionNote(6780, 6870));

		this->notes[0].push_back((Note*)new NormalNote(INF));
		this->notes[1].push_back((Note*)new NormalNote(INF));
		this->notes[2].push_back((Note*)new NormalNote(INF));
		this->notes[3].push_back((Note*)new NormalNote(INF));
		break;
	case REVOLUTIONARY:
		this->notes[0].push_back((Note*)new NormalNote(302));
		this->notes[0].push_back((Note*)new NormalNote(326));
		this->notes[0].push_back((Note*)new NormalNote(350));
		this->notes[0].push_back((Note*)new NormalNote(374));
		this->notes[0].push_back((Note*)new NormalNote(398));
		this->notes[0].push_back((Note*)new NormalNote(422));
		this->notes[0].push_back((Note*)new NormalNote(446));
		this->notes[2].push_back((Note*)new NormalNote(470));
		this->notes[0].push_back((Note*)new NormalNote(488));
		this->notes[1].push_back((Note*)new NormalNote(494));
		this->notes[1].push_back((Note*)new NormalNote(518));
		this->notes[1].push_back((Note*)new NormalNote(542));
		this->notes[1].push_back((Note*)new NormalNote(566));
		this->notes[1].push_back((Note*)new NormalNote(590));
		this->notes[1].push_back((Note*)new NormalNote(614));
		this->notes[1].push_back((Note*)new NormalNote(638));
		this->notes[2].push_back((Note*)new NormalNote(662));
		this->notes[0].push_back((Note*)new NormalNote(680));
		this->notes[2].push_back((Note*)new ItemNote(686, SWITCHLINE));
		this->notes[3].push_back((Note*)new NormalNote(698));
		this->notes[2].push_back((Note*)new NormalNote(704));
		this->notes[1].push_back((Note*)new NormalNote(710));
		this->notes[0].push_back((Note*)new NormalNote(716));
		this->notes[2].push_back((Note*)new NormalNote(722));
		this->notes[1].push_back((Note*)new NormalNote(728));
		this->notes[0].push_back((Note*)new NormalNote(734));
		this->notes[3].push_back((Note*)new NormalNote(740));
		this->notes[1].push_back((Note*)new NormalNote(746));
		this->notes[0].push_back((Note*)new NormalNote(752));
		this->notes[3].push_back((Note*)new NormalNote(758));
		this->notes[2].push_back((Note*)new NormalNote(764));
		this->notes[0].push_back((Note*)new NormalNote(770));
		this->notes[3].push_back((Note*)new NormalNote(776));
		this->notes[2].push_back((Note*)new NormalNote(782));
		this->notes[1].push_back((Note*)new NormalNote(788));
		this->notes[3].push_back((Note*)new NormalNote(794));
		this->notes[2].push_back((Note*)new NormalNote(800));
		this->notes[1].push_back((Note*)new NormalNote(806));
		this->notes[0].push_back((Note*)new NormalNote(812));
		this->notes[2].push_back((Note*)new NormalNote(818));
		this->notes[1].push_back((Note*)new NormalNote(824));
		this->notes[0].push_back((Note*)new NormalNote(830));
		this->notes[3].push_back((Note*)new NormalNote(836));
		this->notes[1].push_back((Note*)new NormalNote(842));
		this->notes[0].push_back((Note*)new NormalNote(848));
		this->notes[3].push_back((Note*)new ItemNote(854, SWITCHLINE));
		this->notes[2].push_back((Note*)new NormalNote(860));
		this->notes[0].push_back((Note*)new NormalNote(866));
		this->notes[3].push_back((Note*)new NormalNote(872));
		this->notes[2].push_back((Note*)new NormalNote(878));
		this->notes[1].push_back((Note*)new NormalNote(884));
		this->notes[1].push_back((Note*)new NormalNote(890));
		this->notes[0].push_back((Note*)new NormalNote(896));
		this->notes[3].push_back((Note*)new NormalNote(902));
		this->notes[2].push_back((Note*)new NormalNote(908));
		this->notes[2].push_back((Note*)new NormalNote(914));
		this->notes[1].push_back((Note*)new NormalNote(920));
		this->notes[0].push_back((Note*)new NormalNote(926));
		this->notes[3].push_back((Note*)new NormalNote(932));
		this->notes[3].push_back((Note*)new NormalNote(938));
		this->notes[2].push_back((Note*)new NormalNote(944));
		this->notes[1].push_back((Note*)new NormalNote(950));
		this->notes[0].push_back((Note*)new NormalNote(956));
		this->notes[3].push_back((Note*)new NormalNote(962));
		this->notes[2].push_back((Note*)new NormalNote(968));
		this->notes[1].push_back((Note*)new NormalNote(974));
		this->notes[0].push_back((Note*)new NormalNote(980));
		this->notes[3].push_back((Note*)new NormalNote(986));
		this->notes[2].push_back((Note*)new NormalNote(992));
		this->notes[1].push_back((Note*)new NormalNote(998));
		this->notes[0].push_back((Note*)new NormalNote(1004));
		this->notes[3].push_back((Note*)new NormalNote(1010));
		this->notes[2].push_back((Note*)new NormalNote(1016));
		this->notes[1].push_back((Note*)new NormalNote(1022));
		this->notes[0].push_back((Note*)new NormalNote(1028));
		this->notes[3].push_back((Note*)new NormalNote(1034));
		this->notes[2].push_back((Note*)new NormalNote(1040));
		this->notes[1].push_back((Note*)new NormalNote(1046));
		this->notes[0].push_back((Note*)new NormalNote(1052));
		this->notes[2].push_back((Note*)new NormalNote(1058));
		this->notes[1].push_back((Note*)new NormalNote(1064));
		this->notes[0].push_back((Note*)new NormalNote(1070));
		this->notes[0].push_back((Note*)new NormalNote(1094));
		this->notes[0].push_back((Note*)new NormalNote(1118));
		this->notes[0].push_back((Note*)new NormalNote(1142));
		this->notes[2].push_back((Note*)new NormalNote(1166));
		this->notes[2].push_back((Note*)new NormalNote(1190));
		this->notes[2].push_back((Note*)new NormalNote(1214));
		this->notes[0].push_back((Note*)new NormalNote(1232));
		this->notes[1].push_back((Note*)new NormalNote(1238));
		this->notes[3].push_back((Note*)new NormalNote(1256));
		this->notes[3].push_back((Note*)new NormalNote(1262));
		this->notes[2].push_back((Note*)new NormalNote(1328));
		this->notes[2].push_back((Note*)new NormalNote(1334));
		this->notes[2].push_back((Note*)new NormalNote(1352));
		this->notes[3].push_back((Note*)new NormalNote(1358));
		this->notes[2].push_back((Note*)new NormalNote(1406));
		this->notes[0].push_back((Note*)new NormalNote(1424));
		this->notes[1].push_back((Note*)new NormalNote(1430));
		this->notes[2].push_back((Note*)new NormalNote(1448));
		this->notes[2].push_back((Note*)new NormalNote(1454));
		this->notes[1].push_back((Note*)new NormalNote(1520));
		this->notes[1].push_back((Note*)new NormalNote(1526));
		this->notes[1].push_back((Note*)new NormalNote(1544));
		this->notes[3].push_back((Note*)new NormalNote(1550));
		this->notes[2].push_back((Note*)new NormalNote(1646));
		this->notes[1].push_back((Note*)new NormalNote(1670));
		this->notes[0].push_back((Note*)new NormalNote(1712));
		this->notes[1].push_back((Note*)new NormalNote(1718));
		this->notes[0].push_back((Note*)new NormalNote(1736));
		this->notes[2].push_back((Note*)new NormalNote(1742));
		this->notes[3].push_back((Note*)new NormalNote(1754));
		this->notes[2].push_back((Note*)new NormalNote(1766));
		this->notes[2].push_back((Note*)new NormalNote(1808));
		this->notes[3].push_back((Note*)new NormalNote(1814));
		this->notes[1].push_back((Note*)new NormalNote(1832));
		this->notes[2].push_back((Note*)new NormalNote(1838));
		this->notes[3].push_back((Note*)new NormalNote(1928));
		this->notes[3].push_back((Note*)new NormalNote(1934));
		this->notes[0].push_back((Note*)new NormalNote(1958));
		this->notes[0].push_back((Note*)new NormalNote(2030));
		this->notes[1].push_back((Note*)new NormalNote(2036));
		this->notes[2].push_back((Note*)new NormalNote(2042));
		this->notes[3].push_back((Note*)new NormalNote(2048));
		this->notes[2].push_back((Note*)new NormalNote(2054));
		this->notes[1].push_back((Note*)new NormalNote(2060));
		this->notes[0].push_back((Note*)new NormalNote(2066));
		this->notes[1].push_back((Note*)new NormalNote(2072));
		this->notes[2].push_back((Note*)new NormalNote(2078));
		this->notes[3].push_back((Note*)new NormalNote(2084));
		this->notes[2].push_back((Note*)new NormalNote(2090));
		this->notes[1].push_back((Note*)new NormalNote(2096));
		this->notes[0].push_back((Note*)new NormalNote(2102));
		this->notes[1].push_back((Note*)new NormalNote(2108));
		this->notes[2].push_back((Note*)new NormalNote(2114));
		this->notes[1].push_back((Note*)new NormalNote(2120));
		this->notes[0].push_back((Note*)new NormalNote(2126));
		this->notes[1].push_back((Note*)new NormalNote(2132));
		this->notes[2].push_back((Note*)new NormalNote(2138));
		this->notes[3].push_back((Note*)new NormalNote(2144));
		this->notes[2].push_back((Note*)new NormalNote(2150));
		this->notes[3].push_back((Note*)new NormalNote(2156));
		this->notes[2].push_back((Note*)new NormalNote(2162));
		this->notes[1].push_back((Note*)new NormalNote(2168));
		this->notes[0].push_back((Note*)new NormalNote(2174));
		this->notes[1].push_back((Note*)new NormalNote(2180));
		this->notes[2].push_back((Note*)new NormalNote(2186));
		this->notes[3].push_back((Note*)new NormalNote(2192));
		this->notes[2].push_back((Note*)new NormalNote(2198));
		this->notes[3].push_back((Note*)new NormalNote(2204));
		this->notes[2].push_back((Note*)new NormalNote(2210));
		this->notes[1].push_back((Note*)new NormalNote(2216));
		this->notes[0].push_back((Note*)new NormalNote(2222));
		this->notes[1].push_back((Note*)new NormalNote(2228));
		this->notes[2].push_back((Note*)new NormalNote(2234));
		this->notes[3].push_back((Note*)new NormalNote(2240));
		this->notes[2].push_back((Note*)new NormalNote(2246));
		this->notes[1].push_back((Note*)new NormalNote(2252));
		this->notes[0].push_back((Note*)new NormalNote(2258));
		this->notes[1].push_back((Note*)new NormalNote(2264));
		this->notes[2].push_back((Note*)new NormalNote(2270));
		this->notes[3].push_back((Note*)new NormalNote(2276));
		this->notes[2].push_back((Note*)new NormalNote(2282));
		this->notes[1].push_back((Note*)new NormalNote(2288));
		this->notes[0].push_back((Note*)new NormalNote(2294));
		this->notes[1].push_back((Note*)new NormalNote(2300));
		this->notes[2].push_back((Note*)new NormalNote(2306));
		this->notes[1].push_back((Note*)new NormalNote(2312));
		this->notes[0].push_back((Note*)new NormalNote(2318));
		this->notes[1].push_back((Note*)new NormalNote(2324));
		this->notes[2].push_back((Note*)new NormalNote(2330));
		this->notes[3].push_back((Note*)new NormalNote(2336));
		this->notes[2].push_back((Note*)new NormalNote(2342));
		this->notes[3].push_back((Note*)new NormalNote(2348));
		this->notes[2].push_back((Note*)new NormalNote(2354));
		this->notes[1].push_back((Note*)new NormalNote(2360));
		this->notes[0].push_back((Note*)new NormalNote(2366));
		this->notes[1].push_back((Note*)new NormalNote(2372));
		this->notes[2].push_back((Note*)new NormalNote(2378));
		this->notes[3].push_back((Note*)new NormalNote(2384));
		this->notes[2].push_back((Note*)new NormalNote(2390));
		this->notes[3].push_back((Note*)new NormalNote(2396));
		this->notes[2].push_back((Note*)new NormalNote(2402));
		this->notes[1].push_back((Note*)new NormalNote(2408));
		this->notes[0].push_back((Note*)new NormalNote(2414));
		this->notes[1].push_back((Note*)new NormalNote(2420));
		this->notes[2].push_back((Note*)new NormalNote(2426));
		this->notes[3].push_back((Note*)new NormalNote(2432));
		this->notes[2].push_back((Note*)new NormalNote(2438));
		this->notes[1].push_back((Note*)new NormalNote(2444));
		this->notes[0].push_back((Note*)new NormalNote(2450));
		this->notes[1].push_back((Note*)new NormalNote(2456));
		this->notes[2].push_back((Note*)new NormalNote(2462));
		this->notes[3].push_back((Note*)new NormalNote(2468));
		this->notes[2].push_back((Note*)new NormalNote(2474));
		this->notes[1].push_back((Note*)new NormalNote(2480));
		this->notes[0].push_back((Note*)new NormalNote(2486));
		this->notes[1].push_back((Note*)new NormalNote(2492));
		this->notes[2].push_back((Note*)new NormalNote(2498));
		this->notes[3].push_back((Note*)new NormalNote(2504));
		this->notes[1].push_back((Note*)new NormalNote(2510));
		this->notes[2].push_back((Note*)new NormalNote(2516));
		this->notes[3].push_back((Note*)new NormalNote(2522));
		this->notes[2].push_back((Note*)new NormalNote(2528));
		this->notes[3].push_back((Note*)new NormalNote(2534));
		this->notes[2].push_back((Note*)new NormalNote(2540));
		this->notes[1].push_back((Note*)new NormalNote(2546));
		this->notes[0].push_back((Note*)new NormalNote(2552));
		this->notes[1].push_back((Note*)new NormalNote(2558));
		this->notes[2].push_back((Note*)new NormalNote(2564));
		this->notes[3].push_back((Note*)new NormalNote(2570));
		this->notes[2].push_back((Note*)new NormalNote(2576));
		this->notes[1].push_back((Note*)new NormalNote(2582));
		this->notes[2].push_back((Note*)new NormalNote(2588));
		this->notes[3].push_back((Note*)new NormalNote(2594));
		this->notes[2].push_back((Note*)new NormalNote(2600));
		this->notes[0].push_back((Note*)new NormalNote(2606));
		this->notes[0].push_back((Note*)new NormalNote(2642));
		this->notes[1].push_back((Note*)new NormalNote(2666));
		this->notes[1].push_back((Note*)new NormalNote(2690));
		this->notes[2].push_back((Note*)new NormalNote(2714));
		this->notes[0].push_back((Note*)new NormalNote(2738));
		this->notes[1].push_back((Note*)new NormalNote(2762));
		this->notes[2].push_back((Note*)new NormalNote(2774));
		this->notes[3].push_back((Note*)new NormalNote(2786));
		this->notes[3].push_back((Note*)new NormalNote(2798));
		this->notes[1].push_back((Note*)new NormalNote(2846));
		this->notes[1].push_back((Note*)new NormalNote(2870));
		this->notes[3].push_back((Note*)new NormalNote(2888));
		this->notes[0].push_back((Note*)new NormalNote(2894));
		this->notes[0].push_back((Note*)new NormalNote(2990));
		this->notes[0].push_back((Note*)new NormalNote(3002));
		this->notes[1].push_back((Note*)new NormalNote(3008));
		this->notes[2].push_back((Note*)new NormalNote(3014));
		this->notes[3].push_back((Note*)new NormalNote(3020));
		this->notes[1].push_back((Note*)new NormalNote(3026));
		this->notes[2].push_back((Note*)new NormalNote(3032));
		this->notes[3].push_back((Note*)new NormalNote(3038));
		this->notes[2].push_back((Note*)new NormalNote(3044));
		this->notes[3].push_back((Note*)new NormalNote(3050));
		this->notes[0].push_back((Note*)new NormalNote(3056));
		this->notes[1].push_back((Note*)new NormalNote(3062));
		this->notes[2].push_back((Note*)new NormalNote(3068));
		this->notes[2].push_back((Note*)new NormalNote(3074));
		this->notes[3].push_back((Note*)new NormalNote(3080));
		this->notes[0].push_back((Note*)new NormalNote(3086));
		this->notes[3].push_back((Note*)new NormalNote(3092));
		this->notes[0].push_back((Note*)new NormalNote(3098));
		this->notes[1].push_back((Note*)new NormalNote(3104));
		this->notes[2].push_back((Note*)new NormalNote(3110));
		this->notes[3].push_back((Note*)new NormalNote(3116));
		this->notes[1].push_back((Note*)new NormalNote(3122));
		this->notes[2].push_back((Note*)new NormalNote(3128));
		this->notes[3].push_back((Note*)new NormalNote(3134));
		this->notes[0].push_back((Note*)new NormalNote(3140));
		this->notes[2].push_back((Note*)new NormalNote(3146));
		this->notes[3].push_back((Note*)new NormalNote(3152));
		this->notes[0].push_back((Note*)new NormalNote(3158));
		this->notes[1].push_back((Note*)new NormalNote(3164));
		this->notes[2].push_back((Note*)new NormalNote(3170));
		this->notes[3].push_back((Note*)new NormalNote(3176));
		this->notes[0].push_back((Note*)new NormalNote(3182));
		this->notes[1].push_back((Note*)new NormalNote(3194));
		this->notes[2].push_back((Note*)new NormalNote(3200));
		this->notes[3].push_back((Note*)new NormalNote(3206));
		this->notes[0].push_back((Note*)new NormalNote(3212));
		this->notes[2].push_back((Note*)new NormalNote(3218));
		this->notes[3].push_back((Note*)new NormalNote(3224));
		this->notes[0].push_back((Note*)new NormalNote(3230));
		this->notes[1].push_back((Note*)new NormalNote(3236));
		this->notes[3].push_back((Note*)new NormalNote(3242));
		this->notes[0].push_back((Note*)new NormalNote(3248));
		this->notes[1].push_back((Note*)new NormalNote(3254));
		this->notes[2].push_back((Note*)new NormalNote(3260));
		this->notes[0].push_back((Note*)new NormalNote(3266));
		this->notes[3].push_back((Note*)new NormalNote(3272));
		this->notes[2].push_back((Note*)new NormalNote(3278));
		this->notes[3].push_back((Note*)new NormalNote(3284));
		this->notes[0].push_back((Note*)new NormalNote(3290));
		this->notes[1].push_back((Note*)new NormalNote(3296));
		this->notes[2].push_back((Note*)new NormalNote(3302));
		this->notes[3].push_back((Note*)new NormalNote(3308));
		this->notes[1].push_back((Note*)new NormalNote(3314));
		this->notes[2].push_back((Note*)new NormalNote(3320));
		this->notes[3].push_back((Note*)new NormalNote(3326));
		this->notes[0].push_back((Note*)new NormalNote(3332));
		this->notes[2].push_back((Note*)new NormalNote(3338));
		this->notes[3].push_back((Note*)new NormalNote(3344));
		this->notes[0].push_back((Note*)new NormalNote(3350));
		this->notes[1].push_back((Note*)new NormalNote(3356));
		this->notes[2].push_back((Note*)new NormalNote(3362));
		this->notes[3].push_back((Note*)new NormalNote(3368));
		this->notes[0].push_back((Note*)new NormalNote(3374));
		this->notes[3].push_back((Note*)new NormalNote(3380));
		this->notes[1].push_back((Note*)new NormalNote(3386));
		this->notes[2].push_back((Note*)new NormalNote(3392));
		this->notes[3].push_back((Note*)new NormalNote(3398));
		this->notes[2].push_back((Note*)new NormalNote(3404));
		this->notes[1].push_back((Note*)new NormalNote(3410));
		this->notes[0].push_back((Note*)new NormalNote(3416));
		this->notes[1].push_back((Note*)new NormalNote(3422));
		this->notes[2].push_back((Note*)new NormalNote(3428));
		this->notes[3].push_back((Note*)new NormalNote(3434));
		this->notes[0].push_back((Note*)new NormalNote(3440));
		this->notes[1].push_back((Note*)new NormalNote(3446));
		this->notes[2].push_back((Note*)new NormalNote(3452));
		this->notes[1].push_back((Note*)new NormalNote(3458));
		this->notes[3].push_back((Note*)new NormalNote(3464));
		this->notes[0].push_back((Note*)new NormalNote(3470));
		this->notes[3].push_back((Note*)new NormalNote(3476));
		this->notes[1].push_back((Note*)new NormalNote(3482));
		this->notes[2].push_back((Note*)new NormalNote(3488));
		this->notes[3].push_back((Note*)new NormalNote(3494));
		this->notes[2].push_back((Note*)new NormalNote(3500));
		this->notes[1].push_back((Note*)new NormalNote(3506));
		this->notes[0].push_back((Note*)new NormalNote(3512));
		this->notes[1].push_back((Note*)new NormalNote(3518));
		this->notes[2].push_back((Note*)new NormalNote(3524));
		this->notes[3].push_back((Note*)new NormalNote(3530));
		this->notes[0].push_back((Note*)new NormalNote(3536));
		this->notes[1].push_back((Note*)new NormalNote(3542));
		this->notes[2].push_back((Note*)new NormalNote(3548));
		this->notes[1].push_back((Note*)new NormalNote(3554));
		this->notes[3].push_back((Note*)new NormalNote(3560));
		this->notes[0].push_back((Note*)new NormalNote(3566));
		this->notes[3].push_back((Note*)new NormalNote(3572));
		this->notes[1].push_back((Note*)new NormalNote(3578));
		this->notes[2].push_back((Note*)new NormalNote(3584));
		this->notes[3].push_back((Note*)new NormalNote(3590));
		this->notes[2].push_back((Note*)new NormalNote(3596));
		this->notes[1].push_back((Note*)new NormalNote(3602));
		this->notes[0].push_back((Note*)new NormalNote(3608));
		this->notes[3].push_back((Note*)new NormalNote(3614));
		this->notes[2].push_back((Note*)new NormalNote(3620));
		this->notes[1].push_back((Note*)new NormalNote(3626));
		this->notes[0].push_back((Note*)new NormalNote(3632));
		this->notes[1].push_back((Note*)new NormalNote(3638));
		this->notes[2].push_back((Note*)new NormalNote(3644));
		this->notes[3].push_back((Note*)new NormalNote(3650));
		this->notes[2].push_back((Note*)new NormalNote(3656));
		this->notes[0].push_back((Note*)new NormalNote(3662));
		this->notes[1].push_back((Note*)new NormalNote(3668));
		this->notes[2].push_back((Note*)new NormalNote(3674));
		this->notes[1].push_back((Note*)new NormalNote(3680));
		this->notes[3].push_back((Note*)new NormalNote(3686));
		this->notes[2].push_back((Note*)new NormalNote(3692));
		this->notes[1].push_back((Note*)new NormalNote(3698));
		this->notes[0].push_back((Note*)new NormalNote(3704));
		this->notes[1].push_back((Note*)new NormalNote(3710));
		this->notes[3].push_back((Note*)new NormalNote(3716));
		this->notes[2].push_back((Note*)new NormalNote(3722));
		this->notes[1].push_back((Note*)new NormalNote(3728));
		this->notes[3].push_back((Note*)new NormalNote(3734));
		this->notes[2].push_back((Note*)new NormalNote(3740));
		this->notes[1].push_back((Note*)new NormalNote(3746));
		this->notes[0].push_back((Note*)new NormalNote(3752));
		this->notes[3].push_back((Note*)new NormalNote(3758));
		this->notes[2].push_back((Note*)new NormalNote(3806));
		this->notes[2].push_back((Note*)new NormalNote(3830));
		this->notes[1].push_back((Note*)new NormalNote(3854));
		this->notes[0].push_back((Note*)new NormalNote(3902));
		this->notes[2].push_back((Note*)new NormalNote(3950));
		this->notes[1].push_back((Note*)new NormalNote(3998));
		this->notes[1].push_back((Note*)new NormalNote(4022));
		this->notes[0].push_back((Note*)new NormalNote(4046));
		this->notes[0].push_back((Note*)new NormalNote(4118));
		this->notes[1].push_back((Note*)new NormalNote(4136));
		this->notes[0].push_back((Note*)new NormalNote(4142));
		this->notes[3].push_back((Note*)new NormalNote(4154));
		this->notes[2].push_back((Note*)new NormalNote(4160));
		this->notes[1].push_back((Note*)new NormalNote(4166));
		this->notes[0].push_back((Note*)new NormalNote(4172));
		this->notes[2].push_back((Note*)new NormalNote(4178));
		this->notes[1].push_back((Note*)new NormalNote(4184));
		this->notes[0].push_back((Note*)new NormalNote(4190));
		this->notes[3].push_back((Note*)new NormalNote(4196));
		this->notes[1].push_back((Note*)new NormalNote(4202));
		this->notes[0].push_back((Note*)new NormalNote(4208));
		this->notes[3].push_back((Note*)new NormalNote(4214));
		this->notes[2].push_back((Note*)new NormalNote(4220));
		this->notes[0].push_back((Note*)new NormalNote(4226));
		this->notes[3].push_back((Note*)new NormalNote(4232));
		this->notes[2].push_back((Note*)new NormalNote(4238));
		this->notes[1].push_back((Note*)new NormalNote(4244));
		this->notes[3].push_back((Note*)new NormalNote(4250));
		this->notes[2].push_back((Note*)new NormalNote(4256));
		this->notes[1].push_back((Note*)new NormalNote(4262));
		this->notes[0].push_back((Note*)new NormalNote(4268));
		this->notes[3].push_back((Note*)new NormalNote(4274));
		this->notes[2].push_back((Note*)new NormalNote(4280));
		this->notes[1].push_back((Note*)new NormalNote(4286));
		this->notes[0].push_back((Note*)new NormalNote(4292));
		this->notes[2].push_back((Note*)new NormalNote(4298));
		this->notes[0].push_back((Note*)new NormalNote(4304));
		this->notes[2].push_back((Note*)new NormalNote(4310));
		this->notes[0].push_back((Note*)new NormalNote(4316));
		this->notes[2].push_back((Note*)new NormalNote(4322));
		this->notes[0].push_back((Note*)new NormalNote(4328));
		this->notes[2].push_back((Note*)new NormalNote(4334));
		this->notes[3].push_back((Note*)new NormalNote(4346));
		this->notes[2].push_back((Note*)new NormalNote(4352));
		this->notes[1].push_back((Note*)new NormalNote(4358));
		this->notes[0].push_back((Note*)new NormalNote(4364));
		this->notes[2].push_back((Note*)new NormalNote(4370));
		this->notes[1].push_back((Note*)new NormalNote(4376));
		this->notes[0].push_back((Note*)new NormalNote(4382));
		this->notes[3].push_back((Note*)new NormalNote(4388));
		this->notes[1].push_back((Note*)new NormalNote(4394));
		this->notes[0].push_back((Note*)new NormalNote(4400));
		this->notes[3].push_back((Note*)new NormalNote(4406));
		this->notes[2].push_back((Note*)new NormalNote(4412));
		this->notes[0].push_back((Note*)new NormalNote(4418));
		this->notes[3].push_back((Note*)new NormalNote(4424));
		this->notes[2].push_back((Note*)new NormalNote(4430));
		this->notes[1].push_back((Note*)new NormalNote(4436));
		this->notes[3].push_back((Note*)new NormalNote(4442));
		this->notes[2].push_back((Note*)new NormalNote(4448));
		this->notes[1].push_back((Note*)new NormalNote(4454));
		this->notes[0].push_back((Note*)new NormalNote(4460));
		this->notes[3].push_back((Note*)new NormalNote(4466));
		this->notes[2].push_back((Note*)new NormalNote(4472));
		this->notes[1].push_back((Note*)new NormalNote(4478));
		this->notes[0].push_back((Note*)new NormalNote(4484));
		this->notes[2].push_back((Note*)new NormalNote(4490));
		this->notes[0].push_back((Note*)new NormalNote(4496));
		this->notes[2].push_back((Note*)new NormalNote(4502));
		this->notes[0].push_back((Note*)new NormalNote(4508));
		this->notes[2].push_back((Note*)new NormalNote(4514));
		this->notes[0].push_back((Note*)new NormalNote(4520));
		this->notes[3].push_back((Note*)new NormalNote(4526));
		this->notes[3].push_back((Note*)new NormalNote(4538));
		this->notes[2].push_back((Note*)new NormalNote(4544));
		this->notes[1].push_back((Note*)new NormalNote(4550));
		this->notes[0].push_back((Note*)new NormalNote(4556));
		this->notes[3].push_back((Note*)new NormalNote(4562));
		this->notes[2].push_back((Note*)new NormalNote(4568));
		this->notes[1].push_back((Note*)new NormalNote(4574));
		this->notes[0].push_back((Note*)new NormalNote(4580));
		this->notes[1].push_back((Note*)new NormalNote(4586));
		this->notes[0].push_back((Note*)new NormalNote(4592));
		this->notes[3].push_back((Note*)new NormalNote(4598));
		this->notes[2].push_back((Note*)new NormalNote(4604));
		this->notes[1].push_back((Note*)new NormalNote(4610));
		this->notes[0].push_back((Note*)new NormalNote(4616));
		this->notes[3].push_back((Note*)new NormalNote(4622));
		this->notes[2].push_back((Note*)new NormalNote(4628));
		this->notes[3].push_back((Note*)new NormalNote(4634));
		this->notes[2].push_back((Note*)new NormalNote(4640));
		this->notes[1].push_back((Note*)new NormalNote(4646));
		this->notes[0].push_back((Note*)new NormalNote(4652));
		this->notes[3].push_back((Note*)new NormalNote(4658));
		this->notes[2].push_back((Note*)new NormalNote(4664));
		this->notes[1].push_back((Note*)new NormalNote(4670));
		this->notes[0].push_back((Note*)new NormalNote(4676));
		this->notes[1].push_back((Note*)new NormalNote(4682));
		this->notes[0].push_back((Note*)new NormalNote(4688));
		this->notes[3].push_back((Note*)new NormalNote(4694));
		this->notes[2].push_back((Note*)new NormalNote(4700));
		this->notes[1].push_back((Note*)new NormalNote(4706));
		this->notes[0].push_back((Note*)new NormalNote(4712));
		this->notes[3].push_back((Note*)new NormalNote(4718));
		this->notes[2].push_back((Note*)new NormalNote(4724));
		this->notes[2].push_back((Note*)new NormalNote(4730));
		this->notes[1].push_back((Note*)new NormalNote(4736));
		this->notes[0].push_back((Note*)new NormalNote(4742));
		this->notes[3].push_back((Note*)new NormalNote(4748));
		this->notes[2].push_back((Note*)new NormalNote(4754));
		this->notes[1].push_back((Note*)new NormalNote(4760));
		this->notes[0].push_back((Note*)new NormalNote(4766));
		this->notes[3].push_back((Note*)new NormalNote(4772));
		this->notes[0].push_back((Note*)new NormalNote(4778));
		this->notes[3].push_back((Note*)new NormalNote(4784));
		this->notes[2].push_back((Note*)new NormalNote(4790));
		this->notes[1].push_back((Note*)new NormalNote(4796));
		this->notes[0].push_back((Note*)new NormalNote(4802));
		this->notes[3].push_back((Note*)new NormalNote(4808));
		this->notes[2].push_back((Note*)new NormalNote(4814));
		this->notes[1].push_back((Note*)new NormalNote(4820));
		this->notes[3].push_back((Note*)new NormalNote(4826));
		this->notes[2].push_back((Note*)new NormalNote(4832));
		this->notes[1].push_back((Note*)new NormalNote(4838));
		this->notes[0].push_back((Note*)new NormalNote(4844));
		this->notes[3].push_back((Note*)new NormalNote(4850));
		this->notes[2].push_back((Note*)new NormalNote(4856));
		this->notes[1].push_back((Note*)new NormalNote(4862));
		this->notes[0].push_back((Note*)new NormalNote(4868));
		this->notes[3].push_back((Note*)new NormalNote(4874));
		this->notes[2].push_back((Note*)new NormalNote(4880));
		this->notes[1].push_back((Note*)new NormalNote(4886));
		this->notes[0].push_back((Note*)new NormalNote(4892));
		this->notes[3].push_back((Note*)new NormalNote(4898));
		this->notes[2].push_back((Note*)new NormalNote(4904));
		this->notes[0].push_back((Note*)new NormalNote(4910));
		this->notes[3].push_back((Note*)new NormalNote(4922));
		this->notes[2].push_back((Note*)new NormalNote(4928));
		this->notes[1].push_back((Note*)new NormalNote(4934));
		this->notes[0].push_back((Note*)new NormalNote(4940));
		this->notes[2].push_back((Note*)new NormalNote(4946));
		this->notes[1].push_back((Note*)new NormalNote(4952));
		this->notes[0].push_back((Note*)new NormalNote(4958));
		this->notes[3].push_back((Note*)new NormalNote(4964));
		this->notes[1].push_back((Note*)new NormalNote(4970));
		this->notes[0].push_back((Note*)new NormalNote(4976));
		this->notes[3].push_back((Note*)new NormalNote(4982));
		this->notes[2].push_back((Note*)new NormalNote(4988));
		this->notes[0].push_back((Note*)new NormalNote(4994));
		this->notes[3].push_back((Note*)new NormalNote(5000));
		this->notes[2].push_back((Note*)new NormalNote(5006));
		this->notes[1].push_back((Note*)new NormalNote(5012));
		this->notes[3].push_back((Note*)new NormalNote(5018));
		this->notes[2].push_back((Note*)new NormalNote(5024));
		this->notes[1].push_back((Note*)new NormalNote(5030));
		this->notes[0].push_back((Note*)new NormalNote(5036));
		this->notes[3].push_back((Note*)new NormalNote(5042));
		this->notes[2].push_back((Note*)new NormalNote(5048));
		this->notes[1].push_back((Note*)new NormalNote(5054));
		this->notes[0].push_back((Note*)new NormalNote(5060));
		this->notes[3].push_back((Note*)new NormalNote(5066));
		this->notes[2].push_back((Note*)new NormalNote(5072));
		this->notes[1].push_back((Note*)new NormalNote(5078));
		this->notes[0].push_back((Note*)new NormalNote(5084));
		this->notes[2].push_back((Note*)new NormalNote(5090));
		this->notes[1].push_back((Note*)new NormalNote(5096));
		this->notes[2].push_back((Note*)new NormalNote(5102));
		this->notes[2].push_back((Note*)new NormalNote(5150));
		this->notes[1].push_back((Note*)new NormalNote(5186));
		this->notes[1].push_back((Note*)new NormalNote(5192));
		this->notes[3].push_back((Note*)new NormalNote(5198));
		this->notes[0].push_back((Note*)new NormalNote(5222));
		this->notes[2].push_back((Note*)new NormalNote(5342));
		this->notes[2].push_back((Note*)new NormalNote(5360));
		this->notes[2].push_back((Note*)new NormalNote(5378));
		this->notes[3].push_back((Note*)new NormalNote(5390));

		this->notes[0].push_back((Note*)new NormalNote(INF));
		this->notes[1].push_back((Note*)new NormalNote(INF));
		this->notes[2].push_back((Note*)new NormalNote(INF));
		this->notes[3].push_back((Note*)new NormalNote(INF));

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
