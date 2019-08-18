#version 410

in VertexData
{
    vec2 texCoord;
} vertexData;

out vec4 fragColor;

uniform sampler2D tex;
uniform float windowW;
uniform float windowH;

void main()
{
	// blur >> color
	int half_size = 2;
	vec4 color_sum = vec4(0);
	for (int i = -half_size; i <= half_size ; ++i) {
		for (int j = -half_size; j <= half_size ; ++j) {
			ivec2 coord = ivec2(gl_FragCoord.xy) + ivec2(i, j);
			color_sum += texelFetch(tex, coord, 0); 
		} 
	} 
	int sample_count = (half_size * 2 + 1) * (half_size * 2 + 1);
	vec4 color = color_sum / sample_count;

	// quantization >> color
	float nbins = 8.0;
	color = floor(color * nbins) / nbins; 
	fragColor = vec4(color.rgb, 1.0);

	// DOG
	float sigma_e = 2.0f;
	float sigma_r = 2.8f;
	float phi = 3.4f;
	float tau = 0.99f;
	float twoSigmaESquared = 2.0 * sigma_e * sigma_e;
	float twoSigmaRSquared = 2.0 * sigma_r * sigma_r;
	int halfWidth = int(ceil( 2.0 * sigma_r ));
	float img_size = windowH * windowW;
	vec2 sum = vec2(0.0);
	vec2 norm = vec2(0.0);
	for ( int i = -halfWidth; i <= halfWidth; ++i ) {
		for ( int j = -halfWidth; j <= halfWidth; ++j ) {
			float d = length(vec2(i,j));
			vec2 kernel= vec2( exp( -d * d / twoSigmaESquared ), exp( -d * d / twoSigmaRSquared ));
			vec4 c= texture(tex, vec2(vertexData.texCoord.x + i/windowW ,  vertexData.texCoord.y + j/windowH) );
			vec2 L= vec2(0.299 * c.r + 0.587 * c.g + 0.114 * c.b);
			norm += 2.0 * kernel;
			sum += kernel * L; 
		}
	}
	sum /= norm;
	float H = 100.0 * (sum.x - tau * sum.y);
	float edge = ( H > 0.0 )? 1.0 : 2.0 * smoothstep(-2.0, 2.0, phi * H );
	vec4 colorDOG = vec4(edge, edge, edge, 1.0 );

	// final
	fragColor = colorDOG * color;


}
