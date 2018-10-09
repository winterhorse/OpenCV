
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>

using namespace std;

void creatXML()
{
	//�����ĵ��ͽڵ�ָ��

	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");

	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST"root");

	//���ø��ڵ�

	xmlDocSetRootElement(doc, root_node);

	//�ڸ��ڵ���ֱ�Ӵ����ڵ�

	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode1", BAD_CAST "newNode1 content");

	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode2", BAD_CAST "newNode2 content");

	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode3", BAD_CAST "newNode3 content");

	//����һ���ڵ㣬���������ݺ����ԣ�Ȼ���������

	xmlNodePtr node = xmlNewNode(NULL, BAD_CAST"node2");

	xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");

	xmlAddChild(root_node, node);

	xmlAddChild(node, content);

	xmlNewProp(node, BAD_CAST"attribute", BAD_CAST "yes");

	//����һ�����Ӻ����ӽڵ�

	node = xmlNewNode(NULL, BAD_CAST "son");

	xmlAddChild(root_node, node);

	xmlNodePtr grandson = xmlNewNode(NULL, BAD_CAST "grandson");

	xmlAddChild(node, grandson);

	xmlAddChild(grandson, xmlNewText(BAD_CAST "This is a grandson node"));

	//�洢xml�ĵ�

	int nRel = xmlSaveFile("CreatedXml.xml", doc);

	if (nRel != -1)

	{
		cout << "һ��xml�ĵ�������,д��" << nRel << "���ֽ�" << endl;
	}
	//�ͷ��ĵ��ڽڵ㶯̬������ڴ�
	xmlFreeDoc(doc);
}

void readXML()
{
	xmlDocPtr doc;           //��������ĵ�ָ��
	xmlNodePtr curNode;      //������ָ��(����Ҫ��Ϊ���ڸ��������ƶ�)
	xmlChar *szKey;          //��ʱ�ַ�������
	char *szDocName;

	szDocName = "./CreatedXml.xml";
	doc = xmlReadFile(szDocName, "GB2312", XML_PARSE_RECOVER); //�����ļ�
	//�������ĵ��Ƿ�ɹ���������ɹ���libxml��ָһ��ע��Ĵ���ֹͣ��
	//һ�����������ǲ��ʵ��ı��롣XML��׼�ĵ�������UTF-8��UTF-16�⻹�����������뱣�档
	//����ĵ���������libxml���Զ���Ϊ��ת����UTF-8���������XML������Ϣ������XML��׼��.
	if (NULL == doc)
	{
		cout << "Document not parsed successfully";
		return;
	}
	curNode = xmlDocGetRootElement(doc); //ȷ���ĵ���Ԫ��
	/*���ȷ�ϵ�ǰ�ĵ��а�������*/
	if (NULL == curNode)
	{
		cout << "empty document";
		xmlFreeDoc(doc);
		return;
	}
	/*����������У�������Ҫȷ���ĵ�����ȷ�����͡���root���������ʾ����ʹ���ĵ��ĸ����͡�*/
	if (xmlStrcmp(curNode->name, BAD_CAST "root"))
	{
		cout << "document of the wrong type, root node != root";
		xmlFreeDoc(doc);
		return;
	}
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr = curNode;
	while (curNode != NULL)
	{
		//ȡ���ڵ��е�����
		if ((!xmlStrcmp(curNode->name, (const xmlChar *)"newNode1")))
		{
			szKey = xmlNodeGetContent(curNode);
			cout << "newNode1" << szKey;
			xmlFree(szKey);
		}
		//���Ҵ�������attribute�Ľڵ�
		if (xmlHasProp(curNode, BAD_CAST "attribute"))
		{
			propNodePtr = curNode;
		}
		curNode = curNode->next;
	}
	//��������
	xmlAttrPtr attrPtr = propNodePtr->properties;
	while (attrPtr != NULL)
	{
		if (!xmlStrcmp(attrPtr->name, BAD_CAST "attribute"))
		{
			xmlChar* szAttr = xmlGetProp(propNodePtr, BAD_CAST "attribute");
			cout << "get attribute = " << szAttr << endl;
			xmlFree(szAttr);
		}
		attrPtr = attrPtr->next;
	}
	xmlFreeDoc(doc);
}

int main()
{
	creatXML();
}

