#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
	vec3 texColor = texture(tex, vertexData.texCoord).rgb;
	fragColor = vec4(1.0 - texColor.x, 1.0 - texColor.y, 1.0 - texColor.z, 1.0);
}
