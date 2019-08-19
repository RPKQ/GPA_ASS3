#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex; // 0
uniform float windowW; // GeeXLab built-in
uniform float windowH; // GeeXLab built-in

const float rnd_factor = 0.05;
const float rnd_scale = 2.1;
const vec2 v1 = vec2(92.0, 80.0);
const vec2 v2 = vec2(100.0, 62.0);

float rand(vec2 co)
{
  return fract(sin(dot(co ,v1)) + cos(dot(co ,v2))* rnd_scale);
}

void main() 
{ 
	vec2 uv = vertexData.texCoord;
  
	vec2 rnd = vec2(rand(uv.xy), rand(uv.yx));  
	fragColor = texture(tex, uv + rnd * rnd_factor);  
  
}