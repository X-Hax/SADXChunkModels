#include "pch.h"
#include "framework.h"
#include "CommonFunctions.h"

float flt_173CEF8[]{
	0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 3, 0, 0, 4, 0, 0, 5, 0, 0, 6, 0,
	0, 7, 0, 0, 8, 0, 0, 9, 0, 0, 10, 0, 4, 0, -2, 0, 0, -1, 0, 0,
	3, 0, 0, 6, 0, 0, 9, 0, 0, 11, 0, 0, 13, 0, 0, 15, 0, 0, 17, 0,
	0, 19, 0, 0, 20, 0, -0.000099999997f, -0.80000001f, 0.17f, 0.001f, 0.029999999f, 12
};
JiggleInfo* __cdecl InitJiggle(NJS_OBJECT* arg0)
{
	__int16 v1; // si
	Sint32* v2; // eax
	int i; // edx
	__int16 v4; // di
	int v5; // ecx
	int v6; // edx
	int* v12; // eax
	NJS_CNK_MODEL* v15; // eax
	NJS_OBJECT* v19; // eax
	JiggleInfo* v23; // eax

	v2 = arg0->chunkmodel->vlist;
	v1 = 0;
	for (i = 0; *v2 != 255; v1 += v4)
	{
		v4 = *((short*)v2 + 3);
		v5 = 4 * (*((unsigned __int16*)v2 + 1) + 1);
		v2 = (Sint32*)((char*)v2 + v5);
		i += v5;
	}
	v6 = i + 4;
	v12 = new int[v6 / 4];
	if (v12 == nullptr)
	{
		return nullptr;
	}
	v15 = new NJS_CNK_MODEL();
	if (v15 == nullptr)
	{
		delete[] v12;
		return nullptr;
	}
	v19 = new NJS_OBJECT();
	if (v19 == nullptr)
	{
		delete v15;
		delete[] v12;
		return nullptr;
	}
	v23 = new JiggleInfo();
	v23 = v23;
	if (v23 == nullptr)
	{
		delete v19;
		delete v15;
		delete[] v12;
		return nullptr;
	}
	v23->field_2 = v1;
	v23->SourceModelCopy = v19;
	v23->speed = 0.89999998;
	v23->field_8 = 4096;
	v23->field_C = 0;
	v23->field_10 = 1024;
	v23->SourceModelPtr = arg0;
	memcpy(v23->field_34, flt_173CEF8, sizeof(v23->field_34));
	v23->field_B8 = 0;
	v23->field_BC = 0;
	v23->field_C0 = 0;
	v23->field_C4 = 0;
	v23->field_C8 = 0;
	v23->field_CC = 0;
	v23->field_D0 = 0;
	v23->field_D4 = 0;
	v23->field_D8 = 0;
	v23->field_DC = 0;
	v23->field_E0 = 0;
	v23->field_E4 = 0;
	v23->field_E8 = 0;
	v23->field_EC = 0;
	v23->field_F0 = 0;
	v23->field_F4 = 0;
	v23->field_F8 = 0;
	v23->field_FC = 0;
	v23->field_100 = 0;
	v23->field_104 = 0;
	v23->field_108 = 0;
	v23->field_10C = 0;
	v23->field_110 = 0;
	v23->field_114 = 0;
	v23->field_118 = 0;
	v23->field_11C = 0;
	v23->field_120 = 0;
	v23->field_124 = 0;
	v23->field_128 = 0;
	v23->field_12C = 0;
	v23->field_130 = 0;
	v23->field_134 = 0;
	v23->field_138 = 0;
	*v19 = *arg0;
	*v15 = *arg0->chunkmodel;
	v19->chunkmodel = v15;
	memcpy(v12, arg0->chunkmodel->vlist, 4 * ((v6 + 3) >> 2));
	v15->vlist = v12;
	return v23;
}

void FreeJiggle(JiggleInfo* a1)
{
	if (a1)
	{
		if (a1->SourceModelCopy)
		{
			if (a1->SourceModelCopy->chunkmodel)
			{
				if (a1->SourceModelCopy->chunkmodel->vlist)
				{
					delete[] a1->SourceModelCopy->chunkmodel->vlist;
					a1->SourceModelCopy->chunkmodel->vlist = nullptr;
				}
				delete a1->SourceModelCopy->chunkmodel;
				a1->SourceModelCopy->chunkmodel = nullptr;
			}
			delete a1->SourceModelCopy;
			a1->SourceModelCopy = nullptr;
		}
		delete a1;
	}
}

void ApplyJiggle_5(JiggleInfo* a1, float* a2, float* a3, float a4)
{
	float* v4; // ebx
	double v5; // st7
	int v6; // ecx
	signed int v7; // edi
	double v8; // st7
	double v9; // st7
	double v10; // st5
	double v11; // st6
	double v12; // st5
	double v13; // st4
	double v14; // st3
	double v15; // st3
	double v16; // rt2
	double v17; // st3
	double v18; // rt0
	double v19; // st2
	double v20; // st7
	double v21; // st5
	signed int v22; // esi
	double v23; // st7
	int v24; // esi
	double v25; // st7
	double v26; // st6
	double v27; // st5
	double v28; // st7
	double v29; // st6
	double v30; // st5
	double v31; // rtt
	double v32; // st5
	double v33; // rt0
	_BOOL1 v34; // zf
	signed int v35; // esi
	double v36; // st7
	double v37; // st6
	double v38; // st5
	float v39; // [esp+10h] [ebp-38h]
	float v40; // [esp+10h] [ebp-38h]
	float v41; // [esp+10h] [ebp-38h]
	float v42; // [esp+14h] [ebp-34h]
	float v43; // [esp+14h] [ebp-34h]
	float v44; // [esp+14h] [ebp-34h]
	float v45; // [esp+18h] [ebp-30h]
	float v46; // [esp+1Ch] [ebp-2Ch]
	float v47; // [esp+1Ch] [ebp-2Ch]
	float v48; // [esp+20h] [ebp-28h]
	float v49; // [esp+20h] [ebp-28h]
	float v50; // [esp+20h] [ebp-28h]
	float v51; // [esp+2Ch] [ebp-1Ch]
	float v52; // [esp+30h] [ebp-18h]
	float v53; // [esp+34h] [ebp-14h]
	float v54; // [esp+34h] [ebp-14h]
	signed int v55; // [esp+38h] [ebp-10h]
	float v56; // [esp+3Ch] [ebp-Ch]
	int v57; // [esp+40h] [ebp-8h]
	float v58; // [esp+44h] [ebp-4h]

	v4 = a2;
	v5 = a1->SourceModelCopy->chunkmodel->r;
	v6 = a1->field_C;
	v53 = v5 + v5;
	v7 = (unsigned __int16)(v6 + a1->field_8);
	v55 = (unsigned __int16)(v6 + a1->field_8);
	a1->field_C = v6 + a1->field_10;
	if (v7 >= 0x8000)
	{
		v8 = (double)(v7 - 0x8000);
	}
	else
	{
		v8 = (double)v55;
	}
	v57 = a1->field_2;
	v45 = v8 * v53 * 0.000030517578125;
	v9 = v45;
	v52 = v53 - v45;
	v10 = 1.0 - a4;
	v54 = v45 * 3.141592025756836 * 0.5 * a4 + v45 * v10;
	v56 = a4 * (0.5 * (3.141592025756836 * v52)) + v10 * v52;
	if (a1->field_2)
	{
		v11 = v54;
		v12 = v56;
		v13 = 0.0;
		v14 = 0.0;
		while (1)
		{
			v51 = *a3;
			v48 = a3[1];
			a3 += 6;
			v58 = *(a3 - 4);
			v19 = v48;
			if (v48 < v13)
			{
				v20 = v14;
				v39 = v13;
				v21 = v13;
				v42 = v48;
				goto LABEL_16;
			}
			if (v11 + v14 <= v19)
			{
				if (v13 != v12)
				{
					v35 = 0x10000 - (signed int)((v19 - v11 - v14) / v12 * 32768.0);
					v41 = njSin(v35) * a4 * v52 * 0.5;
					v44 = v45 - (njCos(v35) - 1.0) * v52 * 0.5 + 0.0;
					v50 = njSin((0x4000 - v35) >> 1);
					v47 = njCos((0x4000 - v35) >> 1);
					if (v55 >= 0x8000)
					{
						v41 = -v41;
						v36 = v47;
						v37 = v47 * v51 + v47 * v51;
						v38 = v44 - v50 * v37;
					}
					else
					{
						v36 = v47;
						v37 = v47 * v51 + v47 * v51;
						v38 = v50 * v37 + v44;
					}
					v7 = v55;
					v42 = v38;
					v39 = v41 - v37 * v36;
					v28 = v54;
					v29 = 0.0;
					v30 = 0.0;
					goto LABEL_15;
				}
				v42 = v9 + v48 - v11;
				v21 = v13;
				v20 = v14;
				v39 = v13;
			}
			else
			{
				v20 = v14;
				if (v13 != v11)
				{
					v22 = (signed int)((v19 - v14) / v11 * 32768.0);
					v40 = njSin(v22) * a4 * v45 * 0.5;
					v23 = njCos(v22);
					v24 = (v22 + 0x4000) >> 1;
					v43 = 0.0 - (v23 - 1.0) * v45 * 0.5;
					v49 = njSin(v24);
					v46 = njCos(v24);
					if (v7 >= 0x8000)
					{
						v40 = -v40;
						v25 = v46;
						v26 = v46 * v51 + v46 * v51;
						v27 = v49 * v26 + v43;
					}
					else
					{
						v25 = v46;
						v26 = v46 * v51 + v46 * v51;
						v27 = v43 - v49 * v26;
					}
					v42 = v27;
					v39 = v40 - v26 * v25;
					v28 = v54;
					v29 = 0.0;
					v30 = 0.0;
				LABEL_15:
					v31 = v30;
					v32 = v28;
					v20 = v31;
					v33 = v32;
					v21 = v29;
					v11 = v33;
					goto LABEL_16;
				}
				v21 = v13;
				v42 = v48;
				v39 = v13;
			}
		LABEL_16:
			v4 += 6;
			v34 = v57-- == 1;
			*(v4 - 6) = v39 * 0.800000011920929 + v51;
			*(v4 - 5) = v42 * 1.149999976158142;
			*(v4 - 4) = v58;
			if (v34)
			{
				return;
			}
			v15 = v20;
			v9 = v45;
			v16 = v15;
			v17 = v21;
			v12 = v56;
			v18 = v17;
			v14 = v16;
			v13 = v18;
		}
	}
}

float sub_447520(float a1, float a2, float a3)
{
	float v3; // st7
	float v4; // st6
	float v5; // st6
	float v7; // st6
	float v8; // [esp+4h] [ebp+4h]
	float v10; // [esp+4h] [ebp+4h]

	v3 = a1;
	if (a2 >= a1)
	{
		if (a2 <= v3)
		{
			return v3;
		}
		v7 = v3 + a3;
		v3 = a2;
		v10 = v7;
		v5 = v10;
		if (v10 > a2)
		{
			return v3;
		}
	}
	else
	{
		v4 = v3 - a3;
		v3 = a2;
		v8 = v4;
		v5 = v8;
		if (v8 < a2)
		{
			return v3;
		}
	}
	return v5;
}

void ApplyJiggle_6_7_12(JiggleInfo* a1, float* a2, float* a3, char a4)
{
	float* v4; // ecx
	signed int v5; // edx
	signed int v6; // esi
	double v7; // st6
	double v8; // st6
	double v9; // st7
	double v10; // st5
	double v11; // st5
	double v12; // rt1
	double v13; // st6
	double v14; // st7
	float v15; // ST20_4
	double v16; // rt2
	double v17; // st6
	double v18; // st7
	float v19; // ST20_4
	float v20; // ST28_4
	unsigned int v21; // ecx
	float v22; // ST20_4
	double v23; // st7
	float v24; // ST20_4
	double v25; // st7
	double v26; // st6
	float v27; // ST20_4
	float* v28; // ecx
	double v29; // st6
	double v30; // st6
	double v31; // st7
	float* v32; // ecx
	double v33; // st5
	double v34; // rt0
	double v35; // st6
	double v36; // st7
	float v37; // ST20_4
	double v38; // rt1
	double v39; // st6
	double v40; // st7
	float v41; // ST20_4
	unsigned int v42; // ebx
	Float v43; // ecx
	Float v44; // edx
	float v45; // ST2C_4
	double v46; // st7
	float v47; // ST2C_4
	double v48; // st7
	double v49; // st7
	Float v50; // eax
	Float v51; // ecx
	float v54; // ST38_4
	signed int v55; // esi
	float v56; // ST38_4
	signed int v57; // ebx
	float v58; // ST38_4
	double v59; // st6
	float* v60; // eax
	float v61; // [esp+20h] [ebp-2Ch]
	float v62; // [esp+20h] [ebp-2Ch]
	float v63; // [esp+20h] [ebp-2Ch]
	float v64; // [esp+20h] [ebp-2Ch]
	float v65; // [esp+20h] [ebp-2Ch]
	float v66; // [esp+20h] [ebp-2Ch]
	signed int i; // [esp+24h] [ebp-28h]
	int j; // [esp+24h] [ebp-28h]
	float v69; // [esp+28h] [ebp-24h]
	float v70; // [esp+28h] [ebp-24h]
	float v71; // [esp+28h] [ebp-24h]
	float v72; // [esp+28h] [ebp-24h]
	float v73; // [esp+28h] [ebp-24h]
	float v74; // [esp+28h] [ebp-24h]
	float v75; // [esp+2Ch] [ebp-20h]
	float v76; // [esp+2Ch] [ebp-20h]
	float v77; // [esp+30h] [ebp-1Ch]
	float v78; // [esp+30h] [ebp-1Ch]
	float v79; // [esp+30h] [ebp-1Ch]
	float v80; // [esp+30h] [ebp-1Ch]
	float v81; // [esp+30h] [ebp-1Ch]
	float v82; // [esp+30h] [ebp-1Ch]
	signed int v83; // [esp+34h] [ebp-18h]
	float v84; // [esp+34h] [ebp-18h]
	float v85; // [esp+34h] [ebp-18h]
	NJS_VECTOR v86; // [esp+3Ch] [ebp-10h]

	v83 = 0;
	if (njScalor(&a1->field_24) <= 0.001)
	{
		v4 = &a1->field_DC;
		v61 = 0.0;
		v5 = 3;
		do
		{
			v77 = fabs(*(v4 - 3));
			if (v77 > (double)v61)
			{
				v61 = v77;
			}
			v78 = fabs(*v4);
			if (v78 > (double)v61)
			{
				v61 = v78;
			}
			v79 = fabs(v4[3]);
			if (v79 > (double)v61)
			{
				v61 = v79;
			}
			v4 += 9;
			--v5;
		} while (v5);
		if (v61 < 4.0)
		{
			v83 = 1;
		}
	}
	v6 = 1;
	for (i = 1; ; v6 = i)
	{
		v75 = (double)i;
		v80 = pow(0.9399999976158142, v75);
		if (njScalor(&a1->field_24) > 0.02999999932944775)
		{
			*((float*)& a1->field_B8 + 3 * v6) = a1->field_24.y;
			*((float*)& a1->field_BC + 3 * v6) = a1->field_24.x;
			*((float*)& a1->type + 3 * v6 + 48) = -a1->field_24.z;
		}
		else if (v6 == 1)
		{
			v69 = a1->field_C4;
			v7 = v69;
			if (v69 <= 0.0)
			{
				if (v7 >= 0.0)
				{
					v62 = v69;
					v8 = 0.0;
					v9 = 0.03500000014901161;
				}
				else
				{
					v62 = v7 + 0.03500000014901161;
					v8 = 0.0;
					v9 = 0.03500000014901161;
					if (v62 > 0.0)
					{
						v62 = 0.0;
					}
				}
			}
			else
			{
				v62 = v7 - 0.03500000014901161;
				v8 = 0.0;
				v9 = 0.03500000014901161;
				if (v62 < 0.0)
				{
					v62 = 0.0;
				}
			}
			a1->field_C4 = v62;
			v70 = a1->field_C8;
			v10 = v70;
			if (v70 <= v8)
			{
				if (v10 >= v8)
				{
					v63 = v70;
				}
				else
				{
					v63 = v10 + v9;
					if (v8 < v63)
					{
						v63 = v8;
					}
				}
			}
			else
			{
				v63 = v10 - v9;
				if (v8 > v63)
				{
					v63 = v8;
				}
			}
			a1->field_C8 = v63;
			v71 = a1->field_CC;
			v11 = v71;
			if (v71 <= v8)
			{
				if (v11 >= v8)
				{
					a1->field_CC = v71;
					goto LABEL_57;
				}
				v16 = v8;
				v17 = v9 + v11;
				v18 = v16;
				v64 = v17;
				if (v16 < v64)
				{
					v19 = v18;
					a1->field_CC = v19;
					goto LABEL_57;
				}
			}
			else
			{
				v12 = v8;
				v13 = v11 - v9;
				v14 = v12;
				v64 = v13;
				if (v12 > v64)
				{
					v15 = v14;
					a1->field_CC = v15;
					goto LABEL_57;
				}
			}
			a1->field_CC = v64;
		}
		else
		{
			v20 = pow(0.5, v75);
			v21 = 12 * v6;
			v72 = v20 * 0.07000000029802322;
			v22 = fabs(a1->field_34[3 * v6]);
			v23 = *(&a1->field_24.y + 3 * v6) - a1->field_34[3 * v6];
			if (v22 <= 12.0)
			{
				v27 = v23;
				v25 = sub_447520(*(float*)((char*)& a1->field_B8 + v21), v27, v72);
				v26 = v75 * -0.00009999999747378752;
			}
			else
			{
				v24 = v23;
				v25 = sub_447520(*(float*)((char*)& a1->field_B8 + v21), v24, v72);
				v26 = v75 * -0.800000011920929;
			}
			*(float*)((char*)& a1->field_B8 + v21) = v25 - v26 + a1->field_34[v21 / 4 + 30] * 0.1700000017881393;
			v28 = (float*)((char*)& a1->field_BC + v21);
			v65 = *v28;
			v29 = v65;
			if (v65 <= 0.0)
			{
				if (v29 >= 0.0)
				{
					v30 = 0.0;
					v31 = v72;
				}
				else
				{
					v65 = v29 + v72;
					v30 = 0.0;
					v31 = v72;
					if (v65 > 0.0)
					{
						v65 = 0.0;
					}
				}
			}
			else
			{
				v65 = v29 - v72;
				v30 = 0.0;
				v31 = v72;
				if (v65 < 0.0)
				{
					v65 = 0.0;
				}
			}
			*v28 = v65;
			v32 = (float*)(&a1->type + 4 * (3 * v6 + 48));
			v73 = *v32;
			v33 = v73;
			if (v73 <= v30)
			{
				if (v33 >= v30)
				{
					*v32 = v73;
					goto LABEL_57;
				}
				v38 = v30;
				v39 = v31 + v33;
				v40 = v38;
				v66 = v39;
				if (v38 < v66)
				{
					v41 = v40;
					*v32 = v41;
					goto LABEL_57;
				}
			}
			else
			{
				v34 = v30;
				v35 = v33 - v31;
				v36 = v34;
				v66 = v35;
				if (v34 > v66)
				{
					v37 = v36;
					*v32 = v37;
					goto LABEL_57;
				}
			}
			*v32 = v66;
		}
	LABEL_57:
		v42 = 12 * v6;
		v43 = a1->field_34[3 * v6 + 1];
		v44 = a1->field_34[3 * v6 + 2];
		v86.x = a1->field_34[3 * v6];
		v86.y = v43;
		v86.z = v44;
		if (njScalor(&a1->field_24) > 0.02999999932944775)
		{
			v86.x = *(float*)((char*)& a1->field_B8 + v42) + v86.x;
			v86.y = *(float*)((char*)& a1->field_BC + v42) + v86.y;
			v46 = *((float*)& a1->type + 3 * v6 + 48) + v86.z;
		}
		else if (v6 == 1)
		{
			v45 = pow(1.0, 0.1700000017881393);
			v86.x = v86.x * 0.8999999761581421 + v45 * 0.300000011920929;
			v86.y = v86.y * 1.100000023841858;
			v46 = 0.8999999761581421 * v86.z;
		}
		else
		{
			if (v83)
			{
				v47 = pow(v75, 0.1700000017881393);
				v48 = v47 * 0.300000011920929 * 0.03999999910593033 + v86.x * 0.9599999785423279;
			}
			else
			{
				v48 = *(float*)((char*)& a1->field_B8 + v42) + v86.x;
			}
			v86.x = v48;
			v86.y = *(float*)((char*)& a1->field_BC + v42) + v86.y * 1.100000023841858;
			v46 = *((float*)& a1->type + 3 * v6 + 48) + v86.z * 0.8999999761581421;
		}
		v86.z = v46;
		v81 = v80 * v80;
		v86.x = v86.x - *(Float*)((char*)& a1->field_24.y + v42);
		v86.y = v86.y - *(Float*)((char*)& a1->field_24.z + v42);
		v86.z = v86.z - *(float*)& a1->gap30[v42];
		njUnitVector(&v86);
		v49 = flt_173CEF8[v42 / 4 + 35] - flt_173CEF8[v42 / 4 + 32];
		v86.x = v86.x * v49;
		v86.y = v86.y * v49;
		v86.z = v49 * v86.z;
		if (v81 > (double)v86.y)
		{
			v86.y = v81;
		}
		njUnitVector(&v86);
		v86.x = *(Float*)((char*)& a1->field_24.y + v42) + v86.x;
		v86.y = *(Float*)((char*)& a1->field_24.z + v42) + v86.y;
		v86.z = *(float*)& a1->gap30[v42] + v86.z;
		if (a4 & 2 && a1->speed < (double)v86.x)
		{
			v86.x = a1->speed;
		}
		v50 = v86.y;
		v51 = v86.z;
		a1->field_34[v42 / 4] = v86.x;
		a1->field_34[v42 / 4 + 1] = v50;
		a1->field_34[v42 / 4 + 2] = v51;
		if (++i >= 11)
		{
			break;
		}
	}
	for (j = a1->field_2; j > 0; --j)
	{
		v84 = *a2;
		v76 = a2[1];
		a2 += 6;
		v74 = *(a2 - 4);
		if (v76 < 0.0)
		{
			v76 = 0.0;
		}
		v54 = floor(v76);
		v55 = (signed int)v54;
		v56 = ceil(v76);
		v57 = (signed int)v56;
		v58 = modf(v76, (double*)& v86.x);
		v59 = 1.0 - v58;
		v85 = v58 * a1->field_34[3 * v57] + v84 + a1->field_34[3 * v55] * v59;
		v60 = a3;
		v82 = v58 * a1->field_34[3 * v57 + 1] + v59 * a1->field_34[3 * v55 + 1];
		if (a4 & 1)
		{
			*a3 = v85 * 0.07999999821186066 + *a3 * 0.9200000166893005;
			a3[1] = a3[1] * 0.9200000166893005 + v82 * 0.07999999821186066;
			a3[2] = 0.07999999821186066 * v74 + 0.9200000166893005 * a3[2];
		}
		else
		{
			*a3 = v85;
			a3[1] = v82;
			a3[2] = v74;
			v60 = a3;
		}
		a3 = v60 + 6;
	}
}

void ApplyJiggle_8_9_10(float* a1, JiggleInfo* a2, float* a3, float a4)
{
	double v4; // st7
	int v5; // edx
	double v6; // st6
	double v7; // st5
	float* v8; // eax
	float v9; // ST08_4
	double v10; // st5
	float v11; // ST10_4
	float v12; // ST00_4
	float v13; // ST04_4
	float v14; // ST0C_4
	float a4a; // [esp+18h] [ebp+4h]
	float a4b; // [esp+18h] [ebp+4h]

	v4 = a4;
	++a2->field_C;
	v5 = a2->field_2;
	a4a = 1.0 - a4;
	if (v5)
	{
		v6 = a4a;
		do
		{
			v7 = v4 * a1[1];
			v8 = a1 + 2;
			v9 = v7;
			a3 += 6;
			v10 = *v8;
			a1 = v8 + 4;
			--v5;
			v11 = v10 * v4;
			v12 = *(a3 - 6) * v6;
			v13 = *(a3 - 5) * v6;
			v14 = *(a3 - 4) * v6;
			a4b = *(a1 - 6) * v4;
			*(a1 - 6) = a4b + v12;
			*(a1 - 5) = v13 + v9;
			*(a1 - 4) = v14 + v11;
		} while (v5);
	}
}

void ApplyJiggle_10_11(JiggleInfo* a1, float* a2, float* a3, float a4)
{
	int v4; // ecx
	signed int v5; // ebx
	double v6; // st7
	double v7; // st5
	double v8; // st7
	double v9; // st6
	double v10; // st5
	double v11; // st4
	double v12; // st3
	double v13; // st2
	signed int v14; // esi
	double v15; // st7
	int v16; // esi
	signed int v17; // esi
	double v18; // st7
	double v19; // st6
	double v20; // st5
	_BOOL1 v21; // zf
	float v22; // [esp+8h] [ebp-30h]
	float v23; // [esp+8h] [ebp-30h]
	float v24; // [esp+Ch] [ebp-2Ch]
	float v25; // [esp+Ch] [ebp-2Ch]
	float v26; // [esp+10h] [ebp-28h]
	float v27; // [esp+14h] [ebp-24h]
	float v28; // [esp+18h] [ebp-20h]
	float v29; // [esp+18h] [ebp-20h]
	float v30; // [esp+20h] [ebp-18h]
	float v31; // [esp+24h] [ebp-14h]
	float v32; // [esp+28h] [ebp-10h]
	float v33; // [esp+28h] [ebp-10h]
	signed int v34; // [esp+2Ch] [ebp-Ch]
	int v35; // [esp+2Ch] [ebp-Ch]
	float v36; // [esp+30h] [ebp-8h]
	float v37; // [esp+34h] [ebp-4h]

	v4 = a1->field_C;
	v5 = (unsigned __int16)(v4 + a1->field_8);
	v32 = a1->SourceModelCopy->chunkmodel->r + a1->SourceModelCopy->chunkmodel->r;
	v34 = (unsigned __int16)(v4 + a1->field_8);
	a1->field_C = v4 + 1;
	if (v5 >= 0x8000)
	{
		v6 = (double)(v5 - 0x8000);
	}
	else
	{
		v6 = (double)v34;
	}
	v35 = a1->field_2;
	v26 = v6 * v32 * 0.000030517578125;
	v31 = v32 - v26;
	v7 = 1.0 - a4;
	v33 = v26 * 3.141592025756836 * 0.5 * a4 + v26 * v7;
	v36 = v31 * v7 + a4 * (0.5 * (3.141592025756836 * v31));
	if (a1->field_2)
	{
		v8 = v33;
		v9 = 0.0;
		v10 = 0.0;
		v11 = 0.1000000014901161;
		v12 = 0.8999999761581421;
		while (1)
		{
			v30 = *a2;
			v28 = a2[1];
			a2 += 6;
			v37 = *(a2 - 4);
			v13 = v28;
			if (v28 >= v9)
			{
				break;
			}
			v22 = v9;
			v24 = v28;
		LABEL_20:
			v21 = v35-- == 1;
			a3 += 6;
			*(a3 - 6) = (v22 * 0.800000011920929 + v30) * v11 + *(a3 - 6) * v12;
			*(a3 - 5) = v24 * 1.149999976158142 * v11 + *(a3 - 5) * v12;
			*(a3 - 4) = *(a3 - 4) * v12 + v37 * v11;
			if (v21)
			{
				return;
			}
		}
		if (v8 + v10 <= v13)
		{
			if (v36 == v9)
			{
				v13 = v13 - v8 + v26;
			LABEL_19:
				v24 = v13;
				v22 = v9;
				goto LABEL_20;
			}
			v17 = 0x10000 - (signed int)((v13 - v8 - v10) / v36 * 32768.0);
			v23 = njSin(v17) * a4 * v31 * 0.5;
			v25 = v26 - (njCos(v17) - 1.0) * v31 * 0.5 + 0.0;
			v29 = njSin((0x4000 - v17) >> 1);
			v27 = njCos((0x4000 - v17) >> 1);
			if (v5 < 0x8000)
			{
				goto LABEL_14;
			}
			v23 = -v23;
		}
		else
		{
			if (v9 == v8)
			{
				goto LABEL_19;
			}
			v14 = (signed int)((v13 - v10) / v8 * 32768.0);
			v23 = njSin(v14) * a4 * v26 * 0.5;
			v15 = njCos(v14);
			v16 = (v14 + 0x4000) >> 1;
			v25 = 0.0 - (v15 - 1.0) * v26 * 0.5;
			v29 = njSin(v16);
			v27 = njCos(v16);
			if (v5 >= 0x8000)
			{
				v23 = -v23;
			LABEL_14:
				v18 = v27;
				v19 = v27 * v30 + v27 * v30;
				v20 = v29 * v19 + v25;
			LABEL_17:
				v24 = v20;
				v22 = v23 - v19 * v18;
				v8 = v33;
				v9 = 0.0;
				v10 = 0.0;
				v11 = 0.1000000014901161;
				v12 = 0.8999999761581421;
				goto LABEL_20;
			}
		}
		v18 = v27;
		v19 = v27 * v30 + v27 * v30;
		v20 = v25 - v29 * v19;
		goto LABEL_17;
	}
}

void ApplyJiggle(JiggleInfo* a1)
{
	JiggleInfo* v1; // edi
	NJS_OBJECT* v2; // ebp
	NJS_OBJECT* v3; // eax
	float* v4; // ebx
	float* v5; // esi
	int v6; // ecx
	signed int v7; // ecx
	int v8; // edi
	float v9; // st7
	float v10; // ST40_4
	float v11; // ST4C_4
	float v12; // ST3C_4
	float v13; // ST54_4
	signed int v14; // eax
	signed int v15; // ecx
	int v16; // edi
	float v17; // ST44_4
	float* v18; // ebx
	float v19; // st7
	float v20; // ST4C_4
	float v21; // ST40_4
	float v22; // ST54_4
	signed int v23; // eax
	int v24; // ebp
	int v25; // ebx
	float v26; // st7
	signed int v27; // edi
	int v28; // esi
	float v29; // ST54_4
	float v30; // st7
	float* v31; // esi
	float v32; // st7
	signed int v33; // eax
	signed int v34; // edx
	int v35; // edi
	int v36; // ebx
	float v37; // st7
	int v38; // esi
	float v39; // ST5C_4
	float v40; // st7
	float* v41; // esi
	float v42; // st7
	int v43; // eax
	int v44; // edx
	float v45; // ST64_4
	float v46; // st6
	float v47; // st6
	float v48; // ST64_4
	float v49; // st7
	float v50; // st7
	NJS_CNK_MODEL* v51; // edx
	int* v52; // ecx
	unsigned int v53; // eax
	float v54; // ST64_4
	float v55; // st6
	char v56; // dl
	int* v57; // ecx
	unsigned int v58; // ebp
	unsigned int v59; // eax
	int* v60; // ecx
	signed int v61; // eax
	int v62; // edi
	int v63; // edx
	float v64; // st4
	float v65; // st4
	float v66; // st3
	float v67; // st2
	float v68; // st2
	float v69; // st4
	float v70; // st2
	float v71; // st3
	float v72; // st2
	_BOOL1 v73; // c0
	_BOOL1 v74; // c3
	float v75; // rtt
	float v76; // rt0
	float v77; // ST64_4
	float v78; // ST64_4
	float v79; // ST64_4
	float v80; // ST64_4
	float v81; // ST64_4
	float v82; // ST64_4
	int v83; // edx
	float v84; // ST64_4
	float v85; // st6
	float v86; // st6
	float v87; // ST64_4
	float v88; // st7
	float v89; // st7
	NJS_CNK_MODEL* v90; // ecx
	int* v91; // edx
	unsigned int v92; // eax
	float v93; // ST64_4
	signed int v94; // edi
	float v95; // st5
	char v96; // cl
	int* v97; // edx
	unsigned int v98; // eax
	int* v99; // edx
	signed int v100; // eax
	int v101; // ebp
	int v102; // ecx
	unsigned int v103; // edi
	float v104; // st4
	float* v105; // ebx
	float v106; // st4
	float v107; // st3
	float v108; // st2
	float v109; // st2
	float v110; // st4
	float v111; // ST64_4
	float v112; // ST64_4
	float v113; // ST64_4
	float v114; // st4
	float v115; // st3
	float* v116; // esi
	float v117; // st4
	float* v118; // ebx
	float v119; // st4
	float v120; // st3
	float v121; // st2
	float v122; // st2
	float v123; // st4
	float v124; // ST64_4
	float v125; // ST64_4
	float v126; // ST64_4
	float v127; // st4
	float v128; // st3
	float* v129; // esi
	float v130; // st4
	float* v131; // ebx
	float v132; // st4
	float v133; // st3
	float v134; // st2
	float v135; // st2
	float v136; // st4
	float v137; // ST64_4
	float v138; // ST64_4
	float v139; // ST64_4
	float v140; // st4
	float v141; // st3
	float* v142; // esi
	float v143; // st4
	float v144; // st4
	float v145; // st3
	float v146; // st2
	float v147; // st2
	float v148; // st4
	float v149; // ST64_4
	float v150; // ST64_4
	float v151; // ST64_4
	float v152; // st4
	float v153; // st3
	int v154; // ecx
	float v155; // st4
	float v156; // st4
	float v157; // st3
	float v158; // st2
	float v159; // st2
	float v160; // st4
	float v161; // ST64_4
	float v162; // ST64_4
	float v163; // ST64_4
	float v164; // st4
	float v165; // st3
	signed int v166; // ecx
	float v167; // ST40_4
	float v168; // ST64_4
	float v169; // ST64_4
	float v170; // ST64_4
	signed int v171; // ebp
	float v172; // ST64_4
	float v173; // ST64_4
	float v174; // ST64_4
	float v175; // st7
	int v176; // eax
	int v177; // ecx
	float v178; // st7
	float v179; // st6
	float v180; // st5
	float v181; // st4
	float v182; // st3
	float* v183; // ebx
	float v184; // st2
	float v185; // st2
	float v186; // st1
	float v187; // st3
	float v188; // st1
	float v189; // st2
	float v190; // st0
	float v191; // st3
	float v192; // st2
	float v193; // st3
	float v194; // st2
	float v195; // st0
	float v196; // st2
	float v197; // ST24_4
	float v198; // st3
	float v199; // st2
	float v200; // ST6C_8
	float v201; // st2
	float v202; // st2
	float v203; // rtt
	float v204; // st1
	float* v205; // esi
	float v206; // st1
	NJS_OBJECT* v207; // eax
	float* v208; // ebp
	signed int v209; // ebx
	float v210; // ST64_4
	signed int v211; // ST34_4
	float v212; // ST64_4
	float v213; // ST64_4
	signed int v214; // ST34_4
	float v215; // ST64_4
	float v216; // ST64_4
	signed int v217; // ST34_4
	float v218; // ST64_4
	float v219; // ST64_4
	signed int v220; // ebx
	float v221; // st7
	int v222; // ecx
	float v223; // st7
	float v224; // st6
	float v225; // st5
	float v226; // st4
	float v227; // st3
	float v228; // rt1
	float* v229; // ebp
	float v230; // st2
	float v231; // st2
	float v232; // st1
	float v233; // st2
	float v234; // st4
	float v235; // st2
	float v236; // st2
	float v237; // st2
	float v238; // st0
	float v239; // st4
	float v240; // st2
	float v241; // st4
	float v242; // st2
	float v243; // st0
	float v244; // st4
	float v245; // rt1
	float v246; // st3
	float v247; // st4
	float* v248; // esi
	float v249; // ST20_4
	float v250; // st3
	_BOOL1 v251; // c0
	float v252; // rt1
	float v253; // st1
	float v254; // st2
	float v255; // rt2
	float v256; // st1
	float* v257; // esi
	float v258; // ST20_4
	float v259; // rt1
	signed int v260; // ecx
	float v261; // ST64_4
	float v262; // ST64_4
	float v263; // st7
	float v264; // ST64_4
	float v265; // ST64_4
	signed int v266; // ebp
	float v267; // ST64_4
	float v268; // ST64_4
	float v269; // ST64_4
	float v270; // st7
	int v271; // ecx
	float v272; // ST64_4
	float v273; // st7
	float v274; // st6
	float v275; // st5
	float v276; // st3
	float* v277; // ebx
	float v278; // st2
	float v279; // st2
	float v280; // st1
	float v281; // st3
	float* v282; // esi
	float v283; // rt2
	float v284; // st2
	float v285; // st1
	float v286; // rtt
	float v287; // st1
	float v288; // st2
	float v289; // rt0
	float v290; // st2
	float v291; // st1
	float* v292; // esi
	signed int v293; // ecx
	float v294; // ST40_4
	float v295; // ST64_4
	float v296; // ST64_4
	float v297; // ST64_4
	signed int v298; // ebp
	float v299; // ST64_4
	float v300; // ST64_4
	float v301; // ST64_4
	float v302; // st7
	int v303; // eax
	float v304; // ST64_4
	float v305; // st7
	int v306; // ecx
	float v307; // st7
	float v308; // st6
	float v309; // st5
	float v310; // st4
	float v311; // st3
	float* v312; // ebx
	float v313; // st2
	float v314; // st1
	float v315; // st2
	float v316; // st2
	float v317; // rt1
	float v318; // st5
	float v319; // rtt
	float v320; // st5
	float v321; // rt0
	float v322; // st3
	float v323; // st5
	float* v324; // esi
	float v325; // ST24_4
	float v326; // st3
	float v327; // st2
	float v328; // rtt
	float v329; // rt1
	float v330; // rt1
	float* v331; // esi
	signed int v332; // ecx
	float v333; // ST64_4
	float v334; // ST64_4
	float v335; // ST64_4
	float v336; // ST64_4
	float v337; // st7
	signed int v338; // ebp
	signed int v339; // ST64_4
	float v340; // ST44_4
	float v341; // ST64_4
	float v342; // ST64_4
	float v343; // ST64_4
	float v344; // ST64_4
	float v345; // ST28_4
	float v346; // st6
	float v347; // ST24_4
	float v348; // st7
	int v349; // eax
	float v350; // st5
	int v351; // ecx
	float v352; // st5
	float v353; // st4
	float v354; // st3
	float v355; // st2
	float v356; // st2
	float v357; // rt1
	float* v358; // ebx
	float v359; // st1
	float v360; // st1
	float v361; // st5
	float v362; // st5
	float v363; // st2
	float v364; // st7
	float v365; // rt0
	float v366; // st5
	float v367; // st5
	float v368; // st3
	float v369; // st0
	float v370; // st3
	float v371; // st4
	float* v372; // esi
	float v373; // st1
	float v374; // st3
	float v375; // st7
	float v376; // rt0
	float v377; // rt2
	float v378; // st7
	float v379; // st7
	float v380; // rt0
	float v381; // st2
	float v382; // st1
	float v383; // st2
	float v384; // rt2
	float v385; // rtt
	float v386; // st3
	float v387; // rt0
	float v388; // [esp+18h] [ebp-58h]
	float v389; // [esp+18h] [ebp-58h]
	float v390; // [esp+18h] [ebp-58h]
	float v391; // [esp+18h] [ebp-58h]
	float v392; // [esp+18h] [ebp-58h]
	float v393; // [esp+18h] [ebp-58h]
	float v394; // [esp+18h] [ebp-58h]
	float v395; // [esp+18h] [ebp-58h]
	float v396; // [esp+18h] [ebp-58h]
	float v397; // [esp+18h] [ebp-58h]
	float v398; // [esp+18h] [ebp-58h]
	float v399; // [esp+18h] [ebp-58h]
	float v400; // [esp+18h] [ebp-58h]
	float v401; // [esp+18h] [ebp-58h]
	float v402; // [esp+1Ch] [ebp-54h]
	float v403; // [esp+1Ch] [ebp-54h]
	float v404; // [esp+1Ch] [ebp-54h]
	float v405; // [esp+1Ch] [ebp-54h]
	float v406; // [esp+1Ch] [ebp-54h]
	float v407; // [esp+1Ch] [ebp-54h]
	float v408; // [esp+1Ch] [ebp-54h]
	float v409; // [esp+1Ch] [ebp-54h]
	float v410; // [esp+1Ch] [ebp-54h]
	float v411; // [esp+1Ch] [ebp-54h]
	float v412; // [esp+1Ch] [ebp-54h]
	float v413; // [esp+1Ch] [ebp-54h]
	float v414; // [esp+1Ch] [ebp-54h]
	float v415; // [esp+20h] [ebp-50h]
	float v416; // [esp+20h] [ebp-50h]
	float v417; // [esp+20h] [ebp-50h]
	float v418; // [esp+20h] [ebp-50h]
	float v419; // [esp+20h] [ebp-50h]
	float v420; // [esp+20h] [ebp-50h]
	float v421; // [esp+20h] [ebp-50h]
	float v422; // [esp+24h] [ebp-4Ch]
	float v423; // [esp+24h] [ebp-4Ch]
	float v424; // [esp+24h] [ebp-4Ch]
	float v425; // [esp+28h] [ebp-48h]
	float v426; // [esp+28h] [ebp-48h]
	float v427; // [esp+28h] [ebp-48h]
	float v428; // [esp+28h] [ebp-48h]
	float v429; // [esp+28h] [ebp-48h]
	float v430; // [esp+2Ch] [ebp-44h]
	float v431; // [esp+2Ch] [ebp-44h]
	float v432; // [esp+2Ch] [ebp-44h]
	float v433; // [esp+2Ch] [ebp-44h]
	float v434; // [esp+2Ch] [ebp-44h]
	float v435; // [esp+30h] [ebp-40h]
	float v436; // [esp+30h] [ebp-40h]
	float v437; // [esp+30h] [ebp-40h]
	float v438; // [esp+30h] [ebp-40h]
	float v439; // [esp+30h] [ebp-40h]
	float v440; // [esp+30h] [ebp-40h]
	float v441; // [esp+30h] [ebp-40h]
	float v442; // [esp+30h] [ebp-40h]
	float v443; // [esp+30h] [ebp-40h]
	float v444; // [esp+30h] [ebp-40h]
	float v445; // [esp+30h] [ebp-40h]
	float v446; // [esp+34h] [ebp-3Ch]
	float v447; // [esp+34h] [ebp-3Ch]
	float v448; // [esp+34h] [ebp-3Ch]
	float v449; // [esp+34h] [ebp-3Ch]
	float v450; // [esp+34h] [ebp-3Ch]
	signed int v451; // [esp+38h] [ebp-38h]
	float v452; // [esp+38h] [ebp-38h]
	float v453; // [esp+38h] [ebp-38h]
	float v454; // [esp+38h] [ebp-38h]
	float v455; // [esp+38h] [ebp-38h]
	float v456; // [esp+38h] [ebp-38h]
	float v457; // [esp+38h] [ebp-38h]
	float v458; // [esp+38h] [ebp-38h]
	float v459; // [esp+3Ch] [ebp-34h]
	float v460; // [esp+3Ch] [ebp-34h]
	float v461; // [esp+3Ch] [ebp-34h]
	float v462; // [esp+3Ch] [ebp-34h]
	float v463; // [esp+3Ch] [ebp-34h]
	float v464; // [esp+3Ch] [ebp-34h]
	float v465; // [esp+3Ch] [ebp-34h]
	float v466; // [esp+44h] [ebp-2Ch]
	float v467; // [esp+44h] [ebp-2Ch]
	float v468; // [esp+44h] [ebp-2Ch]
	float v469; // [esp+44h] [ebp-2Ch]
	float v470; // [esp+44h] [ebp-2Ch]
	float v471; // [esp+48h] [ebp-28h]
	float v472; // [esp+48h] [ebp-28h]
	float v473; // [esp+48h] [ebp-28h]
	float v474; // [esp+48h] [ebp-28h]
	float v475; // [esp+48h] [ebp-28h]
	float v476; // [esp+48h] [ebp-28h]
	float v477; // [esp+48h] [ebp-28h]
	float v478; // [esp+48h] [ebp-28h]
	float v479; // [esp+48h] [ebp-28h]
	float v480; // [esp+4Ch] [ebp-24h]
	float v481; // [esp+4Ch] [ebp-24h]
	float v482; // [esp+4Ch] [ebp-24h]
	float v483; // [esp+4Ch] [ebp-24h]
	signed int v484; // [esp+54h] [ebp-1Ch]
	float v485; // [esp+54h] [ebp-1Ch]
	signed int v486; // [esp+54h] [ebp-1Ch]
	float v487; // [esp+54h] [ebp-1Ch]
	signed int v488; // [esp+54h] [ebp-1Ch]
	float v489; // [esp+54h] [ebp-1Ch]
	signed int v490; // [esp+54h] [ebp-1Ch]
	float v491; // [esp+54h] [ebp-1Ch]
	unsigned int v492; // [esp+54h] [ebp-1Ch]
	float v493; // [esp+54h] [ebp-1Ch]
	float v494; // [esp+54h] [ebp-1Ch]
	float v495; // [esp+54h] [ebp-1Ch]
	float v496; // [esp+54h] [ebp-1Ch]
	float v497; // [esp+54h] [ebp-1Ch]
	float a1a; // [esp+5Ch] [ebp-14h]
	float a1b; // [esp+5Ch] [ebp-14h]
	float a1c; // [esp+5Ch] [ebp-14h]
	float a1d; // [esp+5Ch] [ebp-14h]
	float a1e; // [esp+5Ch] [ebp-14h]
	float a1f; // [esp+5Ch] [ebp-14h]
	float a1g; // [esp+5Ch] [ebp-14h]
	float a1h; // [esp+5Ch] [ebp-14h]
	float a1i; // [esp+5Ch] [ebp-14h]
	float a1j; // [esp+5Ch] [ebp-14h]
	float v508; // [esp+64h] [ebp-Ch]
	float v509; // [esp+64h] [ebp-Ch]

	v1 = a1;
	v2 = a1->SourceModelPtr;
	v3 = a1->SourceModelCopy;
	v4 = (float*)(v2->chunkmodel->vlist + 2);
	v5 = (float*)(v3->chunkmodel->vlist + 2);
	switch (v1->type)
	{
	case 0:
		v6 = v1->field_C;
		v471 = v1->speed;
		v1->field_C = v6 + v1->field_10;
		v484 = v6;
		v7 = v1->field_8;
		v459 = v3->chunkmodel->r;
		v8 = v1->field_2;
		if (v8 > 0)
		{
			a1a = v7;
			v485 = v484;
			v9 = v459;
			do
			{
				v10 = *v4;
				v4 += 6;
				v11 = *(v4 - 5) - v9;
				v12 = *(v4 - 4);
				--v8;
				v5 += 6;
				v13 = njSin((signed int)(a1a * v11 + v485)) * (1.0 - v471) + v471;
				*(v5 - 6) = v13 * v10;
				*(v5 - 5) = v13 * v11 + v459;
				v9 = v459;
				*(v5 - 4) = v13 * v12;
			} while (v8 > 0);
		}
		return;
	case 1:
	case 3:
		v486 = v1->field_C;
		v14 = (signed int)(((double)rand() * 0.000030517578125 + 3.0) * (double)v1->field_10 * 0.25
			+ (double)v1->field_C);
		v15 = v1->field_8;
		v472 = v1->speed;
		v1->field_C = v14;
		v16 = v1->field_2;
		if (v16 > 0)
		{
			a1b = v15;
			v487 = v486;
			do
			{
				v17 = *v4;
				v18 = &v4[2];
				v19 = v18[-1];
				v4 = &v18[4];
				v20 = v19;
				v21 = *(v4 - 4);
				--v16;
				v5 += 6;
				v22 = njSin((signed int)(a1b * v20 + v487)) * (1.0 - v472) + v472;
				*(v5 - 6) = v22 * v17;
				*(v5 - 5) = v22 * v20;
				*(v5 - 4) = v22 * v21;
			} while (v16 > 0);
		}
		return;
	case 2:
		v488 = v1->field_C;
		v23 = (signed int)(((double)rand() * 0.000030517578125 + 3.0) * (double)v1->field_10 * 0.25
			+ (double)v1->field_C);
		v24 = v1->field_2;
		v473 = v1->speed;
		v1->field_C = v23;
		if (v24 > 0)
		{
			a1c = (double)v1->field_8;
			v489 = (double)v488;
			do
			{
				v460 = *v4;
				v25 = (int)(v4 + 2);
				v26 = *(float*)(v25 - 4);
				v4 = (float*)(v25 + 16);
				v466 = v26;
				v452 = *(v4 - 4);
				v27 = (signed int)(a1c * v466 + v489);
				v28 = (int)(v5 + 1);
				v29 = njSin(v27) * (1.0 - v473) + v473;
				v30 = v29;
				*(float*)(v28 - 4) = v29 * v460;
				if (v466 >= -3.0)
				{
					v31 = (float*)(v28 + 4);
					*(v31 - 1) = v466 * v30;
					v32 = v30 * v452;
				}
				else
				{
					v31 = (float*)(v28 + 4);
					*(v31 - 1) = v466;
					if (v460 <= 0.0)
					{
						v32 = v452 - njSin(v27);
					}
					else
					{
						v32 = njSin(v27) + v452;
					}
				}
				*v31 = v32;
				--v24;
				v5 = v31 + 4;
			} while (v24 > 0);
		}
		return;
	case 4:
		v490 = v1->field_C;
		v33 = (signed int)(((double)rand() * 0.000030517578125 + 3.0) * (double)v1->field_10 * 0.25
			+ (double)v1->field_C);
		v34 = v1->field_8;
		v474 = v1->speed;
		v1->field_C = v33;
		v35 = v1->field_2;
		if (v35 > 0)
		{
			a1d = (double)v34;
			v453 = (double)v490;
			do
			{
				v480 = *v4;
				v36 = (int)(v4 + 2);
				v37 = *(float*)(v36 - 4);
				v4 = (float*)(v36 + 16);
				v467 = v37;
				v446 = *(v4 - 4);
				v508 = a1d * v467;
				v38 = (int)(v5 + 1);
				v39 = njSin((signed int)(v508 + v453)) * (1.0 - v474) + v474;
				v40 = v39;
				*(float*)(v38 - 4) = v39 * v480;
				if (v467 >= -25.0)
				{
					v41 = (float*)(v38 + 4);
					*(v41 - 1) = v467 * v40;
					v42 = v40 * v446;
				}
				else
				{
					v41 = (float*)(v38 + 4);
					*(v41 - 1) = v467;
					if (v480 <= 0.0)
					{
						v42 = v446 - njSin((signed int)(v453 * 0.5 + v508)) * 5.0;
					}
					else
					{
						v42 = njSin((signed int)(v453 * 0.5 + v508)) * 5.0 + v446;
					}
				}
				*v41 = v42;
				--v35;
				v5 = v41 + 4;
			} while (v35 > 0);
		}
		return;
	case 5:
		ApplyJiggle_5(v1, v5, v4, 1.0);
		v43 = v1->field_C & 0x70000;
		if (v43 > 0x40000)
		{
			switch (v43)
			{
			case 0x50000:
				v1->field_10 = 0x1C0;
				break;
			case 0x60000:
				v1->field_10 = 0x240;
				break;
			case 0x70000:
				v1->field_10 = 0x2A0;
				break;
			}
		}
		else if (v43 == 0x40000)
		{
			v1->field_10 = 0x140;
		}
		else if (v43 > 0x20000)
		{
			if (v43 == 0x30000)
			{
				v1->field_10 = 0x280;
			}
		}
		else if (v43 == 0x20000)
		{
			v1->field_10 = 0x2C0;
		}
		else if (v43)
		{
			if (v43 == 0x10000)
			{
				v1->field_10 = 0x220;
			}
		}
		else
		{
			v1->field_10 = 0x300;
		}
		return;
	case 6:
		ApplyJiggle_6_7_12(v1, v4, v5, 0);
		return;
	case 7:
		ApplyJiggle_6_7_12(v1, v4, v5, 2);
		return;
	case 8:
		ApplyJiggle_8_9_10(v5, v1, (float*)v1->Model->chunkmodel->vlist + 2, 0.89999998f);
		return;
	case 9:
		ApplyJiggle_8_9_10(v5, v1, (float*)(**(_DWORD * *)(*(_DWORD*)v1->gap20 + 4) + 8), 0.5f);
		return;
	case 10:
		ApplyJiggle_8_9_10(v5, v1, v4, 0.89999998f);
	case 11:
		ApplyJiggle_10_11(v1, v4, v5, 1);
		return;
	case 12:
		ApplyJiggle_6_7_12(v1, v4, v5, 1);
		return;
	case 13:
		v44 = v1->field_C;
		v435 = v1->speed;
		v1->field_C = v44 + 1152;
		v45 = fabs(v435);
		v46 = v1->speed;
		if (v45 <= 0.0099999998)
		{
			v47 = v46 * 0.8999999761581421;
		}
		else
		{
			v47 = v46 * 0.9200000166893005;
		}
		v1->speed = v47;
		v48 = fabs(v1->speed);
		if (v48 < 0.00009999999747378752)
		{
			v1->speed = 0.0;
		}
		if (v435 <= 0.8999999761581421)
		{
			if (v435 >= -0.8999999761581421)
			{
				goto LABEL_61;
			}
			v49 = -0.89999998;
		}
		else
		{
			v49 = 0.89999998;
		}
		v435 = v49;
	LABEL_61:
		v50 = njSin(v44 + v1->field_8);
		v51 = v2->chunkmodel;
		v52 = v51->vlist;
		v53 = *v51->vlist;
		if ((char)v53 == -1)
		{
			return;
		}
		v54 = v50 * v435;
		v55 = v54;
		while (1)
		{
			v56 = v53;
			v57 = v52 + 1;
			v58 = v53 >> 16;
			v59 = *v57;
			v60 = v57 + 1;
			v61 = v59 >> 16;
			switch (v56)
			{
			case 41:
				v451 = 6;
				break;
			case 44:
				v451 = 7;
				break;
			case 42:
				v451 = 4;
				break;
			}
			v62 = v61;
			if (v61 > 0)
			{
				break;
			}
		LABEL_98:
			v53 = v60[v58 - 1];
			v52 = &v60[v58 - 1];
			v5 += 2;
			v4 += 2;
			if ((char)v53 == -1)
			{
				return;
			}
		}
		v63 = 4 * v451;
		while (1)
		{
			v491 = *v4;
			a1e = v4[1];
			v64 = v4[2];
			v4 = (float*)((char*)v4 + v63);
			v481 = v64;
			v65 = a1e;
			v66 = v491;
			v67 = v481;
			if (a1e < 0.60000002)
			{
				v68 = a1e;
				v69 = v481;
				if (a1e > 0.4000000059604645 && v66 < 1.0)
				{
					v70 = v491;
					v71 = a1e;
					if (v491 > 0.800000011920929)
					{
						v72 = v481;
						if (v481 >= 0.2000000029802322)
						{
							v70 = v491;
							v69 = v481;
						}
						else
						{
							v73 = v72 < -0.2000000029802322;
							v74 = v72 == -0.2000000029802322;
							v70 = v491;
							v69 = v481;
							if (!((unsigned __int8)v73 | (unsigned __int8)v74))
							{
								*v5 = v491;
							LABEL_96:
								v5[1] = v71;
								goto LABEL_97;
							}
						}
					}
					v75 = v70;
					v68 = a1e;
					v66 = v75;
				}
				v76 = v68;
				v67 = v69;
				v65 = v76;
			}
			if (v65 >= 0.69999999
				|| v65 <= 0.30000001
				|| v66 >= 1.0
				|| v66 <= 0.69999999
				|| v67 >= 0.60000002
				|| v67 <= -0.60000002)
			{
				if (v65 >= 5.0 || v65 <= 0.0 || v66 >= 1.0 || v66 <= -0.60000002 || v67 >= 1.0 || v67 <= -1.0)
				{
					*v5 = v66;
					v71 = v65;
					v69 = v67;
					goto LABEL_96;
				}
				v80 = fabs(v55 * 0.5 * v65);
				*v5 = v66 + v80;
				v81 = fabs(v55 * v65);
				v5[1] = v65 - v81 * 0.1000000014901161;
				v82 = fabs(v55 * 0.2000000029802322);
				v69 = v67 + v82 * v67;
			}
			else
			{
				v77 = fabs(v55 * 0.25 * v65);
				*v5 = v66 + v77;
				v78 = fabs(v55 * v65);
				v5[1] = v65 - v78 * 0.05000000074505806;
				v79 = fabs(v55 * 0.1000000014901161);
				v69 = v67 + v79 * v67;
			}
		LABEL_97:
			v5[2] = v69;
			--v62;
			v5 = (float*)((char*)v5 + v63);
			if (v62 <= 0)
			{
				goto LABEL_98;
			}
		}
	case 14:
		v83 = v1->field_C;
		v436 = v1->speed;
		v1->field_C = v83 + 1152;
		v84 = fabs(v436);
		v85 = v1->speed;
		if (v84 <= 0.0099999998)
		{
			v86 = v85 * 0.8999999761581421;
		}
		else
		{
			v86 = v85 * 0.9200000166893005;
		}
		v1->speed = v86;
		v87 = fabs(v1->speed);
		if (v87 < 0.00009999999747378752)
		{
			v1->speed = 0.0;
		}
		if (v436 <= 0.8999999761581421)
		{
			if (v436 >= -0.8999999761581421)
			{
				goto LABEL_110;
			}
			v88 = -0.89999998;
		}
		else
		{
			v88 = 0.89999998;
		}
		v436 = v88;
	LABEL_110:
		v89 = njSin(v83 + v1->field_8);
		v90 = v2->chunkmodel;
		v91 = v90->vlist;
		v92 = *v90->vlist;
		if ((char)v92 == -1)
		{
			return;
		}
		v94 = *(int*)&v436;
		v93 = v89 * v436;
		v95 = v93;
		while (1)
		{
			v96 = v92;
			v97 = v91 + 1;
			v492 = v92 >> 16;
			v98 = *v97;
			v99 = v97 + 1;
			v100 = v98 >> 16;
			if (v96 == 41)
			{
				break;
			}
			if (v96 == 44)
			{
				v94 = 7;
				goto LABEL_118;
			}
			if (v96 == 42)
			{
				v94 = 4;
				goto LABEL_118;
			}
		LABEL_119:
			v101 = v100;
			if (v100 < 4)
			{
				goto LABEL_159;
			}
			v102 = v94;
			v103 = ((unsigned int)(v100 - 4) >> 2) + 1;
			v101 = v100 - 4 * v103;
			do
			{
				v402 = *v4;
				v415 = v4[1];
				v104 = v4[2];
				v105 = &v4[v102];
				v388 = v104;
				v106 = v415;
				v107 = v402;
				v108 = v388;
				if (v415 < 5.0)
				{
					v109 = v415;
					v110 = v388;
					if (v415 > 0.239999994635582 && v107 < 0.60000002 && v107 > -0.5 && v110 < 1.5 && v110 > -1.5)
					{
						v111 = fabs(v95 * 0.5 * v109);
						*v5 = v107 + v111;
						v112 = fabs(v95 * v109);
						v5[1] = v109 - v112 * 0.1000000014901161;
						v113 = fabs(v95 * 0.2000000029802322);
						v114 = v110 + v113 * v110;
						goto LABEL_130;
					}
					v108 = v388;
					v106 = v415;
				}
				*v5 = v402;
				v115 = v106;
				v114 = v108;
				v5[1] = v115;
			LABEL_130:
				v5[2] = v114;
				v116 = &v5[v102];
				v403 = *v105;
				v416 = v105[1];
				v117 = v105[2];
				v118 = &v105[v102];
				v389 = v117;
				v119 = v416;
				v120 = v403;
				v121 = v389;
				if (v416 < 5.0)
				{
					v122 = v416;
					v123 = v389;
					if (v416 > 0.239999994635582 && v120 < 0.60000002 && v120 > -0.5 && v123 < 1.5 && v123 > -1.5)
					{
						v124 = fabs(v95 * 0.5 * v122);
						*v116 = v120 + v124;
						v125 = fabs(v95 * v122);
						v116[1] = v122 - v125 * 0.1000000014901161;
						v126 = fabs(v95 * 0.2000000029802322);
						v127 = v123 + v126 * v123;
						goto LABEL_139;
					}
					v121 = v389;
					v119 = v416;
				}
				*v116 = v403;
				v128 = v119;
				v127 = v121;
				v116[1] = v128;
			LABEL_139:
				v116[2] = v127;
				v129 = &v116[v102];
				v404 = *v118;
				v417 = v118[1];
				v130 = v118[2];
				v131 = &v118[v102];
				v390 = v130;
				v132 = v417;
				v133 = v404;
				v134 = v390;
				if (v417 < 5.0)
				{
					v135 = v417;
					v136 = v390;
					if (v417 > 0.239999994635582 && v133 < 0.60000002 && v133 > -0.5 && v136 < 1.5 && v136 > -1.5)
					{
						v137 = fabs(v95 * 0.5 * v135);
						*v129 = v133 + v137;
						v138 = fabs(v95 * v135);
						v129[1] = v135 - v138 * 0.1000000014901161;
						v139 = fabs(v95 * 0.2000000029802322);
						v140 = v136 + v139 * v136;
						goto LABEL_148;
					}
					v134 = v390;
					v132 = v417;
				}
				*v129 = v404;
				v141 = v132;
				v140 = v134;
				v129[1] = v141;
			LABEL_148:
				v129[2] = v140;
				v142 = &v129[v102];
				v405 = *v131;
				v418 = v131[1];
				v143 = v131[2];
				v4 = &v131[v102];
				v391 = v143;
				v144 = v418;
				v145 = v405;
				v146 = v391;
				if (v418 < 5.0)
				{
					v147 = v418;
					v148 = v391;
					if (v418 > 0.239999994635582 && v145 < 0.60000002 && v145 > -0.5 && v148 < 1.5 && v148 > -1.5)
					{
						v149 = fabs(v95 * 0.5 * v147);
						*v142 = v145 + v149;
						v150 = fabs(v95 * v147);
						v142[1] = v147 - v150 * 0.1000000014901161;
						v151 = fabs(v95 * 0.2000000029802322);
						v152 = v148 + v151 * v148;
						goto LABEL_157;
					}
					v146 = v391;
					v144 = v418;
				}
				*v142 = v405;
				v153 = v144;
				v152 = v146;
				v142[1] = v153;
			LABEL_157:
				v142[2] = v152;
				v5 = &v142[v102];
				--v103;
			} while (v103);
			v94 = *(int*)&v436;
		LABEL_159:
			if (v101 > 0)
			{
				v154 = 4 * v94;
				while (1)
				{
					v406 = *v4;
					v419 = v4[1];
					v155 = v4[2];
					v4 = (float*)((char*)v4 + v154);
					v392 = v155;
					v156 = v419;
					v157 = v406;
					v158 = v392;
					if (v419 >= 5.0)
					{
						goto LABEL_169;
					}
					v159 = v419;
					v160 = v392;
					if (v419 <= 0.239999994635582
						|| v157 >= 0.60000002
						|| v157 <= -0.5
						|| v160 >= 1.5
						|| v160 <= -1.5)
					{
						break;
					}
					v161 = fabs(v95 * 0.5 * v159);
					*v5 = v157 + v161;
					v162 = fabs(v95 * v159);
					v5[1] = v159 - v162 * 0.1000000014901161;
					v163 = fabs(v95 * 0.2000000029802322);
					v164 = v160 + v163 * v160;
				LABEL_170:
					v5[2] = v164;
					--v101;
					v5 = (float*)((char*)v5 + v154);
					if (v101 <= 0)
					{
						goto LABEL_171;
					}
				}
				v158 = v392;
				v156 = v419;
			LABEL_169:
				*v5 = v406;
				v165 = v156;
				v164 = v158;
				v5[1] = v165;
				goto LABEL_170;
			}
		LABEL_171:
			v91 = &v99[v492 - 1];
			v92 = *v91;
			v5 += 2;
			v4 += 2;
			if ((unsigned __int8)* v91 == -1)
			{
				return;
			}
		}
		v94 = 6;
	LABEL_118:
		v436 = *(float*)& v94;
		goto LABEL_119;
	case 15:
		v166 = v1->field_C;
		v437 = v1->speed;
		v1->field_C = v166 + 1024;
		v167 = v437 * 0.9900000095367432;
		v1->speed = v167;
		v168 = fabs(v167);
		if (v168 < 0.001)
		{
			v1->speed = 0.0;
		}
		if (v437 <= 1.4)
		{
			if (v437 < -1.4)
			{
				v437 = -1.4;
			}
		}
		else
		{
			v437 = 1.4;
		}
		v169 = njSin(v166) * v437;
		v170 = atan(v169 / 1.5);
		v171 = (signed int)(v170 * 10430.38043493439);
		v461 = njSin(v171 >> 2);
		v454 = njSin(v171 >> 1);
		v438 = njSin(v171);
		v475 = njSin(2 * v171 >> 1);
		v172 = fabs(njCos(v171 >> 2));
		v447 = v172;
		v173 = fabs(njCos(v171 >> 1));
		v493 = v173;
		v174 = fabs(njCos(v171));
		v430 = v174;
		v175 = njCos(2 * v171 >> 1);
		v176 = v1->field_8;
		a1f = fabs(v175);
		if (v176 > 0)
		{
			v1->field_8 = v176 - 1;
		}
		else
		{
			v1->field_8 = 0;
		}
		v177 = v1->field_2;
		if (v177 <= 0)
		{
			return;
		}
		v178 = v461;
		v179 = v454;
		v180 = v447;
		v181 = v493;
		v182 = 1.799999952316284;
		while (1)
		{
			v393 = *v4;
			v183 = v4 + 2;
			v184 = *(v183 - 1);
			v4 = v183 + 4;
			v407 = v184;
			v425 = *(v4 - 4);
			v185 = v407;
			v186 = v393;
			if (v407 >= 5.0 || v185 <= -1.0)
			{
				v187 = v393;
				goto LABEL_213;
			}
			if (v186 >= 2.2 || v186 <= 0.0)
			{
				v188 = v182;
				v187 = v393;
			LABEL_201:
				if (v187 < 1.5 && v187 > -5.0)
				{
					if (v185 <= 3.0)
					{
						if (v185 <= 2.5)
						{
							if (v188 >= v185)
							{
								v395 = v187 - v185 * v178;
								v408 = v407 * v180;
								v182 = 1.799999952316284;
							}
							else
							{
								v202 = v185 - v188;
								v203 = v188;
								v204 = v187 - v179 * v202 - v178 * v188;
								v182 = v203;
								v395 = v204;
								v408 = v202 * v181 + v180 * v203;
							}
						}
						else
						{
							v395 = v187 - (v185 - 2.5) * v438 - v179 * 0.7000000476837158 - v178 * v188;
							v182 = v188;
							v408 = 0.7000000476837158 * v181 + v430 * (v185 - 2.5) + v180 * v188;
						}
					}
					else
					{
						v200 = v185 - 3.0;
						v201 = v187 - v200 * v475 - v438 * 0.5 - v179 * 0.7000000476837158 - v178 * v188;
						v182 = v188;
						v395 = v201;
						v408 = a1f * v200 + v430 * 0.5 + v181 * 0.7000000476837158 + v180 * v188;
					}
					v205 = v5 + 2;
					*(v205 - 2) = *(v205 - 2) * 0.8999999761581421 + v395 * 0.1000000238418579;
					*(v205 - 1) = 0.8999999761581421 * *(v205 - 1) + v408 * 0.1000000238418579;
					*v205 = v425;
					goto LABEL_215;
				}
			LABEL_213:
				*v5 = *v5 * 0.8999999761581421 + v187 * 0.1000000238418579;
				v198 = 0.8999999761581421;
				v199 = v185 * 0.1000000238418579;
				goto LABEL_214;
			}
			v187 = v393;
			if (v425 >= -1.0 && v425 <= 1.0)
			{
				v188 = 1.799999952316284;
				goto LABEL_201;
			}
			if (v185 <= 0.800000011920929)
			{
				if (v185 <= 1.5)
				{
					if (v185 <= 1.600000023841858)
					{
						v394 = v187 - v185 * v178;
						v193 = v407 * v180;
					}
					else
					{
						v196 = v185 - 1.600000023841858;
						v394 = v187 - v179 * v196 - v178 * 1.600000023841858;
						v193 = 1.600000023841858 * v180 + v196 * v181;
					}
					goto LABEL_199;
				}
				v194 = v185 - 1.5;
				v195 = v187 - v438 * v194 - v179 * -0.1000000238418579;
				v191 = 1.600000023841858;
				v394 = v195 - v178 * 1.600000023841858;
				v192 = v194 * v430;
			}
			else
			{
				v189 = v185 - 0.800000011920929;
				v190 = v187 - v475 * v189 - v438 * -0.699999988079071 - v179 * -0.1000000238418579;
				v191 = 1.600000023841858;
				v394 = v190 - v178 * 1.600000023841858;
				v192 = v189 * a1f - v430 * 0.699999988079071;
			}
			v193 = v191 * v180 + v192 - v181 * 0.1000000238418579;
		LABEL_199:
			v197 = v193;
			v198 = 0.8999999761581421;
			*v5 = *v5 * 0.8999999761581421 + v394 * 0.1000000238418579;
			v199 = 0.1000000238418579 * v197;
		LABEL_214:
			v206 = v5[1];
			v205 = v5 + 2;
			*(v205 - 1) = v198 * v206 + v199;
			*v205 = v425;
			v182 = 1.799999952316284;
		LABEL_215:
			--v177;
			v5 = v205 + 4;
			if (v177 <= 0)
			{
				return;
			}
		}
	case 16:
		v207 = v1->Model;
		v1->field_8 = 120;
		v208 = (float*)(v207->chunkmodel->vlist + 2);
		v209 = (signed int)((double)rand() * 0.000030517578125 * 2048.0 + 2048.0 + (double)v1->field_C);
		v1->field_C = v209;
		v210 = atan(njSin(v209) * 0.5);
		v211 = (signed int)(v210 * 10430.38043493439);
		v494 = njSin(v211);
		v212 = fabs(njCos(v211));
		v209 -= 4096;
		v482 = v212;
		v213 = atan(njSin(v209) * 0.5);
		v214 = (signed int)(v213 * 10430.38043493439);
		v462 = njSin(v214);
		v215 = fabs(njCos(v214));
		v209 -= 4096;
		v426 = v215;
		v216 = atan(njSin(v209) * 0.5);
		v217 = (signed int)(v216 * 10430.38043493439);
		v439 = njSin(v217);
		v218 = fabs(njCos(v217));
		v431 = v218;
		v219 = atan(njSin(v209 - 4096) * 0.5);
		v220 = (signed int)(v219 * 10430.38043493439);
		v476 = njSin(v220);
		v221 = njCos(v220);
		v222 = v1->field_2;
		a1g = fabs(v221);
		if (v222 <= 0)
		{
			return;
		}
		v223 = v494;
		v224 = v482;
		v225 = v462;
		v226 = 2.5;
		v227 = 2.0;
		while (2)
		{
			v409 = *v208;
			v229 = v208 + 2;
			v230 = *(v229 - 1);
			v208 = v229 + 4;
			v396 = v230;
			v422 = *(v208 - 4);
			v231 = v396;
			v232 = v409;
			if (v396 >= 5.0)
			{
				goto LABEL_247;
			}
			if (v231 <= -1.0 || v232 >= 2.2)
			{
				goto LABEL_227;
			}
			v233 = v409;
			v234 = v396;
			if (v232 <= -0.1000000014901161 || v422 >= -1.4 && v422 <= 1.4)
			{
				v226 = 2.5;
				v232 = v409;
				v231 = v396;
			LABEL_227:
				if (v231 <= -2.0 || v232 >= 0.0 || v232 <= -5.0)
				{
				LABEL_247:
					*v5 = v232;
					v257 = v5 + 1;
				}
				else
				{
					if (v231 <= 3.0)
					{
						if (v231 <= 2.5)
						{
							v251 = 0.0 < v231;
							v252 = v232;
							v253 = v231;
							v254 = v252;
							if (v251)
							{
								v255 = v253 - 0.0;
								v410 = v254 - v225 * v255 - v223 * v227;
								v236 = v255 * v426 + v224 * v227;
							}
							else
							{
								v256 = v253 + v227;
								v410 = v254 - v223 * v256;
								v236 = v256 * v224;
							}
						}
						else
						{
							v410 = v232 - v439 * (v231 - v226) - v225 * v226 - v223 * v227;
							v236 = (v231 - v226) * v431 + v426 * v226 + v224 * v227;
						}
					}
					else
					{
						v235 = v231 - 3.0;
						v226 = 2.5;
						v410 = v232 - v476 * v235 - v439 * 0.5 - v225 * 2.5 - v223 * v227;
						v236 = v235 * a1g + v431 * 0.5 + v426 * 2.5 + v224 * v227;
					}
					v257 = v5 + 1;
					v258 = v236 - v227;
					*(v257 - 1) = *(v257 - 1) * 0.8999999761581421 + v410 * 0.1000000014901161;
					v231 = 0.8999999761581421 * *v257 + v258 * 0.1000000014901161;
				}
				*v257 = v231;
				v248 = v257 + 1;
				*v248 = v422;
				v259 = v227;
				v250 = v226;
				v247 = v259;
			LABEL_249:
				--v222;
				v5 = v248 + 4;
				if (v222 > 0)
				{
					v228 = v250;
					v227 = v247;
					v226 = v228;
					continue;
				}
				return;
			}
			break;
		}
		if (v234 <= 0.0)
		{
			if (v234 <= 1.5)
			{
				if (v234 <= 1.600000023841858)
				{
					v411 = v233 - v223 * (v234 + v227);
					v241 = (v234 + v227) * v224;
				}
				else
				{
					v244 = v234 - 1.600000023841858;
					v411 = v233 - v225 * v244 - v223 * 3.599999904632568;
					v241 = v244 * v426 + 3.599999904632568 * v224;
				}
				goto LABEL_240;
			}
			v242 = v234 - 1.5;
			v243 = v409 - v439 * (v234 - 1.5) - v225 * -0.1000000238418579;
			v239 = 3.599999904632568;
			v411 = v243 - v223 * 3.599999904632568;
			v240 = v242 * v431;
		}
		else
		{
			v237 = v234 - 0.0;
			v238 = v409 - v476 * (v234 - 0.0) - v439 * -1.5 - v225 * -0.1000000238418579;
			v239 = 3.599999904632568;
			v411 = v238 - v223 * 3.599999904632568;
			v240 = v237 * a1g - v431 * 1.5;
		}
		v241 = v239 * v224 + v240 - v426 * 0.1000000238418579;
	LABEL_240:
		v245 = v227;
		v246 = v241 - v227;
		v247 = v245;
		v248 = v5 + 2;
		v249 = v246;
		*(v248 - 2) = *(v248 - 2) * 0.8999999761581421 + v411 * 0.1000000014901161;
		*(v248 - 1) = 0.8999999761581421 * *(v248 - 1) + 0.1000000014901161 * v249;
		*v248 = v422;
		v250 = 2.5;
		goto LABEL_249;
	case 17:
		v260 = v1->field_C;
		v440 = v1->speed;
		v1->field_C = v260 + 2048;
		v261 = v440 * 0.9800000190734863;
		v1->speed = v261;
		v262 = fabs(v261);
		if (v262 < 0.001)
		{
			v1->speed = 0.0;
		}
		if (v440 <= 1.799999952316284)
		{
			if (v440 >= -1.799999952316284)
			{
				goto LABEL_258;
			}
			v263 = -1.8;
		}
		else
		{
			v263 = 1.8;
		}
		v440 = v263;
	LABEL_258:
		v264 = njSin(v260) * v440;
		v265 = atan(v264 / 1.5);
		v266 = (signed int)(v265 * 10430.38043493439);
		v463 = njSin(v266 >> 2);
		v455 = njSin(v266 >> 1);
		v441 = njSin(v266);
		v477 = njSin(2 * v266 >> 1);
		v267 = fabs(njCos(v266 >> 2));
		v448 = v267;
		v268 = fabs(njCos(v266 >> 1));
		v432 = v268;
		v269 = fabs(njCos(v266));
		v423 = v269;
		v270 = njCos(2 * v266 >> 1);
		v271 = v1->field_2;
		v272 = fabs(v270);
		v468 = v272;
		if (v271 <= 0)
		{
			return;
		}
		v273 = v463;
		v274 = v455;
		v275 = v448;
		v276 = -1.899999976158142;
		while (1)
		{
			v495 = *v4;
			v277 = v4 + 2;
			v278 = *(v277 - 1);
			v4 = v277 + 4;
			a1h = v278;
			v427 = *(v4 - 4);
			v279 = a1h;
			v280 = v495;
			if (a1h < 0.800000011920929 && v279 > -5.0 && v280 < 2.0 && v280 > -2.0)
			{
				v281 = v495;
				if (v427 > 1.580000042915344 || v427 < -1.580000042915344)
				{
					if (v279 >= -2.9000001)
					{
						if (v279 >= -1.899999976158142)
						{
							if (v279 >= -1.4)
							{
								v282 = v5 + 2;
								*(v282 - 2) = v281 - v279 * v273;
								*(v282 - 1) = v279 * v275;
							}
							else
							{
								v282 = v5 + 2;
								*(v282 - 2) = v281 - (v279 - -1.899999976158142) * v274 - v273 * -1.399999976158142;
								*(v282 - 1) = (a1h - -1.399999976158142) * v432 - v275 * 1.399999976158142;
							}
							v276 = -1.899999976158142;
						}
						else
						{
							v284 = v279 - -1.899999976158142;
							v282 = v5 + 2;
							v285 = v281 - v441 * v284 - v274 * -0.5 - v273 * -1.399999976158142;
							v276 = -1.899999976158142;
							*(v282 - 2) = v285;
							*(v282 - 1) = v284 * v423 - v432 * 0.5 - v275 * 1.399999976158142;
						}
					}
					else
					{
						v282 = v5 + 2;
						v283 = v279 - -2.900000095367432;
						*(v282 - 2) = v281
							- v477 * v283
							- v441 * -1.00000011920929
							- v274 * -0.5
							- v273 * -1.399999976158142;
						*(v282 - 1) = v283 * v468 - v423 * 1.00000011920929 - v432 * 0.5 - v275 * 1.399999976158142;
						v276 = -1.899999976158142;
					}
					goto LABEL_284;
				}
				v280 = v495;
				v276 = -1.899999976158142;
			}
			v286 = v280;
			v287 = a1h;
			v288 = v286;
			if (a1h >= v276 || v287 <= -5.0)
			{
				v292 = v5 + 1;
				*(v292 - 1) = v288;
				v282 = v292 + 1;
				*(v282 - 1) = a1h;
				goto LABEL_284;
			}
			if (v287 >= -2.9000001)
			{
				if (v287 >= v276)
				{
					v282 = v5 + 2;
					goto LABEL_284;
				}
				v291 = v287 - v276;
				*v5 = v288 - v441 * v291 - v274 * -0.5 - v273 * -1.399999976158142;
				v290 = v291 * v423;
			}
			else
			{
				v289 = v287 - -2.900000095367432;
				*v5 = v288 - v477 * v289 - v441 * -1.00000011920929 - v274 * -0.5 - v273 * -1.399999976158142;
				v290 = v289 * v468 - v423 * 1.00000011920929;
			}
			v282 = v5 + 2;
			*(v282 - 1) = v290 - v432 * 0.5 - v275 * 1.399999976158142;
		LABEL_284:
			--v271;
			*v282 = v427;
			v5 = v282 + 4;
			if (v271 <= 0)
			{
				return;
			}
		}
	case 18:
		v293 = v1->field_C;
		v442 = v1->speed;
		v1->field_C = v293 + 1024;
		v294 = v442 * 0.9900000095367432;
		v1->speed = v294;
		v295 = fabs(v294);
		if (v295 < 0.001)
		{
			v1->speed = 0.0;
		}
		if (v442 <= 1.0)
		{
			if (v442 < -1.0)
			{
				v442 = -1.0;
			}
		}
		else
		{
			v442 = 1.0;
		}
		v296 = njSin(v293) * v442;
		v297 = atan(v296 / 2.5);
		v298 = (signed int)(v297 * 10430.38043493439);
		v456 = njSin(v298 >> 2);
		v449 = njSin(v298 >> 1);
		v478 = njSin(v298);
		v469 = njSin(2 * v298 >> 1);
		v299 = fabs(njCos(v298 >> 2));
		v433 = v299;
		v300 = fabs(njCos(v298 >> 1));
		v496 = v300;
		v301 = fabs(njCos(v298));
		v443 = v301;
		v302 = njCos(2 * v298 >> 1);
		v303 = v1->field_8;
		v304 = fabs(v302);
		v464 = v304;
		if (v303 > 0)
		{
			v305 = 0.89999998;
			v1->field_8 = v303 - 1;
		}
		else
		{
			v305 = 0.1;
			v1->field_8 = 0;
		}
		v306 = v1->field_2;
		v428 = v305;
		if (v306 <= 0)
		{
			return;
		}
		a1i = 1.0 - v428;
		v307 = v456;
		v308 = v449;
		v309 = v478;
		v310 = v433;
		v311 = v496;
		while (2)
		{
			v412 = *v4;
			v312 = v4 + 2;
			v313 = *(v312 - 1);
			v4 = v312 + 4;
			v397 = v313;
			v457 = *(v4 - 4);
			v314 = v412;
			if (v412 >= -1.0)
			{
				v315 = v457;
			}
			else
			{
				v315 = v457;
				if (v457 < -1.0 || v315 > 1.0)
				{
					v316 = v412;
					if (v412 < -2.8)
					{
						v317 = v316 - -2.799999952316284;
						v398 = v397
							- v469 * v317
							- v309 * -0.5999999046325684
							- v308 * -0.6000000238418579
							- v307 * -1.600000023841858;
						v318 = v317 * v464
							- v443 * 0.5999999046325684
							- 0.6000000238418579 * v311
							- v310 * 1.600000023841858;
					LABEL_308:
						v321 = v311;
						v322 = v318;
						v323 = v321;
						v324 = v5 + 1;
						v325 = v322;
						*(v324 - 1) = v325 * a1i + v428 * *(v324 - 1);
						*v324 = v428 * *v324 + a1i * v398;
						v326 = v457;
						goto LABEL_318;
					}
					if (v316 < -2.2)
					{
						v319 = v316 - -2.200000047683716;
						v398 = v397 - v309 * v319 - v308 * -0.6000000238418579 - v307 * -1.600000023841858;
						v318 = v319 * v443 - 0.6000000238418579 * v311 - v310 * 1.600000023841858;
						goto LABEL_308;
					}
					v320 = v412;
					if (v316 < -1.600000023841858)
					{
						v398 = v397 - v308 * (v316 - -1.600000023841858) - -1.600000023841858 * v307;
						v318 = (v316 - -1.600000023841858) * v311 - v310 * 1.600000023841858;
						goto LABEL_308;
					}
				LABEL_307:
					v398 = v397 - v307 * v320;
					v318 = v320 * v310;
					goto LABEL_308;
				}
			}
			if (v314 < -0.1000000014901161)
			{
				v327 = v412;
				if (v412 < -3.5)
				{
					v328 = v327 - -3.5;
					v398 = v397 - v469 * v328 - v309 * -1.0 - -1.0 * v308 - v307 * -1.5;
					v318 = v328 * v464 - v443 - v311 - v310 * 1.5;
					goto LABEL_308;
				}
				if (v327 < -2.5)
				{
					v329 = v327 - -2.5;
					v398 = v397 - v309 * v329 - v308 * -1.0 - v307 * -1.5;
					v318 = v329 * v443 - v311 - v310 * 1.5;
					goto LABEL_308;
				}
				v320 = v412;
				if (v327 < -1.5)
				{
					v398 = v397 - v308 * (v327 - -1.5) - -1.5 * v307;
					v318 = (v327 - -1.5) * v311 - v310 * 1.5;
					goto LABEL_308;
				}
				goto LABEL_307;
			}
			v324 = v5 + 1;
			*(v324 - 1) = v314 * a1i + v428 * *(v324 - 1);
			*v324 = a1i * v397 + v428 * *v324;
			v330 = v311;
			v326 = v315;
			v323 = v330;
		LABEL_318:
			v331 = v324 + 1;
			*v331 = v326;
			--v306;
			v5 = v331 + 4;
			if (v306 > 0)
			{
				v311 = v323;
				v309 = v478;
				continue;
			}
			return;
		}
	case 19:
		v332 = v1->field_C;
		v444 = v1->speed;
		v1->field_C = v332 + 1536;
		v333 = v444 * 0.9700000286102295;
		v1->speed = v333;
		v334 = fabs(v333);
		if (v334 < 0.001)
		{
			v1->speed = 0.0;
		}
		if (v444 <= 1.0)
		{
			if (v444 < -1.0)
			{
				v444 = -1.0;
			}
		}
		else
		{
			v444 = 1.0;
		}
		v335 = njSin(v332) * v444;
		v336 = atan(v335 * 0.5);
		v337 = v336 * 10430.38043493439;
		v338 = (signed int)v337;
		v339 = (signed int)v337 >> 2;
		v424 = njSin(v339);
		v340 = njSin(v338 >> 1);
		v483 = njSin(v338);
		v470 = njSin(2 * v338 >> 1);
		v341 = fabs(njCos(v339));
		v429 = v341;
		v342 = fabs(njCos(v338 >> 1));
		v434 = v342;
		v343 = fabs(njCos(v338));
		v445 = v343;
		v344 = fabs(njCos(2 * v338 >> 1));
		v479 = v344;
		v346 = v340;
		v450 = v340 * 0.6999999284744263;
		v497 = v483 * 0.7000000476837158;
		v458 = 0.6999999284744263 * v434;
		v348 = v483;
		v349 = v1->field_8;
		a1j = 0.7000000476837158 * v445;
		if (v349 > 0)
		{
			v350 = 0.89999998;
			v1->field_8 = v349 - 1;
		}
		else
		{
			v350 = 0.1;
			v1->field_8 = 0;
		}
		v351 = v1->field_2;
		v465 = v350;
		if (v351 <= 0)
		{
			return;
		}
		v352 = v465;
		v353 = 1.0 - v465;
		v509 = v353;
		v345 = v424 * 1.600000023841858;
		v354 = v345;
		v347 = 1.600000023841858 * v429;
		v355 = v347;
		while (2)
		{
			v399 = *v4;
			v358 = v4 + 2;
			v359 = *(v358 - 1);
			v4 = v358 + 4;
			v413 = v359;
			v420 = *(v4 - 4);
			v360 = v420;
			if (v420 < -1.5 || v360 > 1.5)
			{
				if (v360 <= 3.0)
				{
					if (v360 >= -3.0)
					{
						if (2.3 >= v360)
						{
							if (v360 >= -2.3)
							{
								v378 = v420;
								if (v420 <= 1.600000023841858)
								{
									v382 = v420;
									if (v378 >= -1.600000023841858)
									{
										if (v378 <= 0.0)
										{
											v401 = v378 * v424 + v399;
											v375 = v355;
											v421 = v382 * v429;
										}
										else
										{
											v401 = v399 - v378 * v424;
											v421 = v378 * v429;
											v353 = v509;
											v375 = v355;
										}
									}
									else
									{
										v401 = v346 * (v378 + 1.600000023841858) + v399 - v354;
										v375 = v355;
										v421 = (v382 + 1.600000023841858) * v434 - v355;
									}
								}
								else
								{
									v379 = v378 - 1.600000023841858;
									v401 = v399 - v346 * v379 - v354;
									v380 = v355;
									v381 = v379 * v434 + v355;
									v375 = v380;
									v421 = v381;
								}
							}
							else
							{
								v377 = v360 + 2.299999952316284;
								v401 = v348 * v377 + v399 - v450 - v354;
								v375 = v355;
								v421 = v377 * v445 - v458 - v355;
							}
						}
						else
						{
							v376 = v360 - 2.299999952316284;
							v401 = v399 - v348 * v376 - v450 - v354;
							v375 = v355;
							v421 = v376 * v445 + v458 + v355;
						}
					}
					else
					{
						v375 = v355;
						v401 = v470 * (v360 + 3.0) + v399 - v497 - v450 - v354;
						v421 = (v360 + 3.0) * v479 - a1j - v458 - v355;
					}
				}
				else
				{
					v375 = v355;
					v401 = v399 - v470 * (v360 - 3.0) - v497 - v450 - v354;
					v421 = (v360 - 3.0) * v479 + a1j + v458 + v355;
				}
				v383 = *v5;
				v5 += 6;
				*(v5 - 6) = v383 * v352 + v401 * v353;
				*(v5 - 5) = v413;
				*(v5 - 4) = *(v5 - 4) * v352 + v421 * v353;
				v384 = v354;
				v374 = v375;
				v364 = v384;
				goto LABEL_360;
			}
			if (v399 >= -1.0)
			{
				v372 = v5 + 1;
				v373 = *(v372 - 1);
				v5 = v372 + 5;
				*(v5 - 6) = v399 * v509 + v373 * v352;
				*(v5 - 5) = *(v5 - 5) * v352 + v413 * v509;
				*(v5 - 4) = v420;
				v364 = v354;
				v374 = v355;
				v353 = v509;
			LABEL_360:
				v385 = v374;
				v386 = v352;
				v362 = v385;
				v387 = v386;
				v370 = v353;
				v371 = v387;
				goto LABEL_361;
			}
			v361 = v399;
			if (v399 >= -6.0)
			{
				if (v361 >= -2.5)
				{
					if (v361 >= -1.799999952316284)
					{
						v414 = v413 - v361 * v424;
						v367 = v361 * v429;
					}
					else
					{
						v366 = v361 - -1.799999952316284;
						v414 = v413 - v346 * v366 - -1.799999952316284 * v424;
						v367 = v366 * v434 - v429 * 1.799999952316284;
					}
					v400 = v367;
					v364 = v354;
					v362 = v355;
				}
				else
				{
					v362 = v355;
					v365 = v399 - -2.5;
					v414 = v413 - v348 * v365 - v346 * -0.7000000476837158 - v424 * -1.799999952316284;
					v364 = v354;
					v400 = v365 * v445 - v434 * 0.7000000476837158 - v429 * 1.799999952316284;
				}
			}
			else
			{
				v362 = v355;
				v363 = v399 - -6.0;
				v414 = v413 - v470 * v363 - v348 * -3.5 - v346 * -0.7000000476837158 - v424 * -1.799999952316284;
				v364 = v354;
				v400 = v363 * v479 - v445 * 3.5 - v434 * 0.7000000476837158 - v429 * 1.799999952316284;
			}
			v368 = *v5;
			v5 += 6;
			v369 = v368 * v465;
			v370 = v509;
			*(v5 - 6) = v400 * v509 + v369;
			*(v5 - 5) = *(v5 - 5) * v465 + v414 * v509;
			v371 = v465;
			*(v5 - 4) = v420;
		LABEL_361:
			if (--v351 > 0)
			{
				v356 = v364;
				v348 = v483;
				v357 = v356;
				v355 = v362;
				v352 = v371;
				v353 = v370;
				v354 = v357;
				continue;
			}
			return;
		}
	default:
		return;
	}
}