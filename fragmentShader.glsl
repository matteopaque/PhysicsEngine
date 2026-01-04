#version 330 core
out vec4 fragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main(){
    fragColor = vertexColor;

}