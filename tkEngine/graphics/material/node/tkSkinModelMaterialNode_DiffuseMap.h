/*!
 *@brief	スキンモデルのマテリアルノード(ディフューズマップ)
 */

#pragma once

#include "tkEngine/graphics/material/node/tkSkinModelMaterialNode.h"

namespace tkEngine{
	/*!
	 *@brief	スキンモデルのマテリアルノード(ディフューズマップ)
	 */
	class CSkinModelMaterialNode_DiffuseMap : public ISkinModelMaterialNode
	{
	public:
		void SendMaterialParam() override
		{
		}
	};
}
