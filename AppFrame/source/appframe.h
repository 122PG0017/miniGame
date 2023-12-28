/*****************************************************************//**
 * \file   appframe.h
 * \brief  フレームワークのライブラリ指定
 *
 * \author 山本莉久
 * \date   March 2023
 *********************************************************************/
#pragma once
#include<vector>
#include<map>
#include<string>
#include<cmath>
#include <thread>
#include <future>

#if _DEBUG
#pragma comment(lib,"../x64/Debug/AppFrame.lib")
#elif !_DEBUG
#pragma comment(lib,"../x64/Release/AppFrame.lib")
#endif

#include "Application/ApplicationBase.h"
#include "CFile/CFile.h"
#include "Mode/ModeBase.h"
#include "Mode/ModeServer.h"
#include "modelManager/modelManager.h"
#include "Math/math.h"
#include "Object/inputManager.h"
#include "Object/ObjectBase.h"
#include "Object/ComponentBase.h"
#include "Object/componentMV1.h"
#include "Object/ObjectServer.h"
#include "ResourceServer/ResourceServer.h"
#include "ResourceServer/SoundServer.h"
