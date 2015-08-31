#!/usr/bin/python
gPrefix = 'GL'

def main():
    import sys
    if len(sys.argv)<3:
        print "Usage: ./createFile.py dir name"
        return;
    dirname = sys.argv[1].replace('include','').replace('/','')
    name = sys.argv[2].replace('/', '')
    print dirname, name
    hname = 'include/' + dirname + '/' + gPrefix + name + ".h"
    cname = 'src/' + dirname + '/' + gPrefix + name + ".cpp"

    hcontent = ''
    hcontent += 'class ' + gPrefix + name + '\n{\n};\n'

    ccontent = ''
    ccontent += '#include \"' + dirname + '/' + gPrefix + name + '.h\"'
    with open(hname, 'w') as f:
        f.write(hcontent)
    with open(cname, 'w') as f:
        f.write(ccontent)
if __name__ == '__main__':
    main()

