/*!
 * @brief	インゲーム中のライト。
 */

#pragma once


/*!
 * @brief	インゲーム中のライト。
 */
class InGameLight : public IGameObject{
public:
	InGameLight();
	~InGameLight();
	bool Start() override;
	void Update() override; 
	/*!
	 * @brief	デフォルトライトの取得。
	 */
	CLight& GetDefaultLight()
	{
		return defaultLight;
	}
private:
	CLight	defaultLight;		//!<デフォルトライト。
};