cbuffer myCBuffer : register(b0)
{
    float4x4 mat;
};


struct VS_INPUT
{
    float3 inPosition : POSITION;
    float2 inTexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT inVertex) 
{
    VS_OUTPUT vOut;

    vOut.outPosition = mul(float4(inVertex.inPosition, 1.0f), mat);
    vOut.outTexCoord = inVertex.inTexCoord;

    return vOut;
}