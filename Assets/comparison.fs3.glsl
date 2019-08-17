#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D texOrigin;
uniform sampler2D texFiltered;

void main()
{
	const vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
	if(gl_FragCoord.x > 500)
	{
		fragColor = texture(texOrigin, vertexData.texCoord);
	}
	else
	{
		fragColor = texture(texFiltered, vertexData.texCoord);
	}
}
