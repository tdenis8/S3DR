-- Utility lib
project "Utility"
    kind "StaticLib"
    language "c++"
    location "."
    targetdir "lib"
    objdir "build"
    
    files  "src/**.cpp"
    --files  "include/**.hpp"

    includedirs {"include/utility"}
    
    configuration "Debug"
        defines { "DEBUG" }
        flags "Symbols"
        targetname("utility_D")

    configuration "Release"
        defines {"RELEASE", "NDEBUG"};
        flags {"Optimize", "ExtraWarnings"};
        targetname("utility")   


-- Utility lib test
project "UtilityTest"
    kind "ConsoleApp"
    language "c++"
    location "."
    targetdir "bin"
    objdir "build"

    files  "tests/**.cpp"
    files  "tests/**.hpp"

    links {}
    includedirs {"include/"}

    configuration "Debug"
        defines { "DEBUG" }
        flags "Symbols"
        targetname("utility_test_D")

    configuration "Release"
        defines {"RELEASE", "NDEBUG"};
        flags {"Optimize", "ExtraWarnings"};
        targetname("utility_test")  

