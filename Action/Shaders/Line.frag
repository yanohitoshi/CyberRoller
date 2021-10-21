// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// GLSL 3.3 ��v��
#version 330

uniform vec3 uColor;
out vec4 outColor;

void main()
{
	// �X�N���[�����W�ʒu����v�Z���Ĕj���ɂ��� 
    //uint x = uint(gl_FragCoord.x);
	//uint y = uint(gl_FragCoord.y);
	//if( mod(x, 2) == 0 || mod(y, 2) == 0)
	//{
	//   discard; //�`��j��
	//}
	outColor = vec4(uColor.r, uColor.g, uColor.b, 1.0);
}
