// mod.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include "IniFile.hpp"
#include "SADXModLoader.h"
#include "ModelInfo.h"
#include "AnimationFile.h"
#include "..\CommonFunctions\CommonFunctions.h"

using std::unordered_map;
using std::vector;
using std::string;

unordered_map<int, NJS_OBJECT*> modelmap;
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

bool chestjiggle = false;
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
			data2->SpineJiggle = InitJiggle(modelmap[21]->child);
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
NJS_MATRIX flt_1A51A3C, flt_1A519D0, flt_1A51A6C;
short twistamount[8] = {};
void NodeCallback(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[2] || obj == modelmap[419])
	{
		if (EntityData1Ptrs[currentplayer]->Action == 2)
			njRotateX(v1, twistamount[currentplayer]);
	}
	else if (obj == modelmap[23])
		memcpy(flt_1A51A3C, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[11])
		memcpy(flt_1A519D0, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[12])
		memcpy(flt_1A51A6C, v1, sizeof(NJS_MATRIX));
}

void NodeCallback2(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[2] || obj == modelmap[419])
	{
		if (EntityData1Ptrs[currentplayer]->Action == 2)
			njRotateX(v1, twistamount[currentplayer]);
	}
	else if (obj == modelmap[3])
	{
		if (jiggledata[currentplayer] && jiggledata[currentplayer]->SpineJiggle)
		{
			NJS_VECTOR v = { 0, 0, 0 };
			njCalcPoint(v1, &v, &jiggledata[currentplayer]->HeadNodePos);
		}
	}
	else if (obj == modelmap[15])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[0]);
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[6]);
	}
	else if (obj == modelmap[16])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[1]);
		v.z = -1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[7]);
	}
}

void(__cdecl** NodeCallbackFuncPtr)(NJS_OBJECT* obj) = (decltype(NodeCallbackFuncPtr))0x3AB9908;
void DrawSonicModel(CharObj2* a2, int animNum, NJS_ACTION* action, JiggleData* jiggle)
{
	njPushMatrix(nullptr);
	SetupWorldMatrix();
	Direct3D_SetChunkModelRenderState();
	NJS_OBJECT* v16 = nullptr;
	NJS_CNK_MODEL* v55 = nullptr;
	NJS_OBJECT* v24 = nullptr;
	NJS_CNK_MODEL* v25 = nullptr;
	NJS_OBJECT* v23 = nullptr;
	NJS_CNK_MODEL* v39 = nullptr;
	if (jiggle && jiggle->SpineJiggle)
	{
		v16 = modelmap[21]->child;
		v55 = v16->chunkmodel;
		v16->chunkmodel = jiggle->SpineJiggle->SourceModelCopy->chunkmodel;
	}
	*NodeCallbackFuncPtr = NodeCallback;
	if (*(int*)0x3ABD9CC)
	{
		DrawQueueDepthBias = -5952.0;
		njCnkAction_Queue(action, a2->AnimationThing.Frame, QueuedModelFlagsB_EnableZWrite);
		DrawQueueDepthBias = 0.0;
	}
	else
	{
		njCnkAction(action, a2->AnimationThing.Frame);
	}
	*NodeCallbackFuncPtr = nullptr;
	if (jiggle && jiggle->SpineJiggle)
		v16->chunkmodel = v55;
	if (!MetalSonicFlag && animNum != 32)
		if (animNum < 134 || animNum > 145)
		{
			if ((a2->Upgrades & Upgrades_CrystalRing) && modelmap.find(26) != modelmap.cend())
			{
				memcpy(_nj_current_matrix_ptr_, flt_1A51A3C, sizeof(NJS_MATRIX));
				DrawChunkObject(modelmap[26]);
			}
			if ((a2->Upgrades & Upgrades_LightShoes) && modelmap.find(14) != modelmap.cend())
			{
				memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
				DrawChunkObject(modelmap[14]);
				memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
				DrawChunkObject(modelmap[13]);
			}
		}
	Direct3D_UnsetChunkModelRenderState();
	njPopMatrix(1);
	*NodeCallbackFuncPtr = NodeCallback2;
	njPushMatrix(nullptr);
	njNullAction(action, a2->AnimationThing.Frame);
	njPopMatrix(1);
	*NodeCallbackFuncPtr = nullptr;
}

int sub_446960(int result, int a2, __int16 a3)
{
	result = (unsigned __int16)result;
	if ((signed __int16)(result - a3) > a2 || (signed __int16)(result - a3) < -a2)
	{
		if (((short)result - a3) & 0x8000)
		{
			result = (unsigned __int16)(a3 - a2);
		}
		else
		{
			result = (unsigned __int16)(a3 + a2);
		}
	}
	return result;
}

short savedyrot[8][256];
uint8_t savedyrotindex[8] = {};
FunctionPointer(void, sub_4187D0, (EntityData1* a1), 0x4187D0);
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
	NJS_VECTOR a2; // [esp+Ch] [ebp-Ch]

	data2_pp = (EntityData2*)obj->Data2;
	data2 = data2_pp->CharacterData;
	data1 = obj->Data1;
	if (!IsGamePaused())
	{
		savedyrot[data1->CharIndex][savedyrotindex[data1->CharIndex]++] = data1->Rotation.y;
		if (data2->PhysicsData.RollEnd > (double)data2->Speed.x)
			v5 = 0;
		else
		{
			v5 = savedyrot[data1->CharIndex][(uint8_t)(savedyrotindex[data1->CharIndex] - 3)];
			v5 = sub_446960(4 * (signed __int16)(LOWORD(v5) - LOWORD(data1->Rotation.y)), 0x1D00, 0);
		}
		v6 = twistamount[data1->CharIndex];
		unsigned short v7 = (unsigned __int16)(v5 - v6);
		if ((v7 & 0x8000u) != 0)
			v7 = -v7;
		twistamount[data1->CharIndex] = sub_446960(v5, (unsigned int)(unsigned __int16)v7 >> 2, v6);
	}
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
			else if (v4 < 134 || v4 > 145)
				njSetTexture(&SONIC_TEXLIST);
			else
				njSetTexture(&SUPERSONIC_TEXLIST);
			njPushMatrix(0);
			if (*((_DWORD*)data1->field_3C + 16))
				njTranslateV(0, &data1->CollisionInfo->CollisionArray->origin);
			else
				njTranslateV(0, &data1->Position);
			v5 = data1->Rotation.z;
			if (v5)
				njRotateZ(0, (unsigned __int16)v5);
			v6 = data1->Rotation.x;
			if (v6)
				njRotateX(0, (unsigned __int16)v6);
			if (data1->Rotation.y != 0x8000)
				njRotateY(0, (unsigned __int16)(-0x8000 - LOWORD(data1->Rotation.y)));
			if (v4 == 14)
			{
				if (data1->Status & (Status_Unknown1 | Status_Ground))
				{
					a2.x = 0;
					a2.y = -1;
					a2.z = 0;
					njTranslateV(0, &a2);
					njTranslate(0, 0, 5, 0);
					njRotateZ(0, 0x2000);
					njTranslate(0, 0, -5, 0);
					a2.x = 0.69999999f;
					a2.y = 1.1f;
					a2.z = 0.80000001f;
					njScaleV(0, &a2);
				}
			}
			if (*((_DWORD*)data1->field_3C + 16))
				sub_4187D0(data1);
			else
			{
				if (data2->AnimationThing.State == 2)
					DrawSonicModel(data2, v4, data2->AnimationThing.action, jiggledata[data1->CharIndex]);
				else
				{
					if (!MetalSonicFlag && (data1->Status & Status_Ball) && v4 != 145 && (data2->SonicSpinTimer & 0x11))
						v4 = 32;
					DrawSonicModel(data2, v4, data2->AnimationThing.AnimData[v4].Animation, jiggledata[data1->CharIndex]);
				}
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

#define AnimCount 147
AnimData_t SonicAnimList[AnimCount];
AnimData_t MetalAnimList[AnimCount];
int loc_49AB51 = 0x49AB51;
__declspec(naked) void SetAnimList()
{
	__asm
	{
		mov eax, [MetalSonicFlag]
		mov al, [eax]
		test al, al
		jnz metal
		mov dword ptr[ebp + 140h], offset SonicAnimList
		jmp loc_49AB51
		metal :
		mov dword ptr[ebp + 140h], offset MetalAnimList
			jmp loc_49AB51
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
		string mdlpath = string(path) + "\\system\\sonicmdl\\";
		unordered_map<string, void*> labels;
		if (!FindModels(mdlpath, labels)) return;
		const IniFile* mdlini = new IniFile(mdlpath + "sonicmdl.ini");
		const IniGroup* mdlgrp = mdlini->getGroup("");
		for (auto i = mdlgrp->cbegin(); i != mdlgrp->cend(); ++i)
			modelmap[std::stol(i->first)] = (NJS_OBJECT*)labels[i->second];
		delete mdlini;
		string mtnpath = string(path) + "\\system\\sonicmtn\\";
		ProcessAnimList(SonicAnimList, mtnpath, modelmap);
		mtnpath = string(path) + "\\system\\metalsonicmtn\\";
		ProcessAnimList(MetalAnimList, mtnpath, modelmap);
		WriteJump((void*)0x49AB47, SetAnimList);
		WriteData((short*)0x49ACD8, (short)0x9090);
		WriteJump(Sonic_Display, Sonic_Display_r);
		WriteJump(MetalSonic_AfterImages_Main, MetalSonic_AfterImages_Main_r);
		WriteData<2>((void*)0x4916A5, 0x90u); // disable metal's weird tilting thing
		WriteData((char*)0x49BE22, (char)0xEB);
		WriteJump(Sonic_Jiggle_Main, Sonic_Jiggle_Main_r); // remove this line to disable the jiggle effect
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}