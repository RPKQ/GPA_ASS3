#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;
uniform vec2 center;

void main()
{
	const vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
	const float radius = 150.0f;
	const float magScale = 0.5f;
	vec2 curVec = gl_FragCoord.xy - center;
	if(curVec.x * curVec.x + curVec.y * curVec.y < radius * radius)
	{
		vec2 samplePoint = center + curVec * magScale;
		fragColor = texelFetch(tex, ivec2(samplePoint), 0);
	}
	else 
	{
		fragColor = texture(tex, vertexData.texCoord);
	}
}
