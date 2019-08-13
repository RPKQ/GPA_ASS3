#version 410

in VertexData
{
	vec3 fragCoord;
	vec3 normal;
    vec2 texCoord;
} vertexData;

layout(location = 0) out vec4 fragColor;

uniform int useTex;
uniform sampler2D tex;
uniform vec3 lightPos;

void main()
{
    vec3 texColor = texture(tex,vertexData.texCoord).rgb;

	const vec3 lightColor = vec3(1.0);
	const vec3 red = vec3(1.0, 0.0, 0.0);
	const vec3 grey = vec3(0.8, 0.8, 0.8);

	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
	vec3 norm = normalize(vertexData.normal);
    vec3 lightDir = normalize(lightPos - vertexData.fragCoord);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
	vec3 result = (useTex == 1)? (ambient + diffuse) * texColor : (ambient + diffuse) * grey;
    fragColor = vec4(result, 1.0);
}