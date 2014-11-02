#!/usr/bin/python
gDefaultPath = "glsl"
gOutputHeadFile = "AllShader.h"
gOutputSourceFile = "glsl/AllShader.cpp"
import os
def findAllShader(path):
    cmd = "find " + path + " -name \"*.vex\""
    vexs = os.popen(cmd).read().split('\n')
    cmd = "find " + path + " -name \"*.fra\""
    fras = os.popen(cmd).read().split('\n')
    output = []
    for f in vexs:
        if len(f)>1:
            output.append(f)
    for f in fras:
        if len(f)>1:
            output.append(f)
    return output

def getName(fileName):
    s1 = fileName.replace("/", "_")
    s1 = s1.replace(".", "_")
    return s1

def generateFile(headfile, sourcefile, shaders):
    h = "#ifndef GLSL_SHADER_AUTO_GENERATE_H\n#define GLSL_SHADER_AUTO_GENERATE_H\n"
    cpp = "#include \"" + headfile +"\"\n"
    for s in shaders:
        name = getName(s)
        h += "extern const char* " + name + ";\n";
        cpp += "const char* " + name + " = \n";
        with open(s) as f:
            lines = f.read().split("\n")
            for l in lines:
                if (len(l) < 1):
                    continue
                cpp += "\""+l+"\"\n"
        cpp += ";\n"
    h+= "#endif"
    headfile = "include/" + headfile;
    with open(headfile, "w") as f:
        f.write(h);
    with open(sourcefile, "w") as f:
        f.write(cpp);

if __name__ == '__main__':
    shaders = findAllShader(gDefaultPath)
    generateFile(gOutputHeadFile, gOutputSourceFile, shaders);
