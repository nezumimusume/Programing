/*!
 * @brief	大気錯乱をシミュレーションするためのパラメータ。
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	大気錯乱をシミュレーションするためのパラメータ。
	 */
	#pragma pack (4)
	struct SAtmosphericScatteringParam{
		CVector3 v3LightPos;
		CVector3 v3LightDirection;
		CVector3 v3InvWavelength;	// 1 / pow(wavelength, 4) for the red, green, and blue channels
		float fCameraHeight;		// The camera's current height
		float fCameraHeight2;		// fCameraHeight^2
		float fOuterRadius;		// The outer (atmosphere) radius
		float fOuterRadius2;		// fOuterRadius^2
		float fInnerRadius;		// The inner (planetary) radius
		float fInnerRadius2;		// fInnerRadius^2
		float fKrESun;				// Kr * ESun
		float fKmESun;				// Km * ESun
		float fKr4PI;				// Kr * 4 * PI
		float fKm4PI;				// Km * 4 * PI
		float fScale;				// 1 / (fOuterRadius - fInnerRadius)
		float fScaleDepth;
		float fScaleOverScaleDepth;// fScale / fScaleDepth
		float g;
		float g2;
	};
	#pragma pack ()
}