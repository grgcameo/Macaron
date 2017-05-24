#include <stdio.h>
#include <string.h>
/* original define - will remove later */
#define MAX_EVENT_TEXT_SIZE 256
#define true 1
#define false 0

typedef unsigned char bool;

typedef enum eMESSAGE_DIRECTION
{
	IN_BOUND = 0,
	OUT_BOUND
} MESSAGE_DIRECTION;

//--
#define MAX_CALL_ID_BUF_SIZE 33
#define MAX_CONNECTION_ID_BUF_SIZE 33

#define MAX_MGCP_VERB_CODE_BUF_SIZE 5
/* 
char strCRCX[] = "CRCX 372 aaln/1@700-3074.HUMAX.COM MGCP 1.0 NCS 1.0;\nC: 38ddb16404e4d3c7\nL : e:on, s : off, p : 20, a : PCMU\nM : recvonly\nX : 04e4d3c7\n\nv = 0\no = root 5635 5635 IN IP4 172.16.0.15\ns = session\nc = IN IP4 172.16.0.15\nt = 0 0\nm = audio 10212 RTP / AVP 0\na = rtpmap:0 PCMU / 8000\n";
char strDLCX[] = "DLCX 374 aaln/1@700-3074.HUMAX.COM MGCP 1.0 NCS 1.0\nC: 38ddb16404e4d3c7\nX: 04e4d3c7\nI: 4D87\n";
char strDLCX_RSP[] = "250 374 Connection was deleted\nP: PS=0, OS=0, PR=0, OR=0, PL=0, JI=0, LA=0, PC/RPS=0, PC/ROS=0, PC/RPL=0, PC/RJI=0\n";
*/

char* pMGCPLog[][2] = {
	{"CRCX 372 aaln/1@700-3074.HUMAX.COM MGCP 1.0 NCS 1.0\nC: 38ddb16404e4d3c7\nL : e:on, s : off, p : 20, a : PCMU\nM : recvonly\nX : 04e4d3c7\n\nv = 0\no = root 5635 5635 IN IP4 172.16.0.15\ns = session\nc = IN IP4 172.16.0.15\nt = 0 0\nm = audio 10212 RTP / AVP 0\na = rtpmap:0 PCMU / 8000\n", "0"},
    {"200 372 OK\nI: 4D87\n\nv=0\no=- 428 19851 IN IP4 20.20.30.74\ns=-\nc=IN IP4 20.20.30.74\nb=AS:80\nt=0 0\nm=audio 53456 RTP/AVP 0\na=mptime:20\na=ptime:20\na=sqn: 0\na=cdsc: 1 image udptl t38\n" , "0"},
	//{"CRCX 373 aaln/1@700-3074.HUMAX.COM MGCP 1.0 NCS 1.0\nC: 38ddb16404e4d3c7\nL : e:on, s : off, p : 20, a : PCMU\nM : recvonly\nX : 04e4d3c7\n\nv = 0\no = root 5635 5635 IN IP4 172.16.0.15\ns = session\nc = IN IP4 172.16.0.15\nt = 0 0\nm = audio 10212 RTP / AVP 0\na = rtpmap:0 PCMU / 8000\n", "0" },
	//{"DLCX 374 aaln/1@700-3074.HUMAX.COM MGCP 1.0 NCS 1.0\nC: 38ddb16404e4d3c7\nX: 04e4d3c7\nI: 4D87\n", "0"},
	{"250 374 Connection was deleted\nP: PS=1, OS=0, PR=1, OR=0, PL=0, JI=0, LA=0, PC/RPS=0, PC/ROS=0, PC/RPL=0, PC/RJI=0\n", "0"}
};

typedef struct stCallCnxInfo
{
	bool bIsRecvCRCX;
	bool bIsRecvDLCX;
	bool bIsValidCRCX;
	bool bIsValidDLCX;

	int nCRCXTransactionID;
	int nDLCXTransactionID;

	/* Call identifiers are hexadecimal strings, which are created by the Call Agent.  The maximum length of call identifiers is 32 characters. */
	char aCRCXCallID[MAX_CALL_ID_BUF_SIZE];		// C:
	char aDLCXCallID[MAX_CALL_ID_BUF_SIZE];		// C:
	char aCRCXConnectionID[MAX_CONNECTION_ID_BUF_SIZE];	// I:
    char aDLCXConnectionID[MAX_CONNECTION_ID_BUF_SIZE];	// I:

    bool bIsCallConnected;
    int  nCallDirection;
	
} StCallCnxInfo;

StCallCnxInfo gCallCnxSuccessInfo[2];

void emtaCheckCallHistoryByMgcpMsg(char *pMsg, int nLength, int nEndpt, MESSAGE_DIRECTION eDirection)
{	
	char aMGCPVerbCode[MAX_MGCP_VERB_CODE_BUF_SIZE] = { 0, };	
	char* pCnxIDParam = NULL;	

	switch (eDirection)
	{
		case IN_BOUND:
		{
			int nTransactionID;

			//strSScanf(pMsg, "%S", aMGCPVerbCode, sizeof(aMGCPVerbCode));
			sscanf(pMsg, "%s %d", aMGCPVerbCode, &nTransactionID);

			if (gCallCnxSuccessInfo[nEndpt].bIsValidCRCX)
			{
				if (strncmp(aMGCPVerbCode, "DLCX", strlen("DLCX")) == 0)
				{
					/* 1. Check DLCX */
					gCallCnxSuccessInfo[nEndpt].bIsRecvDLCX = true;					

					if (strstr(pMsg, gCallCnxSuccessInfo[nEndpt].aCRCXCallID))
					{
                        if (strstr(pMsg, gCallCnxSuccessInfo[nEndpt].aCRCXConnectionID))
                        {
                            gCallCnxSuccessInfo[nEndpt].bIsValidDLCX = true;
                            gCallCnxSuccessInfo[nEndpt].nDLCXTransactionID = nTransactionID;
                        }
					}

					if (gCallCnxSuccessInfo[nEndpt].bIsValidDLCX == false)
					{	
						// gCallCnxSuccessInfo 초기화
						memset(&gCallCnxSuccessInfo[nEndpt], 0, sizeof(StCallCnxInfo));
                        printf("Non-vol write => Call Log : [Line %d] Fail\n", nEndpt + 1);
					}
				}
				else if (strncmp(aMGCPVerbCode, "CRCX", strlen("CRCX")) == 0)
				{					
					printf("Could this case happens? \n");

					// valid crcx가 있을 때 CRCX가 온다면...이런 상황이 생길 수 있는가?? 있다면 예외처리를 어떻게 해야 하는가?
					/* 초기화 후 다시 CRCX 검토?
					memset(&gCallCnxSuccessInfo[nEndpt], 0, sizeof(StCallCnxInfo));

					gCallCnxSuccessInfo[nEndpt].bIsRecvCRCX = true;					
					pCnxIDParam = strstr(pMsg, "\nC:");

					if (pCnxIDParam)
					{
						//strSScanf
						sscanf(pCnxIDParam, "%*s %s", gCallCnxSuccessInfo[nEndpt].aCRCXCallID);
						gCallCnxSuccessInfo[nEndpt].nCRCXTransactionID = nTransactionID;
					}
					*/
				}// 이 조건은 동작 상황 봐서 사용할 수 있는지 검토.
                else if (strncmp(aMGCPVerbCode, "RQNT", strlen("RQNT")) == 0)
                {
                    if (strstr(pMsg, "S: L/rt"))
                    {
                        gCallCnxSuccessInfo[nEndpt].nCallDirection = 1; // 발신
                    }
                    else if (strstr(pMsg, "S: L/rg"))
                    {
                        gCallCnxSuccessInfo[nEndpt].nCallDirection = 2; // 수신
                    }
                    else
                    {
                        gCallCnxSuccessInfo[nEndpt].nCallDirection = 0; // 모름
                    }
                }
			}
			else
			{
				if (strncmp(aMGCPVerbCode, "CRCX", strlen("CRCX")) == 0)
				{   
					/* Extract CRCX ConnectionID */
					pCnxIDParam = strstr(pMsg, "\nC:");

					if (pCnxIDParam)
					{
						//strSScanf
                        char strTmp[MAX_CALL_ID_BUF_SIZE] = { 0, };
						sscanf(pCnxIDParam, "%*s %s", strTmp);
                        sprintf(gCallCnxSuccessInfo[nEndpt].aCRCXCallID, "C: %s", strTmp);
                        gCallCnxSuccessInfo[nEndpt].nCRCXTransactionID = nTransactionID;
                        gCallCnxSuccessInfo[nEndpt].bIsRecvCRCX = true;
					}
				}
			}			
		}
		break;
		case OUT_BOUND:
		{
			char strTmp[MAX_CONNECTION_ID_BUF_SIZE] = { 0, };

			// CRCX의 200 응답 처리
			if (gCallCnxSuccessInfo[nEndpt].bIsRecvCRCX == true && gCallCnxSuccessInfo[nEndpt].bIsRecvDLCX == false)
			{
				sprintf(strTmp, "200 %d", gCallCnxSuccessInfo[nEndpt].nCRCXTransactionID);

				if (strstr(pMsg, strTmp))
				{
					pCnxIDParam = strstr(pMsg, "\nI:");

					if (pCnxIDParam)
					{
                        memset(strTmp, 0, sizeof(strTmp));
						sscanf(pCnxIDParam, "%*s %s", strTmp);
                        sprintf(gCallCnxSuccessInfo[nEndpt].aCRCXConnectionID, "I: %s", strTmp);
						gCallCnxSuccessInfo[nEndpt].bIsValidCRCX = true;
					}

                    if (gCallCnxSuccessInfo[nEndpt].bIsValidCRCX == false)
                    {
                        // gCallCnxSuccessInfo 초기화
                        memset(&gCallCnxSuccessInfo[nEndpt], 0, sizeof(StCallCnxInfo));
                        printf("Non-vol write => Call Log : [Line %d] Fail\n", nEndpt + 1);
                    }
				}
			}
			
			// DLCX의 250 응답 처리
			if (gCallCnxSuccessInfo[nEndpt].bIsValidDLCX)
			{
				sprintf(strTmp, "250 %d", gCallCnxSuccessInfo[nEndpt].nDLCXTransactionID);				

				if (strstr(pMsg, strTmp))
				{
					char* pFoundPS = NULL;
					char* pFoundPR = NULL;
					
					pFoundPR = strstr(pMsg, " PR=0");
					pFoundPS = strstr(pMsg, " PS=0");

					// PS, PR 조합은 여러 통화 테스트 후 다시 한번 검토 해보도록 한다.
					// non-vol에 기록
					if (pFoundPR)
					{
						// 이 변수 활용성이 없다면 삭제해도될것같음.
						gCallCnxSuccessInfo[nEndpt].bIsCallConnected = false;
						printf("Non-vol write => Call Log : [Line %d] Fail\n", nEndpt + 1);
					}
					else
					{
						gCallCnxSuccessInfo[nEndpt].bIsCallConnected = true;
						printf("Non-vol write => Call Log : [Line %d] Success\n", nEndpt + 1);
					}

					// gCallCnxSuccessInfo 초기화
					memset(&gCallCnxSuccessInfo[nEndpt], 0, sizeof(StCallCnxInfo));
				}
			}
		}
		break;
	}
}

int main(void)
{
	int nIndex;
	int nDirect = 0;
	int nEndpt = 0;

	// 이 초기화를 어디에서 시키는 것이 좋을까?
	
	memset(&gCallCnxSuccessInfo[0], 0, sizeof(StCallCnxInfo));
	memset(&gCallCnxSuccessInfo[1], 0, sizeof(StCallCnxInfo));	
	// --

	for (nIndex = 0; nIndex < 3; nIndex++)
	{	
		nDirect = atoi(pMGCPLog[nIndex][1]);
		emtaCheckCallHistoryByMgcpMsg(pMGCPLog[nIndex][0], strlen(pMGCPLog[nIndex][0]), nEndpt, nDirect);
	}

	system("pause");
	return 0;
}
