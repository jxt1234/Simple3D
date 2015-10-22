#!/usr/bin/python
import xml.etree.ElementTree as ET
import string

def turnFunc(model):
    model = model.split('.')[0]
    model = model.replace('/', '')
    return model
def main(model, glsl):
    glslcontents = 'precision mediump float;\n'
    glslcontents += 'varying vec2 textureCoordinate;\nuniform sampler2D inputImageTexture;\n'
    glslcontents += 'uniform float filterRatio;\n'
    for i in ['r', 'g', 'b']:
        glslcontents += generateFunction(model+'_'+i)
    glslcontents += 'void main()\n{\n'
    glslcontents += 'vec4 curColor = clamp(texture2D(inputImageTexture, textureCoordinate), vec4(0.0), vec4(1.0));\n'
    for i in ['r', 'g', 'b']:
        glslcontents += 'float '+i+' = ' + turnFunc(model) + '_' + i + '(curColor.rgb);\n'
    glslcontents += 'gl_FragColor = vec4(mix(curColor.rgb, vec3(r, g, b), filterRatio), curColor.a);\n'
    glslcontents += '}\n'
    with open(glsl,'w') as f:
        f.write(glslcontents)

def generateFunction(model):
    tree = ET.parse(model)
    number = 0
    offset = 0
    parameters = ''
    for element in tree.getroot():
        if element.tag == 'Offset':
            offset = string.atoi(element.text)
        elif element.tag == 'Number':
            number = string.atoi(element.text)
        elif element.tag == 'Parameters':
            parameters = element.text
    parameters = parameters.split('\n')
    parameters = filter(lambda x : len(x)>1, parameters)
    name = turnFunc(model)
    functions_line = 'float ' + name + ('(vec3 color)\n')
    functions_line += '{\n'
    functions_line += 'float v1 = color.r;\n'
    functions_line += 'float v2 = color.g;\n'
    functions_line += 'float v3 = color.b;\n'
    functions_line += 'float res = 0.0\n'
    for [i, p] in enumerate(parameters):
        s1 = 'v1';
        if i < 4 :
            s1 = '(1.0-v1)'
        s2 = 'v2'
        if (i%4)<2:
            s2 = '(1.0-v2)'
        s3 = 'v3'
        if i%2 == 0:
            s3 = '(1.0-v3)'
        p_4 = filter(lambda x:len(x)>1, p.split('    '))
        functions_line += '+('+p_4[0] + '*color.r + ' + p_4[1] + '*color.g + ' + p_4[2] + '*color.b + '+ p_4[3]+')*'+s1 + '*'+s2 + '*'+s3 + '\n'
    functions_line += ';\nreturn clamp(res,0.0,1.0);\n}\n'
    return functions_line

if __name__ == '__main__':
    import sys
    if len(sys.argv)<3:
        print 'Usage: ./turnModelToGLSL.py input output.glsl'
    else:
        main(sys.argv[1], sys.argv[2])
