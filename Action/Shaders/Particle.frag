// GLSL 3.3 
#version 330

//layout (location = 0) out vec4 HDRBuffer;
//layout (location = 1) out vec4 HiBrightBuffer;


in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;


out vec4 outColor;

uniform sampler2D uTexture;
uniform float     uAlpha;
uniform vec3      uColor;

void main()
{
    vec4 col = texture(uTexture, fragTexCoord);
	outColor.rgb = col.rgb * uColor;
	outColor.a = col.a * uAlpha;
}
