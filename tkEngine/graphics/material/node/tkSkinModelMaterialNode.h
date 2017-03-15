/*!
 *@brief	スキンモデルのマテリアルノードの基底クラス。
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	スキンモデルのマテリアルノードの基底クラス。
	 */
	class ISkinModelMaterialNode{
	public:
		ISkinModelMaterialNode()
		{
		}
		virtual ~ISkinModelMaterialNode()
		{
		}
		/*!
		 *@brief	マテリアルパラメータをGPUに転送。
		 */
		virtual void SendMaterialParamToGPU() = 0;
	};
}
