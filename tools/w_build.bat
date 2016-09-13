set VCTargetsPath=c:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\V120

msbuild ..\ArcaneCore.sln /v:n /p:Configuration=Base_lib
msbuild ..\ArcaneCore.sln /v:n /p:Configuration=IO_lib
msbuild ..\ArcaneCore.sln /v:n /p:Configuration=GFX_lib
msbuild ..\ArcaneCore.sln /v:n /p:Configuration=Test_lib
msbuild ..\ArcaneCore.sln /v:n /p:Configuration=tests
