#version 460 core

in vec3 ourColor;

out vec4 FragColor;

void main(){
  // FragColor = vec4(1.0f, 0.2f, 0.6f, 1.0f);
  FragColor = vec4(ourColor, 1.0f);
}
