echo off
:: $(ProjectDir)ReleaseQuantumCloudAi.bat $(SolutionDir)
color 6f
echo "Hello QuantumCloudAI"
:: 拷贝QC20文件
set m_SourceFile=%1Debug\ReleaseQuantumCloudAI.exe	::E:\toolset\QC20\QC20\Resource\product\ReleaseQuantumCloudAI.exe
set m_TargetFile=E:\Sheldon\source\repos\SheldonSolution\Sheldon\
xcopy /Y /F %m_SourceFile% %m_TargetFile%

:: 获取QC20文件的版本号
for /f "usebackq delims=" %%a in (`"wmic datafile where name='%m_SourceFile:\=\\%' get Version /format:Textvaluelist"`) do (
    for /f "delims=" %%# in ("%%a") do set "%%#"
)
set m_Version=%version%
:: 拆分版本号
for /f "tokens=1,2,3,4 delims=." %%a in ("%m_Version%") do (
	set m_Version_1=%%a
	set m_Version_2=%%b
	set m_Version_3=%%c
	set m_Version_4=%%d
)



::candle	-d"DevEnvDir=C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\Common7\IDE\\" 	^
::		-dSolutionDir=%1QC20\ 																			^
::		-dSolutionExt=.sln 																				^
::		-dSolutionFileName=QC20.sln 																	^
::		-dSolutionName=QC20 																			^
::		-dSolutionPath=%1QC20\QC20.sln 																	^
::		-dConfiguration=Release 																		^
::		-dOutDir=%1QC20\QC20\bin\Release\																^
::		-dPlatform=x86 																					^
::		-dProjectDir=%1QC20\QC20\ 																		^
::		-dProjectExt=.wixproj 																			^
::		-dProjectFileName=QC20.wixproj 																	^
::		-dProjectName=QC20 																				^
::		-dProjectPath=%1QC20\QC20\QC20.wixproj 															^
::		-dTargetDir=%1QC20\QC20\bin\Release\ 															^
::		-dTargetExt=.msi 																				^
::		-dTargetFileName=QC20.msi 																		^
::		-dTargetName=QC20 																				^
::		-dTargetPath=%1QC20\QC20\bin\Release\QC20.msi 													^
::		-out %1QC20\QC20\obj\Release\ 																	^
::		-arch x86 																						^
::		-ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\\WixUtilExtension.dll" 						^
::		-ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\\WixUIExtension.dll" 						^
::		%1QC20\QC20\Product.wxs %1QC20\QC20\SpecialDlg.wxs
::
::Light -out %1QC20\QC20\bin\Release\en-us\QC20.msi 																	^
::		-pdbout %1QC20\QC20\bin\Release\en-us\QC20.wixpdb 															^
::		-cultures:en-us 																							^
::		-ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\\WixUtilExtension.dll" 									^
::		-ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\\WixUIExtension.dll" 									^
::		-loc %1QC20\QC20\Language\en-us.wxl 																		^
::		-loc %1QC20\QC20\Language\zh-cn.wxl 																		^
::		-contentsfile %1QC20\QC20\obj\Release\QC20.wixproj.BindContentsFileListen-us.txt 							^
::		-outputsfile %1QC20\QC20\obj\Release\QC20.wixproj.BindOutputsFileListen-us.txt 								^
::		-builtoutputsfile %1QC20\QC20\obj\Release\QC20.wixproj.BindBuiltOutputsFileListen-us.txt 					^
::		-wixprojectfile %1QC20\QC20\QC20.wixproj %1QC20\QC20\obj\Release\Product.wixobj %1QC20\QC20\obj\Release\SpecialDlg.wixobj































:: %1QC20\QC20\Product.wxs(241,0): warning LGHT1076: ICE57: Component 'ApplicationShortcut' has both per-user and per-machine data with an HKCU Registry KeyPath.
:: %1QC20\QC20\Product.wxs(66,0): warning LGHT1076: ICE61: This product should remove only older versions of itself. No Maximum version was detected for the current product. (WIX_UPGRADE_DETECTED)
:: %1QC20\QC20\Product.wxs(32,0): warning LGHT1076: ICE80: This 32Bit Package is using 64 bit Locator Type in RegLocator table entry Search_Install_String
:: 		QC20 -> %1QC20\QC20\bin\Release\en-us\QC20.msi
:: 		C:\Program Files (x86)\WiX Toolset v3.11\bin\Light.exe -out %1QC20\QC20\bin\Release\zh-cn\QC20.msi -pdbout %1QC20\QC20\bin\Release\zh-cn\QC20.wixpdb -cultures:zh-cn -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\\WixUtilExtension.dll" -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\\WixUIExtension.dll" -loc Language\en-us.wxl -loc Language\zh-cn.wxl -contentsfile obj\Release\QC20.wixproj.BindContentsFileListzh-cn.txt -outputsfile obj\Release\QC20.wixproj.BindOutputsFileListzh-cn.txt -builtoutputsfile obj\Release\QC20.wixproj.BindBuiltOutputsFileListzh-cn.txt -wixprojectfile %1QC20\QC20\QC20.wixproj obj\Release\Product.wixobj obj\Release\SpecialDlg.wixobj
:: %1QC20\QC20\Product.wxs(241,0): warning LGHT1076: ICE57: Component 'ApplicationShortcut' has both per-user and per-machine data with an HKCU Registry KeyPath.
:: %1QC20\QC20\Product.wxs(66,0): warning LGHT1076: ICE61: This product should remove only older versions of itself. No Maximum version was detected for the current product. (WIX_UPGRADE_DETECTED)
:: %1QC20\QC20\Product.wxs(32,0): warning LGHT1076: ICE80: This 32Bit Package is using 64 bit Locator Type in RegLocator table entry Search_Install_String
:: 		QC20 -> %1QC20\QC20\bin\Release\zh-cn\QC20.msi


















pause