#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
	const float weight = 0.09f;
	const float offScale = 0.002f;
	const vec2 offsets[9] =
	{
		vec2(-offScale, -offScale), vec2(0, -offScale), vec2(offScale, -offScale),
		vec2(-offScale, 0), vec2(0, 0), vec2(offScale, 0),
		vec2(-offScale, offScale), vec2(0, offScale), vec2(offScale, offScale)
	};

	const float mFilter[9] = 
	{
		1.0f, 2.0f, 1.0f,
		2.0f, 4.0, 2.0,
		1.0f, 2.0f, 1.0f
	};

    vec4 sum = vec4(0.0f);
    for(int i=0; i<9; i++)
		sum += texture(tex, vertexData.texCoord + offsets[i]) * mFilter[i];
	fragColor = sum * weight;

}
