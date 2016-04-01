/*!
 *@brief	グラフィックス関係の型定義
 */
 
#ifndef _TKGRAPHICSTYPE_H_
#define _TKGRAPHICSTYPE_H_

namespace tkEngine{
	/*!
	 *@brief	ビューポート。
	 */
	struct SViewport{
		u32		x;		//!<ビューポートの左上のx座標(スクリーン座標系)
		u32		y;		//!<ビューポートの左上のy座標(スクリーン座標系)
		u32		width;	//!<ビューポートの幅。
		u32		height;	//!<ビューポートの高さ。
		f32		minZ;	//!<近平面。
		f32		maxZ;	//!<遠平面。
	};
	
	/*!
	 * @brief	レンダリングステートタイプ
	 */
	enum ERenderStateType {
		RS_ZENABLE                   = D3DRS_ZENABLE                   ,
		RS_FILLMODE                  = D3DRS_FILLMODE                  ,
		RS_SHADEMODE                 = D3DRS_SHADEMODE                 ,
		RS_ZWRITEENABLE              = D3DRS_ZWRITEENABLE              ,
		RS_ALPHATESTENABLE           = D3DRS_ALPHATESTENABLE           ,
		RS_LASTPIXEL                 = D3DRS_LASTPIXEL                 ,
		RS_SRCBLEND                  = D3DRS_SRCBLEND                  ,
		RS_DESTBLEND                 = D3DRS_DESTBLEND                 ,
		RS_CULLMODE                  = D3DRS_CULLMODE                  ,
		RS_ZFUNC                     = D3DRS_ZFUNC                     ,
		RS_ALPHAREF                  = D3DRS_ALPHAREF                  ,
		RS_ALPHAFUNC                 = D3DRS_ALPHAFUNC                 ,
		RS_DITHERENABLE              = D3DRS_DITHERENABLE              ,
		RS_ALPHABLENDENABLE          = D3DRS_ALPHABLENDENABLE          ,
		RS_FOGENABLE                 = D3DRS_FOGENABLE                 ,
		RS_SPECULARENABLE            = D3DRS_SPECULARENABLE            ,
		RS_FOGCOLOR                  = D3DRS_FOGCOLOR                  ,
		RS_FOGTABLEMODE              = D3DRS_FOGTABLEMODE              ,
		RS_FOGSTART                  = D3DRS_FOGSTART                  ,
		RS_FOGEND                    = D3DRS_FOGEND                    ,
		RS_FOGDENSITY                = D3DRS_FOGDENSITY                ,
		RS_RANGEFOGENABLE            = D3DRS_RANGEFOGENABLE            ,
		RS_STENCILENABLE             = D3DRS_STENCILENABLE             ,
		RS_STENCILFAIL               = D3DRS_STENCILFAIL               ,
		RS_STENCILZFAIL              = D3DRS_STENCILZFAIL              ,
		RS_STENCILPASS               = D3DRS_STENCILPASS               ,
		RS_STENCILFUNC               = D3DRS_STENCILFUNC               ,
		RS_STENCILREF                = D3DRS_STENCILREF                ,
		RS_STENCILMASK               = D3DRS_STENCILMASK               ,
		RS_STENCILWRITEMASK          = D3DRS_STENCILWRITEMASK          ,
		RS_TEXTUREFACTOR             = D3DRS_TEXTUREFACTOR             ,
		RS_WRAP0                     = D3DRS_WRAP0                     ,
		RS_WRAP1                     = D3DRS_WRAP1                     ,
		RS_WRAP2                     = D3DRS_WRAP2                     ,
		RS_WRAP3                     = D3DRS_WRAP3                     ,
		RS_WRAP4                     = D3DRS_WRAP4                     ,
		RS_WRAP5                     = D3DRS_WRAP5                     ,
		RS_WRAP6                     = D3DRS_WRAP6                     ,
		RS_WRAP7                     = D3DRS_WRAP7                     ,
		RS_CLIPPING                  = D3DRS_CLIPPING                  ,
		RS_LIGHTING                  = D3DRS_LIGHTING                  ,
		RS_AMBIENT                   = D3DRS_AMBIENT                   ,
		RS_FOGVERTEXMODE             = D3DRS_FOGVERTEXMODE             ,
		RS_COLORVERTEX               = D3DRS_COLORVERTEX               ,
		RS_LOCALVIEWER               = D3DRS_LOCALVIEWER               ,
		RS_NORMALIZENORMALS          = D3DRS_NORMALIZENORMALS          ,
		RS_DIFFUSEMATERIALSOURCE     = D3DRS_DIFFUSEMATERIALSOURCE     ,
		RS_SPECULARMATERIALSOURCE    = D3DRS_SPECULARMATERIALSOURCE    ,
		RS_AMBIENTMATERIALSOURCE     = D3DRS_AMBIENTMATERIALSOURCE     ,
		RS_EMISSIVEMATERIALSOURCE    = D3DRS_EMISSIVEMATERIALSOURCE    ,
		RS_VERTEXBLEND               = D3DRS_VERTEXBLEND               ,
		RS_CLIPPLANEENABLE           = D3DRS_CLIPPLANEENABLE           ,
		RS_POINTSIZE                 = D3DRS_POINTSIZE                 ,
		RS_POINTSIZE_MIN             = D3DRS_POINTSIZE_MIN             ,
		RS_POINTSPRITEENABLE         = D3DRS_POINTSPRITEENABLE         ,
		RS_POINTSCALEENABLE          = D3DRS_POINTSCALEENABLE          ,
		RS_POINTSCALE_A              = D3DRS_POINTSCALE_A              ,
		RS_POINTSCALE_B              = D3DRS_POINTSCALE_B              ,
		RS_POINTSCALE_C              = D3DRS_POINTSCALE_C              ,
		RS_MULTISAMPLEANTIALIAS      = D3DRS_MULTISAMPLEANTIALIAS      ,
		RS_MULTISAMPLEMASK           = D3DRS_MULTISAMPLEMASK           ,
		RS_PATCHEDGESTYLE            = D3DRS_PATCHEDGESTYLE            ,
		RS_DEBUGMONITORTOKEN         = D3DRS_DEBUGMONITORTOKEN         ,
		RS_POINTSIZE_MAX             = D3DRS_POINTSIZE_MAX             ,
		RS_INDEXEDVERTEXBLENDENABL   = D3DRS_INDEXEDVERTEXBLENDENABLE  ,
		RS_COLORWRITEENABLE          = D3DRS_COLORWRITEENABLE          ,
		RS_TWEENFACTOR               = D3DRS_TWEENFACTOR               ,
		RS_BLENDOP                   = D3DRS_BLENDOP                   ,
		RS_POSITIONDEGREE            = D3DRS_POSITIONDEGREE            ,
		RS_NORMALDEGREE              = D3DRS_NORMALDEGREE              ,
		RS_SCISSORTESTENABLE         = D3DRS_SCISSORTESTENABLE         ,
		RS_SLOPESCALEDEPTHBIAS       = D3DRS_SLOPESCALEDEPTHBIAS       ,
		RS_ANTIALIASEDLINEENABLE     = D3DRS_ANTIALIASEDLINEENABLE     ,
		RS_MINTESSELLATIONLEVEL      = D3DRS_MINTESSELLATIONLEVEL      ,
		RS_MAXTESSELLATIONLEVEL      = D3DRS_MAXTESSELLATIONLEVEL      ,
		RS_ADAPTIVETESS_X            = D3DRS_ADAPTIVETESS_X            ,
		RS_ADAPTIVETESS_Y            = D3DRS_ADAPTIVETESS_Y            ,
		RS_ADAPTIVETESS_Z            = D3DRS_ADAPTIVETESS_Z            ,
		RS_ADAPTIVETESS_W            = D3DRS_ADAPTIVETESS_W            ,
		RS_ENABLEADAPTIVETESSELLAT   = D3DRS_ENABLEADAPTIVETESSELLATION,
		RS_TWOSIDEDSTENCILMODE       = D3DRS_TWOSIDEDSTENCILMODE       ,
		RS_CCW_STENCILFAIL           = D3DRS_CCW_STENCILFAIL           ,
		RS_CCW_STENCILZFAIL          = D3DRS_CCW_STENCILZFAIL          ,
		RS_CCW_STENCILPASS           = D3DRS_CCW_STENCILPASS           ,
		RS_CCW_STENCILFUNC           = D3DRS_CCW_STENCILFUNC           ,
		RS_COLORWRITEENABLE1         = D3DRS_COLORWRITEENABLE1         ,
		RS_COLORWRITEENABLE2         = D3DRS_COLORWRITEENABLE2         ,
		RS_COLORWRITEENABLE3         = D3DRS_COLORWRITEENABLE3         ,
		RS_BLENDFACTOR               = D3DRS_BLENDFACTOR               ,
		RS_SRGBWRITEENABLE           = D3DRS_SRGBWRITEENABLE           ,
		RS_DEPTHBIAS                 = D3DRS_DEPTHBIAS                 ,
		RS_WRAP8                     = D3DRS_WRAP8                     ,
		RS_WRAP9                     = D3DRS_WRAP9                     ,
		RS_WRAP10                    = D3DRS_WRAP10                    ,
		RS_WRAP11                    = D3DRS_WRAP11                    ,
		RS_WRAP12                    = D3DRS_WRAP12                    ,
		RS_WRAP13                    = D3DRS_WRAP13                    ,
		RS_WRAP14                    = D3DRS_WRAP14                    ,
		RS_WRAP15                    = D3DRS_WRAP15                    ,
		RS_SEPARATEALPHABLENDENABL   = D3DRS_SEPARATEALPHABLENDENABLE  ,
		RS_SRCBLENDALPHA             = D3DRS_SRCBLENDALPHA             ,
		RS_DESTBLENDALPHA            = D3DRS_DESTBLENDALPHA            ,
		RS_BLENDOPALPHA              = D3DRS_BLENDOPALPHA              ,
		RS_FORCE_DWORD               = D3DRS_FORCE_DWORD               ,
	};
	/*!
	 *@brief	D3DCULLに一対一で対応する列挙。
	 */
	enum ECull {
		CULL_NONE	= D3DCULL_NONE,
		CULL_CW		= D3DCULL_CW,
		CULL_CCW    = D3DCULL_CCW,
		CULL_FORCE_DWORD = D3DCULL_FORCE_DWORD,
	};
	/*!
	 *@brief	D3DFORMATに一対一で対応する列挙。
	 */
	enum EFormat{
		FMT_UNKNOWN             = D3DFMT_UNKNOWN              ,
	    FMT_R8G8B8              = D3DFMT_R8G8B8               ,
	    FMT_A8R8G8B8            = D3DFMT_A8R8G8B8             ,
	    FMT_X8R8G8B8            = D3DFMT_X8R8G8B8             ,
	    FMT_R5G6B5              = D3DFMT_R5G6B5               ,
	    FMT_X1R5G5B5            = D3DFMT_X1R5G5B5             ,
	    FMT_A1R5G5B5            = D3DFMT_A1R5G5B5             ,
	    FMT_A4R4G4B4            = D3DFMT_A4R4G4B4             ,
	    FMT_R3G3B2              = D3DFMT_R3G3B2               ,
	    FMT_A8                  = D3DFMT_A8                   ,
	    FMT_A8R3G3B2            = D3DFMT_A8R3G3B2             ,
	    FMT_X4R4G4B4            = D3DFMT_X4R4G4B4             ,
	    FMT_A2B10G10R10         = D3DFMT_A2B10G10R10          ,
	    FMT_A8B8G8R8            = D3DFMT_A8B8G8R8             ,
	    FMT_X8B8G8R8            = D3DFMT_X8B8G8R8             ,
	    FMT_G16R16              = D3DFMT_G16R16               ,
	    FMT_A2R10G10B10         = D3DFMT_A2R10G10B10          ,
	    FMT_A16B16G16R16        = D3DFMT_A16B16G16R16         ,
	    FMT_A8P8                = D3DFMT_A8P8                 ,
	    FMT_P8                  = D3DFMT_P8                   ,
	    FMT_L8                  = D3DFMT_L8                   ,
	    FMT_A8L8                = D3DFMT_A8L8                 ,
	    FMT_A4L4                = D3DFMT_A4L4                 ,
	    FMT_V8U8                = D3DFMT_V8U8                 ,
	    FMT_L6V5U5              = D3DFMT_L6V5U5               ,
	    FMT_X8L8V8U8            = D3DFMT_X8L8V8U8             ,
	    FMT_Q8W8V8U8            = D3DFMT_Q8W8V8U8             ,
	    FMT_V16U16              = D3DFMT_V16U16               ,
	    FMT_A2W10V10U10         = D3DFMT_A2W10V10U10          ,
	    FMT_UYVY                = D3DFMT_UYVY                 ,
	    FMT_R8G8_B8G8           = D3DFMT_R8G8_B8G8            ,
	    FMT_YUY2                = D3DFMT_YUY2                 ,
	    FMT_G8R8_G8B8           = D3DFMT_G8R8_G8B8            ,
	    FMT_DXT1                = D3DFMT_DXT1                 ,
	    FMT_DXT2                = D3DFMT_DXT2                 ,
	    FMT_DXT3                = D3DFMT_DXT3                 ,
	    FMT_DXT4                = D3DFMT_DXT4                 ,
	    FMT_DXT5                = D3DFMT_DXT5                 ,
	    FMT_D16_LOCKABLE        = D3DFMT_D16_LOCKABLE         ,
	    FMT_D32                 = D3DFMT_D32                  ,
	    FMT_D15S1               = D3DFMT_D15S1                ,
	    FMT_D24S8               = D3DFMT_D24S8                ,
	    FMT_D24X8               = D3DFMT_D24X8                ,
	    FMT_D24X4S4             = D3DFMT_D24X4S4              ,
	    FMT_D16                 = D3DFMT_D16                  ,
	    FMT_D32F_LOCKABLE       = D3DFMT_D32F_LOCKABLE        ,
	    FMT_D24FS8              = D3DFMT_D24FS8               ,
	/* D3D9Ex only -- */
	#if !defined(D3D_DISABLE_9EX)

	    /* Z-Stencil formats valid for CPU access */
	    FMT_D32_LOCKABLE        = D3DFMT_D32_LOCKABLE         ,
	    FMT_S8_LOCKABLE         = D3DFMT_S8_LOCKABLE          ,

	#endif // !D3D_DISABLE_9EX
	/* -- D3D9Ex only */


	    FMT_L16                 = D3DFMT_L16                  ,
        
	    FMT_VERTEXDATA          = D3DFMT_VERTEXDATA           ,
	    FMT_INDEX16             = D3DFMT_INDEX16              ,
	    FMT_INDEX32             = D3DFMT_INDEX32              ,
        
	    FMT_Q16W16V16U16        = D3DFMT_Q16W16V16U16         ,
        
	    FMT_MULTI2_ARGB8        = D3DFMT_MULTI2_ARGB8         ,

	    // Floating point surface formats

	    // s10e5 formats (16-bits per channel)
	    FMT_R16F                = D3DFMT_R16F                 ,
	    FMT_G16R16F             = D3DFMT_G16R16F              ,
	    FMT_A16B16G16R16F       = D3DFMT_A16B16G16R16F        ,

	    // IEEE s23e8 formats (32-bits per channel)
	    FMT_R32F                = D3DFMT_R32F                 ,
	    FMT_G32R32F             = D3DFMT_G32R32F              ,
	    FMT_A32B32G32R32F       = D3DFMT_A32B32G32R32F        ,
        
	    FMT_CxV8U8              = D3DFMT_CxV8U8               ,

	/* D3D9Ex only -- */
	#if !defined(D3D_DISABLE_9EX)

	    // Monochrome 1 bit per pixel format
	    FMT_A1                   = D3DFMT_A1                   ,

	    // 2.8 biased fixed point
	    FMT_A2B10G10R10_XR_BIAS  = D3DFMT_A2B10G10R10_XR_BIAS  ,


	    // Binary format indicating that the data has no inherent type
	    FMT_BINARYBUFFER          = D3DFMT_BINARYBUFFER         ,
	    
	#endif // !D3D_DISABLE_9EX
	/* -- D3D9Ex only */


	    FMT_FORCE_DWORD           = D3DFMT_FORCE_DWORD          ,
	};
	/*!
	 *@brief	D3DMULTISAMPLE_TYPEと一対一で対応した列挙。
	 */
	enum EMultisampleType {
		MULTISAMPLE_NONE            = D3DMULTISAMPLE_NONE            ,
	    MULTISAMPLE_NONMASKABLE     = D3DMULTISAMPLE_NONMASKABLE     ,
	    MULTISAMPLE_2_SAMPLES       = D3DMULTISAMPLE_2_SAMPLES       ,
	    MULTISAMPLE_3_SAMPLES       = D3DMULTISAMPLE_3_SAMPLES       ,
	    MULTISAMPLE_4_SAMPLES       = D3DMULTISAMPLE_4_SAMPLES       ,
	    MULTISAMPLE_5_SAMPLES       = D3DMULTISAMPLE_5_SAMPLES       ,
	    MULTISAMPLE_6_SAMPLES       = D3DMULTISAMPLE_6_SAMPLES       ,
	    MULTISAMPLE_7_SAMPLES       = D3DMULTISAMPLE_7_SAMPLES       ,
	    MULTISAMPLE_8_SAMPLES       = D3DMULTISAMPLE_8_SAMPLES       ,
	    MULTISAMPLE_9_SAMPLES       = D3DMULTISAMPLE_9_SAMPLES       ,
	    MULTISAMPLE_10_SAMPLES      = D3DMULTISAMPLE_10_SAMPLES      ,
	    MULTISAMPLE_11_SAMPLES      = D3DMULTISAMPLE_11_SAMPLES      ,
	    MULTISAMPLE_12_SAMPLES      = D3DMULTISAMPLE_12_SAMPLES      ,
	    MULTISAMPLE_13_SAMPLES      = D3DMULTISAMPLE_13_SAMPLES      ,
	    MULTISAMPLE_14_SAMPLES      = D3DMULTISAMPLE_14_SAMPLES      ,
	    MULTISAMPLE_15_SAMPLES      = D3DMULTISAMPLE_15_SAMPLES      ,
	    MULTISAMPLE_16_SAMPLES      = D3DMULTISAMPLE_16_SAMPLES      ,
        
	    MULTISAMPLE_FORCE_DWORD     = D3DMULTISAMPLE_FORCE_DWORD     ,
	};
}

#endif //_TKGRAPHICSTYPE_H_