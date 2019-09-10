#pragma once
#include "SADXModLoader.h"
#include "IniFile.hpp"
#include "AnimationFile.h"

void DrawChunkModel(NJS_CNK_MODEL* model);
extern D3DMATRIX WorldMatrixBackup;
void DrawTransformedChunkObject(void* a1);
void njCnkAction_Queue(NJS_ACTION* action, float frame, QueuedModelFlagsB flags);
void njCnkAction(NJS_ACTION* action, float frame);
void NullModel(NJS_MODEL_SADX*, int, int);
void njNullAction(NJS_ACTION* action, float frame);
void SetupWorldMatrix();
bool FindModels(std::string& mdlpath, std::unordered_map<std::string, void*>& labels);

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

