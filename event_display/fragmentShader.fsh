#version 120

//! [0]
uniform vec4 color;

varying vec4 varyingColor;


void main(void)
{
    gl_FragColor = varyingColor;
}
//! [0]
