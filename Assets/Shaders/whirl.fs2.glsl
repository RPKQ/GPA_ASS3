#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;
uniform float windowW;
uniform float windowH;
uniform vec2 center;


vec4 PostFX(sampler2D tex, vec2 uv)
{
	const float radius = 200.0;
	const float angle = 0.8;
	vec2 texSize = vec2(windowW, windowH);
	vec2 tc = uv * texSize;
	tc -= center;
	float dist = length(tc);
	if (dist < radius) 
	{
	float percent = (radius - dist) / radius;
	float theta = percent * percent * angle * 8.0;
	float s = sin(theta);
	float c = cos(theta);
	tc = vec2(dot(tc, vec2(c, -s)), dot(tc, vec2(s, c)));
	}
	tc += center;
	vec3 color = texture2D(tex, tc / texSize).rgb;
	return vec4(color, 1.0);
}

void main (void)
{
  vec2 uv = vertexData.texCoord;
  gl_FragColor = PostFX(tex, uv);
}