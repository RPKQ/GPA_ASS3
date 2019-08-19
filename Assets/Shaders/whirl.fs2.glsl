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

void main (void)
{
	const float radius = 200.0;
	const float scale = 10.0;
	vec2 texSize = vec2(windowW, windowH);
	vec2 curPoint = vertexData.texCoord * texSize;
	vec2 curVec = curPoint - center;
	float dist = length(curVec);
	if (dist < radius) 
	{
		// get rotate magnitude 
		float percent = (radius - dist) / radius;
		float rotateAngle = percent * percent * scale;

		// rotate vector
		float s = sin(rotateAngle);
		float c = cos(rotateAngle);
		vec2 newVec = vec2(dot(curVec, vec2(c, -s)), dot(curVec, vec2(s, c)));

		// sample the texture
		fragColor = texture(tex, (newVec + center) / texSize);
	}
	else
	{
		fragColor = texture(tex, vertexData.texCoord);
	}
	
}