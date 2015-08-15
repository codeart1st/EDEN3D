cbuffer ConstantBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
}

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
};

VS_OUTPUT VShader(float4 Pos : POSITION, float4 normal : NORMAL) {

	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Color = float4(normal.x, normal.y, normal.z, 1.0);
	return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET {

	return color;
}
