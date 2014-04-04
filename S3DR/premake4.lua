-- S3DR lib
project "S3DRLib"
    prebuildcommands {"echo '*** Warning: prebuild commands in S3DR are not executed!'" }
    -- prebuildcommands {"./pre_build_tasks.sh" }
    kind "StaticLib"
    language "c++"
    location "."
    targetdir "lib"
    objdir "build"
    
    files  "src/**.cpp"
    --files  "include/**.hpp"

    includedirs {"include/", "include/misc", "include/view", "include/model", "include/operator",
                 "include/open_gl", "include/open_gl/object_adapters", "include/open_gl/object_renderers",
                 "include/open_gl/misc", "include/open_gl/techniques/" }
    
    configuration "Debug"
        defines { "DEBUG" }
        flags "Symbols"
        targetname("s3dr_D")

    configuration "Release"
        defines {"RELEASE", "NDEBUG"};
        flags {"Optimize", "ExtraWarnings"};
        targetname("s3dr")   

-- S3DR test
project "S3DRTest"
    kind "ConsoleApp"
    language "c++"
    location "."
    targetdir "bin"
    objdir "build"

    files  "tests/**.cpp"
    files  "tests/**.hpp"

    links {"SOIL", "S3DRLib", "GL", "GLEW", "glfw", "assimp"}
    includedirs {"include"}

    configuration "Debug"
        defines { "DEBUG" }
        flags "Symbols"
        targetname("s3dr_test_D")

    configuration "Release"
        defines {"RELEASE", "NDEBUG"};
        flags {"Optimize", "ExtraWarnings"};
        targetname("s3dr_test")  
