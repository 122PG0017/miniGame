#pragma once
/*****************************************************************//**
 * \file   ModeTest.h
 * \brief  ���[�h�̎�����ł��B�Q�[�����ł͎g�p���Ȃ��B
 *
 * \author 
 * \date   December 2022
 *********************************************************************/
#pragma once

//using namespace AppFrame;

class ModeTest : public ModeBase
{
public:
    ModeTest() {};
    ~ModeTest() {};
    bool Initialize()override;
    bool Terminate()override;
    bool Process(InputManager& input)override;
    bool Render()override;
    //bool Debug()override;
protected:
    bool  isAnimEnd;
    int Handle;
    //ModeServer* _modeServer;
    modelInf _modelInf;
    Rserver RS;
};