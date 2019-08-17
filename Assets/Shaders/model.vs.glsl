#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out VertexData
{
	vec3 fragCoord;
	vec3 normal;
    vec2 texCoord;
} vertexData;

uniform mat4 pvMat;
uniform mat4 modelMat;

void main()
{
    gl_Position = pvMat * modelMat * vec4(position, 1.0);
    
	// output
	vertexData.fragCoord = vec3(modelMat * vec4(position, 1.0));
	vertexData.normal = mat3(transpose(inverse(modelMat))) * normal;
	vertexData.texCoord = texCoord;
}