struct VS_INPUT
{
    float3 inPosition : SV_POSITION;
    float3 inColor : COLOR;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float3 outColor : COLOR;
};

VS_OUTPUT main(VS_INPUT inVertex) 
{
    VS_OUTPUT vOut;
    vOut.outPosition = float4(inVertex.inPosition, 1.0);
    vOut.outColor = inVertex.inColor;

    return vOut;
}