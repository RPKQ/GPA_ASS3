#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
	vec4 texture_color_Left = texture(tex, vertexData.texCoord - vec2(0.005,0.0));
	vec4 texture_color_Right = texture(tex, vertexData.texCoord + vec2(0.005,0.0));
	vec4 texture_color = vec4(texture_color_Left.r*0.29 + texture_color_Left.g*0.58 + texture_color_Left.b*0.114, texture_color_Right.g, texture_color_Right.b, 0.0);
	fragColor = texture_color;
}
