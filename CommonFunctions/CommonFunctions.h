#pragma once
#include "SADXModLoader.h"

void DrawChunkModel(NJS_CNK_MODEL* model);
extern D3DMATRIX WorldMatrixBackup;
void DrawTransformedChunkObject(void* a1);
void njCnkAction_Queue(NJS_ACTION* action, float frame, QueuedModelFlagsB flags);
void njCnkAction(NJS_ACTION* action, float frame);
void NullModel(NJS_MODEL_SADX*, int, int);
void njNullAction(NJS_ACTION* action, float frame);
void SetupWorldMatrix();
void ProcessAnimList(AnimData_t* animlist, const std::string& mtnpath, int animcount, std::unordered_map<int, NJS_OBJECT*>& modelmap);
bool FindModels(std::string& mdlpath, std::unordered_map<std::string, void*>& labels);
