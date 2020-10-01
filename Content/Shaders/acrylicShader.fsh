#version 330
#if __VERSION__ < 130
#define TEXTURE2D texture2D
#else
#define TEXTURE2D texture
#endif

out vec4 fragColor;
in vec2 texCoord;


uniform int pass;

uniform sampler2D textureSampler;
uniform float tintOpacity;
uniform vec3 tintColor;
uniform float noiseOpacity;
uniform float height;
uniform float width;
uniform float v_offset;
uniform int blendMode;

uniform float offset[16] = float[]( 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0);
uniform float weight[16] = float[]( 0.06707, 0.066147, 0.063453, 0.059206, 0.053733, 0.047433, 0.040727, 0.034013, 0.02763, 0.021831, 0.016778, 0.012542, 0.009119, 0.006449, 0.004436, 0.002968 );


vec4 pass_1_skipBlurring()
{
    return TEXTURE2D(textureSampler, texCoord.xy);
}

vec4 pass_2_discreteGaussianBlur_vertical()
{
    vec2 uv = texCoord.xy;
    vec3 tc = TEXTURE2D(textureSampler, uv).rgb * weight[0];
    if (texCoord.x>(v_offset) && texCoord.x<(1.0f-v_offset) && texCoord.y>(v_offset) && texCoord.y<(1.0f-v_offset))
    {
          for (int i=1; i<16; i++)
          {
            tc += TEXTURE2D(textureSampler, uv + vec2(0.0,offset[i])/height, 0.0).rgb * weight[i];
            tc += TEXTURE2D(textureSampler, uv - vec2(0.0,offset[i])/height, 0.0).rgb * weight[i];
          }
    }
    else
    {
        tc = TEXTURE2D(textureSampler, texCoord.xy).rgb;
    }
    return vec4(tc, 1.0);
}

vec4 pass_3_discreteGaussianBlur_horizontal()
{
    vec2 uv = texCoord.xy;
    vec3 tc = TEXTURE2D(textureSampler, uv).rgb * weight[0];
    if (texCoord.x>(v_offset) && texCoord.x<(1.0f-v_offset) && texCoord.y>(v_offset) && texCoord.y<(1.0f-v_offset))
    {
        for (int i=1; i<16; i++)
        {
          tc += TEXTURE2D(textureSampler, uv + vec2(offset[i],0.0)/width, 0.0).rgb * weight[i];
          tc += TEXTURE2D(textureSampler, uv - vec2(offset[i],0.0)/width, 0.0).rgb * weight[i];
        }
    }
    else
    {
        tc = TEXTURE2D(textureSampler, texCoord.xy).rgb;
    }
    return vec4(tc, 1.0);
}

vec4 pass_4_tint_and_noise_blend()
{
    vec3 tc = vec3(0.0, 0.0, 0.0);
    vec2 uv = texCoord.xy;
    float colorValue = fract(sin(dot(texCoord.xy ,vec2(12.9898,78.233))) * 43758.5453);
    vec3 backgroundColor = TEXTURE2D(textureSampler, texCoord.xy).rgb;
	
    if (texCoord.x>(v_offset) && texCoord.x<(1.0f-v_offset) && texCoord.y>(v_offset) && texCoord.y<(1.0f-v_offset))
    {
        //Можно разбить режимы смешивания на отдельные сабрутины, чтобы не грузить GPU лишними условными операторами
        //EXCLUSION
        if(blendMode == 1) tc = backgroundColor + tintColor - 2*backgroundColor*tintColor;
        //SCREEN
        else if(blendMode == 2) tc = backgroundColor + tintColor - backgroundColor*tintColor;
        //MULTIPLY
        else if(blendMode == 3) tc = tintColor*backgroundColor;
        //LIGHTEN
        else if(blendMode == 4) tc = max(tintColor, backgroundColor);
        tc = mix(backgroundColor,tc, tintOpacity);
        if(blendMode == 0) tc = mix(backgroundColor, tintColor, tintOpacity);

        tc = mix(tc, vec3(colorValue,colorValue,colorValue), noiseOpacity);
    }
    else
    {
        tc = backgroundColor;
    }
    return vec4(tc, 1.0);
}

void main(void)
{
    //Для версий шейдеров 4.0 и выше можно использовать Shader Subroutine
         if( pass == 1 ) fragColor = pass_1_skipBlurring();
    else if( pass == 2 ) fragColor = pass_2_discreteGaussianBlur_vertical();
    else if( pass == 3 ) fragColor = pass_3_discreteGaussianBlur_horizontal();
    else if( pass == 4 ) fragColor = pass_4_tint_and_noise_blend();
}

