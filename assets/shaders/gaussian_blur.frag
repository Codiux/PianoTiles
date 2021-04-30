uniform sampler2D	texture;
uniform vec2		textureSize;
uniform float		sigma;
uniform vec2		direction;

float CalcGauss( float x, float sigma )
{
	if ( sigma <= 0.0 )
		return 0.0;
	return exp( -(x*x) / (2.0 * sigma) ) / (2.0 * 3.14157 * sigma);
}

void main()
{
	vec2 texC     = gl_TexCoord[0].xy;
	vec4 texCol   = texture2D( texture, texC );
	vec4 gaussCol = vec4( texCol.rgb, 1.0 );
	vec2 step     = direction / textureSize;
	for ( int i = 1; i <= 32; ++ i )
	{
		float weight = CalcGauss( float(i) / 32.0, sigma * 0.5 );
		if ( weight < 1.0/255.0 )
			break;
		texCol    = texture2D( texture, texC + step * float(i) );
		gaussCol += vec4( texCol.rgb * weight, weight );
		texCol    = texture2D( texture, texC - step * float(i) );
		gaussCol += vec4( texCol.rgb * weight, weight );
	}
	gaussCol.rgb = clamp( gaussCol.rgb / gaussCol.w, 0.0, 1.0 );
	gl_FragColor = vec4( gaussCol.rgb, 1.0 );
}
