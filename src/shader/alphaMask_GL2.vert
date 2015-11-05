#extension GL_ARB_texture_rectangle : enable

varying vec2 texCoordVarying;

void main()
{
    texCoordVarying = gl_MultiTexCoord0.xy;
	gl_Position = ftransform();
}