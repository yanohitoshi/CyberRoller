//----------------------------------------------------------+
// �X�J�C�{�b�N�X�p�t���O�����g�V�F�[�_�[
//----------------------------------------------------------+
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
    // �X�J�C�{�b�N�X�p�e�N�X�`�����T���v�����O
	FragColor = texture(skybox, TexCoords);
}