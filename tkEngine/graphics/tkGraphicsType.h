/*!
 *@brief	グラフィックス関係の型定義
 */
 
#ifndef _TKGRAPHICSTYPE_H_
#define _TKGRAPHICSTYPE_H_

namespace tkEngine{
	typedef D3DVIEWPORT9	SViewport;
	

//	typedef D3DVERTEXELEMENT9			SVertexElement;
	typedef IDirect3DVertexDeclaration9  SVertexDecralation;
	/*!
	 * @brief	D3DDECLTYPEと一体一で対応した列挙
	 */
	enum EDeclType
	{
		DECLTYPE_FLOAT1    = D3DDECLTYPE_FLOAT1 , 	 	// 1D float expanded to (value, 0., 0., 1.)
		DECLTYPE_FLOAT2    = D3DDECLTYPE_FLOAT2 ,  		// 2D float expanded to (value, value, 0., 1.)
		DECLTYPE_FLOAT3    = D3DDECLTYPE_FLOAT3 ,  		// 3D float expanded to (value, value, value, 1.)
		DECLTYPE_FLOAT4    = D3DDECLTYPE_FLOAT4 ,  		// 4D float
		DECLTYPE_D3DCOLOR  = D3DDECLTYPE_D3DCOLOR ,  	// 4D packed unsigned bytes mapped to 0. to 1. range
													// Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
		DECLTYPE_UBYTE4    = D3DDECLTYPE_UBYTE4 ,  		// 4D unsigned byte
		DECLTYPE_SHORT2    = D3DDECLTYPE_SHORT2 ,  		// 2D signed short expanded to (value, value, 0., 1.)
		DECLTYPE_SHORT4    = D3DDECLTYPE_SHORT4 ,  		// 4D signed short
        
													// The following types are valid only with vertex shaders >= 2.0
        
        
		DECLTYPE_UBYTE4N   = D3DDECLTYPE_UBYTE4N,  		// Each of 4 bytes is normalized by dividing to 255.0
		DECLTYPE_SHORT2N   = D3DDECLTYPE_SHORT2N,  		// 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
		DECLTYPE_SHORT4N   = D3DDECLTYPE_SHORT4N,  		// 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
		DECLTYPE_USHORT2N  = D3DDECLTYPE_USHORT2N,  	// 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
		DECLTYPE_USHORT4N  = D3DDECLTYPE_USHORT4N,  	// 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
		DECLTYPE_UDEC3     = D3DDECLTYPE_UDEC3,  		// 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
		DECLTYPE_DEC3N     = D3DDECLTYPE_DEC3N,  		// 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
		DECLTYPE_FLOAT16_2 = D3DDECLTYPE_FLOAT16_2, 	// Two 16-bit floating point values, expanded to (value, value, 0, 1)
		DECLTYPE_FLOAT16_4 = D3DDECLTYPE_FLOAT16_4,  	// Four 16-bit floating point values
		DECLTYPE_UNUSED    = D3DDECLTYPE_UNUSED,  		// When the type field in a decl is unused.
	};
	/*!
	 * @brief	D3DDECLMETHODと一体一で対応した列挙。
	 */
	enum EDeclMethod
	{
		 DECLMETHOD_DEFAULT 			= D3DDECLMETHOD_DEFAULT,
		 DECLMETHOD_PARTIALU			= D3DDECLMETHOD_PARTIALU,
		 DECLMETHOD_PARTIALV			= D3DDECLMETHOD_PARTIALV,
		 DECLMETHOD_CROSSUV				= D3DDECLMETHOD_CROSSUV,    // Normal
		 DECLMETHOD_UV					= D3DDECLMETHOD_UV,
		 DECLMETHOD_LOOKUP				= D3DDECLMETHOD_LOOKUP,               // Lookup a displacement map
		 DECLMETHOD_LOOKUPPRESAMPLED	= D3DDECLMETHOD_LOOKUPPRESAMPLED,     // Lookup a pre-sampled displacement map
	};

	// Vertex element semantics
	//
	/*!
	 * @brief	D3DDECLUSAGEと一体一で対応した列挙。
	 */
	enum EDeclUsage
	{
		DECLUSAGE_POSITION 			= D3DDECLUSAGE_POSITION,
		DECLUSAGE_BLENDWEIGHT   	= D3DDECLUSAGE_BLENDWEIGHT,   // 1
		DECLUSAGE_BLENDINDICES   	= D3DDECLUSAGE_BLENDINDICES,  // 2
		DECLUSAGE_NORMAL	        = D3DDECLUSAGE_NORMAL,        // 3
		DECLUSAGE_PSIZE				= D3DDECLUSAGE_PSIZE,         // 4
		DECLUSAGE_TEXCOORD			= D3DDECLUSAGE_TEXCOORD,      // 5
		DECLUSAGE_TANGENT			= D3DDECLUSAGE_TANGENT,       // 6
		DECLUSAGE_BINORMAL			= D3DDECLUSAGE_BINORMAL,      // 7
		DECLUSAGE_TESSFACTOR		= D3DDECLUSAGE_TESSFACTOR,    // 8
		DECLUSAGE_POSITIONT			= D3DDECLUSAGE_POSITIONT,     // 9
		DECLUSAGE_COLOR				= D3DDECLUSAGE_COLOR,         // 10
		DECLUSAGE_FOG				= D3DDECLUSAGE_FOG,           // 11
		DECLUSAGE_DEPTH				= D3DDECLUSAGE_DEPTH,         // 12
		DECLUSAGE_SAMPLE			= D3DDECLUSAGE_SAMPLE,        // 13
	};
	enum BLEND {
	    BLEND_ZERO                  = D3DBLEND_ZERO              ,
	    BLEND_ONE                   =D3DBLEND_ONE                ,
	    BLEND_SRCCOLOR              =D3DBLEND_SRCCOLOR           ,
	    BLEND_INVSRCCOLOR           =D3DBLEND_INVSRCCOLOR        ,
	    BLEND_SRCALPHA              =D3DBLEND_SRCALPHA           ,
	    BLEND_INVSRCALPHA           =D3DBLEND_INVSRCALPHA        ,
	    BLEND_DESTALPHA             =D3DBLEND_DESTALPHA          ,
	    BLEND_INVDESTALPHA          =D3DBLEND_INVDESTALPHA       ,
	    BLEND_DESTCOLOR             =D3DBLEND_DESTCOLOR          ,
	    BLEND_INVDESTCOLOR          =D3DBLEND_INVDESTCOLOR       ,
	    BLEND_SRCALPHASAT           =D3DBLEND_SRCALPHASAT        ,
	    BLEND_BOTHSRCALPHA          =D3DBLEND_BOTHSRCALPHA       ,
	    BLEND_BOTHINVSRCALPHA       =D3DBLEND_BOTHINVSRCALPHA    ,
	    BLEND_BLENDFACTOR           =D3DBLEND_BLENDFACTOR        ,
	    BLEND_INVBLENDFACTOR        =D3DBLEND_INVBLENDFACTOR     ,
	/* D3D9Ex only -- *//* D3D9Ex only -- */
	#if !defined(D3D_DISABLE_9EX)
    
	    BLEND_SRCCOLOR2             =D3DBLEND_SRCCOLOR2          ,
	    BLEND_INVSRCCOLOR2          =D3DBLEND_INVSRCCOLOR2       ,
    
	#endif // !D3D_DISABLE_9EX
	/* -- D3D9Ex only *//* -- D3D9Ex only */
	    BLEND_FORCE_DWORD           =D3DBLEND_FORCE_DWORD        ,
	};

	enum CMPFUNC {
		CMP_NEVER				= D3DCMP_NEVER 		,
		CMP_LESS				= D3DCMP_LESS			,
		CMP_EQUAL				= D3DCMP_EQUAL			,
		CMP_LESSEQUAL			= D3DCMP_LESSEQUAL	,
		CMP_GREATER				= D3DCMP_GREATER		,
		CMP_NOTEQUAL			= D3DCMP_NOTEQUAL		,
		CMP_GREATEREQUAL		= D3DCMP_GREATEREQUAL ,
		CMP_ALWAYS				= D3DCMP_ALWAYS		,
		CMP_FORCE_DWORD         = D3DCMP_FORCE_DWORD	
	};


}

#endif //_TKGRAPHICSTYPE_H_