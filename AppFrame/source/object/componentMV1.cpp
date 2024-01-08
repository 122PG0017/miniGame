/*****************************************************************//**
 * \file   MV1Component.cpp
 * \brief  MV1のトランスフォーム更新、描画、アニメーションフレームの進行機能
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#include "componentMV1.h"
#include "../AppFrame/source/object/objectBase.h"
#include "../AppFrame/source/Mode/ModeBase.h"
#include "../AppFrame/source/Application/ApplicationBase.h"
#include <sstream>
namespace AppFrame {
	MV1Component::MV1Component(int modelHandle)
		:_modelHandle{ modelHandle }
		, _attachIndex{ -1 }
		, _playTime{ 0.0f }
		, _totalTime{ 0.0f }
		, _animSpeed{ 60.0f }
		, _animIndex{ -1 }
		, _isValid{ true }
		, _useOriginalShader{ false }
		, _vertexShader{ -1 }
		, _pixelShader{ -1 }
		, _bloom{ false }
	{
		int animNumber = MV1GetAnimNum(_modelHandle);
		_animFunction.clear();
		_animFunction.resize(animNumber);

		_constantBufferArray.clear();
	}

	MV1Component::~MV1Component()
	{
		for (auto&& handle : _constantBufferArray) {
			DeleteShaderConstantBuffer(handle._bufferHandle);
		}
		MV1TerminateCollInfo(_modelHandle, -1);
		DeleteShader(_vertexShader);
		DeleteShader(_pixelShader);
		MV1DeleteModel(_modelHandle);
	}

	bool MV1Component::Initialize()
	{
		MV1SetScale(_modelHandle, _parent->GetScale());
		MV1SetRotationXYZ(_modelHandle, _parent->GetRotation());
		MV1SetPosition(_modelHandle, _parent->GetPosition());
		MV1SetupCollInfo(_modelHandle, -1, 1, 1);
		return true;
	}

	void MV1Component::Process(InputManager& input)
	{
		if (_attachIndex == -1) {
			return;
		}

		float preTime = _playTime;

		if (_isValid) {
			_playTime += _parent->GetMode()->GetStepTm() * 0.001f * _animSpeed;
		}

		CheckAnimFunction(preTime, _playTime);

		if (_playTime >= _totalTime) {
			_playTime = 0.0f;
		}
	}

	void MV1Component::Render()
	{
		if (!_parent->GetVisible()) {
			return;
		}

		if (_useOriginalShader) {
			SetShader();
		}


		/*if (isBrending == true) { rate = 0.0f; isBrending = false; }
		if (rate <= 1.0f)
		{
			rate >= 1.0f ? rate = 1.0f : rate += 0.1;
			MV1SetAttachAnimTime(_modelHandle, _attachIndexOld, _playTimeOld);
		}
		else
		{
			_playTime += _animSpeed;
			if (_playTime >= _totalTime)
			{
				if (_animOldLoop) { _playTime = 0.0f; }
				else { _playTime = _totalTime; }
			}
		}
		MV1SetAttachAnimBlendRate(_modelHandle, _attachIndexOld, 1.0f - rate);
		MV1SetAttachAnimBlendRate(_modelHandle, _attachIndex, rate);*/

		MV1SetScale(_modelHandle, _parent->GetScale());
		MV1SetRotationXYZ(_modelHandle, _parent->GetRotation());
		MV1SetPosition(_modelHandle, _parent->GetPosition());
		MV1SetAttachAnimTime(_modelHandle, _attachIndex, _playTime);

		bool skinMesh{ false };

		if (_attachIndex != -1) {
			skinMesh = true;
		}
		MV1DrawModel(_modelHandle);
	}
	void MV1Component::Debug()
	{

	}

	void MV1Component::SetModelHandle(int modelHandle)
	{
		_modelHandle = modelHandle;
		int animNumber = MV1GetAnimNum(modelHandle);
		_animFunction.clear();
		_animFunction.resize(animNumber);
	}

	void MV1Component::SetAnimation(int index, bool loop, bool override, bool brend)
	{
		//if (_animIndexOld == index && !override) { return; }
		_isValid = true;
		//isBrending = brend;
		MV1DetachAnim(_modelHandle, _attachIndex);
		//MV1DetachAnim(_modelHandle, _attachIndexOld);
		_animIndex = index;
		_attachIndex = MV1AttachAnim(_modelHandle, _animIndex, -1, true);
		//_attachIndexOld = MV1AttachAnim(_modelHandle, _animIndexOld, -1, true);
		//_animIndexOld = index;
		//_animOldLoop = loop;
		_totalTime = MV1GetAttachAnimTotalTime(_modelHandle, _attachIndex);
		//_playTimeOld = _playTime;
		_playTime = 0.0f;
	}

	void MV1Component::AddAnimFunction(int animIndex, float activateTime, std::function<void(void)> function)
	{
		if (_animFunction.size() - 1 < animIndex) {
			return;
		}

		_animFunction[animIndex].push_back({ activateTime, function });

		typedef std::pair<float, std::function<void(void)>> AnimFuncType;
		auto sortAnimFunc = [](AnimFuncType lhs, AnimFuncType rhs) {return lhs.first < rhs.first; };

		std::sort(_animFunction[animIndex].begin(), _animFunction[animIndex].end(), sortAnimFunc);
	}

	void MV1Component::SetOriginalShader(const CHAR* vertexShaderPath, const CHAR* pixelShaderPath)
	{
		_vertexShader = LoadVertexShader(vertexShaderPath);
		_pixelShader = LoadPixelShader(pixelShaderPath);

		if (_vertexShader != -1 && _pixelShader != -1) {
			_useOriginalShader = true;
		}
	}

	void MV1Component::AddShaderBuffer(std::function<FLOAT4()> func, bool usePixelShader)
	{
		shaderBuffer addBuffer;
		SetUseVertexShader(_vertexShader);
		SetUsePixelShader(_pixelShader);
		addBuffer._bufferHandle = CreateShaderConstantBuffer(sizeof(float) * 4);
		addBuffer._getter = func;
		addBuffer._usePixelShader = usePixelShader;
		int size = static_cast<int>(_constantBufferArray.size());
		addBuffer._slot = size + 2;
		_constantBufferArray.emplace_back(addBuffer);
	}

	void MV1Component::CheckAnimFunction(float preTime, float nowTime)
	{
		for (auto&& func : _animFunction[_animIndex]) {
			if (func.first > preTime && func.first <= nowTime) {
				func.second();
			}
		}
	}

	void MV1Component::SetShader()
	{
		SetUseVertexShader(_vertexShader);
		SetUsePixelShader(_pixelShader);
		MV1SetUseOrigShader(true);

		if (static_cast<int>(_constantBufferArray.size()) > 0) {
			for (auto&& handle : _constantBufferArray) {
				auto bufferAdress = (FLOAT4*)GetBufferShaderConstantBuffer(handle._bufferHandle);
				FLOAT4 value = handle._getter();

				*bufferAdress = value;
				UpdateShaderConstantBuffer(handle._bufferHandle);

				auto type = DX_SHADERTYPE_VERTEX;

				if (handle._usePixelShader) {
					type = DX_SHADERTYPE_PIXEL;
				}

				SetShaderConstantBuffer(handle._bufferHandle, type, handle._slot);
			}
		}
	}

}