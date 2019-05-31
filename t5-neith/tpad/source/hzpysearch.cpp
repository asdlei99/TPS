// HZPYSearch.cpp: implementation of the CHZPYSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "HZPYSearch.h" 
#include "UIDataMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
节点配对计算
CNode* pNode:  待分析的接点
char *pString: 待分析的串
0返回失败或0个，非0返回顺序配对正确的个数
*/
int Calc( CNode* pNode, char *pString )
{
	if( NULL == pNode || 0 == strlen( pString ) )
	{
		return 0;
	}
	
	int bResult = 0;
	if( pNode->m_bySymbol != pString[0] )
	{
		if( NULL != pNode->m_pMultiNext )
		{
			CNode *pCurNode = pNode->m_pMultiNext;
			for(; pCurNode; pCurNode = pCurNode->m_pMultiNext )
			{
				if( pCurNode->m_bySymbol == pString[0] )
				{
					if( NULL != pCurNode->m_pNodeNext )
					{
						bResult = Calc( pCurNode->m_pNodeNext, pString + 1);
						if( bResult )
						{
							bResult = Calc( pNode->m_pNodeNext, pString + 2) + 2;
						}
					}
					else
					{
						bResult = Calc( pNode->m_pNodeNext, pString + 1 ) + 1;
					}
					break;
				}
			}
		}
	}
	else
	{
		bResult = Calc( pNode->m_pNodeNext, pString + 1 ) + 1;
	}
	return bResult;
}

/*
递归节点配对计算配对信息
CNode* pNode:  待分析的接点
char *pString: 待分析的串
0返回失败或0个，非0返回顺序配对正确的个数
*/
int OutCalc( CNode* pNode, char *pString )
{
	if ( NULL == pString )
	{
		return 0;
	}
	
	int bResult = Calc( pNode, pString );

	//if( 0 != bResult )  //解决"ssh" "cch"等搜索不到问题
	if( /*0*/strlen(pString) != bResult )
	{
		pNode = pNode->m_pNodeNext;
		while( pNode )
		{
			bResult = Calc( pNode, pString );

			if ( strlen(pString) != bResult )
			{
				if ( pNode->m_pNodeNext != NULL )
				{
					pNode = pNode->m_pNodeNext;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	return bResult;
}

void strtolower( char *string )
{
	if ( NULL == string )
	{
		return;
	}
	
	int nLen = strlen(string);
	for ( int i = 0; i < nLen; i++ )
	{
		if ( string[i] >= 'A' && string[i] <= 'Z' )
		{
			string[i] += 'a' - 'A';
		}
	}
}

BOOL IsGb2312( short wGbCode )
{
	unsigned char qu = wGbCode >> 8;
	unsigned char wei = wGbCode;
	
	if ( qu >= 0xa1 && qu <= 0xf7 )
	{
		if ( wei >= 0xa1 && wei <= 0xfe )
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHZPYSearch::CHZPYSearch()
{
	m_vectNode.clear();
}

CHZPYSearch::~CHZPYSearch()
{
   DestoryNodeList();
}

/*
功能：PinYin检索判断
参数：const char *strTextInput: 待判断的对象串(用户输入PY项)
	  const char* strTextSrc : 判断源字对象串(汉字项)
返回值:配对成功 TRUE, 配对失败 FALSE;
*/
BOOL  CHZPYSearch::HZPYMatchList( const char *strTextInput, const char* strTextSrc )
{
	if ( NULL == strTextInput )
	{
		return TRUE;
	}

	if ( NULL == strTextSrc )
	{
		return FALSE;
	}

	//1.直接配对原串, 不使用strstr，有bug场合
	//char *ch = strstr( strTextSrc, strTextInput );   //bug char *ch = strstr( "陆川县米场所", "壮" );
	CStringA str1(strTextInput);
	CStringA str2(strTextSrc);

    //检索不区分大小写
    str1.MakeLower();
    //str2.MakeLower();
	CharLowerA(str2.GetBuffer());
	str2.ReleaseBuffer();
	//int nFind = str1.Find(str2);
	int nFind = str2.Find(str1);
	
	if ( nFind != -1 )
	{
		return TRUE;
	}

	CNode* pHead = CreateNodeList( (LPSTR)(LPCSTR)str2 ); /*strTextSrc*/
    
    //空则返回 防止崩溃 dyy
    if ( !pHead )
    {
        return FALSE;
    }
    int nResult = OutCalc( pHead, (LPSTR)(LPCSTR)str1 );

	DestoryNodeList();

	if( nResult == strlen( strTextInput ) )
	{
		return TRUE;
	}

	return FALSE;
}

/*
功能：通过配对的汉字，字母数字串，创建分析节点链表，
创建后需要调用DestoryNodeList()进行销毁处理
参数：const char *strTextParm  判断目标
*/
CNode* CHZPYSearch::CreateNodeList( const char *strTextParm )
{
	if ( NULL == strTextParm )
	{
		return NULL;
	}
	
	char* strText = NULL;	
	CNode *pHeadMulti = NULL;
	CNode *pHead = NULL;
	
	//把 strTextParm翻转后放入strText
	char achText[512] = {0};
	
	int length = strlen(strTextParm);
	
	for (int k=0; k < length; )
	{
		if ( strTextParm[k] & 0x80 ) //汉字
		{
            //防止有字符有汉字的情况下遇到汉字+2后超出长度 length-k-2 为负值 dyy
            if ( k + 2 > length )
            {
                break;
            }
			achText[length-k-2] = strTextParm[k];
			achText[length-k-1] = strTextParm[k+1];
			k += 2;
		}
		else
		{
			achText[length-k-1] = strTextParm[k];
			k++;
		}
	}
	
	strText = achText;
	
	if ( NULL == strText )
	{
		return NULL;
	}
	
	int nLen = strlen( strText );
	
	for ( int i = 0; i < nLen;  )
	{
		if ( strText[i] & 0x80 ) //汉字
		{
			char p[3] = {0};
			memcpy( p, strText+i, 2);
			
			//获取对应的拼音码
			char arInputChr[ MAX_FIND_HANZI_LEN ] = { 0 }; 
			char arPYResult[ MAX_FIND_HANZI_LEN ][ MAX_FIND_HANZI_PY_CNT ] = {0};
			char pym[10] = {0};

			memcpy(arInputChr,  strText+i, 2);

			bool bRet = ConvertHZPY( arInputChr, arPYResult );

			if ( !bRet )
			{
				return NULL;
			}
		
			int m = 0;

			while ( arPYResult[0][m] != '\0' )
			{
				pym[m] = arPYResult[0][m];
				m++;
			}
		
			int nPymLen = strlen( pym );
			
			pHead = new CNode( '0', pHead );
			
			m_vectNode.push_back( pHead );
			
			for ( int j = 0; j < nPymLen; j++ )
			{			
				if ( j == 0)
				{
					pHeadMulti = new CNode( pym[j] );
				}
				else
				{
					pHeadMulti = new CNode( pym[j], NULL, pHeadMulti );
				}

				m_vectNode.push_back( pHeadMulti );
			}
			
			pHeadMulti = new CNode( p[0], NULL, pHeadMulti );

			m_vectNode.push_back( pHeadMulti );

			pHeadMulti->m_pNodeNext = new CNode( p[1] );

			m_vectNode.push_back( pHeadMulti->m_pNodeNext );

			pHead->m_pMultiNext = pHeadMulti;
			
			i += 2;
		}
		else
		{
			pHead = new CNode( strText[i], pHead );
			
			m_vectNode.push_back( pHead );
			
			i++;
		}  
	}
	
	return pHead;
}

/*
功能：释放CreateNodeList new出来的节点资源
*/
void  CHZPYSearch::DestoryNodeList()
{
	int nCnt = m_vectNode.size();

	for ( int i = 0; i < nCnt; ++i )
	{
		CNode* pNode = m_vectNode[i];
		if ( NULL != pNode )
		{
			delete pNode;
			pNode = NULL;
		}
	}
	
	m_vectNode.clear();
}


/*
功能：汉字拼音码转换
参数: char arInputChr[ MAX_FIND_HANZI_LEN ] 输入的汉字串
	  char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]   转换结果	      
*/
bool  CHZPYSearch::ConvertHZPY( char arInputChr[ MAX_FIND_HANZI_LEN ], char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT] )
{
	
	// 调用优化后的查找拼音的函数
    return SearchHZPY( arInputChr, arPYResult );

#if 0
    UINT i;
    HRSRC HGBSrc;
    LPVOID GBTemp;

    // 查找对应表资源
    HGBSrc = FindResource( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_PYGBK1), "PYGBK" );
    
	if( HGBSrc == NULL )
	{
		return false;
	}

    // 得到对应表数据的大小
    DWORD size = SizeofResource( AfxGetInstanceHandle(), HGBSrc );

    // 装入对应表
    HGLOBAL m_HGBStr = LoadResource( AfxGetInstanceHandle(), HGBSrc );

    // 锁定资源并得到数据指针
    GBTemp = LockResource( m_HGBStr );

    // 转换为 char 类型的指针
    char *buf = (char *)GBTemp;
 
    for( i = 0; i < MAX_FIND_HANZI_LEN; i++ )
	{
		arPYResult[i][0] = 0;
	}

    // 调用查找拼音的函数
    return SearchHZPY( buf, size, arInputChr, arPYResult );

#endif
}

/*
功能：查找拼音的函数(性能优化，解决大数据量检索)
参数: hzstr - 输入的汉字串，
	  arPY  - 结果保存在 arPY 数组，用于保存与汉字对应的所有拼音
参数: true: 查找转换成功	      
*/
bool CHZPYSearch::SearchHZPY( char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT])
{
	long len = 0;
	len = strlen( hzstr );
	
	int nCnt = 0;

	for( int k = 0; k<len; )
	{
		if ( hzstr[k] & 0x80 )//汉字
		{
			char chOneWord[3] = {0};
			memcpy( chOneWord, hzstr+k, 2);
			CStringA strKey(chOneWord) ;
			//std::vector<CString> vect;
			//CHWCiHuiIF::Instance()->GetCiHui( strKey, vect );

			CString strLetter;
			CUIDataMgr::GetFirstLetter( strKey, strLetter );
			strLetter.MakeLower();			
			
			memcpy( arPY[nCnt], strLetter, 1 );
// 			for ( int m=0; m < vect.size(); m++ )
// 			{
// 				char chPYResult[2] = {0};
// 				memcpy( chPYResult, vect[m], 1);
// 				strcat(arPY[nCnt], vect[m]);
// 			}
			
			k = k + 2;
		}
		else
		{
			memcpy(arPY[nCnt], hzstr+k, 1);	
			k++;
		}
		
		nCnt++;
	}
	
    return true;
}

/*
功能：查找拼音的函数
参数: buf - 拼音和汉字的对应表数组
	  size- 此数组的大小
	  hzstr - 输入的汉字串，
	  arPY  - 结果保存在 arPY 数组，用于保存与汉字对应的所有拼音
参数: true: 查找转换成功	      
*/
bool CHZPYSearch::SearchHZPY(char *buf, long size, char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT])
{
    char *ptr, str[1000], szPY[10], szHZ[1000];
    long i, j, k, start=0, len, len2;
    len2 = strlen(hzstr);    // 输入的汉字串的长度
	
	int nPYindex = 0;
	for( k=0; k<len2; /*k=k+2*/)
	{
		start = 0;
		if ( hzstr[k] & 0x80 )//汉字
		{
			for( i=0; i<size; i++)
			{
				if( buf[i]==0x0a )    // 到达行末
				{
					ptr = &buf[start];
					len = i-start;    // 此行的长度
					strncpy(str, ptr, len);    // 取此行的数据
					str[len]=0;
					start = i+1;    // 定位下一行的开始位置
					
					sscanf(str, "%s %s", szPY, szHZ);    // 分离拼音和对应的汉字
					len=strlen(szHZ);
					// 循环查找
					for(j=0; j<len; j=j+2)
					{
						// 找到匹配结果
						if(szHZ[j]==hzstr[k] && szHZ[j+1]==hzstr[k+1])
						{
							szPY[1] = '\0'; //需要全拼时注释此句
							//strcat(arPY[k/2], szPY);
							//strcat(arPY[k/2], ",");
							strcat(arPY[nPYindex], szPY);
							//strcat(arPY[k], ",");
						}
					}
				}
			}
			
			k=k+2;
		}
		else
		{
			
			char ach[2] = {0};
			ach[0] = hzstr[k];
			memcpy(arPY[nPYindex], ach, sizeof( ach ));	
			
			k=k+1;
		}
		
		nPYindex++;
	}
	
    return true;
}









//CPYChar类，用于获取二级汉字首字母拼音
CString CPYChar::m_ArrQWSecond[32];
CPYChar g_PYChar;

CPYChar::CPYChar()
{
    m_ArrQWSecond[0]="CJWGNSPGCGNESYPBTYYZDXYKYGTDJNNJQMBSGZSCYJSYYQPGKBZGYCYWJKGKLJSWKPJQHYTWDDZLSGMRYPYWWCCKZNKYDG";

    m_ArrQWSecond[1]="TTNGJEYKKZYTCJNMCYLQLYPYQFQRPZSLWBTGKJFYXJWZLTBNCXJJJJZXDTTSQZYCDXXHGCKBPHFFSSWYBGMXLPBYLLLHLX";

    m_ArrQWSecond[2]="SPZMYJHSOJNGHDZQYKLGJHSGQZHXQGKEZZWYSCSCJXYEYXADZPMDSSMZJZQJYZCDJZWQJBDZBXGZNZCPWHKXHQKMWFBPBY";

    m_ArrQWSecond[3]="DTJZZKQHYLYGXFPTYJYYZPSZLFCHMQSHGMXXSXJJSDCSBBQBEFSJYHWWGZKPYLQBGLDLCCTNMAYDDKSSNGYCSGXLYZAYBN";

    m_ArrQWSecond[4]="PTSDKDYLHGYMYLCXPYCJNDQJWXQXFYYFJLEJBZRXCCQWQQSBNKYMGPLBMJRQCFLNYMYQMSQTRBCJTHZTQFRXQHXMJJCJLX";

    m_ArrQWSecond[5]="QGJMSHZKBSWYEMYLTXFSYDSGLYCJQXSJNQBSCTYHBFTDCYZDJWYGHQFRXWCKQKXEBPTLPXJZSRMEBWHJLBJSLYYSMDXLCL";

    m_ArrQWSecond[6]="QKXLHXJRZJMFQHXHWYWSBHTRXXGLHQHFNMNYKLDYXZPWLGGTMTCFPAJJZYLJTYANJGBJPLQGDZYQYAXBKYSECJSZNSLYZH";

    m_ArrQWSecond[7]="ZXLZCGHPXZHZNYTDSBCJKDLZAYFMYDLEBBGQYZKXGLDNDNYSKJSHDLYXBCGHXYPKDJMMZNGMMCLGWZSZXZJFZNMLZZTHCS";

    m_ArrQWSecond[8]="YDBDLLSCDDNLKJYKJSYCJLKOHQASDKNHCSGANHDAASHTCPLCPQYBSDMPJLPCJOQLCDHJJYSPRCHNWJNLHLYYQYYWZPTCZG";

    m_ArrQWSecond[9]="WWMZFFJQQQQYXACLBHKDJXDGMMYDJXZLLSYGXGKJRYWZWYCLZMSSJZLDBYDCFCXYHLXCHYZJQSFQAGMNYXPFRKSSBJLYXY";

    m_ArrQWSecond[10]="SYGLNSCMHCWWMNZJJLXXHCHSYDSTTXRYCYXBYHCSMXJSZNPWGPXXTAYBGAJCXLYSDCCWZOCWKCCSBNHCPDYZNFCYYTYCKX";

    m_ArrQWSecond[11]="KYBSQKKYTQQXFCWCHCYKELZQBSQYJQCCLMTHSYWHMKTLKJLYCXWHEQQHTQHZPQSQSCFYMMDMGBWHWLGSSLYSDLMLXPTHMJ";

    m_ArrQWSecond[12]="HWLJZYHZJXHTXJLHXRSWLWZJCBXMHZQXSDZPMGFCSGLSXYMJSHXPJXWMYQKSMYPLRTHBXFTPMHYXLCHLHLZYLXGSSSSTCL";

    m_ArrQWSecond[13]="SLDCLRPBHZHXYYFHBBGDMYCNQQWLQHJJZYWJZYEJJDHPBLQXTQKWHLCHQXAGTLXLJXMSLXHTZKZJECXJCJNMFBYCSFYWYB";

    m_ArrQWSecond[14]="JZGNYSDZSQYRSLJPCLPWXSDWEJBJCBCNAYTWGMPAPCLYQPCLZXSBNMSGGFNZJJBZSFZYNDXHPLQKZCZWALSBCCJXJYZGWK";

    m_ArrQWSecond[15]="YPSGXFZFCDKHJGXDLQFSGDSLQWZKXTMHSBGZMJZRGLYJBPMLMSXLZJQQHZYJCZYDJWBMJKLDDPMJEGXYHYLXHLQYQHKYCW";

    m_ArrQWSecond[16]="CJMYYXNATJHYCCXZPCQLBZWWYTWBQCMLPMYRJCCCXFPZNZZLJPLXXYZTZLGDLDCKLYRZZGQTGJHHHJLJAXFGFJZSLCFDQZ";

    m_ArrQWSecond[17]="LCLGJDJCSNCLLJPJQDCCLCJXMYZFTSXGCGSBRZXJQQCTZHGYQTJQQLZXJYLYLBCYAMCSTYLPDJBYREGKLZYZHLYSZQLZNW";

    m_ArrQWSecond[18]="CZCLLWJQJJJKDGJZOLBBZPPGLGHTGZXYGHZMYCNQSYCYHBHGXKAMTXYXNBSKYZZGJZLQJDFCJXDYGJQJJPMGWGJJJPKQSB";

    m_ArrQWSecond[19]="GBMMCJSSCLPQPDXCDYYKYFCJDDYYGYWRHJRTGZNYQLDKLJSZZGZQZJGDYKSHPZMTLCPWNJAFYZDJCNMWESCYGLBTZCGMSS";

    m_ArrQWSecond[20]="LLYXQSXSBSJSBBSGGHFJLWPMZJNLYYWDQSHZXTYYWHMCYHYWDBXBTLMSYYYFSXJCSDXXLHJHFSSXZQHFZMZCZTQCXZXRTT";

    m_ArrQWSecond[21]="DJHNNYZQQMNQDMMGYYDXMJGDHCDYZBFFALLZTDLTFXMXQZDNGWQDBDCZJDXBZGSQQDDJCMBKZFFXMKDMDSYYSZCMLJDSYN";

    m_ArrQWSecond[22]="SPRSKMKMPCKLGDBQTFZSWTFGGLYPLLJZHGJJGYPZLTCSMCNBTJBQFKTHBYZGKPBBYMTTSSXTBNPDKLEYCJNYCDYKZDDHQH";

    m_ArrQWSecond[23]="SDZSCTARLLTKZLGECLLKJLQJAQNBDKKGHPJTZQKSECSHALQFMMGJNLYJBBTMLYZXDCJPLDLPCQDHZYCBZSCZBZMSLJFLKR";

    m_ArrQWSecond[24]="ZJSNFRGJHXPDHYJYBZGDLQCSEZGXLBLGYXTWMABCHECMWYJYZLLJJYHLGBDJLSLYGKDZPZXJYYZLWCXSZFGWYYDLYHCLJS";

    m_ArrQWSecond[25]="CMBJHBLYZLYCBLYDPDQYSXQZBYTDKYXJYYCNRJMPDJGKLCLJBCTBJDDBBLBLCZQRPPXJCGLZCSHLTOLJNMDDDLNGKAQHQH";

    m_ArrQWSecond[26]="JGYKHEZNMSHRPHQQJCHGMFPRXHJGDYCHGHLYRZQLCYQJNZSQTKQJYMSZSWLCFQQQXYFGGYPTQWLMCRNFKKFSYYLQBMQAMM";

    m_ArrQWSecond[27]="MYXCTPSHCPTXXZZSMPHPSHMCLMLDQFYQXSZYJDJJZZHQPDSZGLSTJBCKBXYQZJSGPSXQZQZRQTBDKYXZKHHGFLBCSMDLDG";

    m_ArrQWSecond[28]="DZDBLZYYCXNNCSYBZBFGLZZXSWMSCCMQNJQSBDQSJTXXMBLTXZCLZSHZCXRQJGJYLXZFJPHYMZQQYDFQJJLZZNZJCDGZYG";

    m_ArrQWSecond[29]="CTXMZYSCTLKPHTXHTLBJXJLXSCDQXCBBTJFQZFSLTJBTKQBXXJJLJCHCZDBZJDCZJDCPRNPQCJPFCZLCLZXZDMXMPHJSGZ";

    m_ArrQWSecond[30]="GSZZQJYLWTJPFSYASMCJBTZKYCWMYTCSJJLJCQLWZMALBXYFBPNLSFHTGJWEJJXXGLLJSTGSHJQLZFKCGNNDSZFDEQFHBS";

    m_ArrQWSecond[31]="AQTGLLBXMMYGSZLDYDQMJJRGBJTKGDHGKBLQKBDMBYLXWCXYTTYBKMRTJZXQJBHLMHMJJZMQASLDCYXYQDLQCAFYWYXQHZ";

}

CPYChar::~CPYChar()
{

}

//功能：检测Value  是否在Lp..Hp之间   
BOOL CPYChar::In(int Lp, int Hp,int Value)   
{   
    ASSERT(Lp<=Hp);   
    return  ((Value<=Hp)&&(Value>=Lp));   
}  

//参数：一个汉字   
//返回值：该汉字的拼音   
char CPYChar::GetPYChar(CString HZ)   
{   
    ASSERT(HZ.GetLength()==2); 
    return GetPYChar(HZ.GetAt(0),HZ.GetAt(1));
}   

//参数：一个汉字   
//返回值：该汉字的拼音   
char CPYChar::GetPYChar(TCHAR c1,TCHAR c2)   
{   
    WORD  Hi=WORD(c1)<<8;   
    WORD  Lo=BYTE(c2);   
    int  n= Hi + Lo;
    if ( n<=0xD7F9 )
    {
        if   (In(0xB0A1,0xB0C4,n))   return   'A';   
        if   (In(0XB0C5,0XB2C0,n))   return   'B';   
        if   (In(0xB2C1,0xB4ED,n))   return   'C';   
        if   (In(0xB4EE,0xB6E9,n))   return   'D';   
        if   (In(0xB6EA,0xB7A1,n))   return   'E';   
        if   (In(0xB7A2,0xB8C0,n))   return   'F';   
        if   (In(0xB8C1,0xB9FD,n))   return   'G';   
        if   (In(0xB9FE,0xBBF6,n))   return   'H';   
        if   (In(0xBBF7,0xBFA5,n))   return   'J';   
        if   (In(0xBFA6,0xC0AB,n))   return   'K';   
        if   (In(0xC0AC,0xC2E7,n))   return   'L';   
        if   (In(0xC2E8,0xC4C2,n))   return   'M';   
        if   (In(0xC4C3,0xC5B5,n))   return   'N';   
        if   (In(0xC5B6,0xC5BD,n))   return   'O';   
        if   (In(0xC5BE,0xC6D9,n))   return   'P';   
        if   (In(0xC6D1,0xC8BA,n))   return   'Q';   
        if   (In(0xC8BB,0xC8F5,n))   return   'R';   
        if   (In(0xC8F6,0xCBF9,n))   return   'S';   
        if   (In(0xCBFA,0xCDD9,n))   return   'T';   
        if   (In(0xCDDA,0xCEF3,n))   return   'W';   
        if   (In(0xCEF4,0xD1B8,n))   return   'X';   
        if   (In(0xD1B9,0xD4D0,n))   return   'Y';   
        if   (In(0xD4D1,0xD7F9,n))   return   'Z';  
        return   char(0);
    }
    else
    {
        char b1 = (c1&0x7F)-0x20 - 56;
        char b2 = (c2&0x7F)-0x20 - 1;
        if (b1>=0 && b1<=31 && b2>=0 && b2<=93)
        {
            return m_ArrQWSecond[b1].GetAt(b2);
        }
        return   char(0);
    }
}   