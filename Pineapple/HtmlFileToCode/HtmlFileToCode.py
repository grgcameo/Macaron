# coding = utf-8

import time

class HtmlFileToCode:

    # Discriptor
    def _DoMakeDescriptor(self, strOutFile):
        outFile = open(strOutFile, 'a')
        strFIleName = '//  Filename: {} \n'.format(strOutFile)
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
    def _DoMakeClass(self, strOutFile, strClassName):

        outFile = open(strOutFile, 'a')
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

    # 본문 작성
    def _DoMakeContents(self, strOutFile, strInputFile, strClassName):

        inputFile = open(strInputFile, 'r')
        outFile = open(strOutFile, 'a')
        strContents = inputFile.read()

        contentsVariablePartList = [
            'namespace HSP {\n',
            '   const char *  ',strClassName,'::s_strURL         = \"/{}\";\n'.format(strInputFile),
            '   unsigned int  ',strClassName,'::s_uContentLength = {};\n'.format(len(strContents)),
            '   unsigned char ',strClassName,'::s_pContentBody[] = {\n',
            ]

        contentsArrayPartList = ['        ']

        nCount = 0

        for ch in strContents:
            contentsArrayPartList.append(str(ord(ch)) + ',')
            nCount += 1
            if (nCount == 16):
                nCount = 0
                contentsArrayPartList.append('\n        ')

        contentsTailPartList = [
            '\n'
            '};\n'
            '\n',
            '} // end if namespace\n',
        ]

        outFile.writelines(contentsVariablePartList)
        outFile.writelines(contentsArrayPartList)
        outFile.writelines(contentsTailPartList)


        inputFile.close()
        outFile.close()



# main test
test = HtmlFileToCode()
iName = 'myClass.html'
fName = 'myClass.cpp'
cName = 'myClass'
test._DoMakeDescriptor(fName)
test._DoMakeClass(fName, cName)
test._DoMakeContents(fName, iName, cName)


