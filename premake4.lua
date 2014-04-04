solution("S3DR")
    configurations {"Debug", "Release"}
                
    configuration "linux"
        defines "LINUX"
        buildoptions { "-std=c++0x"}
        
	include("S3DR")


