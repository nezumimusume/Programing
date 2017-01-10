#pragma once

class Sky : public IGameObject {
	enum InitStep {
		InitStep_Load,
		InitStep_Wait,
	};
	CSkinModelDataHandle	skinModelData;		//スキンモデルデータ。
	CSkinModel				skinModel;			//スキンモデル。
	CAnimation				animation;			//アニメーション。
	CLight					light;				//ライト。
	CTexture				normalMap;
	Player*					player;				//プレイヤ。
	InitStep				initStep = InitStep_Load;
	SAtmosphericScatteringParam	atomosphereParam;	//大気錯乱パラメータ。
	CVector3				sunPosition = CVector3::Zero;			//太陽の位置。
	float					sunAngle = 0.0f;
	CLight					sunLight;				//ライト。
	CSkinModelDataHandle	sunModelData;			//太陽のモデルデータ。
	CSkinModel				sunModel;				//太陽のモデル。
	CVector3				sunDir;					//太陽の方向。
	float					deltaTimeMul = 1.0f;	//⊿タイムに乗算される値。
public:
	Sky();
	
	~Sky()
	{

	}
	bool Start() override;
	void SetPlayer(Player* player)
	{
		this->player = player;
	}
	void Update() override;
	
	//大気錯乱パラメーターを取得。
	const SAtmosphericScatteringParam& GetAtomosphereParam() const
	{
		return atomosphereParam;
	}
	void Render(CRenderContext& renderContext) override;
	/*!
	* @brief	太陽の方向を取得。
	* @details
	*  惑星の中心から見た場合の太陽の方向です。
	*/
	const CVector3& GetSunDir() const
	{
		return sunDir;
	}
	/*!
	* @brief	⊿タイムに乗算される値を設定。
	*@param[in]	mul		グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になります。
	*/
	void SetFrameDeltaTimeMul(float mul)
	{
		deltaTimeMul = mul;
	}
	
};
