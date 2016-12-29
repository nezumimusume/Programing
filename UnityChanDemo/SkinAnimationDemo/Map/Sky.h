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
	
};
