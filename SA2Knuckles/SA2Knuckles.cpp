// SA2Sonic.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include "IniFile.hpp"
#include "SADXModLoader.h"
#include "ModelInfo.h"
#include "AnimationFile.h"

using std::unordered_map;
using std::vector;
using std::string;

FastcallFunctionPointer(void, sub_7917F0, (Sint32* a1, Sint16* a2), 0x7917F0);
void DrawChunkModel(NJS_CNK_MODEL* model)
{
	sub_7917F0(model->vlist, model->plist);
}

void njCnkAction(NJS_ACTION* action, float frame)
{
	DisplayAnimationFrame(action, frame, (QueuedModelFlagsB)0, 0, (void(__cdecl*)(NJS_MODEL_SADX*, int, int))DrawChunkModel);
}

void NullModel(NJS_MODEL_SADX*, int, int)
{

}

void njNullAction(NJS_ACTION* action, float frame)
{
	DisplayAnimationFrame(action, frame, (QueuedModelFlagsB)0, 0, NullModel);
}

namespace models
{
	enum _
	{
		knuckles,
		rouge,
		tikal,
		chaos
	};
}

namespace outfits
{
	enum _
	{
		normal,
		alt,
		dc,
		dcalt,
		hallo,
		xmas,
		rouge,
		amy
	};
}

char modelnum;
char outfitnum;
char currentplayer;
unordered_map<int, NJS_OBJECT*> modelmap;
short twistamount[8] = {};
void NodeCallback(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
}

void(__cdecl** NodeCallbackFuncPtr)(NJS_OBJECT* obj) = (decltype(NodeCallbackFuncPtr))0x3AB9908;
void DrawKnucklesModel(CharObj2* a2, int animNum, NJS_ACTION* action)
{
	njPushMatrix(nullptr);
	// The next three lines help to reduce floating-point rounding errors at large coordinates.
	ProjectToWorldSpace(); // set WorldMatrix to _nj_current_matrix_ptr_ * InverseViewMatrix
	Direct3D_SetWorldTransform(); // set device's world transform to WorldMatrix
	memcpy(_nj_current_matrix_ptr_, &ViewMatrix, sizeof(NJS_MATRIX)); // reset current matrix to ViewMatrix
	Direct3D_SetChunkModelRenderState();
	*NodeCallbackFuncPtr = NodeCallback;
	njCnkAction(action, a2->AnimationThing.Frame);
	*NodeCallbackFuncPtr = nullptr;

	Direct3D_UnsetChunkModelRenderState();
	njPopMatrix(1);
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

#pragma pack(push, 8)
struct __declspec(align(4)) charobj2_arraything
{
	float CollisionRadius;
	NJS_VECTOR PositionOffset;
	NJS_VECTOR njs_vector10;
	NJS_VECTOR njs_vector1C;
	__int16 SomeIndex1;
	short SomeIndex2;
	char gap2C[8];
	_DWORD RotationX;
	_DWORD RotationZ;
	NJS_VECTOR njs_vector3C;
	NJS_VECTOR SurfaceNormal;
	NJS_VECTOR njs_vector54;
	NJS_VECTOR njs_vector60;
	NJS_VECTOR njs_vector6C;
};
#pragma pack(pop)

short savedyrot[8][256];
uint8_t savedyrotindex[8] = {};
FunctionPointer(void, sub_4187D0, (EntityData1* a1), 0x4187D0);
FunctionPointer(void, sub_49F0B0, (EntityData1* a1, struct_a3* a2), 0x49F0B0);
void __cdecl Knuckles_Display_r(ObjectMaster* obj_1)
{
	EntityData1* data1; // esi
	CharObj2* data2; // edi
	signed int v3; // ebx
	int v4; // eax
	_BOOL1 v5; // zf
	double v6; // st7
	Angle v7; // eax
	Angle v8; // eax
	char v9; // al
	charobj2_arraything* v10; // eax
	Angle v11; // eax
	Angle v12; // eax
	int v13; // ebp
	Angle v14; // eax
	long double v15; // st7
	__int16 v16; // ax
	unsigned __int16 v17; // ax
	NJS_VECTOR vd; // [esp+18h] [ebp-18h]
	NJS_VECTOR vs; // [esp+24h] [ebp-Ch]
	EntityData2* data2_pp; // [esp+34h] [ebp+4h]

	data1 = obj_1->Data1;
	data2_pp = (EntityData2*)obj_1->Data2;
	data2 = data2_pp->CharacterData;
	if (!IsGamePaused())
	{
		savedyrot[data1->CharIndex][savedyrotindex[data1->CharIndex]++] = data1->Rotation.y;
		if (data2->PhysicsData.RollEnd > (double)data2->Speed.x)
			v7 = 0;
		else
		{
			v7 = savedyrot[data1->CharIndex][(uint8_t)(savedyrotindex[data1->CharIndex] - 3)];
			v7 = sub_446960(4 * (signed __int16)(LOWORD(v7) - LOWORD(data1->Rotation.y)), 0x1D00, 0);
		}
		v8 = twistamount[data1->CharIndex];
		unsigned short v1 = (unsigned __int16)(v7 - v8);
		if ((v1 & 0x8000u) != 0)
			v1 = -v1;
		twistamount[data1->CharIndex] = sub_446960(v7, (unsigned int)(unsigned __int16)v1 >> 2, v8);
	}
	currentplayer = data1->CharIndex;
	if (IsVisible(&data1->Position, 20.0))
	{
		Direct3D_SetZFunc(1u);
		v3 = (unsigned __int16)data2->AnimationThing.Index;
		if (data2->AnimationThing.State == 2)
		{
			v3 = (unsigned __int16)data2->AnimationThing.LastIndex;
		}
		if (data1->Status & Status_Ball)
		{
			if (!IsGamePaused())
			{
				++*(short*)&data2->field_84;
				v4 = *(char*)&data2->field_84;
				if (data2->AnimationThing.Index == 34)
				{
					v5 = (v4 & 1) == 0;
				}
				else
				{
					v5 = (v4 & 0x11) == 0;
				}
				if (!v5)
				{
					v3 = 16;
				}
			}
		}
		if (!(data1->InvulnerableTime & 2))
		{
			njSetTexture(&KNUCKLES_TEXLIST);
			Direct3D_PerformLighting(2);
			njPushMatrix(0);
			v6 = data2->PhysicsData.CollisionSize * 0.5;
			vs.z = 0.0;
			vs.x = 0.0;
			vs.y = (float)v6;
			njPushMatrix(_nj_unit_matrix_);
			v7 = data1->Rotation.z;
			if (v7)
			{
				njRotateZ(0, (unsigned __int16)v7);
			}
			v8 = data1->Rotation.x;
			if (v8)
			{
				njRotateX(0, (unsigned __int16)v8);
			}
			if (data1->Rotation.y)
			{
				njRotateY(0, (unsigned __int16)-LOWORD(data1->Rotation.y));
			}
			njCalcVector(0, &vs, &vd);
			njPopMatrix(1u);
			v9 = data1->Action;
			v5 = data1->Action == 19;
			vd.x = vd.x + data1->Position.x;
			vd.y = vd.y + data1->Position.y;
			vd.z = vd.z + data1->Position.z;
			if (v5 || v9 == 20)
			{
				v10 = (charobj2_arraything*)data2->array_1x132;
				vd.x = v10->SurfaceNormal.x * *(float*)&data1->LoopData + vd.x;
				vd.y = v10->SurfaceNormal.y * *(float*)&data1->LoopData + vd.y;
				vd.z = v10->SurfaceNormal.z * *(float*)&data1->LoopData + vd.z;
			}
			njTranslateV(0, &vd);
			data1->CollisionInfo->CollisionArray->origin = vd;
			if (v3 == 51)
			{
				v16 = (short)(data2_pp->Forward.y - data1->Rotation.y);
				data2->LightdashTimer = BAMS_SubWrap(data2->LightdashTimer, -v16, 2048);
				if (data1->Rotation.y != 0x8000)
				{
					njRotateY(0, (unsigned __int16)(-32768 - LOWORD(data1->Rotation.y)));
				}
				v17 = data2->LightdashTimer;
				if (v17)
				{
					njRotateX(0, v17);
				}
			}
			else if (v3 == 52)
			{
				v13 = (int)((1.0
					- data2->AnimationThing.Frame
					/ (double)data2->AnimationThing.AnimData[(unsigned __int16)data2->AnimationThing.Index].Animation->motion->nbFrame)
					* (double)data2->LightdashTimer);
				v14 = data1->Rotation.y;
				if (v14 != 0x8000)
				{
					njRotateY(0, (unsigned __int16)(-32768 - v14));
				}
				if (v13)
				{
					njRotateX(0, (unsigned __int16)v13);
				}
				v15 = acos(((charobj2_arraything*)data2->array_1x132)->SurfaceNormal.y) * 65536.0 * -0.1591549762031479;
				if ((unsigned int)(unsigned __int64)v15)
				{
					njRotateZ(0, (unsigned __int16)(unsigned __int64)v15);
				}
			}
			else
			{
				v11 = data1->Rotation.z;
				if (v11)
				{
					njRotateZ(0, (unsigned __int16)v11);
				}
				v12 = data1->Rotation.x;
				if (v12)
				{
					njRotateX(0, (unsigned __int16)v12);
				}
				if (data1->Rotation.y != 0x8000)
				{
					njRotateY(0, (unsigned __int16)(-32768 - LOWORD(data1->Rotation.y)));
				}
				if (v3 == 14)
				{
					if (data1->Status & (Status_Unknown1 | Status_Ground))
					{
						vd.x = 0.0;
						vd.y = -1.0;
						vd.z = 0.0;
						njTranslateV(0, &vd);
						njRotateZ(0, 0x2000);
						vd.x = 0.69999999f;
						vd.y = 1.1f;
						vd.z = 0.80000001f;
						njScaleV(0, &vd);
					}
				}
			}
			if (*((_DWORD*)data1->field_3C + 16))
			{
				sub_4187D0(data1);
			}
			else if (data2->AnimationThing.State == 2)
			{
				DrawKnucklesModel(data2, v3, data2->AnimationThing.action);
			}
			else
			{
				DrawKnucklesModel(data2, v3, data2->AnimationThing.AnimData[v3].Animation);
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
}

#define AnimCount 115
AnimData_t KnucklesAnimList[AnimCount];
extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		if (helperFunctions.Version < 6)
			PrintDebug("The SA2 Knuckles mod requires the mod loader's API version to be at least 6, it is currently %d. Some features will not work.\n", helperFunctions.Version);
		const IniFile* cfgini = new IniFile(string(path) + "\\config.ini");
		string outfit = cfgini->getString("", "Outfit", "Normal");
		string mdlpath = string(path) + "\\system\\knuckmdl\\";
		outfitnum = 0;
		if (!outfit.compare("Alternate"))
			outfitnum = outfits::alt;
		else if (!outfit.compare("Dreamcast"))
			outfitnum = outfits::dc;
		else if (!outfit.compare("Dreamcast Alternate"))
			outfitnum = outfits::dcalt;
		else if (!outfit.compare("Halloween"))
			outfitnum = outfits::hallo;
		else if (!outfit.compare("Christmas"))
			outfitnum = outfits::xmas;
		else if (!outfit.compare("Rouge"))
			outfitnum = outfits::rouge;
		else if (!outfit.compare("Amy"))
			outfitnum = outfits::amy;
		switch (outfitnum)
		{
		case outfits::dc:
		case outfits::dcalt:
		case outfits::hallo:
		case outfits::xmas:
			mdlpath = string(path) + "\\system\\knuckmdl_dc\\";
			break;
		}
		unordered_map<string, void*> labels;
		WIN32_FIND_DATAA data;
		const string srcPathSearch = mdlpath + "*.sa2mdl";
		const HANDLE hFind = FindFirstFileA(srcPathSearch.c_str(), &data);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			// No files found.
			return;
		}

		do
		{
			const string modFile = mdlpath + string(data.cFileName);
			ModelInfo* mdl = new ModelInfo(modFile.c_str());
			auto map = mdl->getlabels();
			for (auto i = map->cbegin(); i != map->cend(); ++i)
				labels[i->first] = i->second;
		} while (FindNextFileA(hFind, &data) != 0);
		FindClose(hFind);
		if (outfitnum != outfits::normal && outfitnum != outfits::dc)
		{
			string mdlpath2;
			switch (outfitnum)
			{
			case outfits::alt:
				mdlpath2 = string(path) + "\\system\\knuckmdl_alt\\";
				break;
			case outfits::dcalt:
				mdlpath2 = string(path) + "\\system\\knuckmdl_dcalt\\";
				break;
			case outfits::hallo:
				mdlpath2 = string(path) + "\\system\\knuckmdl_h\\";
				break;
			case outfits::xmas:
				mdlpath2 = string(path) + "\\system\\knuckmdl_x\\";
				break;
			case outfits::rouge:
				mdlpath2 = string(path) + "\\system\\knuckmdl_rg\\";
				break;
			case outfits::amy:
				mdlpath2 = string(path) + "\\system\\knuckmdl_am\\";
				break;
			}
			const string srcPathSearch = mdlpath2 + "*.sa2mdl";
			const HANDLE hFind = FindFirstFileA(srcPathSearch.c_str(), &data);
			if (hFind == INVALID_HANDLE_VALUE)
			{
				// No files found.
				return;
			}

			do
			{
				const string modFile = mdlpath2 + string(data.cFileName);
				ModelInfo* mdl = new ModelInfo(modFile.c_str());
				auto map = mdl->getlabels();
				for (auto i = map->cbegin(); i != map->cend(); ++i)
					labels[i->first] = i->second;
			} while (FindNextFileA(hFind, &data) != 0);
			FindClose(hFind);
		}
		const IniFile* mdlini = new IniFile(mdlpath + "knuckmdl.ini");
		const IniGroup* mdlgrp = mdlini->getGroup("");
		for (auto i = mdlgrp->cbegin(); i != mdlgrp->cend(); ++i)
			modelmap[std::stol(i->first)] = (NJS_OBJECT*)labels[i->second];
		delete mdlini;
		string mtnpath;
		const string mdlset = cfgini->getString("", "Model", "Knuckles");
		if (!mdlset.compare("Rouge"))
		{
			modelnum = models::rouge;
			mtnpath = string(path) + "\\system\\rougemtn\\";
			if (helperFunctions.Version >= 6)
			{
				switch (outfitnum)
				{
				case outfits::alt:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\rouge_alt.pvm");
					break;
				case outfits::dcalt:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\rouge_dcalt.pvm");
					break;
				case outfits::hallo:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\rouge_h.pvm");
					break;
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\rouge_x.pvm");
					break;
				case outfits::amy:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\rouge_am.pvm");
					break;
				default:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\rouge.pvm");
					break;
				}
			}
		}
		else if (!mdlset.compare("Tikal"))
		{
			modelnum = models::tikal;
			mtnpath = string(path) + "\\system\\tikalmtn\\";
			if (helperFunctions.Version >= 6)
			{
				switch (outfitnum)
				{
				case outfits::dc:
				case outfits::dcalt:
				case outfits::hallo:
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\ktikal_dc.pvm");
					break;
				case outfits::rouge:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\ktikal_rg.pvm");
					break;
				default:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\ktikal.pvm");
					break;
				}
			}
		}
		else if (!mdlset.compare("Chaos"))
		{
			modelnum = models::chaos;
			mtnpath = string(path) + "\\system\\chaos0mtn\\";
			if (helperFunctions.Version >= 6)
			{
				switch (outfitnum)
				{
				case outfits::dc:
				case outfits::dcalt:
				case outfits::hallo:
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\kchaos0_dc.pvm");
					break;
				case outfits::rouge:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\kchaos0_rg.pvm");
					break;
				default:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\kchaos0.pvm");
					break;
				}
			}
		}
		else
		{
			modelnum = models::knuckles;
			mtnpath = string(path) + "\\system\\knuckmtn\\";
			if (helperFunctions.Version >= 6)
			{
				switch (outfitnum)
				{
				case outfits::alt:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\knuck_alt.pvm");
					break;
				case outfits::dcalt:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\knuck_dcalt.pvm");
					break;
				case outfits::hallo:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\knuck_h.pvm");
					break;
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\knuck_x.pvm");
					break;
				case outfits::rouge:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\knuck_rg.pvm");
					break;
				case outfits::amy:
					helperFunctions.ReplaceFile("system\\knuckles.pvm", "system\\knuck_am.pvm");
					break;
				}
			}
		}
		delete cfgini;
		IniFile* mtnini = new IniFile(mtnpath + "Animation List.ini");
		char idxbuf[4];
		for (int i = 0; i < AnimCount; i++)
		{
			sprintf_s(idxbuf, "%d", i);
			if (mtnini->hasGroup(idxbuf))
			{
				const IniGroup* grp = mtnini->getGroup(idxbuf);
				AnimationFile* mtn = new AnimationFile(mtnpath + grp->getString("Animation") + ".saanim");
				KnucklesAnimList[i].Animation = new NJS_ACTION();
				KnucklesAnimList[i].Animation->object = modelmap[grp->getInt("Model")];
				KnucklesAnimList[i].Animation->motion = mtn->getmotion();
				KnucklesAnimList[i].Instance = (char)mtn->getmodelcount();
				KnucklesAnimList[i].Property = (char)grp->getInt("Property");
				if (KnucklesAnimList[i].Property >= 5) --KnucklesAnimList[i].Property;
				KnucklesAnimList[i].NextAnim = (short)grp->getInt("NextAnimation");
				KnucklesAnimList[i].TransitionSpeed = grp->getFloat("TransitionSpeed");
				KnucklesAnimList[i].AnimationSpeed = grp->getFloat("AnimationSpeed");
			}
			else
				KnucklesAnimList[i] = KnucklesAnimList[0];
		}
		delete mtnini;
		WriteData((AnimData_t**)0x47A874, KnucklesAnimList);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}