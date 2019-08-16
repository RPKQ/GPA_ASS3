#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform float time;
uniform sampler2D tex;

void main()
{
	const float shakeness = 0.02;
	const float curliness = 8;
	float offset = time / 1500.0;
	float sampleX = vertexData.texCoord.x + sin(vertexData.texCoord.y * curliness + offset) * shakeness;
	float sampleY = vertexData.texCoord.y;
	fragColor = texture(tex, vec2(sampleX, sampleY));

}
