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
	 * \brief ゲーム内感度の取得
	 * \return ゲーム内感度
	 */
	inline std::tuple<double, double, int> sensitivity() const { return _sensitivity; }
	/**
	 * \brief ゲーム内感度の設定
	 * \param cameraSens カメラ感度
	 * \param aimSens エイム感度
	 * \param deadZone デッドゾーン
	 */
	inline void sensitivity(double cameraSens, double aimSens, int deadZone) { _sensitivity = std::make_tuple(cameraSens, aimSens, deadZone); }
	//ModeServer& getModeServer() { return *_modeServer; };

private:
	std::tuple<double, double, int> _sensitivity;                       //!< ゲーム内感度及びデッドゾーン値のTuple型
protected:
	int LightHandle01, LightHandle02, shadowMapHandle, animIndexOld;
	float spd, cameraDir, cameraHigh;
	VECTOR cameraPos, cameraFor;
	//modelInf plMI, stage;
	std::string NS;

	bool _debug;
};