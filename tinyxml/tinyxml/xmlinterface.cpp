#include <stdio.h>
#include "tinyxml.h"
#include "xmlinterface.h"

TiXmlNode* XmlNodeCheck(XML_DOCUMENT XmlDoc,char *pcNodePath, bool bInsertIfNotExist)
{
	TiXmlDocument *pXmlDoc = (TiXmlDocument *)XmlDoc;
	if(!pXmlDoc || !pcNodePath)
		return NULL;

	TiXmlHandle docHandle( pXmlDoc );
	TiXmlNode*pNode = NULL;
	TiXmlNode*pTmpNode = NULL;
	TiXmlNode*pRoot = docHandle.Node();
	if(!pRoot){
		return NULL;
	}

	pNode = pRoot;

	int j = 0;
	char *pch = pcNodePath;
	int nLen = strlen(pcNodePath);

	char szName[DEF_MAX_STR_LEN] = {0};
	if(pcNodePath[0] == '\\' || pcNodePath[0] == '/' ){
		for(int i = 1; i < nLen; ++i){
			if(pch[i] == '\\' || pch[i] == '/'){
				szName[j++] = '\0';
////////////////////////////////////////////////////////////////
				pTmpNode = pNode->FirstChild(szName);
				if(!pTmpNode){
					if(bInsertIfNotExist){
						TiXmlElement element(szName);
						pNode = pNode->InsertEndChild(element);
					}else{
						return NULL;
					}
				}else{
					pNode = pTmpNode;
				}
////////////////////////////////////////////////////////////////
				j = 0;
			}else{
				szName[j++] = pch[i];
			}
		}

		if(j != 0 && szName[0] != '\0')
		{
			szName[j++] = '\0';
////////////////////////////////////////////////////////////////
			pTmpNode = pNode->FirstChild(szName);
			if(!pTmpNode){
				if(bInsertIfNotExist){
					TiXmlElement element(szName);
					pNode = pNode->InsertEndChild(element);
				}else{
					return NULL;
				}
			}else{
				pNode = pTmpNode;
			}
////////////////////////////////////////////////////////////////
		}

	}else{
////////////////////////////////////////////////////////////////
		pTmpNode = pNode->FirstChild(szName);
		if(!pTmpNode){
			if(bInsertIfNotExist){
				TiXmlElement element(szName);
				pNode = pNode->InsertEndChild(element);
			}else{
				return NULL;
			}
		}else{
			pNode = pTmpNode;
		}
////////////////////////////////////////////////////////////////
	}
	return pNode;
}


XML_DOCUMENT XmlOpen(char *pcXmlFilePath)
{
	if(!pcXmlFilePath)
		return NULL;
		
	TiXmlDocument *pXmlDoc = new TiXmlDocument();
	if(!pXmlDoc->LoadFile(pcXmlFilePath)){
		if(!pXmlDoc->SaveFile(pcXmlFilePath))
			return NULL;
	}		
	return (XML_DOCUMENT)pXmlDoc;
}

XML_DOCUMENT XmlParse(char *pcXmlContent)
{
	if(!pcXmlContent)
		return NULL;
		
	TiXmlDocument *pXmlDoc = new TiXmlDocument();
	if(!pXmlDoc->Parse(pcXmlContent))
		return NULL;

	return (XML_DOCUMENT)pXmlDoc;
}

int XmlGetContent(XML_DOCUMENT XmlDoc, char *pcNodePath,char *pcXmlContent, int *pLen)
{
	if(!pcXmlContent || !pcXmlContent || !pLen  || *pLen < 1){
		return -1;
	}
	TiXmlPrinter XmlPrint;
	TiXmlNode* pNode = NULL;
	pNode = XmlNodeCheck(XmlDoc,pcNodePath, false);
	if(!pNode){
		return -1;
	}

	if(!pNode->Accept(&XmlPrint)){
		return -1;
	}

	if((size_t)(*pLen) < XmlPrint.Size()){
		return -1;
	}

	memset(pcXmlContent, 0, *pLen);
	memcpy(pcXmlContent, XmlPrint.CStr(), XmlPrint.Size());

	*pLen = (int)XmlPrint.Size();
	
	return 0;
}

int XmlSave(XML_DOCUMENT XmlDoc)
{
	TiXmlDocument *pXmlDoc = (TiXmlDocument *)XmlDoc;
	if(NULL != pXmlDoc){
		pXmlDoc->SaveFile();
	}
	return 0;
}

int XmlClose(XML_DOCUMENT XmlDoc)
{
	TiXmlDocument *pXmlDoc = (TiXmlDocument *)XmlDoc;
	if(NULL != pXmlDoc){
		delete pXmlDoc;
		pXmlDoc = NULL;
	}
	
	return 0;
}

int XmlClear(XML_DOCUMENT XmlDoc)
{
	TiXmlDocument *pXmlDoc = (TiXmlDocument *)XmlDoc;
	if(NULL != pXmlDoc){
		TiXmlElement*pRoot = pXmlDoc->RootElement();
		if(pRoot){
			pRoot->Clear();
		}
	}
	return 0;
}

int XmlSetNodeComment(XML_DOCUMENT XmlDoc, char *pcNodePath, char *pcNodeComment)
{
	TiXmlNode* pNode = NULL;
	pNode = XmlNodeCheck(XmlDoc,pcNodePath, true);
	if(!pNode){
		return -1;
	}
	if(!pcNodeComment){
		return -1;
	}
	TiXmlNode* pChild = NULL;
	TiXmlNode* pPreChild = NULL;
	TiXmlNode* pParent = pNode->Parent();
	if(pParent){
		for( pChild = pParent->FirstChild(); pChild; pChild = pChild->NextSibling()){
			if(pChild == pNode){
				break;
			}
			pPreChild = pChild;
		}

		if(pPreChild){
			if(pPreChild->ToComment()){
				pPreChild->SetValue(pcNodeComment);
			}
			else
			{
				TiXmlComment comment(pcNodeComment);
				pParent->InsertBeforeChild(pChild, comment);
			}
		}else{
			TiXmlComment comment(pcNodeComment);
			pParent->InsertBeforeChild(pChild, comment);
		}
	}
	return 0;
}

int XmlSetNode(XML_DOCUMENT XmlDoc, char *pcNodePath, NODE_VAL *pNodeValue)//pcNodePath: /root/child
{
	TiXmlNode* pNode = NULL;
	pNode = XmlNodeCheck(XmlDoc,pcNodePath, true);
	if(!pNode){
		return -1;
	}
	if(!pNodeValue){
		return -1;
	}

	if(pNodeValue->_t == eNT_INT)
	{
		sprintf(pNodeValue->_sVal,"%d",pNodeValue->_nVal);
	}

	TiXmlNode* pFirstNode = pNode->FirstChild();
	if(pFirstNode){
		if(pFirstNode->ToText()){
			pFirstNode->SetValue(pNodeValue->_sVal);
		}else{
			TiXmlText text(pNodeValue->_sVal);
			pNode->InsertBeforeChild(pFirstNode, text);
		}
	}else{
		TiXmlText text(pNodeValue->_sVal);
		pNode->InsertEndChild(text);
	}
	return 0;
}

int XmlGetNode(XML_DOCUMENT XmlDoc,char *pcNodePath, NODE_VAL *pNodeValue)
{
	TiXmlNode* pNode = NULL;
	pNode = XmlNodeCheck(XmlDoc,pcNodePath, false);
	if(!pNode){
		return -1;
	}
	if(!pNodeValue){
		return 0;//only check if the node exist
	}
	if(pNode->FirstChild()){
		pNodeValue->_sLen = (int)pNode->FirstChild()->ValueTStr().size();
		if( pNodeValue->_sLen >= (int)sizeof(pNodeValue->_sVal)){
			pNodeValue->_sLen = (int)sizeof(pNodeValue->_sVal) - 1;
		}
		memset(pNodeValue->_sVal, 0,sizeof(pNodeValue->_sVal));
		memcpy(pNodeValue->_sVal, pNode->FirstChild()->Value(),pNodeValue->_sLen);
		if(pNodeValue->_t == eNT_INT)
		{
			pNodeValue->_nVal = atoi(pNodeValue->_sVal);
		}
	}
	return 0;
}

int XmlDelNode(XML_DOCUMENT XmlDoc,char *pcNodePath)
{
	TiXmlNode* pNode = NULL;
	pNode = XmlNodeCheck(XmlDoc,pcNodePath, false);
	if(!pNode){
		return 0;//not exist
	}

	TiXmlNode *pParNode =  pNode->Parent();  
	if(!pParNode){
		return -1;
	}
	
	TiXmlElement* pParentEle = pParNode->ToElement();
	if(!pParentEle){
		return -1;
	}

	pParentEle->RemoveChild(pNode);   
	return 0;
}

int XmlSetNodeAttr(XML_DOCUMENT XmlDoc,char *pcNodePath,char *pcNodeAttr, NODE_VAL *pAttrVal)
{
	TiXmlNode* pNode = NULL;
	pNode = XmlNodeCheck(XmlDoc,pcNodePath, true);
	if(!pNode){
		return -1;
	}
	if(!pcNodeAttr || !pAttrVal){
		return -1;
	}
	TiXmlElement *pElement = pNode->ToElement();
	if(!pElement){
		return -1;
	}
	if(pAttrVal->_t == eNT_INT){
		pElement->SetAttribute(pcNodeAttr, pAttrVal->_nVal);
	}else if(pAttrVal->_t == eNT_STR){
		pElement->SetAttribute(pcNodeAttr, pAttrVal->_sVal);
	}else{
		return -1;
	}
	
	return 0;
}

int XmlGetNodeAttr(XML_DOCUMENT XmlDoc,char *pcNodePath,char *pcNodeAttr, NODE_VAL *pAttrVal)
{
	TiXmlNode* pNode = NULL;
	pNode = XmlNodeCheck(XmlDoc,pcNodePath, false);
	if(!pNode){
		return -1;
	}
	if(!pcNodeAttr || !pAttrVal){
		return -1;
	}
	TiXmlElement *pElement = pNode->ToElement();
	if(!pElement){
		return -1;
	}
	const char *pAttr = NULL; 
	if(pAttrVal->_t == eNT_INT){
		pAttr = pElement->Attribute(pcNodeAttr, &pAttrVal->_nVal);
	}else if(pAttrVal->_t == eNT_STR){
		pAttr = pElement->Attribute(pcNodeAttr);
	}else{
		return -1;
	}
	strcpy(pAttrVal->_sVal, pAttr);
	return 0;
}
