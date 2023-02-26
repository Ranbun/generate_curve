#version 330 core

out vec4 FragColor;
in vec4 outColor;

void main()
{
    FragColor = outColor;  /// 显示的颜色
    FragColor = vec4(1.0,0.0,0.0,1.0);  /// 显示的颜色
}
