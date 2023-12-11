/*****************************************************************//**
 * \file   EqualizerRender.cpp
 * \brief  ‰¹º‚Ìü”g”–ˆ‚Ì‰¹—Ê‚ğ•`‰æ‚·‚é‹@”\
 *
 * \author ¼“c@—T
 * \date   March 2023
 *********************************************************************/
#include "EqualizerRender.h"
using namespace AppFrame;
using namespace model;


namespace {
    constexpr int Split = 120;//æ“¾ü”g”‚Ì•ªŠ„”
    constexpr int RenderSize = 1024;//•`‰æƒTƒCƒY(px)
    constexpr int RenderSizeHalf = RenderSize / 2;
    constexpr int BarWidth = RenderSize / Split;
    constexpr int RadiusSmall = 100;
    constexpr int RadiusLarge = 600;
    constexpr float StepAngle = DX_PI * 2.0f / Split;
    constexpr float PieceAngle = StepAngle * 0.6f;
    constexpr int colorPatternSize = 7;
    static const std::array<unsigned int, colorPatternSize> ColorPattern = {
        //Color::Red, Color::Blue, Color::Green, Color::Purple, Color::Yellow, Color::LightBlue, Color::White
    };
}

EqualizerRender::EqualizerRender() :_colorIndex{ 0 }
{
    _screen = MakeScreen(RenderSize, RenderSize, true);
}

EqualizerRender::~EqualizerRender()
{
    DeleteGraph(_screen);
}

void EqualizerRender::SetSound(const char* filePath)
{
    _softSoundhandle = SoundServer::LoadSoftSound(filePath);
    _soundHandle = SoundServer::LoadBGM(filePath);
}

void EqualizerRender::Update()
{
    int currentScreen = GetDrawScreen();
    ChangeScreen::ChangeScreenAndSaveCamera(_screen);
    ClearDrawScreen();

    std::array<float, RenderSize> buffer{ 0 };
    _soundPosition = GetCurrentPositionSoundMem(_soundHandle);
    GetFFTVibrationSoftSound(_softSoundhandle, -1, _soundPosition, 4096, buffer.data(), Split);



    // ü”g”•ª•z‚ğ‰æ–Ê‚É•`‰æ‚·‚é
    for (int i = 0; i < Split; i++)
    {
        float weight{ 1.0f };

        if (i < 6) {
            weight = 0.3f;
        }
        else if (i < 22) {
            weight = 0.5f;
        }

        // ŠÖ”‚©‚çæ“¾‚Å‚«‚é’l‚ğ•`‰æ‚É“K‚µ‚½’l‚É’²®
        float param{ pow(buffer[i], 0.3f) * 3.0f * weight + 0.3f };

        int x1 = std::cos(i * StepAngle - PieceAngle) * RadiusLarge * param + RenderSizeHalf;
        int y1 = std::sin(i * StepAngle - PieceAngle) * RadiusLarge * param + RenderSizeHalf;
        int nextStep{ (i + 1) % Split };
        int x2 = std::cos(nextStep * StepAngle - PieceAngle) * RadiusLarge * param + RenderSizeHalf;
        int y2 = std::sin(nextStep * StepAngle - PieceAngle) * RadiusLarge * param + RenderSizeHalf;

        DrawLine(x1, y1, x2, y2, ColorPattern[_colorIndex], 30);
    }

    ChangeScreen::ChangeScreenAndSaveCamera(currentScreen);
}

void EqualizerRender::Render(float scale, float angle, int alpha)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawRotaGraph(RenderSizeHalf, RenderSizeHalf, scale, angle, _screen, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void EqualizerRender::ColorChange()
{
    ++_colorIndex;

    if (_colorIndex >= colorPatternSize) {
        _colorIndex = 0;
    }
}
