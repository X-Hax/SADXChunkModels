// SA2Sonic.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "IniFile.hpp"
#include "SADXModLoader.h"
#include "ModelInfo.h"
#include "AnimationFile.h"
#include "..\CommonFunctions\CommonFunctions.h"
#include "..\CommonFunctions\CommonSADX.h"

using std::unordered_map;
using std::vector;
using std::string;

namespace models
{
	enum _
	{
		sonic,
		shadow,
		amy
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
		trial,
		rouge,
		amy
	};
}

char modelnum;
char outfitnum;
unordered_map<int, NJS_OBJECT*> modelmap;
struct JiggleData
{
	JiggleInfo* SpineJiggle;
	NJS_VECTOR SpineJigglePos;
	NJS_VECTOR HeadNodePos;
	JiggleInfo* TorsoJiggle;
	JiggleInfo* TorsoJiggle2;
	NJS_VECTOR TorsoJigglePos;
	NJS_VECTOR TorsoNodePos;
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
	if (data2->TorsoJiggle)
	{
		FreeJiggle(data2->TorsoJiggle);
		data2->TorsoJiggle = nullptr;
	}
	if (data2->TorsoJiggle2)
	{
		FreeJiggle(data2->TorsoJiggle2);
		data2->TorsoJiggle2 = nullptr;
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
		if (MetalSonicFlag)
		{
			if (chestjiggle)
			{
				data2->TorsoJiggle2 = InitJiggle(modelmap[420]->child->child);
				data2->TorsoJiggle2->type = 14;
				data2->TorsoJiggle2->speed = 0.40000001;
				data2->TorsoJiggle2->field_8 = 12288;
				data2->TorsoJiggle2->field_10 = 1024;
				data2->TorsoJiggle2->Model = modelmap[420]->child->child;
				data2->TorsoJiggle = InitJiggle(modelmap[420]->child);
				data2->TorsoJiggle->type = 13;
				data2->TorsoJiggle->speed = 0.40000001;
				data2->TorsoJiggle->field_8 = 12288;
				data2->TorsoJiggle->field_10 = 1024;
				data2->TorsoJiggle->Model = modelmap[420]->child;
				data2->TorsoJigglePos = pd1->Position;
			}
		}
		else
			switch (modelnum)
			{
			case models::sonic:
				data2->SpineJiggle = InitJiggle(modelmap[21]->child);
				data2->SpineJiggle->type = 18;
				data2->SpineJiggle->speed = 0.40000001f;
				data2->SpineJiggle->field_8 = 0;
				data2->SpineJiggle->field_10 = 1024;
				data2->SpineJiggle->Model = 0;
				data2->SpineJigglePos = pd1->Position;
				if (chestjiggle)
				{
					data2->TorsoJiggle2 = InitJiggle(modelmap[2]->child->child);
					data2->TorsoJiggle2->type = 14;
					data2->TorsoJiggle2->speed = 0.40000001;
					data2->TorsoJiggle2->field_8 = 12288;
					data2->TorsoJiggle2->field_10 = 1024;
					data2->TorsoJiggle2->Model = modelmap[2]->child->child;
					data2->TorsoJiggle = InitJiggle(modelmap[2]->child);
					data2->TorsoJiggle->type = 13;
					data2->TorsoJiggle->speed = 0.40000001;
					data2->TorsoJiggle->field_8 = 12288;
					data2->TorsoJiggle->field_10 = 1024;
					data2->TorsoJiggle->Model = modelmap[2]->child;
					data2->TorsoJigglePos = pd1->Position;
				}
				break;
			case models::shadow:
				data2->SpineJiggle = InitJiggle(modelmap[86]->child);
				data2->SpineJiggle->type = 19;
				data2->SpineJiggle->speed = 0.40000001f;
				data2->SpineJiggle->field_8 = 0;
				data2->SpineJiggle->field_10 = 1024;
				data2->SpineJiggle->Model = 0;
				data2->SpineJigglePos = pd1->Position;
				if (chestjiggle)
				{
					data2->TorsoJiggle2 = InitJiggle(modelmap[67]->child->child);
					data2->TorsoJiggle2->type = 14;
					data2->TorsoJiggle2->speed = 0.40000001;
					data2->TorsoJiggle2->field_8 = 12288;
					data2->TorsoJiggle2->field_10 = 1024;
					data2->TorsoJiggle2->Model = modelmap[67]->child->child;
					data2->TorsoJiggle = InitJiggle(modelmap[67]->child);
					data2->TorsoJiggle->type = 13;
					data2->TorsoJiggle->speed = 0.40000001;
					data2->TorsoJiggle->field_8 = 12288;
					data2->TorsoJiggle->field_10 = 1024;
					data2->TorsoJiggle->Model = modelmap[67]->child;
					data2->TorsoJigglePos = pd1->Position;
				}
				break;
			case models::amy:
				data2->SpineJiggle = InitJiggle(modelmap[414]->child);
				data2->SpineJiggle->type = 18;
				data2->SpineJiggle->speed = 0.40000001f;
				data2->SpineJiggle->field_8 = 0;
				data2->SpineJiggle->field_10 = 1024;
				data2->SpineJiggle->Model = 0;
				data2->SpineJigglePos = pd1->Position;
				if (chestjiggle)
				{
					data2->TorsoJiggle2 = InitJiggle(modelmap[397]->child->child);
					data2->TorsoJiggle2->type = 14;
					data2->TorsoJiggle2->speed = 0.40000001;
					data2->TorsoJiggle2->field_8 = 12288;
					data2->TorsoJiggle2->field_10 = 1024;
					data2->TorsoJiggle2->Model = modelmap[397]->child->child;
					data2->TorsoJiggle = InitJiggle(modelmap[397]->child);
					data2->TorsoJiggle->type = 13;
					data2->TorsoJiggle->speed = 0.40000001;
					data2->TorsoJiggle->field_8 = 12288;
					data2->TorsoJiggle->field_10 = 1024;
					data2->TorsoJiggle->Model = modelmap[397]->child;
					data2->TorsoJigglePos = pd1->Position;
				}
				break;
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
			if (modelnum != models::shadow)
			{
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
			else
			{
				float v95 = data2->HeadNodePos.y;
				float v96 = data2->HeadNodePos.z;
				NJS_VECTOR v117;
				v117.x = data2->HeadNodePos.x;
				float v97 = v117.x - data2->SpineJigglePos.x;
				v117.x = v97;
				v117.y = v95 - data2->SpineJigglePos.y;
				v117.z = v96 - data2->SpineJigglePos.z;
				float v98 = njScalor(&v117);
				float v99 = data2->HeadNodePos.x;
				float v100 = data2->HeadNodePos.y;
				float v101 = data2->HeadNodePos.z;
				float v116 = v98 * 0.2000000029802322f;
				data2->SpineJigglePos.x = v99;
				float v102 = v116;
				data2->SpineJigglePos.y = v100;
				data2->SpineJigglePos.z = v101;
				JiggleInfo* v103 = data2->SpineJiggle;
				v116 = fabs(v102);
				float v104 = v116;
				v116 = fabs(v103->speed);
				float v107;
				if (v116 >= v104)
				{
					v107 = v104;
				}
				else
				{
					float v105 = v104;
					float v106 = v102;
					v107 = v105;
					v103->speed = v106;
				}
				if (v107 < 0.63999999)
				{
					if (v107 > 0.4000000059604645)
					{
						data2->SpineJiggle->field_C = 0x4000;
					}
				}
				else
				{
					data2->SpineJiggle->field_C = (signed int)(v115 * 4096.0
						+ 6144.0
						+ (double)data2->SpineJiggle->field_C);
				}
				ApplyJiggle(data2->SpineJiggle);
			}
		}
		if (data2->TorsoJiggle)
		{
			float v46 = data2->TorsoNodePos.y;
			float v47 = data2->TorsoNodePos.z;
			NJS_VECTOR v115;
			v115.x = data2->TorsoNodePos.x;
			float v48 = v115.x - data2->TorsoJigglePos.x;
			v115.y = v46;
			v115.z = v47;
			v115.x = v48;
			v115.y = v46 - data2->TorsoJigglePos.y;
			v115.z = v47 - data2->TorsoJigglePos.z;
			float v113 = njScalor(&v115);
			if (ControllerPointers[data1->CharIndex]->HeldButtons & Buttons_Z)
				v113 = 5;
			float v49 = data2->TorsoNodePos.y;
			float v45 = v113;
			float v50 = data2->TorsoNodePos.z;
			data2->TorsoJigglePos.x = data2->TorsoNodePos.x;
			JiggleInfo* v44 = data2->TorsoJiggle2;
			data2->TorsoJigglePos.y = v49;
			data2->TorsoJigglePos.z = v50;
			if (v44)
			{
				float v51 = fabs(v45);
				float v52 = v51;
				float v53 = fabs(v44->speed);
				if (v53 < v52)
				{
					v44->speed = v113;
				}
				ApplyJiggle(data2->TorsoJiggle2);
				v45 = v113;
			}
			JiggleInfo* v54 = data2->TorsoJiggle;
			float v55 = fabs(v45);
			float v56 = v55;
			float v57 = fabs(v54->speed);
			if (v57 < v56)
			{
				v54->speed = v45;
			}
			ApplyJiggle(data2->TorsoJiggle);
		}
		break;
	}
}

char currentplayer;
NJS_MATRIX flt_1A51A3C, flt_1A51AA0, flt_1A519D0, flt_1A51A6C, flt_1A51A00, flt_1A51994, flt_1A51ADC, sonicheadmatrix;
short twistamount[8] = {};
void NodeCallback(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[2] || obj == modelmap[67] || obj == modelmap[397] || obj == modelmap[419])
	{
		if (EntityData1Ptrs[currentplayer]->Action == 2)
			njRotateX(v1, twistamount[currentplayer]);
	}
	else if (obj == modelmap[23] || obj == modelmap[88])
		memcpy(flt_1A51A3C, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[24] || obj == modelmap[89])
		memcpy(flt_1A51AA0, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[11] || obj == modelmap[76])
		memcpy(flt_1A519D0, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[12] || obj == modelmap[77])
		memcpy(flt_1A51A6C, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[74])
		memcpy(flt_1A51ADC, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[75])
		memcpy(flt_1A51994, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[21] || obj == modelmap[349])
		memcpy(sonicheadmatrix, v1, sizeof(NJS_MATRIX));
}

NJS_MATRIX posmatrix;
void NodeCallback2(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[2] || obj == modelmap[67] || obj == modelmap[397])
	{
		if (EntityData1Ptrs[currentplayer]->Action == 2)
			njRotateX(v1, twistamount[currentplayer]);
	}
	else if (obj == modelmap[3] || obj == modelmap[68] || obj == modelmap[398])
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
	else if (obj == modelmap[1] || obj == modelmap[66] || obj == modelmap[396])
	{
		if (jiggledata[currentplayer] && jiggledata[currentplayer]->TorsoJiggle)
		{
			NJS_VECTOR v = { 0, 0, 0 };
			NJS_MATRIX m;
			njSetMatrix(m, v1);
			njMultiMatrix(m, posmatrix);
			njCalcPoint(m, &v, &jiggledata[currentplayer]->TorsoNodePos);
		}
	}
	else if (obj == modelmap[419])
	{
		if (EntityData1Ptrs[currentplayer]->Action == 2)
			njRotateX(v1, twistamount[currentplayer]);
		if (jiggledata[currentplayer] && jiggledata[currentplayer]->TorsoJiggle)
		{
			NJS_VECTOR v = { 0, 0, 0 };
			NJS_MATRIX m;
			njSetMatrix(m, v1);
			njMultiMatrix(m, posmatrix);
			njCalcPoint(m, &v, &jiggledata[currentplayer]->TorsoNodePos);
		}
	}
	else if (obj == modelmap[15])
	{
		NJS_VECTOR v = { 0, -1.5, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[0]); //right hand pos
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[6]);  //right hand vec
		CharObj2Ptrs[currentplayer]->SoManyVectors[0].y = CharObj2Ptrs[currentplayer]->SoManyVectors[0].y - 8;
	}
	else if (obj == modelmap[16])
	{
		NJS_VECTOR v = { 0, -1.5, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[1]); //left hand pos
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[7]); //left hand vec
		CharObj2Ptrs[currentplayer]->SoManyVectors[7].y = CharObj2Ptrs[currentplayer]->SoManyVectors[7].y - 8;
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
	if (jiggle)
	{
		if (jiggle->SpineJiggle)
		{
			switch (modelnum)
			{
			case models::sonic:
				v16 = modelmap[21]->child;
				break;
			case models::shadow:
				v16 = modelmap[86]->child;
				break;
			case models::amy:
				v16 = modelmap[414]->child;
				break;
			}
			v55 = v16->chunkmodel;
			v16->chunkmodel = jiggle->SpineJiggle->SourceModelCopy->chunkmodel;
		}
		if (jiggle->TorsoJiggle)
		{
			if (MetalSonicFlag)
				v24 = modelmap[420]->child;
			else
				switch (modelnum)
				{
				case models::sonic:
					v24 = modelmap[2]->child;
					break;
				case models::shadow:
					v24 = modelmap[67]->child;
					break;
				case models::amy:
					v24 = modelmap[397]->child;
					break;
				}
			v25 = v24->chunkmodel;
			v24->chunkmodel = jiggle->TorsoJiggle->SourceModelCopy->chunkmodel;
		}
		if (jiggle->TorsoJiggle2)
		{
			if (MetalSonicFlag)
				v23 = modelmap[420]->child->child;
			else
				switch (modelnum)
				{
				case models::sonic:
					v23 = modelmap[2]->child->child;
					break;
				case models::shadow:
					v23 = modelmap[67]->child->child;
					break;
				case models::amy:
					v23 = modelmap[397]->child->child;
					break;
				}
			v39 = v23->chunkmodel;
			v23->chunkmodel = jiggle->TorsoJiggle2->SourceModelCopy->chunkmodel;
		}
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
	if (jiggle)
	{
		if (jiggle->SpineJiggle)
			v16->chunkmodel = v55;
		if (jiggle->TorsoJiggle)
			v24->chunkmodel = v25;
		if (jiggle->TorsoJiggle2)
			v23->chunkmodel = v39;
	}
	if (!MetalSonicFlag && animNum != 32)
		switch (modelnum)
		{
		case models::sonic:
			if (animNum < 134 || animNum > 145)
			{
				switch (outfitnum)
				{
				case outfits::normal:
				case outfits::dc:
				case outfits::trial:
				case outfits::rouge:
				case outfits::amy:
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
					break;
				case outfits::dcalt:
					if (modelmap.find(394) != modelmap.cend())
					{
						memcpy(_nj_current_matrix_ptr_, sonicheadmatrix, sizeof(NJS_MATRIX));
						DrawChunkObject(modelmap[394]);
					}
					break;
				}
			}
			else if (outfitnum == outfits::dcalt && modelmap.find(394) != modelmap.cend())
			{
				memcpy(_nj_current_matrix_ptr_, sonicheadmatrix, sizeof(NJS_MATRIX));
				DrawChunkObject(modelmap[394]);
			}
			break;
		case models::shadow:
			if (animNum < 134 || animNum > 145)
			{
				switch (outfitnum)
				{
				case outfits::normal:
				case outfits::dc:
				case outfits::trial:
				case outfits::rouge:
				case outfits::amy:
					if ((a2->Upgrades & Upgrades_LightShoes) && modelmap.find(79) != modelmap.cend())
					{
						memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
						DrawChunkObject(modelmap[79]);
						memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
						DrawChunkObject(modelmap[78]);
					}
					break;
				}
			}
			if (modelmap.find(92) != modelmap.cend() && (animNum == 11 || animNum == 12 || animNum == 13))
			{
				NJS_OBJECT* v4 = modelmap[92];
				if (!(FrameCounterUnpaused & 1))
					v4 = modelmap[93];
				memcpy(_nj_current_matrix_ptr_, flt_1A51994, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v4, 0, QueuedModelFlagsB_EnableZWrite);
				NJS_OBJECT* v5 = modelmap[96];
				if (!(FrameCounterUnpaused & 1))
					v5 = modelmap[97];
				memcpy(_nj_current_matrix_ptr_, flt_1A51ADC, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v5, 0, QueuedModelFlagsB_EnableZWrite);
				NJS_OBJECT* v6 = modelmap[94];
				if (!(FrameCounterUnpaused & 1))
					v6 = modelmap[95];
				memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v6, 0, QueuedModelFlagsB_EnableZWrite);
				NJS_OBJECT* v7 = modelmap[98];
				if (!(FrameCounterUnpaused & 1))
					v7 = modelmap[99];
				memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v7, 0, QueuedModelFlagsB_EnableZWrite);
			}
			break;
		}
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

void CnkDrawSonic_Queue(NJS_ACTION* anim, float frame, QueuedModelFlagsB flg) {

	njPushMatrix(nullptr);
	SetupWorldMatrix();
	Direct3D_SetChunkModelRenderState();
	NJS_OBJECT* v16 = nullptr;
	NJS_CNK_MODEL* v55 = nullptr;
	NJS_OBJECT* v24 = nullptr;
	NJS_CNK_MODEL* v25 = nullptr;
	NJS_OBJECT* v23 = nullptr;
	NJS_CNK_MODEL* v39 = nullptr;

	*NodeCallbackFuncPtr = NodeCallback;
	DrawQueueDepthBias = -5952.0;
	njCnkAction_Queue(anim, frame, QueuedModelFlagsB_EnableZWrite);
	DrawQueueDepthBias = 0.0;
	*NodeCallbackFuncPtr = nullptr;

	if (!MetalSonicFlag)
		switch (modelnum)
		{
		case models::sonic:

			switch (outfitnum)
			{
			case outfits::dcalt:
				if (modelmap.find(394) != modelmap.cend())
				{
					memcpy(_nj_current_matrix_ptr_, sonicheadmatrix, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[394]);
				}
				break;
			}
			break;
		case models::shadow:


			if (modelmap.find(92) != modelmap.cend())
			{
				NJS_OBJECT* v4 = modelmap[92];
				if (!(FrameCounterUnpaused & 1))
					v4 = modelmap[93];
				memcpy(_nj_current_matrix_ptr_, flt_1A51994, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v4, 0, QueuedModelFlagsB_EnableZWrite);
				NJS_OBJECT* v5 = modelmap[96];
				if (!(FrameCounterUnpaused & 1))
					v5 = modelmap[97];
				memcpy(_nj_current_matrix_ptr_, flt_1A51ADC, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v5, 0, QueuedModelFlagsB_EnableZWrite);
				NJS_OBJECT* v6 = modelmap[94];
				if (!(FrameCounterUnpaused & 1))
					v6 = modelmap[95];
				memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v6, 0, QueuedModelFlagsB_EnableZWrite);
				NJS_OBJECT* v7 = modelmap[98];
				if (!(FrameCounterUnpaused & 1))
					v7 = modelmap[99];
				memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
				DrawModelCallback_Queue(DrawTransformedChunkObject, v7, 0, QueuedModelFlagsB_EnableZWrite);
			}
			break;
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
	obj* v9; // eax
	_BOOL1 v10; // zf
	int i; // edi
	double v12; // st7
	NJS_MOTION* v13; // edx
	float v14; // ecx
	int v15; // edx
	double v16; // st7
	double v17; // st7
	int j; // eax
	NJS_ACTION* v19; // [esp-4h] [ebp-44h]
	int v20; // [esp+0h] [ebp-40h]
	int v21; // [esp+0h] [ebp-40h]
	float v22; // [esp+0h] [ebp-40h]
	char v23; // [esp+1Bh] [ebp-25h]
	float v24; // [esp+1Ch] [ebp-24h]
	float timer; // [esp+1Ch] [ebp-24h]
	float frame; // [esp+20h] [ebp-20h]
	EVENT_ACTION_LIST* actionOldList; // [esp+24h] [ebp-1Ch]
	NJS_ACTION_LINK* v28[2]; // [esp+28h] [ebp-18h] BYREF
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

	if (!IsIngame())
	{
		data1->pos.y -= 5.5f; //fix wrong pos on CharSel Screen
	}

	actionMode = actionList->mode;
	frame = (float)actionList->action.motion->nbFrame;
	v24 = event->action.timer;
	texlist = actionList->texlist;
	unsigned __int8 flag = ((unsigned __int8)actionList->mode >> 4) & 0xD;
	QueueModelFlag = (QueuedModelFlagsB)flag;
	v23 = actionList->mode;
	if (texlist)
	{
		njSetTexture(texlist);
		actionMode = v23;
	}
	if (light >= 0 && (actionMode & 0x20) == 0)
	{
		Direct3D_PerformLighting(light);
		actionMode = v23;
	}
	if (actionOld && actionList->linkframe)
	{
		v9 = (obj*)actionList->action.object;
		v28[1] = (NJS_ACTION_LINK*)&a3;
		v30 = actionList->action.motion;
		v10 = (actionOld->mode & 1) == 0;
		v28[0] = (NJS_ACTION_LINK*)v9;
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
		while (data1 != (taskwk*)EntityData1Ptrs[i])
		{
			if (++i >= 8)
			{
				goto OutOfRange;
			}
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
		actionMode = v23;
	OutOfRange:
		v16 = v24 + 1.0;
		v15 = (unsigned __int8)actionList->linkframe + 1;
		if ((actionMode & 8) != 0)
		{
			*(float*)&v20 = v16 / (double)v15;
			late_ActionLinkMesh((NJS_ACTION_LINK*)v28, v20, (unsigned __int8)QueueModelFlag);
		}
		else
		{
			*(float*)&v21 = v16 / (double)v15;
			if ((actionMode & 4) != 0)
			{
				late_ActionLink((NJS_ACTION_LINK*)v28, v21, (unsigned __int8)QueueModelFlag);
			}
			else
			{
				njCnkActionLinkEX((NJS_ACTION_LINK*)v28, v21, (unsigned __int8)QueueModelFlag);
				//late_ActionLinkEx((NJS_ACTION_LINK*)v28, v21, (unsigned __int8)QueueModelFlag);// used at the very end on charsel screen, otherwise cutscene
			}
		}
		v17 = (double)MissedFrames_B + v24;
		timer = v17;
		if ((double)(unsigned __int8)actionList->linkframe > floor(v17))
		{
			goto LABEL_46;
		}
		FreeMemory(actionOldList);
		event->action.old = 0;
		goto LABEL_45;
	}
	j = 0;
	while (data1 != (taskwk*)EntityData1Ptrs[j])
	{
		if (++j >= 8)
		{
			goto OutOfRange_Again;
		}
	}
	EPJoinVertexes(j, actionList->action.object, actionList->action.motion, event->action.timer);
	actionMode = v23;
OutOfRange_Again:
	v22 = event->action.timer;
	if ((actionMode & 8) != 0)
	{

		late_ActionMesh(&actionList->action, v22, QueueModelFlag);
	}
	else
	{
		v19 = &actionList->action;
		if ((actionMode & 4) != 0)
		{
			njAction_Queue(v19, v22, QueueModelFlag);
		}
		else
		{
			CnkDrawSonic_Queue(v19, v22, QueueModelFlag);
			//late_ActionEx(v19, v22, QueueModelFlag); //charsel
		}
	}
	timer = (double)MissedFrames_B * actionList->speed + v24;
	if ((actionList->mode & 1) != 0)
	{
		if (timer < (double)frame)
		{
		LABEL_46:
			if (light >= 0 && (v23 & 0x20) == 0)
			{
				Direct3D_PerformLighting(0);
			}
			event->action.timer = timer;
			return;
		}
		if (!actionList->next)
		{
			timer = timer - frame;
			goto LABEL_46;
		}
	}
	else if (frame - 1.0 > timer)
	{
		goto LABEL_46;
	}
	event->action.old = actionList;
	event->action.list = actionList->next;
LABEL_45:
	timer = 0.0;
	goto LABEL_46;


}

short savedyrot[8][256];
uint8_t savedyrotindex[8] = {};
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
			else if (modelnum == models::amy || v4 < 134 || v4 > 145)
				njSetTexture(&SONIC_TEXLIST);
			else
				njSetTexture(&SUPERSONIC_TEXLIST);
			memcpy(posmatrix, &IdentityMatrix, sizeof(NJS_MATRIX));
			if (*((_DWORD*)data1->field_3C + 16))
				njTranslateV(posmatrix, &data1->CollisionInfo->CollisionArray->center);
			else
				njTranslateV(posmatrix, &data1->Position);
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
				if (data1->Status & (Status_OnColli | Status_Ground))
				{
					a2.x = 0;
					a2.y = -1;
					a2.z = 0;
					njTranslateV(posmatrix, &a2);
					njTranslate(posmatrix, 0, 5, 0);
					njRotateZ(posmatrix, 0x2000);
					njTranslate(posmatrix, 0, -5, 0);
					a2.x = 0.69999999f;
					a2.y = 1.1f;
					a2.z = 0.80000001f;
					njScaleV(posmatrix, &a2);
				}
			}
			njPushMatrix(nullptr);
			njMultiMatrix(nullptr, posmatrix);
			if (*((_DWORD*)data1->field_3C + 16)) {

				if (!IsIngame())
					DrawEventAction_r((taskwk*)data1, dspl);
				else
					DrawEventAction(data1);
			}
			else
			{
				NJS_ACTION* action;
				if (data2->AnimationThing.State == 2)
					action = data2->AnimationThing.action;
				else
				{
					if (!MetalSonicFlag && (data1->Status & Status_Ball) && v4 != 145 && (data2->SonicSpinTimer & 0x11))
						v4 = 32;
					action = data2->AnimationThing.AnimData[v4].Animation;
				}
				DrawSonicModel(data2, v4, action, jiggledata[data1->CharIndex]);
				*NodeCallbackFuncPtr = NodeCallback2;
				njPushMatrix(_nj_unit_matrix_);
				njNullAction(action, data2->AnimationThing.Frame);
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


DataArray(NJS_ACTION*, SonicCharSelAnim, 0x3C5FF94, 4);

void InitSonicCharSelAnims_r() {
	SonicCharSelAnim[0] = SonicAnimList[11].Animation;
	SonicCharSelAnim[1] = SonicAnimList[75].Animation;
	SonicCharSelAnim[2] = SonicAnimList[76].Animation;
	SonicCharSelAnim[3] = 0;
}

void ResizeTexlist_(NJS_TEXLIST* texlist, uint32_t count)
{
#ifndef NDEBUG
	PrintDebug("SA2Sonic: debug detected, resizing texlist");
	return ResizeTextureList(texlist, count);
#endif
}

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{

		if (helperFunctions.Version < 6)
			PrintDebug("The SA2 Sonic mod requires the mod loader's API version to be at least 6, it is currently %d. Some features will not work.\n", helperFunctions.Version);
		
		const IniFile* cfgini = new IniFile(string(path) + "\\config.ini");
		string outfit = cfgini->getString("", "Outfit", "Normal");
		string mdlpath = string(path) + "\\system\\sonicmdl\\";
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
		else if (!outfit.compare("Trial"))
			outfitnum = outfits::trial;
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
		case outfits::trial:
			mdlpath = string(path) + "\\system\\sonicmdl_dc\\";
			break;
		}
		unordered_map<string, void*> labels;
		if (!FindModels(mdlpath, labels)) return;
		if (outfitnum != outfits::normal && outfitnum != outfits::dc)
		{
			string mdlpath2;
			switch (outfitnum)
			{
			case outfits::alt:
				mdlpath2 = string(path) + "\\system\\sonicmdl_alt\\";
				break;
			case outfits::dcalt:
				mdlpath2 = string(path) + "\\system\\sonicmdl_pso\\";
				break;
			case outfits::hallo:
				mdlpath2 = string(path) + "\\system\\sonicmdl_h\\";
				break;
			case outfits::xmas:
				mdlpath2 = string(path) + "\\system\\sonicmdl_x\\";
				break;
			case outfits::trial:
				mdlpath2 = string(path) + "\\system\\sonicmdl_trial\\";
				break;
			case outfits::rouge:
				mdlpath2 = string(path) + "\\system\\sonicmdl_rg\\";
				break;
			case outfits::amy:
				mdlpath2 = string(path) + "\\system\\sonicmdl_am\\";
				break;
			}
			FindModels(mdlpath2, labels);
		}
		const IniFile* mdlini = new IniFile(mdlpath + "sonicmdl.ini");
		const IniGroup* mdlgrp = mdlini->getGroup("");
		for (auto i = mdlgrp->cbegin(); i != mdlgrp->cend(); ++i)
			modelmap[std::stol(i->first)] = (NJS_OBJECT*)labels[i->second];
		delete mdlini;
		string mtnpath;
		const string mdlset = cfgini->getString("", "Model", "Sonic");
		if (!mdlset.compare("Shadow"))
		{
			modelnum = models::shadow;
			mtnpath = string(path) + "\\system\\teriosmtn\\";
			if (helperFunctions.Version >= 6)
			{
				switch (outfitnum)
				{
				case outfits::alt:
					ResizeTexlist_(&SONIC_TEXLIST, 9);
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios_alt.pvm");
					break;
				case outfits::dcalt:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios_pso.pvm");
					break;
				case outfits::hallo:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios_h.pvm");
					break;
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios_x.pvm");
					break;
				case outfits::rouge:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios_rg.pvm");
					break;
				case outfits::amy:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios_am.pvm");
					break;
				default:
					ResizeTexlist_(&SONIC_TEXLIST, 10);
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios.pvm");
					break;
				}
				helperFunctions.ReplaceFile("system\\son_eff.pvm", "system\\sh_eff.pvm");
				switch (outfitnum)
				{
				case outfits::dc:
				case outfits::trial:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\sshadow_dc.pvm");
					break;
				case outfits::alt:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\sshadow_alt.pvm");
					break;
				case outfits::dcalt:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\sshadow_pso.pvm");
					break;
				case outfits::hallo:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\sshadow_h.pvm");
					break;
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\sshadow_x.pvm");
					break;
				default:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\sshadow.pvm");
					break;
				}
			}
		}
		else if (!mdlset.compare("Amy"))
		{
			modelnum = models::amy;
			mtnpath = string(path) + "\\system\\amymtn\\";
			if (helperFunctions.Version >= 6)
			{
				switch (outfitnum)
				{
				case outfits::dc:
				case outfits::dcalt:
				case outfits::hallo:
				case outfits::xmas:
				case outfits::trial:
					ResizeTexlist_(&SONIC_TEXLIST, 10);
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\samy_dc.pvm");
					break;
				case outfits::rouge:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\samy_rg.pvm");
					break;
				default:
					ResizeTexlist_(&SONIC_TEXLIST, 10);
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\samy.pvm");
					break;
				}
				helperFunctions.ReplaceFile("system\\son_eff.pvm", "system\\samy_eff.pvm");
			}
		}
		else
		{
			modelnum = models::sonic;
			mtnpath = string(path) + "\\system\\sonicmtn\\";
			if (helperFunctions.Version >= 6)
			{
				switch (outfitnum)
				{
				case outfits::alt:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\sonic_alt.pvm");
					ResizeTexlist_(&SONIC_TEXLIST, 7);
					break;
				case outfits::dcalt:
					ResizeTexlist_(&SONIC_TEXLIST, 8);
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\sonic_pso.pvm");
					break;
				case outfits::hallo:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\sonic_h.pvm");
					break;
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\sonic_x.pvm");
					break;
				case outfits::trial:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\sonic_trial.pvm");
					break;
				case outfits::rouge:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\sonic_rg.pvm");
					break;
				case outfits::amy:
					helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\sonic_am.pvm");
					break;
				default:
					ResizeTexlist_(&SONIC_TEXLIST, 11);
					break;
				}
				switch (outfitnum)
				{
				case outfits::alt:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\supersonic_alt.pvm");
					break;
				case outfits::dcalt:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\supersonic_pso.pvm");
					break;
				case outfits::hallo:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\supersonic_h.pvm");
					break;
				case outfits::xmas:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\supersonic_x.pvm");
					break;
				case outfits::trial:
					helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\supersonic_trial.pvm");
					break;
				}
			}
		}
		if (helperFunctions.Version >= 6)
		{
			switch (outfitnum)
			{
			case outfits::dc:
			case outfits::dcalt:
			case outfits::hallo:
			case outfits::xmas:
			case outfits::trial:
				helperFunctions.ReplaceFile("system\\metalsonic.pvm", "system\\metalsonic_dc.pvm");
				break;
			case outfits::rouge:
				helperFunctions.ReplaceFile("system\\metalsonic.pvm", "system\\metalsonic_rg.pvm");
				break;
			}
		}
		chestjiggle = cfgini->getBool("", "EnableChestJiggle");
		delete cfgini;


		ProcessAnimList(SonicAnimList, mtnpath, modelmap);
		mtnpath = string(path) + "\\system\\metalsonicmtn\\";
		ProcessAnimList(MetalAnimList, mtnpath, modelmap);
		WriteJump((void*)0x49AB47, SetAnimList);
		WriteData((short*)0x49ACD8, (short)0x9090);
		WriteJump(Sonic_Display, Sonic_Display_r);
		WriteJump(MetalSonic_AfterImages_Main, MetalSonic_AfterImages_Main_r);
		WriteData<2>((void*)0x4916A5, 0x90u); // disable metal's weird tilting thing
		WriteData((char*)0x49BE22, (char)0xEB);
		WriteJump(Sonic_Jiggle_Main, Sonic_Jiggle_Main_r);
		WriteJump(InitSonicCharSelAnims, InitSonicCharSelAnims_r);
		FixSonicDropThrowObject();
		SonicObjectAnimAdjust();

	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}