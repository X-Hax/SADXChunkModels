// SA2Sonic.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include "IniFile.hpp"
#include "SADXModLoader.h"
#include "ModelInfo.h"
#include "AnimationFile.h"
#include "..\CommonFunctions\CommonFunctions.h"
#include "UsercallFunctionHandler.h"

using std::unordered_map;
using std::vector;
using std::string;

unordered_map<int, NJS_OBJECT*> modelmap;
unordered_map<NJS_OBJECT*, NJS_OBJECT*> modelmap2;
char currentplayer;
void NodeCallback2(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[23])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[0]);
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[6]);
	}
	else if (obj == modelmap[25])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[1]);
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[7]);
	}
}

void(__cdecl** NodeCallbackFuncPtr)(NJS_OBJECT* obj) = (decltype(NodeCallbackFuncPtr))0x3AB9908;
void DrawAmyModel(CharObj2* a2, int animNum, NJS_ACTION* action)
{
	njPushMatrix(nullptr);
	SetupWorldMatrix();
	Direct3D_SetChunkModelRenderState();
	NJS_ACTION act2 = *action;
	act2.object = modelmap2[act2.object];
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
	Direct3D_UnsetChunkModelRenderState();
	njPopMatrix(1);
}

FunctionPointer(void, sub_4187D0, (EntityData1* a1), 0x4187D0);
FunctionPointer(void, sub_49F0B0, (EntityData1* a1, struct_a3* a2), 0x49F0B0);
FunctionPointer(int, sub_42FB00, (), 0x42FB00);
auto sub_486CD0 = GenerateUsercallWrapper<signed int (*)(CharObj2* a1, EntityData1* a2)>(rEAX, 0x486CD0, rECX, rESI);
void __cdecl Amy_Display_r(ObjectMaster* obj)
{
	CharObj2* data2; // edi
	EntityData1* data1; // esi
	__int16 v3; // ax
	double v4; // st7
	double v5; // st7
	NJS_OBJECT* v6; // edx
	NJS_OBJECT* v7; // ecx
	unsigned int v8; // eax
	Uint32 v9; // ebx
	int v10; // ebx
	Angle v11; // eax
	signed int v12; // ebp
	double v13; // st7
	Angle v14; // eax
	Angle v15; // eax
	Angle v16; // eax
	Angle v17; // eax
	float frameNumber; // [esp+0h] [ebp-38h]
	NJS_VECTOR v; // [esp+14h] [ebp-24h]
	NJS_VECTOR a2; // [esp+20h] [ebp-18h]
	NJS_VECTOR vs; // [esp+2Ch] [ebp-Ch]

	data1 = obj->Data1;
	data2 = ((EntityData2*)obj->Data2)->CharacterData;
	currentplayer = data1->CharIndex;
	Direct3D_SetZFunc(3u);
	if (HIBYTE(data2->LightdashTime) != 1)
	{
		if (sub_42FB00() == 1)
		{
			goto LABEL_49;
		}
		v3 = data2->AnimationThing.Index;
		if (v3 == 13)
		{
			data2->SomeFrameNumberThing = 1.0;
			goto LABEL_7;
		}
		if (v3 < 85)
		{
		LABEL_49:
			data2->SomeFrameNumberThing = 0.0;
		}
	}
LABEL_7:
	v4 = data2->TailsFlightTime + 0.1;
	if (v4 >= data2->SomeFrameNumberThing)
	{
		v5 = data2->TailsFlightTime - 0.1;
		if (v5 <= data2->SomeFrameNumberThing)
		{
			data2->TailsFlightTime = data2->SomeFrameNumberThing;
		}
		else
		{
			data2->TailsFlightTime = v5;
		}
	}
	else
	{
		data2->TailsFlightTime = v4;
	}
	if ((data2->Upgrades & Upgrades_LongHammer) && modelmap.find(38) != modelmap.cend())
		modelmap[36]->sibling = modelmap[38];
	else
		modelmap[36]->sibling = modelmap[37];
	v7 = modelmap[36]->sibling;
	v6 = v7->child;
	v7->scl[0] = data2->TailsFlightTime;
	v7->scl[1] = data2->TailsFlightTime;
	v7->scl[2] = data2->TailsFlightTime;
	v6->scl[0] = data2->TailsFlightTime;
	v6->scl[1] = data2->TailsFlightTime;
	v6->scl[2] = data2->TailsFlightTime;
	if (data2->TailsFlightTime == 0)
	{
		v7->evalflags |= 8u;
		v8 = v6->evalflags | 8;
	}
	else
	{
		v7->evalflags &= 0xFFFFFFF7;
		v6->evalflags &= 0xFFFFFFF7;
		v9 = v7->evalflags;
		if (data2->TailsFlightTime == 1)
		{
			v7->evalflags = v9 | 4;
			v8 = v6->evalflags | 4;
		}
		else
		{
			v7->evalflags = v9 & 0xFFFFFFFB;
			v8 = v6->evalflags & 0xFFFFFFFB;
		}
	}
	v6->evalflags = v8;
	v10 = (unsigned __int16)data2->AnimationThing.Index;
	if (data2->AnimationThing.State == 2)
	{
		v10 = (unsigned __int16)data2->AnimationThing.LastIndex;
	}
	if (!(data1->InvulnerableTime & 2))
	{
		njSetTexture(&AMY_TEXLIST);
		v12 = sub_486CD0(data2, data1);
		Direct3D_PerformLighting(2);
		v13 = data2->PhysicsData.CollisionSize * 0.5;
		vs.z = 0.0;
		vs.x = 0.0;
		vs.y = v13;
		njPushMatrix(_nj_unit_matrix_);
		v11 = data1->Rotation.z;
		if (v11)
		{
			njRotateZ(0, (unsigned __int16)v11);
		}
		v14 = data1->Rotation.x;
		if (v14)
		{
			njRotateX(0, (unsigned __int16)v14);
		}
		if (data1->Rotation.y)
		{
			njRotateY(0, (unsigned __int16)-LOWORD(data1->Rotation.y));
		}
		njCalcVector(0, &vs, &a2);
		njPopMatrix(1u);
		njAddVector(&a2, &data1->Position);
		njPushMatrix(nullptr);
		njTranslateV(0, &a2);
		data1->CollisionInfo->CollisionArray->center = a2;
		if (!v12)
		{
			v15 = data1->Rotation.z;
			if (v15)
			{
				njRotateZ(0, (unsigned __int16)v15);
			}
			v16 = data1->Rotation.x;
			if (v16)
			{
				njRotateX(0, (unsigned __int16)v16);
			}
			v17 = data1->Rotation.y;
			if (v17 != 0x8000)
			{
				njRotateY(0, (unsigned __int16)(-32768 - v17));
			}
			if (*((_DWORD*)data1->field_3C + 16))
			{
				sub_4187D0(data1);
			}
			else if (Controllers[0].HeldButtons & Buttons_X && data1->Action == 53)
			{
				DrawChunkObject(modelmap2[data2->AnimationThing.AnimData[(unsigned __int16)data2->AnimationThing.Index].Animation->object]);
			}
			else
			{
				NJS_ACTION* action;
				if (data2->AnimationThing.State == 2)
					action = data2->AnimationThing.action;
				else
					action = data2->AnimationThing.AnimData[v10].Animation;
				DrawAmyModel(data2, v10, action);
				NJS_ACTION act2 = *action;
				act2.object = modelmap2[act2.object];
				*NodeCallbackFuncPtr = NodeCallback2;
				njPushMatrix(_nj_unit_matrix_);
				njNullAction(&act2, data2->AnimationThing.Frame);
				njPopMatrix(1);
				*NodeCallbackFuncPtr = nullptr;
			}
		}
		njPopMatrix(1u);
		ClampGlobalColorThing_Thing();
		Direct3D_PerformLighting(0);
	}
	Direct3D_ResetZFunc();
	if (IsGamePaused())
	{
		sub_49F0B0(data1, &data2->_struct_a3);
	}
}

DataArray(AnimData, AmyAnimData, 0x3C54880, 102);
void __cdecl Amy_AfterImage_Main_r(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	char v2; // al
	NJS_OBJECT* v3; // ecx
	NJS_OBJECT* v4; // edx
	Uint32 v5; // eax
	unsigned int v6; // eax
	Uint32 v7; // eax
	float r; // ST04_4
	double v9; // st7
	Angle v10; // eax
	Angle v11; // eax
	Angle v12; // eax
	Angle v13; // eax
	NJS_VECTOR a2; // [esp+14h] [ebp-18h]
	NJS_VECTOR vs = {}; // [esp+20h] [ebp-Ch]

	v1 = obj->Data1;
	v2 = v1->Index + 1;
	v1->Index = v2;
	if ((unsigned __int8)v2 < 5u)
	{
		if ((unsigned __int8)v2 >= 4u && !MissedFrames)
		{
			njControl3D_Backup();
			njControl3D_Add(NJD_CONTROL_3D_OFFSET_MATERIAL);
			v3 = modelmap[36]->sibling;
			v4 = v3->child;
			v3->scl[0] = *(float*)&v1->Object;
			v3->scl[1] = *(float*)&v1->Object;
			v3->scl[2] = *(float*)&v1->Object;
			v4->scl[0] = *(float*)&v1->Object;
			v4->scl[1] = *(float*)&v1->Object;
			v4->scl[2] = *(float*)&v1->Object;
			v5 = v3->evalflags;
			if (*(float*)&v1->Object == 0.0)
			{
				v3->evalflags = v5 | 8;
				v6 = v4->evalflags | 8;
			}
			else
			{
				v3->evalflags = v5 & 0xFFFFFFF7;
				v4->evalflags &= 0xFFFFFFF7;
				v7 = v3->evalflags;
				if (*(float*)&v1->Object == 1)
				{
					v3->evalflags = v7 | 4;
					v6 = v4->evalflags | 4;
				}
				else
				{
					v3->evalflags = v7 & 0xFFFFFFFB;
					v6 = v4->evalflags & 0xFFFFFFFB;
				}
			}
			v4->evalflags = v6;
			Direct3D_PerformLighting(2);
			BackupConstantAttr();
			AddConstantAttr(0, NJD_FLAG_USE_ALPHA);
			r = (double)(unsigned __int8)v1->Index * 0.2 * -0.39999998 - 0.5;
			SetMaterialAndSpriteColor_Float(r, 0.0, 0.0, 0.0);
			njSetTexture(&AMY_TEXLIST);
			njPushMatrix(0);
			v9 = *(float*)&v1->LoopData * 0.5;
			vs.z = 0.0;
			vs.x = 0.0;
			vs.y = v9;
			njPushMatrix(_nj_unit_matrix_);
			v10 = v1->Rotation.z;
			if (v10)
			{
				njRotateZ(0, (unsigned __int16)v10);
			}
			v11 = v1->Rotation.x;
			if (v11)
			{
				njRotateX(0, (unsigned __int16)v11);
			}
			if (v1->Rotation.y)
			{
				njRotateY(0, (unsigned __int16)-LOWORD(v1->Rotation.y));
			}
			njCalcVector(0, &vs, &a2);
			njPopMatrix(1u);
			a2.x = a2.x + v1->Position.x;
			a2.y = a2.y + v1->Position.y;
			a2.z = a2.z + v1->Position.z;
			njTranslateV(0, &a2);
			v12 = v1->Rotation.z;
			if (v12)
			{
				njRotateZ(0, (unsigned __int16)v12);
			}
			v13 = v1->Rotation.x;
			if (v13)
			{
				njRotateX(0, (unsigned __int16)v13);
			}
			if (v1->Rotation.y != 0x8000)
			{
				njRotateY(0, (unsigned __int16)(-32768 - LOWORD(v1->Rotation.y)));
			}
			njPushMatrix(nullptr);
			SetupWorldMatrix();
			Direct3D_SetChunkModelRenderState();
			NJS_ACTION act2 = *AmyAnimData[(unsigned __int16)v1->InvulnerableTime].Animation;
			act2.object = modelmap2[act2.object];
			njCnkAction_Queue(&act2, *(float*)&v1->CharIndex, (QueuedModelFlagsB)0);
			Direct3D_UnsetChunkModelRenderState();
			njPopMatrix(2);
			RestoreConstantAttr();
			ClampGlobalColorThing_Thing();
			Direct3D_PerformLighting(0);
			njControl3D_Restore();
		}
	}
	else
	{
		CheckThingButThenDeleteObject(obj);
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
		for (int i = 0; i < 39; i++)
			if (modelmap.find(i) != modelmap.cend())
				modelmap2[AMY_OBJECTS[i]] = modelmap[i];
		WriteJump(Amy_Display, Amy_Display_r);
		WriteJump((void*)0x486F60, Amy_AfterImage_Main_r);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}