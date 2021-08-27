//-------------------------------------------------------+
// �X�J�C�{�b�N�X�p���_�V�F�[�_
//-------------------------------------------------------+
#version 330 core
// attribute
layout (location = 0) in vec3 a_pos;

out vec3 TexCoords;

uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	// �e�N�X�`�����W�Ƀ��[�J���ʒu�x�N�g����ݒ�
	TexCoords = vec3(a_pos.y, -a_pos.z, a_pos.x);

	vec4 pos = u_projection * u_view * vec4(a_pos, 1.0);

	gl_Position = vec4(-pos.x, -pos.y, pos.w, pos.w);     // z������w�Œu��������(�ŉ��\��)

}