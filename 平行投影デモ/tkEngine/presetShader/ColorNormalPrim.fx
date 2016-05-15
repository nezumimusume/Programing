/*!
 *@brief	頂点カラー、法線ありのプリミティブ。
 */

float4x4	g_mWVP;					//ワールドビュープロジェクション行列。
float4x4	g_worldRotationMatrix;	//ワールド行列の回転成分。
#define NUM_DIFFUSE_LIGHT	4					//ディフューズライトの数。

struct SLight{
	float3	diffuseLightDir[NUM_DIFFUSE_LIGHT];		//ディフューズライトの向き。
	float4  diffuseLightColor[NUM_DIFFUSE_LIGHT];	//ディフューズライトのカラー。
	float3  ambient;								//アンビエントライト。
};
SLight	g_light;		//ライト

struct VS_INPUT{
	float4	pos		: POSITION;
	float3  normal	: NORMAL;
	float4	color 	: COLOR0;
};

struct VS_OUTPUT{
	float4 pos		: POSITION;
	float4 color	: COLOR0;
	float3 normal	: TEXCOORD0;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, g_mWVP);
	Out.color = In.color;
	Out.normal = mul(In.normal, g_worldRotationMatrix);
	//法線を回転。
	return Out;
}
/*!
 *@brief	ディフューズライトを計算。
 */	
float4 DiffuseLight( VS_OUTPUT In )
{
	float4 color = 0.0f;
	color += max( 0, dot(In.normal, g_light.diffuseLightDir[0])) * g_light.diffuseLightColor[0];
	color += max( 0, dot(In.normal, g_light.diffuseLightDir[1])) * g_light.diffuseLightColor[1];
	color += max( 0, dot(In.normal, g_light.diffuseLightDir[2])) * g_light.diffuseLightColor[2];
	color += max( 0, dot(In.normal, g_light.diffuseLightDir[3])) * g_light.diffuseLightColor[3];
	color.a = 1.0f;
	return color;
}
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	float4 color = DiffuseLight(In);
	color.xyz += g_light.ambient;
	color.xyz *= In.color.xyz;
	//トゥーン
/*	float t = dot(In.normal, g_light.diffuseLightDir[0]);
	t = t * 0.5f + 0.5f;
	if(t < 0.3f){
		color = In.color * 0.8f;
	}else{
		color = In.color;
	}
	color.w = 1.0f;*/
	return color;
}

technique ColorNormalPrim
{
    pass P0
    {          
        VertexShader = compile vs_2_0 VSMain();
        PixelShader  = compile ps_2_0 PSMain();
    }
}