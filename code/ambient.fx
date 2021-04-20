//basic ambient light shader with no texture support

float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 WorldInverseTranspose;

float3 LightVector = float3(1, 0, 0);
float4 LightColor = float4(1, 1, 1, 1);
float  LightPower = 0.6;


struct MyVertexInput
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD0;
    float4 normal   : NORMAL;
};

struct MyVertexOutput
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD0;
    float4 color    : COLOR0;
};

MyVertexOutput VertexShaderFunction(MyVertexInput input_param)
{
    MyVertexOutput output = (MyVertexOutput)0;

    //combine world + view + projection Matrices
    float4x4 worldViewProj = mul(World, mul(View, Projection));

    // translate the current vertex
    output.position = mul(input_param.position, worldViewProj);

    float4 normal = mul(input_param.normal, WorldInverseTranspose);
    float intensity = dot(normal, LightVector);
    output.color = saturate(LightColor * LightPower * intensity);

    return output;
}

float4 PixelShaderFunction(MyVertexOutput input_param) : COLOR0
{
    float4 light = saturate(input_param.color + LightColor * LightPower);
    return light;  
}

technique DirectionalLight
{
    pass PO
    {
        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader  = compile ps_2_0 PixelShaderFunction();
        //FillMode = wireframe;
    }
}


