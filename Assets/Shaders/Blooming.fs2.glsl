#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
	// origin >> color
	/*vec4 color = texture(tex, vertexData.texCoord);

	// blur 1 >> color1
	int half_size = 2;
	vec4 color_sum = vec4(0);
	for (int i = -half_size; i <= half_size ; ++i) {
		for (int j = -half_size; j <= half_size ; ++j) {
			ivec2 coord = ivec2(gl_FragCoord.xy) + ivec2(i, j);
			color_sum += texelFetch(tex, coord, 0); 
		} 
	} 
	int sample_count = (half_size * 2 + 1) * (half_size * 2 + 1);
	vec4 color1 = color_sum / sample_count;

	// blur 2 >> color2
	half_size = 4;
	color_sum = vec4(0);
	for (int i = -half_size; i <= half_size ; ++i) {
		for (int j = -half_size; j <= half_size ; ++j) {
			ivec2 coord = ivec2(gl_FragCoord.xy) + ivec2(i, j);
			color_sum += texelFetch(tex, coord, 0); 
		} 
	} 
	sample_count = (half_size * 2 + 1) * (half_size * 2 + 1);
	vec4 color2 = color_sum / sample_count;


	// final
	fragColor = color * color1 * color2 * 4.5;*/

	const float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
	vec2 tex_offset = 1.0 / textureSize(tex, 0); // gets size of single texel
    vec3 result = texture(tex, vertexData.texCoord).rgb * weight[0]; // current fragment's contribution

    for(int i = 1; i < 5; ++i)
    {
        result += texture(tex, vertexData.texCoord + vec2(tex_offset.x * i, tex_offset.y * i)).rgb * weight[i];
        result += texture(tex, vertexData.texCoord - vec2(tex_offset.x * i, tex_offset.y * i)).rgb * weight[i];
    }
    fragColor = vec4(result, 1.0) * 1.5;

}
