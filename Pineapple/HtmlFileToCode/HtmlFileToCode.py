# coding = utf-8

import time

class HtmlFileToCode:

    # Discriptor
    def _DoMakeHtmlCodeDescriptor(self, strOutFileName):
        outFile = open(strOutFileName, 'a')
        strFIleName = '//  Filename: {} \n'.format(strOutFileName)
        strCreateDate = '//  Creation Date: {} \n'.format(time.strftime('%Y.%m.%d'))

        discriptorList = [
            '//****************************************************************************\n',
            '//\n',
            strFIleName,
            '//  Author: HUMAX\n',
            strCreateDate,
            '//\n',
            '//****************************************************************************\n',
        ]

        outFile.writelines(discriptorList)
        outFile.close()


    # 클래스 정의
    def _DoMakeHtmlCodeClassInfo(self, strOutFileName, strClassName):

        outFile = open(strOutFileName, 'a')
        strClassName = 'class {} \n'.format(strClassName)

        classInfoList = [
            'namespace HSP {\n',
            strClassName,
            '{\n'
            '   public:\n',
            '       static const char * s_strURL;\n',
            '       static unsigned int s_uContentLength;\n',
            '       static unsigned char s_pContentBody[];\n',
            '};\n',
            '\n',
            '} // end if namespace\n',
        ]

        outFile.writelines(classInfoList)
        outFile.close()



test = HtmlFileToCode()
fName = 'myClass.cpp'
cName = 'myClass'
test._DoMakeHtmlCodeDescriptor(fName)
test._DoMakeHtmlCodeClassInfo(fName, cName)


