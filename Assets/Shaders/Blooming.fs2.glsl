#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{

	// original >> color
	vec4 color = texture(tex, vertexData.texCoord);

	// blur 1 >> color1
	int half_size = 2;
	int texScale = 2;
	vec4 color_sum = vec4(0);
	for (int i = -half_size; i <= half_size ; ++i) {
		for (int j = -half_size; j <= half_size ; ++j) {
			ivec2 coord = ivec2(gl_FragCoord.xy) + ivec2(i * texScale, j * texScale);
			color_sum += texelFetch(tex, coord, 0); 
		} 
	} 
	int sample_count = (half_size * 2 + 1) * (half_size * 2 + 1);
	vec4 color1 = color_sum / sample_count;

	// blur 2 >> color2
	texScale = 3;
	color_sum = vec4(0);
	for (int i = -half_size; i <= half_size ; ++i) {
		for (int j = -half_size; j <= half_size ; ++j) {
			ivec2 coord = ivec2(gl_FragCoord.xy) + ivec2(i * texScale, j * texScale);
			color_sum += texelFetch(tex, coord, 0); 
		} 
	} 
	sample_count = (half_size * 2 + 1) * (half_size * 2 + 1);
	vec4 color2 = color_sum / sample_count;

	// final
	fragColor= color * 0.3 + color1 * 0.5 + color2 * 0.4;

}
