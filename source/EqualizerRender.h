/*****************************************************************//**
 * \file   EqualizerRender.h
 * \brief  �����̎��g�����̉��ʂ�`�悷��@�\
 *
 * \author ���c�T
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <array>
#include <winnt.h>

class EqualizerRender
{
public:
    EqualizerRender();
    ~EqualizerRender();
    void SetSound(const char* filePath);
    void Update();
    void Render(float scale, float angle, int alpha);
    void ColorChange();
private:
    int _soundHandle;
    int _softSoundhandle;
    LONGLONG _soundPosition;
    int _screen;
    int _colorIndex;
};
