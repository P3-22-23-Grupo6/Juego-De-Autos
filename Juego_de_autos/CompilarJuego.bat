set MotorBin=.\Motor\Bin
set Bin=.\Bin

msbuild Juego_de_autos.sln /p:configuration=Debug
msbuild Juego_de_autos.sln /p:configuration=Release

xcopy %MotorBin% %Bin% /h /i /c /k /e /r /y
cd %Bin%
start LM_Main.exe