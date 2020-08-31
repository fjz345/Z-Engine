
struct VS_OUT
{
	float4 pos      : SV_Position;
};

VS_OUT VS_main(uint vID : SV_VertexID)
{
	// 0:ar output
	VS_OUT output = (VS_OUT)0;

	if(vID == 0)
	{
		output.pos = float4(0.0f, 0.5f, 0.0f, 0.0f);
	}
	else if(vID == 1)
	{
		output.pos = float4(0.45f, -0.5f, 0.0f, 0.0f);
	}
	else if(vID == 2)
	{
		output.pos = float4(-0.45f, -0.5f, 0.0f, 0.0f);
	}
	
	return output;
}