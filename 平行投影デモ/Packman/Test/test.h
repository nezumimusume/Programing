/*!
 * @brief	テストクラス。
 */

#ifndef _TEST_H_
#define _TEST_H_

class CTest : public tkEngine::IGameObject{
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
private:
	
};
#endif // _TEST_H_