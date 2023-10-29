#pragma once
/*****************************************************************//**
 * \file   ModeTest.h
 * \brief  モードの実装例です。ゲーム中では使用しない。
 *
 * \author 
 * \date   December 2022
 *********************************************************************/
#pragma once
#include"appframe.h"
#include"player.h"
//using namespace AppFrame;

class ModeTest : public ModeBase
{
public:
    ModeTest(ModeServer* MS) { _modeServer = MS; };
    ~ModeTest() {};
    bool Initialize()override;
    bool Terminate()override;
    //bool Update(InputManager& input)override;
    bool Render()override;
    //bool Debug()override;
protected:
    bool  isAnimEnd;
    int Handle;
    ModeServer* _modeServer;
    modelInf _modelInf;
    Rserver RS;
};