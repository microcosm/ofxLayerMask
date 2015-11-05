#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;
uniform sampler2DRect maskTex;
varying vec2 texCoordVarying;

void main()
{
    vec3 src = texture2DRect(tex0, texCoordVarying).rgb;
    float srcA = texture2DRect(tex0, texCoordVarying).a;
    float mask = texture2DRect(maskTex, texCoordVarying).r;
    gl_FragColor = vec4(src , mask * srcA);
}