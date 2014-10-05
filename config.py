MAIN_PROGRAM=['libglsl.so', 'test.out', 'gputest.out', 'display.out']
gDepends = ['', 'libglsl.so','libglsl.so', 'libglsl.so']
gDirs = [['src'], ['test'], ['gltest'], []]
gSrcFiles = [[], [], [], ['./display_main.cpp']]
gLinks = [' -lfreeimage ', ' -lfreeimage ./libglsl.so -lGL -lGLEW',' -lfreeimage ./libglsl.so -lGLEW -lGL -lglut', ' -lfreeimage ./libglsl.so -lGLEW -lGL -lglut -lm -lX11']

include_Flag = '-Iinclude'
