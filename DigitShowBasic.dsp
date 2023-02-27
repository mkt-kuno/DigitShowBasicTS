# Microsoft Developer Studio Project File - Name="DigitShowBasic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DigitShowBasic - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "DigitShowBasic.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "DigitShowBasic.mak" CFG="DigitShowBasic - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "DigitShowBasic - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "DigitShowBasic - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DigitShowBasic - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /stack:0x4000000 /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DigitShowBasic - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /stack:0x4000000 /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DigitShowBasic - Win32 Release"
# Name "DigitShowBasic - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BoardSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\CalibrationAmp.cpp
# End Source File
# Begin Source File

SOURCE=.\CalibrationFactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Control_Consolidation.cpp
# End Source File
# Begin Source File

SOURCE=.\Control_File.cpp
# End Source File
# Begin Source File

SOURCE=.\Control_General.cpp
# End Source File
# Begin Source File

SOURCE=.\Control_ID.cpp
# End Source File
# Begin Source File

SOURCE=.\Control_PreConsolidation.cpp
# End Source File
# Begin Source File

SOURCE=.\DA_Channel.cpp
# End Source File
# Begin Source File

SOURCE=.\DA_Vout.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitShowBasic.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitShowBasic.rc
# End Source File
# Begin Source File

SOURCE=.\DigitShowBasicDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitShowBasicView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RS232C.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplingSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\Specimen.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BoardSettings.h
# End Source File
# Begin Source File

SOURCE=.\CalibrationAmp.h
# End Source File
# Begin Source File

SOURCE=.\CalibrationFactor.h
# End Source File
# Begin Source File

SOURCE=.\Control_Consolidation.h
# End Source File
# Begin Source File

SOURCE=.\Control_File.h
# End Source File
# Begin Source File

SOURCE=.\Control_General.h
# End Source File
# Begin Source File

SOURCE=.\Control_ID.h
# End Source File
# Begin Source File

SOURCE=.\Control_PreConsolidation.h
# End Source File
# Begin Source File

SOURCE=.\DA_Channel.h
# End Source File
# Begin Source File

SOURCE=.\DA_Vout.h
# End Source File
# Begin Source File

SOURCE=.\DataConvert.h
# End Source File
# Begin Source File

SOURCE=.\DigitShowBasic.h
# End Source File
# Begin Source File

SOURCE=.\DigitShowBasicDoc.h
# End Source File
# Begin Source File

SOURCE=.\DigitShowBasicView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RS232C.h
# End Source File
# Begin Source File

SOURCE=.\SamplingSettings.h
# End Source File
# Begin Source File

SOURCE=.\Specimen.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DigitShowBasic.ico
# End Source File
# Begin Source File

SOURCE=.\res\DigitShowBasic.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DigitShowBasicDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Caio.lib
# End Source File
# End Target
# End Project
