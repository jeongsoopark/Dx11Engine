


float4 main(float3 inPosition : POSITION) : SV_POSITION
{
    return float4(inPosition.x, inPosition.y, inPosition.z, 1.0);
}