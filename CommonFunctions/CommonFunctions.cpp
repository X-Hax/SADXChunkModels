// CommonFunctions.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "ModelInfo.h"
#include "CommonFunctions.h"
#include "CommonSADX.h"

FastcallFunctionPointer(void, sub_7917F0, (Sint32* a1, Sint16* a2), 0x7917F0);
void DrawChunkModel(NJS_CNK_MODEL* model)
{
	sub_7917F0(model->vlist, model->plist);
}

D3DMATRIX WorldMatrixBackup;
void DrawTransformedChunkObject(void* a1)
{
	D3DMATRIX tmp = WorldMatrix;
	WorldMatrix = WorldMatrixBackup;
	Direct3D_SetWorldTransform();
	DrawChunkObject((NJS_CNK_OBJECT*)a1);
	WorldMatrix = tmp;
}

void njCnkAction_Queue(NJS_ACTION* action, float frame, QueuedModelFlagsB flags)
{
	DisplayAnimationFrame(action, frame, flags, 0, (void(__cdecl*)(NJS_MODEL_SADX*, int, int))DrawChunkModel);
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

void njCnkActionLink(NJS_ACTION_LINK* action, float frame, int flag)
{
	late_ActionLinkEx_(action, frame, (QueuedModelFlagsB)flag, 0.0, (void(__cdecl*)(NJS_MODEL_SADX*, int, int))DrawChunkModel);
}

void SetupWorldMatrix()
{
	// The next three lines help to reduce floating-point rounding errors at large coordinates.
	ProjectToWorldSpace(); // set WorldMatrix to _nj_current_matrix_ptr_ * InverseViewMatrix
	WorldMatrixBackup = WorldMatrix;
	Direct3D_SetWorldTransform(); // set device's world transform to WorldMatrix
	memcpy(_nj_current_matrix_ptr_, &ViewMatrix, sizeof(NJS_MATRIX)); // reset current matrix to ViewMatrix
}

bool FindModels(std::string& mdlpath, std::unordered_map<std::string, void*>& labels)
{
	WIN32_FIND_DATAA data;
	const std::string srcPathSearch = mdlpath + "*.sa2mdl";
	const HANDLE hFind = FindFirstFileA(srcPathSearch.c_str(), &data);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		// No files found.
		return false;
	}

	do
	{
		const std::string modFile = mdlpath + std::string(data.cFileName);
		ModelInfo* mdl = new ModelInfo(modFile.c_str());
		auto map = mdl->getlabels();
		for (auto i = map->cbegin(); i != map->cend(); ++i)
			labels[i->first] = i->second;
	} while (FindNextFileA(hFind, &data) != 0);
	FindClose(hFind);
	return true;
}
