// SA2Sonic.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include "IniFile.hpp"
#include "SADXModLoader.h"
#include "ModelInfo.h"
#include "AnimationFile.h"
#include "..\CommonFunctions\CommonFunctions.h"
#include "..\CommonFunctions\CommonSADX.h"
bool isJiggle = true;

using std::unordered_map;
using std::vector;
using std::string;

unordered_map<int, NJS_OBJECT*> modelmap;
unordered_map<NJS_OBJECT*, NJS_OBJECT*> modelmap2;
struct JiggleData
{
	JiggleInfo* SpineJiggle;
	NJS_VECTOR SpineJigglePos;
	NJS_VECTOR HeadNodePos;
};
static_assert(sizeof(JiggleData) <= sizeof(EntityData2), "JiggleData cannot be larger than EntityData2!");
JiggleData* jiggledata[8] = {};
void Sonic_Jiggle_Delete_r(ObjectMaster* obj)
{
	EntityData1* data1 = obj->Data1;
	JiggleData* data2 = (JiggleData*)obj->Data2;
	if (data2->SpineJiggle)
	{
		FreeJiggle(data2->SpineJiggle);
		data2->SpineJiggle = nullptr;
	}
	jiggledata[data1->CharIndex] = nullptr;
}

void Sonic_Jiggle_Main_r(ObjectMaster* obj)
{
	EntityData1* data1 = obj->Data1;
	JiggleData* data2 = (JiggleData*)obj->Data2;
	EntityData1* pd1 = EntityData1Ptrs[data1->CharIndex];
	CharObj2* co2 = CharObj2Ptrs[data1->CharIndex];

	switch (data1->Action)
	{
	case 0:
		if (!MetalSonicFlag)
		{
			data2->SpineJiggle = InitJiggle(modelmap[46]);
			data2->SpineJiggle->type = 18;
			data2->SpineJiggle->speed = 0.40000001f;
			data2->SpineJiggle->field_8 = 0;
			data2->SpineJiggle->field_10 = 1024;
			data2->SpineJiggle->Model = 0;
			data2->SpineJigglePos = pd1->Position;
		}
		jiggledata[data1->CharIndex] = data2;
		data1->Action = 1;
		obj->DeleteSub = Sonic_Jiggle_Delete_r;
		break;
	case 1:
		if (data2->SpineJiggle)
		{
			int v79 = rand();
			double v115 = (double)v79 * 0.000030517578125;
			float v81 = data2->HeadNodePos.y;
			float v82 = data2->HeadNodePos.z;
			NJS_VECTOR v117;
			v117.x = data2->HeadNodePos.x;
			float v83 = v117.x - data2->SpineJigglePos.x;
			v117.x = v83;
			v117.y = v81 - data2->SpineJigglePos.y;
			v117.z = v82 - data2->SpineJigglePos.z;
			float v84 = njScalor(&v117);
			float v85 = data2->HeadNodePos.x;
			float v86 = data2->HeadNodePos.y;
			float v87 = data2->HeadNodePos.z;
			float v116 = v84 * 0.25f;
			data2->SpineJigglePos.x = v85;
			float v88 = v116;
			JiggleInfo* v89 = data2->SpineJiggle;
			float v90 = v116;
			data2->SpineJigglePos.y = v86;
			data2->SpineJigglePos.z = v87;
			v116 = fabs(v90);
			float v91 = v116;
			v116 = fabs(v89->speed);
			float v94;
			if (v116 >= v91)
			{
				v94 = v91;
			}
			else
			{
				float v92 = v91;
				float v93 = v88;
				v94 = v92;
				v89->speed = v93;
			}
			if (v94 < 0.800000011920929)
			{
				if (v94 > 0.4000000059604645)
				{
					data2->SpineJiggle->field_C = 0x4000;
				}
			}
			else
			{
				data2->SpineJiggle->field_C = (signed int)(v115 * 8192.0
					+ 8192.0
					+ (double)data2->SpineJiggle->field_C);
			}
			ApplyJiggle(data2->SpineJiggle);
		}
		break;
	}
}

char currentplayer;
NJS_MATRIX flt_1A51A3C, flt_1A519D0, flt_1A51A6C, flt_1A51A00, flt_1A51994, flt_1A51ADC, sonicheadmatrix;
void NodeCallback(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[3])
		memcpy(flt_1A51A3C, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[11])
		memcpy(flt_1A519D0, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[12])
		memcpy(flt_1A51A6C, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[48])
		memcpy(sonicheadmatrix, v1, sizeof(NJS_MATRIX));
}

NJS_MATRIX posmatrix;
void NodeCallback2(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[48])
	{
		if (jiggledata[currentplayer] && jiggledata[currentplayer]->SpineJiggle)
		{
			NJS_VECTOR v = { 0, 0, 0 };
			NJS_MATRIX m;
			njSetMatrix(m, v1);
			njMultiMatrix(m, posmatrix);
			njCalcPoint(m, &v, &jiggledata[currentplayer]->HeadNodePos);
		}
	}
	else if (obj == modelmap[5])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[0]);
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[6]);
	}
	else if (obj == modelmap[11])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[1]);
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[7]);
	}
}

void RemapAction(NJS_ACTION& act2)
{

	if (MetalSonicFlag)
	{
		if (act2.object == SONIC_OBJECTS[0])
			act2.object = SONIC_OBJECTS[68];
		else if (act2.object == SONIC_OBJECTS[66])
			act2.object = SONIC_OBJECTS[69];
		else if (act2.object == SONIC_OBJECTS[67])
			act2.object = SONIC_OBJECTS[70];
	}
	act2.object = modelmap2[act2.object];
}

void(__cdecl** NodeCallbackFuncPtr)(NJS_OBJECT* obj) = (decltype(NodeCallbackFuncPtr))0x3AB9908;
void DrawSonicModel(CharObj2* a2, int animNum, NJS_ACTION* action, JiggleData* jiggle)
{
	njPushMatrix(nullptr);
	SetupWorldMatrix();
	Direct3D_SetChunkModelRenderState();
	NJS_OBJECT* v16 = nullptr;
	NJS_CNK_MODEL* v55 = nullptr;
	if (jiggle && isJiggle)
	{
		if (jiggle->SpineJiggle)
		{
			v16 = modelmap[46];
			v55 = v16->chunkmodel;
			v16->chunkmodel = jiggle->SpineJiggle->SourceModelCopy->chunkmodel;
		}
	}
	if ((a2->Upgrades & Upgrades_LightShoes) && modelmap.find(58) != modelmap.cend() && modelmap.find(60) != modelmap.cend())
	{
		modelmap[19]->sibling = modelmap[58];
		modelmap[14]->sibling = modelmap[60];
	}
	else
	{
		modelmap[19]->sibling = modelmap[20];
		modelmap[14]->sibling = modelmap[15];
	}
	NJS_ACTION act2 = *action;
	RemapAction(act2);
	*NodeCallbackFuncPtr = NodeCallback;
	if (*(int*)0x3ABD9CC)
	{
		DrawQueueDepthBias = -5952.0;
		njCnkAction_Queue(&act2, a2->AnimationThing.Frame, QueuedModelFlagsB_EnableZWrite);
		DrawQueueDepthBias = 0.0;
	}
	else
	{
		njCnkAction(&act2, a2->AnimationThing.Frame);
	}
	*NodeCallbackFuncPtr = nullptr;
	if (jiggle && isJiggle)
	{
		if (jiggle->SpineJiggle)
			v16->chunkmodel = v55;
	}
	if (action->object == SONIC_OBJECTS[0] && (a2->Upgrades & Upgrades_CrystalRing) && modelmap.find(63) != modelmap.cend())
	{
		memcpy(_nj_current_matrix_ptr_, flt_1A51A3C, sizeof(NJS_MATRIX));
		DrawChunkObject(modelmap[63]);
	}
	Direct3D_UnsetChunkModelRenderState();
	njPopMatrix(1);
}


void CNK_CommonDrawSonicAction(uint8_t id) {
	njPushMatrix(nullptr);
	SetupWorldMatrix();
	Direct3D_SetChunkModelRenderState();

	CharObj2* co2 = CharObj2Ptrs[id];

	if ((co2->Upgrades & Upgrades_LightShoes) && modelmap.find(58) != modelmap.cend() && modelmap.find(60) != modelmap.cend())
	{
		modelmap[19]->sibling = modelmap[58];
		modelmap[14]->sibling = modelmap[60];
	}
	else
	{
		modelmap[19]->sibling = modelmap[20];
		modelmap[14]->sibling = modelmap[15];
	}
}


void CNK_DrawSonicAction(uint8_t id, NJS_ACTION* action, float frame, int queueModelFlag)
{
	CharObj2* co2 = CharObj2Ptrs[id];

	CNK_CommonDrawSonicAction(id);

	NJS_ACTION act2 = *action;
	RemapAction(act2);
	*NodeCallbackFuncPtr = NodeCallback;

	DrawQueueDepthBias = -5952.0;

	njCnkAction_Queue(&act2, frame, (QueuedModelFlagsB)queueModelFlag);

	DrawQueueDepthBias = 0.0;
	*NodeCallbackFuncPtr = nullptr;

	if (action->object == SONIC_OBJECTS[0] && (co2->Upgrades & Upgrades_CrystalRing) && modelmap.find(63) != modelmap.cend())
	{
		memcpy(_nj_current_matrix_ptr_, flt_1A51A3C, sizeof(NJS_MATRIX));
		DrawChunkObject(modelmap[63]);
	}
	Direct3D_UnsetChunkModelRenderState();
	njPopMatrix(1);
}

void __cdecl DrawEventAction_r(taskwk* data1, int light)
{
	eventwk* event; // ebp
	EVENT_ACTION_LIST* actionOld; // edi
	EVENT_ACTION_LIST* actionList; // esi
	NJS_TEXLIST* texlist; // eax
	char actionMode; // cl
	QueuedModelFlagsB QueueModelFlag; // bl
	NJS_MOTION* OldMotion; // eax
	//obj* v9; // eax
	obj* v9;
	_BOOL1 v10; // zf
	int i; // edi
	double v12; // st7
	NJS_MOTION* v13; // edx
	float v14; // ecx
	int v15; // edx
	double v16; // st7
	double v17; // st7
	int j; // eax
	NJS_ACTION* actionlistMotion; // [esp-4h] [ebp-44h]
	int v20; // [esp+0h] [ebp-40h]
	int v21; // [esp+0h] [ebp-40h]
	float v22; // [esp+0h] [ebp-40h]
	char actionListMode; // [esp+1Bh] [ebp-25h]
	float v24; // [esp+1Ch] [ebp-24h]
	float timer; // [esp+1Ch] [ebp-24h]
	float frame; // [esp+20h] [ebp-20h]
	EVENT_ACTION_LIST* actionOldList; // [esp+24h] [ebp-1Ch]
	NJS_ACTION* v28; // [esp+28h] [ebp-18h] BYREF
	NJS_MOTION* a3; // [esp+30h] [ebp-10h] BYREF
	NJS_MOTION* v30; // [esp+34h] [ebp-Ch]
	float frameOld; // [esp+38h] [ebp-8h]
	float v32; // [esp+3Ch] [ebp-4h]

	event = (eventwk*)data1->ewp;

	if (MissedFrames || !event)
		return;

	actionList = event->action.list;
	actionOld = event->action.old;
	actionOldList = actionOld;

	if (!actionList)
		return;

	uint8_t pid = data1->counter.b[0];
	actionMode = actionList->mode;
	frame = (float)actionList->action.motion->nbFrame;
	v24 = event->action.timer;
	texlist = actionList->texlist;
	unsigned __int8 flag = ((unsigned __int8)actionList->mode >> 4) & 0xD;
	QueueModelFlag = (QueuedModelFlagsB)flag;
	actionListMode = actionList->mode;
	if (texlist)
	{
		njSetTexture(texlist);
		actionMode = actionListMode;
	}
	if (light >= 0 && (actionMode & 0x20) == 0)
	{
		Direct3D_PerformLighting(light);
		actionMode = actionListMode;
	}
	if (actionOld && actionList->linkframe)
	{
	
		v28 = new NJS_ACTION();
		v9 = actionList->action.object;
		v28->object = v9;
		v30 = actionList->action.motion;
		v28->motion = v30;
		v10 = (actionOld->mode & 1) == 0;

		OldMotion = actionOld->action.motion;
		a3 = (NJS_MOTION*)OldMotion;

		if (v10)
		{
			frameOld = (float)((unsigned int)&OldMotion->nbFrame - 1);
		}
		else
		{
			frameOld = 0.0;
		}
		v32 = 0.0;
		i = 0;

		for (i = 0; i < 8; i++) {

			if (data1 != taskwkPtrs[i])
			{
				continue;
			}

			v12 = floor(v24);
			if ((double)(unsigned __int8)actionList->linkframe <= v12 + v12)
			{
				v14 = v32;
				v13 = v30;
			}
			else
			{
				v14 = frameOld;
				v13 = a3;
			}
			EPJoinVertexes(i, actionList->action.object, v13, v14);
			actionMode = actionListMode;
		}

		v16 = v24 + 1.0;
		v15 = (unsigned __int8)actionList->linkframe + 1;
		if ((actionMode & 8) != 0)
		{
			DrawEventAction((EntityData1*)data1);
			return;
		}
		else
		{
			*(float*)&v21 = v16 / (double)v15;
			if ((actionMode & 4) != 0) {

				DrawEventAction((EntityData1*)data1);
				return;
			}
			else
			{
				DrawEventAction((EntityData1*)data1);
				return;
			}
		}
		v17 = (double)MissedFrames_B + v24;
		timer = v17;
		if ((double)(unsigned __int8)actionList->linkframe > floor(v17))
		{
			DrawEventAction_Label46(light, actionListMode, timer);
			event->action.timer = timer;
			return;
		}
		FreeMemory(actionOldList);
		event->action.old = 0;
		timer = 0.0;
		DrawEventAction_Label46(light, actionListMode, timer);
		event->action.timer = timer;
		return;
	}
	for (j = 0; j < 8; j++) {

		if (data1 != taskwkPtrs[j])
		{
			continue;
		}
		EPJoinVertexes(j, actionList->action.object, actionList->action.motion, event->action.timer);
		actionMode = actionListMode;
	}

	v22 = event->action.timer;
	if ((actionMode & 8) != 0)
	{
		//njCnkAction_Queue(&actionList->action, v22, QueueModelFlag);
		CNK_DrawSonicAction(pid, &actionList->action, v22, QueueModelFlag);
	}
	else
	{
		actionlistMotion = &actionList->action;
		if ((actionMode & 4) != 0)
		{
			//njCnkAction_Queue(v19, v22, QueueModelFlag);
			CNK_DrawSonicAction(pid, actionlistMotion, v22, QueueModelFlag);
		}
		else
		{
			CNK_DrawSonicAction(pid, actionlistMotion, v22, QueueModelFlag);
			//njCnkAction_Queue(v19, v22, QueueModelFlag);
		}
	}
	timer = (double)MissedFrames_B * actionList->speed + v24;
	if ((actionList->mode & 1) != 0)
	{
		if (timer < (double)frame)
		{

			if (light >= 0 && (actionListMode & 0x20) == 0)
			{
				Direct3D_PerformLighting(0);
			}
			event->action.timer = timer;
			return;
		}
		if (!actionList->next)
		{
			timer = timer - frame;
			DrawEventAction_Label46(light, actionListMode, timer);
			event->action.timer = timer;
			return;
		}
	}
	else if (frame - 1.0 > timer)
	{
		DrawEventAction_Label46(light, actionListMode, timer);
		event->action.timer = timer;
		return;
	}
	event->action.old = actionList;
	event->action.list = actionList->next;

	timer = 0.0;
	DrawEventAction_Label46(light, actionListMode, timer);
	event->action.timer = timer;
	return;
}

FunctionPointer(void, sub_49F0B0, (EntityData1* a1, struct_a3* a2), 0x49F0B0);
FunctionPointer(void, sub_791A80, (NJS_MATRIX_PTR a1), 0x791A80);
void __cdecl Sonic_Display_r(ObjectMaster* obj)
{
	EntityData2* data2_pp; // ebx
	EntityData1* data1; // edi
	CharObj2* data2; // esi
	unsigned int v4; // ebp
	Angle v5; // eax
	Angle v6; // eax
	NJS_VECTOR a2 = {}; // [esp+Ch] [ebp-Ch]

	data2_pp = (EntityData2*)obj->Data2;
	data2 = data2_pp->CharacterData;
	data1 = obj->Data1;
	currentplayer = data1->CharIndex;
	if (IsVisible(&data1->Position, 15.0))
	{
		Direct3D_SetZFunc(1u);
		BackupConstantAttr();
		AddConstantAttr(0, NJD_FLAG_IGNORE_SPECULAR);
		if (SuperSonicFlag)
			Direct3D_PerformLighting(4);
		else
			Direct3D_PerformLighting(2);
		if (!MetalSonicFlag && SONIC_OBJECTS[6]->sibling != *(NJS_OBJECT**)0x3C55D40)
		{
			data2->AnimationThing.field_2 = 2;
			ProcessVertexWelds(data1, data2_pp, data2);
			data2->AnimationThing.WeldInfo[0xB].ModelB = SONIC_OBJECTS[6]->sibling;
			data2->AnimationThing.field_2 = 0;
			ProcessVertexWelds(data1, data2_pp, data2);
			*(NJS_OBJECT**)0x3C55D40 = SONIC_OBJECTS[6]->sibling;
		}
		v4 = (unsigned __int16)data2->AnimationThing.Index;
		if (data2->AnimationThing.State == 2)
			v4 = (unsigned __int16)data2->AnimationThing.LastIndex;
		if (!(data1->InvulnerableTime & 2))
		{
			if (MetalSonicFlag)
				njSetTexture(&METALSONIC_TEXLIST);
			else if (data2->Upgrades & Upgrades_SuperSonic)
				njSetTexture(&SUPERSONIC_TEXLIST);
			else
				njSetTexture(&SONIC_TEXLIST);
			memcpy(posmatrix, &IdentityMatrix, sizeof(NJS_MATRIX));
			njTranslateV(posmatrix, &data1->CollisionInfo->CollisionArray->center);
			v5 = data1->Rotation.z;
			if (v5)
				njRotateZ(posmatrix, (unsigned __int16)v5);
			v6 = data1->Rotation.x;
			if (v6)
				njRotateX(posmatrix, (unsigned __int16)v6);
			if (data1->Rotation.y != 0x8000)
				njRotateY(posmatrix, (unsigned __int16)(-0x8000 - LOWORD(data1->Rotation.y)));
			if (v4 == 14)
			{
				if (data1->Status & (Status_Unknown1 | Status_Ground))
				{
					a2.x = 0;
					a2.y = -1;
					a2.z = 0;
					njTranslateV(posmatrix, &a2);
					njRotateZ(posmatrix, 0x2000);
					a2.x = 0.69999999f;
					a2.y = 1.1f;
					a2.z = 0.80000001f;
					njScaleV(posmatrix, &a2);
				}
			}
			njPushMatrix(nullptr);
			njMultiMatrix(nullptr, posmatrix);
			if (*((_DWORD*)data1->field_3C + 16))
				DrawEventAction_r((taskwk*)data1, dspl);
			else
			{
				NJS_ACTION* action;
				if (data2->AnimationThing.State == 2)
					action = data2->AnimationThing.action;
				else
				{
					if ((data1->Status & Status_Ball) && v4 != 145 && (data2->SonicSpinTimer & 0x11))
						v4 = 32;
					action = data2->AnimationThing.AnimData[v4].Animation;
				}
				DrawSonicModel(data2, v4, action, jiggledata[data1->CharIndex]);
				NJS_ACTION act2 = *action;
				RemapAction(act2);
				*NodeCallbackFuncPtr = NodeCallback2;
				njPushMatrix(_nj_unit_matrix_);
				njNullAction(&act2, data2->AnimationThing.Frame);
				njPopMatrix(1);
				*NodeCallbackFuncPtr = nullptr;
				/*if (data1->Status & Status_LightDash)
				{
					Direct3D_PerformLighting(0);
					Sonic_DisplayLightDashModel(data1, data2_pp, data2);
				}*/
			}
			njPopMatrix(1u);
		}
		Direct3D_PerformLighting(0);
		ClampGlobalColorThing_Thing();
		RestoreConstantAttr();
		Direct3D_ResetZFunc();

		if (IsGamePaused())
			sub_49F0B0(data1, &data2->_struct_a3);
	}
}

void __cdecl MetalSonic_AfterImage_Display_r(ObjectMaster* obj)
{
	EntityData1* v1; // edi
	CharObj2* v2; // esi
	Angle v3; // eax
	float r; // ST08_4
	Angle v5; // eax
	Angle v6; // eax

	v1 = obj->Data1;
	v2 = GetCharObj2(0);
	if (v2)
	{
		if (IsVisible(&v1->Position, 15.0))
		{
			BackupConstantAttr();
			AddConstantAttr(0, NJD_FLAG_USE_ALPHA);
			njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
			njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);
			r = *(float*)&v1->CharIndex - 1;
			njControl3D_Backup();
			njControl3D_Add(NJD_CONTROL_3D_OFFSET_MATERIAL);
			SetMaterialAndSpriteColor_Float(r, 0, 0, 0);
			njSetTexture(&METALSONIC_TEXLIST);
			njPushMatrix(0);
			njTranslateV(0, &v1->Position);
			v3 = v1->Rotation.z;
			if (v3)
			{
				njRotateZ(0, (unsigned __int16)v3);
			}
			v5 = v1->Rotation.x;
			if (v5)
			{
				njRotateX(0, (unsigned __int16)v5);
			}
			v6 = v1->Rotation.y;
			if (v6 != 0x8000)
			{
				njRotateY(0, (unsigned __int16)(-32768 - v6));
			}
			DrawSonicModel(v2, v2->AnimationThing.Index, v2->AnimationThing.AnimData[v2->AnimationThing.Index].Animation, nullptr);
			njPopMatrix(1u);
			njControl3D_Restore();
			njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
			njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
			ClampGlobalColorThing_Thing();
			RestoreConstantAttr();
		}
	}
}

void __cdecl MetalSonic_AfterImage_Main_r(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	float v2; // st7

	v1 = obj->Data1;
	MetalSonic_AfterImage_Display_r(obj);
	v2 = *(float*)&v1->CharIndex - 0.1f;
	*(float*)&v1->CharIndex = v2;
	if (v2 <= 0.0)
	{
		CheckThingButThenDeleteObject(obj);
	}
}

void __cdecl MetalSonic_AfterImages_Main_r(ObjectMaster* obj)
{
	EntityData1* v1; // eax
	_BOOL1 v2; // sf
	ObjectMaster* v3; // esi
	CharObj2* v4; // edi
	ObjectMaster* v5; // eax
	EntityData1* v6; // ecx
	Rotation3* v7; // edx
	Rotation3* v8; // esi

	v1 = obj->Data1;
	v2 = (*(int*)&v1->Object)-- - 1 < 0;
	if (v2)
	{
		CheckThingButThenDeleteObject(obj);
	}
	else
	{
		v3 = GetCharacterObject(0);
		if (v3)
		{
			v4 = GetCharObj2(0);
			if (v4)
			{
				v5 = LoadObject(LoadObj_Data1, 4, MetalSonic_AfterImage_Main_r);
				if (v5)
				{
					v6 = v5->Data1;
					v6->Position = v3->Data1->Position;
					v7 = &v3->Data1->Rotation;
					v8 = &v6->Rotation;
					v8->x = v7->x;
					v8->y = v7->y;
					v8->z = v7->z;
					*(float*)&v6->LoopData = v4->AnimationThing.Frame;
					*(float*)&v6->CharIndex = 0.5;
					v5->DisplaySub = MetalSonic_AfterImage_Display_r;
				}
			}
		}
	}
}

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		string mdlpath = string(path) + "\\models\\";
		unordered_map<string, void*> labels;
		if (!FindModels(mdlpath, labels)) return;
		const IniFile* mdlini = new IniFile(mdlpath + "models.ini");
		const IniGroup* mdlgrp = mdlini->getGroup("");
		for (auto i = mdlgrp->cbegin(); i != mdlgrp->cend(); ++i)
			if (labels.find(i->second) != labels.cend())
				modelmap[std::stol(i->first)] = (NJS_OBJECT*)labels[i->second];
		delete mdlini;

		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isJiggle = config->getBool("General", "isJiggle", true);
		delete config;


		for (int i = 0; i < 79; i++)
			if (modelmap.find(i) != modelmap.cend())
				modelmap2[SONIC_OBJECTS[i]] = modelmap[i];
		if (modelmap.find(79) != modelmap.cend())
			modelmap2[SONIC_ACTIONS[142]->object] = modelmap[79];
		WriteData((short*)0x49ACD8, (short)0x9090);
		WriteJump(Sonic_Display, Sonic_Display_r);
		WriteJump(MetalSonic_AfterImages_Main, MetalSonic_AfterImages_Main_r);
		WriteData((char*)0x49BE22, (char)0xEB);
		WriteJump(Sonic_Jiggle_Main, Sonic_Jiggle_Main_r);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}