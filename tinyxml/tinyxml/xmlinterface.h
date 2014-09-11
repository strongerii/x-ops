#ifndef _TINY_XML_INTERFACE_H_
#define _TINY_XML_INTERFACE_H_

#define DEF_MAX_STR_LEN			256

typedef enum {eNT_INT = 0, eNT_STR} eNODE_TYPE;

typedef void* XML_DOCUMENT;
typedef struct tag_NODE_VAL
{
	eNODE_TYPE _t;
	int  _nVal;
	int  _sLen;
	char _sVal[DEF_MAX_STR_LEN];
}NODE_VAL;

#ifdef __cplusplus
extern "C"
{
#endif

XML_DOCUMENT XmlOpen(char *pcXmlFilePath);
XML_DOCUMENT XmlParse(char *pcXmlContent);

int XmlClear(XML_DOCUMENT XmlDoc);

int XmlSave(XML_DOCUMENT XmlDoc);
int XmlClose(XML_DOCUMENT XmlDoc);

int XmlGetContent(XML_DOCUMENT XmlDoc, char *pcNodePath,char *pcXmlContent, int *pLen);
int XmlSetNodeComment(XML_DOCUMENT XmlDoc, char *pcNodePath, char *pcNodeComment);

int XmlSetNode(XML_DOCUMENT XmlDoc, char *pcNodePath, NODE_VAL *pNodeValue);
int XmlGetNode(XML_DOCUMENT XmlDoc,char *pcNodePath, NODE_VAL *pNodeValue);
int XmlDelNode(XML_DOCUMENT XmlDoc,char *pcNodePath);

int XmlSetNodeAttr(XML_DOCUMENT XmlDoc,char *pcNodePath,char *pcNodeAttr, NODE_VAL *pAttrVal);
int XmlGetNodeAttr(XML_DOCUMENT XmlDoc,char *pcNodePath,char *pcNodeAttr, NODE_VAL *pAttrVal);

#ifdef __cplusplus
}
#endif

#endif //_TINY_XML_INTERFACE_H_