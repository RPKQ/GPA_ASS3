#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;

void main() 
{ 
	const float hatch_offset = 5.0; // 5.0
	const float threshold_1 = 1.0; // 1.0
	const float threshold_2 = 0.7; // 0.7
	const float threshold_3 = 0.5; // 0.5
	const float threshold_4 = 0.3; // 0.3

	vec2 uv = vertexData.texCoord;
	float brightness = length(texture(tex, uv).rgb);
	vec3 tc = vec3(1.0, 1.0, 1.0);
  
	if (brightness < threshold_1) 
	{
		if (mod(gl_FragCoord.x + gl_FragCoord.y, 10.0) == 0.0) 
		tc = vec3(0.0, 0.0, 0.0);
	}  
  
	if (brightness < threshold_2) 
	{
		if (mod(gl_FragCoord.x - gl_FragCoord.y, 10.0) == 0.0) 
		tc = vec3(0.0, 0.0, 0.0);
	}  
  
	if (brightness < threshold_3) 
	{
		if (mod(gl_FragCoord.x + gl_FragCoord.y - hatch_offset, 10.0) == 0.0) 
		tc = vec3(0.0, 0.0, 0.0);
	}  
  
	if (brightness < threshold_4) 
	{
		if (mod(gl_FragCoord.x - gl_FragCoord.y - hatch_offset, 10.0) == 0.0) 
		tc = vec3(0.0, 0.0, 0.0);
	}
  
	fragColor = vec4(tc, 1.0);
}