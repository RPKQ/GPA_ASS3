#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
    const float threshold = 0.1f;
	const float offScale = 0.002f;
	const vec2 offsets[9] =
	{
		vec2(-offScale, -offScale), vec2(0, -offScale), vec2(offScale, -offScale),
		vec2(-offScale, 0), vec2(0, 0), vec2(offScale, 0),
		vec2(-offScale, offScale), vec2(0, offScale), vec2(offScale, offScale)
	};

	const float mFilter[9] = 
	{
		-1.0f, -1.0f, -1.0f,
		-1.0f, 8.0, -1.0,
		-1.0f, -1.0f, -1.0f
	};

	vec4 sum = vec4(0.0f);
	for(int i=0; i<9; i++)
		sum += texture(tex, vertexData.texCoord + offsets[i]) * mFilter[i];
	sum /= 9.0f;

	vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
	float ave = (sum.x + sum.y + sum.z) / 3.0f;
	vec4 result;
	if(ave > threshold)
	{
		result = white;
	}
	else
	{
		result = black;
	}
	fragColor = result;
}
