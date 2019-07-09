struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
};

Texture2D objTexture : TEXTURE : register(t0);

SamplerState objSamplerState : SAMPLER : register(s0);

float3 main(PS_INPUT inPixel) : SV_TARGET
{
    float3 texColor = objTexture.Sample(objSamplerState, inPixel.inTexCoord);

    return texColor;
}