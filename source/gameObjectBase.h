/*****************************************************************//**
 * \file   gameObjectBase.h
 * \brief  minigame�v���W�F�N�g�Ŏg�p������I�u�W�F�N�g
 * �@�@�@�@�I�u�W�F�N�g�ɋ��ʂ���֐���\���́A�ϐ��̒�`
 *         �g�p�p�x�̑����I�u�W�F�N�g�փ|�C���^���擾
 * \author 
 * \date   
 *********************************************************************/
#pragma once
class Player;
using namespace AppFrame;

class GameObjectBase :public AppFrame::ObjectBase {
public:
    void AddGameComponent(std::unique_ptr<GameComponentBase> component, int id = 0);
    /**  \brief �v���C���[�̃|�C���^���擾*/
    Player* GetPlayer();
};