#version 330 core

layout (location = 0) in vec3 vertPos;    // ������� �������
layout (location = 1) in vec3 vertColor; // �������� ���� �������

out vec4 color; // �������� ���� �������

uniform float colorOffset; // �������� ����� (���������� �� ���������)

void main() {
    gl_Position = vec4(vertPos, 1.0);

    // ������������ �������� ����� �� ������ ������� �������
    vec3 offsetColor = vertColor + vec3(vertPos.x, vertPos.y, colorOffset);

    // ������������ �������� ����� � ��������� [0, 1]
    offsetColor = clamp(offsetColor, 0.0, 1.0);

    color = vec4(offsetColor, 1.0); // ��������� ����� = 1
}
