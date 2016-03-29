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
	typedef enum CULL {
		CULL_NONE	= D3DCULL_NONE,
		CULL_CW		= D3DCULL_CW,
		CULL_CCW    = D3DCULL_CCW,
		CULL_FORCE_DWORD = D3DCULL_FORCE_DWORD,
	} D3DCULL;
}

#endif //_TKGRAPHICSTYPE_H_