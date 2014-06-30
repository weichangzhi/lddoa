# Microsoft Developer Studio Project File - Name="GoodsManageSystem" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GoodsManageSystem - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GoodsManageSystem.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GoodsManageSystem.mak" CFG="GoodsManageSystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GoodsManageSystem - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GoodsManageSystem - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GoodsManageSystem - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/LDD办公系统.exe"

!ELSEIF  "$(CFG)" == "GoodsManageSystem - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libmysql.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/LDD办公系统.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GoodsManageSystem - Win32 Release"
# Name "GoodsManageSystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Dialog_AddUser.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_BaseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DIALOG_CLIENT.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Delete_User.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Detail.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_InputBaseinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Login.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Login2.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Making.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Modify_Permission.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_ModifyList.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_ModifyPassWd.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_ModifyPW_Admin.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_New_List.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Output.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_post.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Query_list.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Schdeule.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_Unpost.cpp
# End Source File
# Begin Source File

SOURCE=.\excel.cpp
# End Source File
# Begin Source File

SOURCE=.\GoodsManageSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\GoodsManageSystem.rc
# End Source File
# Begin Source File

SOURCE=.\GoodsManageSystemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LineColorListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Preview.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Dialog_AddUser.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_BaseInfo.h
# End Source File
# Begin Source File

SOURCE=.\DIALOG_CLIENT.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Delete_User.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Detail.h
# End Source File
# Begin Source File

SOURCE=.\DIALOG_INPUT_CLIENT.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_InputBaseinfo.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Login.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Login2.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Making.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Modify_Permission.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_ModifyList.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_ModifyPassWd.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_ModifyPW_Admin.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_New_List.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Output.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_post.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Query_list.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Schdeule.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_Unpost.h
# End Source File
# Begin Source File

SOURCE=.\excel.h
# End Source File
# Begin Source File

SOURCE=.\GoodsManageSystem.h
# End Source File
# Begin Source File

SOURCE=.\GoodsManageSystemDlg.h
# End Source File
# Begin Source File

SOURCE=.\LineColorListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Preview.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.ico
# End Source File
# Begin Source File

SOURCE=.\res\2.ico
# End Source File
# Begin Source File

SOURCE=".\res\20140516100538697_easyicon_net_128 - 副本.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\20140516100538697_easyicon_net_128.ico
# End Source File
# Begin Source File

SOURCE=.\res\3.ico
# End Source File
# Begin Source File

SOURCE=.\res\4.ico
# End Source File
# Begin Source File

SOURCE=.\res\5.ico
# End Source File
# Begin Source File

SOURCE=.\res\6.ico
# End Source File
# Begin Source File

SOURCE=.\res\7.ico
# End Source File
# Begin Source File

SOURCE=.\res\8.ico
# End Source File
# Begin Source File

SOURCE=.\res\adduser.ico
# End Source File
# Begin Source File

SOURCE=.\res\buy.ico
# End Source File
# Begin Source File

SOURCE=.\res\client.ico
# End Source File
# Begin Source File

SOURCE=.\res\detail.ico
# End Source File
# Begin Source File

SOURCE=.\res\GoodsManageSystem.ico
# End Source File
# Begin Source File

SOURCE=.\res\GoodsManageSystem.rc2
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\list.ico
# End Source File
# Begin Source File

SOURCE=.\res\listadd.ico
# End Source File
# Begin Source File

SOURCE=.\res\listadd1.ico
# End Source File
# Begin Source File

SOURCE=.\res\listadd2.ico
# End Source File
# Begin Source File

SOURCE=.\res\listmodify.ico
# End Source File
# Begin Source File

SOURCE=.\res\listquery.ico
# End Source File
# Begin Source File

SOURCE=.\res\listquery1.ico
# End Source File
# Begin Source File

SOURCE=.\res\main.ico
# End Source File
# Begin Source File

SOURCE=.\res\main2.ico
# End Source File
# Begin Source File

SOURCE=.\res\makeing.ico
# End Source File
# Begin Source File

SOURCE=.\res\makeing1.ico
# End Source File
# Begin Source File

SOURCE=.\res\output.ico
# End Source File
# Begin Source File

SOURCE=.\res\permission.ico
# End Source File
# Begin Source File

SOURCE=.\res\permissionmodify.ico
# End Source File
# Begin Source File

SOURCE=.\res\permissionmodify1.ico
# End Source File
# Begin Source File

SOURCE=.\res\permissions.ico
# End Source File
# Begin Source File

SOURCE=.\res\post.ico
# End Source File
# Begin Source File

SOURCE=.\res\postunpost.ico
# End Source File
# Begin Source File

SOURCE=.\res\process.ico
# End Source File
# Begin Source File

SOURCE=.\res\sell.ico
# End Source File
# Begin Source File

SOURCE=.\res\unpost.ico
# End Source File
# Begin Source File

SOURCE=.\res\useradd.ico
# End Source File
# Begin Source File

SOURCE=.\res\useradd1.ico
# End Source File
# Begin Source File

SOURCE=.\res\userdel.ico
# End Source File
# Begin Source File

SOURCE=.\res\userdel1.ico
# End Source File
# Begin Source File

SOURCE=.\res\usermodify.ico
# End Source File
# Begin Source File

SOURCE=.\res\userpasswd.ico
# End Source File
# Begin Source File

SOURCE=".\res\Win7 LtBlue 1920x1200.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Win7 LtBlue 1920x1200.jpg"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
