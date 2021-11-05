#pragma once
#include "SADXModLoader.h"
#include "IniFile.hpp"
#include "AnimationFile.h"

struct JiggleInfo
{
	char type;
	char field_1;
	__int16 field_2;
	float speed;
	int field_8;
	int field_C;
	int field_10;
	NJS_OBJECT* SourceModelPtr;
	NJS_OBJECT* SourceModelCopy;
	NJS_OBJECT* Model;
	NJS_OBJECT* OtherModel;
	NJS_VECTOR field_24;
	char gap30[4];
	float field_34[33];
	int field_B8;
	int field_BC;
	int field_C0;
	float field_C4;
	float field_C8;
	float field_CC;
	int field_D0;
	int field_D4;
	int field_D8;
	float field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	int field_EC;
	int field_F0;
	int field_F4;
	int field_F8;
	int field_FC;
	int field_100;
	int field_104;
	int field_108;
	int field_10C;
	int field_110;
	int field_114;
	int field_118;
	int field_11C;
	int field_120;
	int field_124;
	int field_128;
	int field_12C;
	int field_130;
	int field_134;
	int field_138;
	int field_13C;
};

void DrawChunkModel(NJS_CNK_MODEL* model);
extern D3DMATRIX WorldMatrixBackup;
void DrawTransformedChunkObject(void* a1);
void njCnkAction_Queue(NJS_ACTION* action, float frame, QueuedModelFlagsB flags);
void njCnkAction(NJS_ACTION* action, float frame);
void NullModel(NJS_MODEL_SADX*, int, int);
void njNullAction(NJS_ACTION* action, float frame);
void SetupWorldMatrix();
bool FindModels(std::string& mdlpath, std::unordered_map<std::string, void*>& labels);
JiggleInfo* __cdecl InitJiggle(NJS_OBJECT* arg0);
void FreeJiggle(JiggleInfo* a1);
void ApplyJiggle(JiggleInfo* a1);
void njCnkActionLinkEX(NJS_ACTION_LINK* action, float frame, int flag);
void DrawEventAction_Label46(int light, char actionListMode, int timer);

template<int N>
void ProcessAnimList(AnimData_t (&animlist)[N], const std::string& mtnpath, std::unordered_map<int, NJS_OBJECT*>& modelmap)
{
	const IniFile* mtnini = new IniFile(mtnpath + "Animation List.ini");
	char idxbuf[4];
	for (int i = 0; i < N; i++)
	{
		sprintf_s(idxbuf, "%d", i);
		if (mtnini->hasGroup(idxbuf))
		{
			const IniGroup* grp = mtnini->getGroup(idxbuf);
			AnimationFile* mtn = new AnimationFile(mtnpath + grp->getString("Animation") + ".saanim");
			animlist[i].Animation = new NJS_ACTION();
			animlist[i].Animation->object = modelmap[grp->getInt("Model")];
			animlist[i].Animation->motion = mtn->getmotion();
			animlist[i].Instance = (char)mtn->getmodelcount();
			animlist[i].Property = (char)grp->getInt("Property");
			if (animlist[i].Property >= 5) --animlist[i].Property;
			animlist[i].NextAnim = (short)grp->getInt("NextAnimation");
			animlist[i].TransitionSpeed = grp->getFloat("TransitionSpeed");
			animlist[i].AnimationSpeed = grp->getFloat("AnimationSpeed");
		}
		else
			animlist[i] = animlist[0];
	}
	delete mtnini;
}

