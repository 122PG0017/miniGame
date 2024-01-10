#pragma once
#include<memory>

class gameMain : public AppFrame::ApplicationBase
{
	typedef AppFrame::ApplicationBase base;
public:
	gameMain() {};
	~gameMain() {};
	bool Initialize(HINSTANCE hInstance) override;
	bool Terminate() override;
	bool Input() override;
	bool Process() override;
	bool Render() override;

	bool AppWindowed() override { return true; }
	int DispSizeW() override { return 1280; }
	int DispSizeH() override { return 720; }

	/**
	 * \brief �Q�[�������x�̎擾
	 * \return �Q�[�������x
	 */
	inline std::tuple<double, double, int> sensitivity() const { return _sensitivity; }
	/**
	 * \brief �Q�[�������x�̐ݒ�
	 * \param cameraSens �J�������x
	 * \param aimSens �G�C�����x
	 * \param deadZone �f�b�h�]�[��
	 */
	inline void sensitivity(double cameraSens, double aimSens, int deadZone) { _sensitivity = std::make_tuple(cameraSens, aimSens, deadZone); }
	//ModeServer& getModeServer() { return *_modeServer; };

private:
	std::tuple<double, double, int> _sensitivity;                       //!< �Q�[�������x�y�уf�b�h�]�[���l��Tuple�^
protected:
	int LightHandle01, LightHandle02, shadowMapHandle, animIndexOld;
	float spd, cameraDir, cameraHigh;
	VECTOR cameraPos, cameraFor;
	//modelInf plMI, stage;
	std::string NS;

	bool _debug;
};