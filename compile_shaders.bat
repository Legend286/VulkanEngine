glslc.exe shaders\basic.vert -o shaders\basic.vert.spv
glslc.exe shaders\basic.frag -o shaders\basic.frag.spv
robocopy /e shaders x64\Release\shaders 
robocopy  /e shaders x64\Debug\shaders
pause