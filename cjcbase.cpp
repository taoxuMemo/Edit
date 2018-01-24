#include "cjcbase.h"
#include "math.h"
//#include"qdatatype.h"
CJCBase::CJCBase(QObject *parent) : CProtocol(parent)
{
    memset(m_sQQBM,0,SJDJGZCB_QQBM_LEN+1);
    memset(m_sXTBM,0,SJDJGZCB_STBM_LEN+1);
    memset(m_sMLBM,0,SJDJGZCB_MLBM_LEN+1);
    memset(m_sFWMM,0,SJDJGZCB_FWMM_LEN+1);
    m_nOverTime=0;
    m_nReCount=0;
    m_nMark=0;

}
bool CJCBase::CheckData(char *pData, int nLen)
{
    char *plData=pData;
    memcpy(m_sQQBM,pData,SJDJGZCB_QQBM_LEN);
    plData+=SJDJGZCB_QQBM_LEN;
    memcpy(m_sXTBM,plData,SJDJGZCB_STBM_LEN);
    plData+=SJDJGZCB_STBM_LEN;
    memcpy(m_sMLBM,pData,SJDJGZCB_MLBM_LEN);
    plData+=SJDJGZCB_MLBM_LEN;
    if(strncmp(m_sFWMM,plData,SJDJGZCB_FWMM_LEN)!=0)
    {
        //访问密码错误
        return false;
    }
    plData+=SJDJGZCB_FWMM_LEN;
    if(strncmp(g_DeviceMark,plData,SJDJGZCB_SBWYBS_LEN)!=0)
    {
        //唯一标识错误
        return false;
    }
    return true;
}
bool CJCBase::CommandData()
{
    int nCommand=0;
    for(int i=0;i<4;i++)
        nCommand+=(CTool::chartoint(m_sMLBM[3+i])*pow10(3-i));

}
