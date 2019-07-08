struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float3 inColor : COLOR;
};



float3 main(PS_INPUT inPixel) : SV_TARGET
{
    return inPixel.inColor;
}