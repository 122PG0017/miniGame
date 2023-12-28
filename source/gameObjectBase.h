/*****************************************************************//**
 * \file   gameObjectBase.h
 * \brief  minigameプロジェクトで使用する基底オブジェクト
 * 　　　　オブジェクトに共通する関数や構造体、変数の定義
 *         使用頻度の多いオブジェクトへポインタを取得
 * \author 
 * \date   
 *********************************************************************/
#pragma once
class Player;
using namespace AppFrame;

class GameObjectBase :public AppFrame::ObjectBase {
public:
    void AddGameComponent(std::unique_ptr<GameComponentBase> component, int id = 0);
    /**  \brief プレイヤーのポインタを取得*/
    Player* GetPlayer();
};