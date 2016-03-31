/*!
 *@brief	ライト
 */

#ifndef _TKLIGHT_H_
#define _TKLIGHT_H_

namespace tkEngine {
	/*!
	 *@brief	ライト
	 */
	class CLight{
	public:
		static const u32 NUM_DIFFUSE_LIGHT = 4;
	public:
		CLight()
		{
			for( u32 i = 0; i < NUM_DIFFUSE_LIGHT; i++ ){
				m_diffuseLightDirection[i] = CVector3::AxisX;
				m_diffuseLightColor[i].Set( 0.0f, 0.0f, 0.0f, 0.0f );
			}
			m_ambientLight.Set( 0.1f, 0.1f, 0.1f );
		}
		/*!
		 *@brief	ディフューズライトの向きを設定。
		 *@param[in]	no				ライトの番号。
		 *@param[in]	lightDirection	ライトの方向。
		 */
		void SetDiffuseLightDirection( u32 no, const CVector3 lightDirection )
		{
			TK_ASSERT( no < NUM_DIFFUSE_LIGHT, "error");
			m_diffuseLightDirection[no] = lightDirection;
		}
		/*!
		 *@brief	ディフューズライトの向きを取得。
		 *@param[in]	no		ライトの番号。
		 *@return	ライトの向き。
		 */
		const CVector3& GetDiffuseLightDirection( u32 no ) const
		{
			return m_diffuseLightDirection[no];
		}
		/*!
		 *@brief	ディフューズライトのカラーを設定。
		 *@param[in]	no			ライトの番号。
		 *@param[in]	lightColor	ライトのカラー。
		 */
		void SetDiffuseLightColor( u32 no, const CVector4& lightColor )
		{
			TK_ASSERT( no < NUM_DIFFUSE_LIGHT, "error" );
			m_diffuseLightColor[no] = lightColor;
		}
		/*!
		 *@brief	ディフューズライトのカラーを取得。
		 */
		const CVector4& GetDiffuseLightColor( u32 no ) const
		{
			TK_ASSERT( no < NUM_DIFFUSE_LIGHT, "error" );
			return m_diffuseLightColor[no];
		}
		/*!
		 *@brief	環境光を取得。
		 */
		const CVector3& GetAmbientLight() const
		{
			return m_ambientLight;
		}
		/*!
		 *@brief	環境光を設定。
		 */
		void SetAmbinetLight( const CVector3& ambient )
		{
			m_ambientLight;
		}
	private:
		CVector3		m_diffuseLightDirection[NUM_DIFFUSE_LIGHT];		//!<ディフューズライトの向き。
		CVector4		m_diffuseLightColor[NUM_DIFFUSE_LIGHT];			//!<ディフューズライトのカラー(x:R成分、y:G成分、z:B成分、w:スペキュラの強さ)。
		CVector3		m_ambientLight;									//!<アンビエントライト。
	};
}
#endif // _TKLIGHT_H_