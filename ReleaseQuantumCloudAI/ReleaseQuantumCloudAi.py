#coding=utf-8
import os
import sys
import shutil
import win32api
import xml.dom.minidom
import hashlib
import traceback        
## 1.拷贝QC20到指定文件夹
#m_SourceFile = sys.argv[1] + "Debug\\ReleaseQuantumCloudAI.exe";
#m_TargetFile = sys.argv[1] + "Sheldon\\QC20.exe"
#shutil.copy(m_SourceFile, m_TargetFile);
#
## 2.对QC20.exe进行签名
## https://www.digicert.com/util/utility-code-signing-command-line.htm
#os.system('E:\\toolset\\QCI_2020\\DigiCertUtil.exe sign /kernelDriverSigning "%s"' %(m_TargetFile));

# 2.提取QC20的版本信息
#def GetFileVersion(file_name):
#    info = win32api.GetFileVersionInfo(file_name, os.sep);
#    ms = info['FileVersionMS'];
#    ls = info['FileVersionLS'];
#    m_version = [win32api.HIWORD(ms), win32api.LOWORD(ms), win32api.HIWORD(ls), win32api.LOWORD(ls)];
#    return m_version;
#
#m_Version = GetFileVersion(m_TargetFile);   # version [x, x, x, x]
#
## 3.修改 QC20\QC20\Include\AppVariables.wxi 文件中的版本号
#m_AppVariablesFile = sys.argv[1] + "QC20\\QC20\\Include\\AppVariables.wxi";
## m_TestFile = sys.argv[1] + "QC20\\QC20\\Include\\test.wxi";
#
#m_Dom = xml.dom.minidom.parse(m_AppVariablesFile);
#m_Root = m_Dom.documentElement;
#print(m_Root.nodeName);
#
#m_Major         = m_Root.childNodes[3];
#m_Minor         = m_Root.childNodes[5];
#m_BuildNumber   = m_Root.childNodes[7];
#m_Revision      = m_Root.childNodes[9];
#
#m_Major.nodeValue       = "Major = %d" % m_Version[0];
#m_Minor.nodeValue       = "Minor = %d" % m_Version[1];
#m_BuildNumber.nodeValue = "BuildNumber = %d" % m_Version[2];
#m_Revision.nodeValue    = "Revision = %d" % m_Version[3];
#
## 先临时关闭, 不然每次都会修改文件
## m_File = open(m_AppVariablesFile, 'wb');
## m_File.write(m_Dom.toprettyxml(indent='', newl='', encoding='utf-8'));
## m_File.close();
#
## 4.调用WIX Tool Set 进行编译链接
## 4.1 清空 \bin\* , \obj\*
#m_Bin = r"%sQC20\QC20\bin" % sys.argv[1];
#m_Obj = r"%sQC20\QC20\obj" % sys.argv[1];
#
##if os.path.exists(m_Bin):shutil.rmtree(m_Bin);
##
##if os.path.exists(m_Obj):shutil.rmtree(m_Obj);
##
## 4.2 Call wix candle
#m_Candle = R'candle -d"DevEnvDir=C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\Common7\IDE\\" -dSolutionDir=%sQC20\ -dSolutionExt=.sln -dSolutionFileName=QC20.sln  -dSolutionName=QC20  -dSolutionPath=%sQC20\QC20.sln  -dConfiguration=Release  -dOutDir=%sQC20\QC20\bin\Release\  -dPlatform=x86 -dProjectDir=%sQC20\QC20\  -dProjectExt=.wixproj  -dProjectFileName=QC20.wixproj -dProjectName=QC20 -dProjectPath=%sQC20\QC20\QC20.wixproj -dTargetDir=%sQC20\QC20\bin\Release\ -dTargetExt=.msi -dTargetFileName=QC20.msi  -dTargetName=QC20  -dTargetPath=%sQC20\QC20\bin\Release\QC20.msi  -out %sQC20\QC20\obj\Release\  -arch x86  -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUtilExtension.dll" -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUIExtension.dll" %sQC20\QC20\Product.wxs %sQC20\QC20\SpecialDlg.wxs';
#m_Candle = m_Candle % (sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1]);
#os.system(m_Candle);
#
## 4.3 Call wic light
#m_Light = R'Light -out %sQC20\QC20\bin\Release\en-us\QC20.msi -pdbout %sQC20\QC20\bin\Release\en-us\QC20.wixpdb -cultures:en-us -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUtilExtension.dll" -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUIExtension.dll" -loc %sQC20\QC20\Language\en-us.wxl -contentsfile %sQC20\QC20\obj\Release\QC20.wixproj.BindContentsFileListen-us.txt -outputsfile %sQC20\QC20\obj\Release\QC20.wixproj.BindOutputsFileListen-us.txt -builtoutputsfile %sQC20\QC20\obj\Release\QC20.wixproj.BindBuiltOutputsFileListen-us.txt -wixprojectfile %sQC20\QC20\QC20.wixproj %sQC20\QC20\obj\Release\Product.wixobj %sQC20\QC20\obj\Release\SpecialDlg.wixobj';
#m_Light = m_Light % (sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1]);
#os.system(m_Light);
#
## 4.4 重命名安装包
#m_OutFileDir = "%sQC20\\QC20\\bin\\Release\\en-us\\" % sys.argv[1];
#m_OutFileName = "QC20_%d.%d.%d.%d_en-us.msi" %(m_Version[0], m_Version[1], m_Version[2], m_Version[3]);
#os.rename(m_OutFileDir + "QC20.msi", m_OutFileDir + m_OutFileName);
#
## 4.5 删除pdb文件
#if os.path.exists(m_OutFileDir + "QC20.wixpdb"):os.remove(m_OutFileDir + "QC20.wixpdb");
#
#
## 5. 对安装包进行签名
#os.system('E:\\toolset\\QCI_2020\\DigiCertUtil.exe sign /kernelDriverSigning "%s"' %(m_OutFileDir + m_OutFileName));
#
## 6. 计算MD5字串
##获取文件的MD5值，适用于较大的文件
#def MD5(fname):
#    hash_md5 = hashlib.md5()
#    with open(fname, "rb") as f:
#        for chunk in iter(lambda: f.read(4096), b""):
#            hash_md5.update(chunk)
#    return hash_md5.hexdigest()
#
#m_IsNew = "%d.%d.%d.%d %s,,%d,,%s,,%s==" % (m_Version[0], m_Version[1], m_Version[2], m_Version[3], sys.argv[2], os.path.getsize(m_OutFileDir + m_OutFileName), m_OutFileName, MD5(m_OutFileDir + m_OutFileName).upper());
#print(m_IsNew);
#
#print("Ok");

def CopyQC20AndSigned(source, target):
    '''将QC20拷贝到指定位置, 并进行数字签名'''
    try:
        shutil.copy(source, target);
        os.system('E:\\toolset\\QCI_2020\\DigiCertUtil.exe sign /kernelDriverSigning "%s"' %(source));
    except Exception:
        print(traceback.format_exc());
    return None;

def GetFileVersion(file_name):
    '''获取指定文件的版本号, 以list[x,x,x,x]形式返回'''
    try:
        info = win32api.GetFileVersionInfo(file_name, os.sep);
        ms = info['FileVersionMS'];
        ls = info['FileVersionLS'];
        version = [win32api.HIWORD(ms), win32api.LOWORD(ms), win32api.HIWORD(ls), win32api.LOWORD(ls)];
        return version;
    except Exception:
        print(traceback.format_exc());
    return [0, 0, 0, 0];

def ModifyAppVariablesFile(version):
    '''
    修改 QC20\QC20\Include\AppVariables.wxi 文件中的版本号,
    目的是不再每次手动修改wix配置项目
    '''
    m_AppVariablesFile = sys.argv[1] + "QC20\\QC20\\Include\\AppVariables.wxi";
    try:
        m_Dom = xml.dom.minidom.parse(m_AppVariablesFile);
        m_Root = m_Dom.documentElement;
    
        m_Major         = m_Root.childNodes[3];
        m_Minor         = m_Root.childNodes[5];
        m_BuildNumber   = m_Root.childNodes[7];
        m_Revision      = m_Root.childNodes[9];

        m_Major.nodeValue       = "Major = %d" % version[0];
        m_Minor.nodeValue       = "Minor = %d" % version[1];
        m_BuildNumber.nodeValue = "BuildNumber = %d" % version[2];
        m_Revision.nodeValue    = "Revision = %d" % version[3];
    
        m_File = open(m_AppVariablesFile, 'wb');
        m_File.write(m_Dom.toprettyxml(indent='', newl='', encoding='utf-8'));
        m_File.close();
    except Exception:
        print(traceback.format_exc());
    return None;

def CallWixCandleLightAndSignedPackage(version):
    try:
        # 1. 清空 \bin\* , \obj\*
        m_Bin = r"%sQC20\QC20\bin" % sys.argv[1];
        m_Obj = r"%sQC20\QC20\obj" % sys.argv[1];

        if os.path.exists(m_Bin):shutil.rmtree(m_Bin);

        if os.path.exists(m_Obj):shutil.rmtree(m_Obj);

        # 2. Call wix candle
        m_Candle = R'candle -d"DevEnvDir=C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\Common7\IDE\\" -dSolutionDir=%sQC20\ -dSolutionExt=.sln -dSolutionFileName=QC20.sln  -dSolutionName=QC20  -dSolutionPath=%sQC20\QC20.sln  -dConfiguration=Release  -dOutDir=%sQC20\QC20\bin\Release\  -dPlatform=x86 -dProjectDir=%sQC20\QC20\  -dProjectExt=.wixproj  -dProjectFileName=QC20.wixproj -dProjectName=QC20 -dProjectPath=%sQC20\QC20\QC20.wixproj -dTargetDir=%sQC20\QC20\bin\Release\ -dTargetExt=.msi -dTargetFileName=QC20.msi  -dTargetName=QC20  -dTargetPath=%sQC20\QC20\bin\Release\QC20.msi  -out %sQC20\QC20\obj\Release\  -arch x86  -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUtilExtension.dll" -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUIExtension.dll" %sQC20\QC20\Product.wxs %sQC20\QC20\SpecialDlg.wxs';
        m_Candle = m_Candle % (sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1]);
        os.system(m_Candle);

        # 3. Call wix light
        m_Light = R'Light -out %sQC20\QC20\bin\Release\en-us\QC20.msi -pdbout %sQC20\QC20\bin\Release\en-us\QC20.wixpdb -cultures:en-us -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUtilExtension.dll" -ext "C:\Program Files (x86)\WiX Toolset v3.11\bin\WixUIExtension.dll" -loc %sQC20\QC20\Language\en-us.wxl -contentsfile %sQC20\QC20\obj\Release\QC20.wixproj.BindContentsFileListen-us.txt -outputsfile %sQC20\QC20\obj\Release\QC20.wixproj.BindOutputsFileListen-us.txt -builtoutputsfile %sQC20\QC20\obj\Release\QC20.wixproj.BindBuiltOutputsFileListen-us.txt -wixprojectfile %sQC20\QC20\QC20.wixproj %sQC20\QC20\obj\Release\Product.wixobj %sQC20\QC20\obj\Release\SpecialDlg.wixobj';
        m_Light = m_Light % (sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1], sys.argv[1]);
        os.system(m_Light);

        # 4. 重命名安装包
        m_OutFileDir = "%sQC20\\QC20\\bin\\Release\\en-us\\" % sys.argv[1];
        m_OutFileName = "QC20_%d.%d.%d.%d_en-us.msi" %(version[0], version[1], version[2], version[3]);
        os.rename(m_OutFileDir + "QC20.msi", m_OutFileDir + m_OutFileName);

        # 5. 删除pdb文件
        if os.path.exists(m_OutFileDir + "QC20.wixpdb"):os.remove(m_OutFileDir + "QC20.wixpdb");    
        
        # 6. 对安装包进行签名
        os.system('E:\\toolset\\QCI_2020\\DigiCertUtil.exe sign /kernelDriverSigning "%s"' %(m_OutFileDir + m_OutFileName));

        return m_OutFileDir, m_OutFileName;
    except Exception:
        print(traceback.format_exc());
    return ("","");

def MD5(fname):
    '''计算文件的MD5值'''
    try:
        hash_md5 = hashlib.md5();
        with open(fname, "rb") as f:
            for chunk in iter(lambda: f.read(4096), b""):
                hash_md5.update(chunk);
        return hash_md5.hexdigest();
    except Exception:
        print(traceback.format_exc());
    return "Error MD5 Code";

def MakeIsNewHtml(version, msipath, msiname):
    m_IsNew = "%d.%d.%d.%d %s,,%d,,%s,,%s==" % (version[0], version[1], version[2], version[3], sys.argv[2], os.path.getsize(msipath + msiname), msiname, MD5(msipath + msiname).upper());
    m_Handle = open(msipath + "is_new.html", "w");
    m_Handle.write(m_IsNew);
    m_Handle.close();
    print(m_IsNew);
    return 0;


if __name__ == '__main__':
    # python ReleaseQuantumCloudAi.py $(SolutionDir) release
    # 1.拷贝QC20到指定文件夹,对QC20.exe进行签名
    # https://www.digicert.com/util/utility-code-signing-command-line.htm
    m_SourceFile = sys.argv[1] + "Debug\\ReleaseQuantumCloudAI.exe";
    m_TargetFile = sys.argv[1] + "Sheldon\\QC20.exe";
    CopyQC20AndSigned(m_SourceFile, m_TargetFile);
    
    m_Version = GetFileVersion(m_TargetFile);   # 记下version [x, x, x, x]备用
    
    # 2.修改 QC20\QC20\Include\AppVariables.wxi 文件中的版本号
    ModifyAppVariablesFile(m_Version);
    
    # 3.调用WIX Tool Set 进行编译链接
    m_OutFile = CallWixCandleLightAndSignedPackage(m_Version);
        
    # 4.生成 is_new.html
    MakeIsNewHtml(m_Version, m_OutFile[0], m_OutFile[1]);