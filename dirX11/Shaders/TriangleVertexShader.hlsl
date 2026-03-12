float4 main(uint vertexID: SV_VertexID) : SV_POSITION
{
    float2 positions[3] =
    {
        float2( .8,  .5),
        float2( .5, -.5),
        float2(-.5, -.5)
    };
    return float4(positions[vertexID], 0, 1);

}