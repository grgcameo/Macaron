****************************************************************************************************************************
** Description
****************************************************************************************************************************

****************************************************************************************************************************
** FileName: HNW_DIFF_SIP-v1.0.zip
** Date: 2023.11.10

** [개선내용]

    1. 테스트 한 SIP packet들을 target version 명의 디렉토리에 위치
    2. convertSipPacketToText.ps1 실행 시 일부 작업을 일괄 자동화 처리
        - sample_input.zip 파일 압축 해제
        - target sip packet copy
        - PC에 WinMerge tool이 설치되어 있다면 "sample_output\_output_useIgnoreKnownDiff" 의 결과물을 자동으로 diff

****************************************************************************************************************************
** FileName: HNW_DIFF_SIP-v1.0.zip
** Date: 2023.11.09

** [sip packet 비교 절차]

    1. sipp를 사용하여 release sw sip packet을 수집.
        - sip packet 파일 이름은 "SIP_[Test_Number]_[Test_CaseName].pcapng" 과 같이 규칙적으로 정의
        - ex> SIP_01_02_Initial_re_register.pcapng
                SIP_03_BYE_fromDUT.pcapng
    2. sample_input.zip 파일 압축 해제
    3. 캡쳐 한 sip packet들을 sample_input 안에 있는 파일명과 동일한 디렉토리에 각각 복사
    4. convertSipPacketToText.ps1를 실행.
        - script 실행 시 TargetVer의 값은 release sw version 값을 입력한다.
        - ex> TargetVer: HB09
    5. sample_output 내에 결과물 비교 검토
        - sample_output\_output : 단순히 pcap to text 변환 된 파일
        - sample_output\_output_useIgnoreKnownDiff : pcap to text 변환 시 비교할 필요 없는 value들을 
          문자열처리한 파일이며 이 디렉토리의 reference/target 을 비교 한다.
****************************************************************************************************************************