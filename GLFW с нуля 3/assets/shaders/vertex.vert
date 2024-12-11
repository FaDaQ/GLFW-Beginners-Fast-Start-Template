#version 330 core

layout (location = 0) in vec3 vertPos;    // Позиция вершины
layout (location = 1) in vec3 vertColor; // Исходный цвет вершины

out vec4 color; // Выходной цвет пикселя

uniform float colorOffset; // Смещение цвета (передается из программы)

void main() {
    gl_Position = vec4(vertPos, 1.0);

    // Рассчитываем смещение цвета на основе позиции вершины
    vec3 offsetColor = vertColor + vec3(vertPos.x, vertPos.y, colorOffset);

    // Ограничиваем значения цвета в диапазоне [0, 1]
    offsetColor = clamp(offsetColor, 0.0, 1.0);

    color = vec4(offsetColor, 1.0); // Применяем альфа = 1
}
