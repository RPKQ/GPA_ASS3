#version 410

in VertexData
{
	vec3 fragCoord;
	vec3 normal;
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

void main()
{
	vec3 texColor = normalize(vertexData.normal);
	vec3 result = vec3(max(texColor.x, 0), max(texColor.y, 0), max(texColor.z, 0));
	fragColor = vec4(result, 1.0);
}
