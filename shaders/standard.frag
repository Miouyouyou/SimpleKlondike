precision highp float;

uniform sampler2D s;

varying vec2 out_st;
void main() { gl_FragColor = texture2D(s, out_st); }
