
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>

using namespace std;

void creatXML()
{
	//定义文档和节点指针

	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");

	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST"root");

	//设置根节点

	xmlDocSetRootElement(doc, root_node);

	//在根节点中直接创建节点

	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode1", BAD_CAST "newNode1 content");

	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode2", BAD_CAST "newNode2 content");

	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode3", BAD_CAST "newNode3 content");

	//创建一个节点，设置其内容和属性，然后加入根结点

	xmlNodePtr node = xmlNewNode(NULL, BAD_CAST"node2");

	xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");

	xmlAddChild(root_node, node);

	xmlAddChild(node, content);

	xmlNewProp(node, BAD_CAST"attribute", BAD_CAST "yes");

	//创建一个儿子和孙子节点

	node = xmlNewNode(NULL, BAD_CAST "son");

	xmlAddChild(root_node, node);

	xmlNodePtr grandson = xmlNewNode(NULL, BAD_CAST "grandson");

	xmlAddChild(node, grandson);

	xmlAddChild(grandson, xmlNewText(BAD_CAST "This is a grandson node"));

	//存储xml文档

	int nRel = xmlSaveFile("CreatedXml.xml", doc);

	if (nRel != -1)

	{
		cout << "一个xml文档被创建,写入" << nRel << "个字节" << endl;
	}
	//释放文档内节点动态申请的内存
	xmlFreeDoc(doc);
}

void readXML()
{
	xmlDocPtr doc;           //定义解析文档指针
	xmlNodePtr curNode;      //定义结点指针(你需要它为了在各个结点间移动)
	xmlChar *szKey;          //临时字符串变量
	char *szDocName;

	szDocName = "./CreatedXml.xml";
	doc = xmlReadFile(szDocName, "GB2312", XML_PARSE_RECOVER); //解析文件
	//检查解析文档是否成功，如果不成功，libxml将指一个注册的错误并停止。
	//一个常见错误是不适当的编码。XML标准文档除了用UTF-8或UTF-16外还可用其它编码保存。
	//如果文档是这样，libxml将自动地为你转换到UTF-8。更多关于XML编码信息包含在XML标准中.
	if (NULL == doc)
	{
		cout << "Document not parsed successfully";
		return;
	}
	curNode = xmlDocGetRootElement(doc); //确定文档根元素
	/*检查确认当前文档中包含内容*/
	if (NULL == curNode)
	{
		cout << "empty document";
		xmlFreeDoc(doc);
		return;
	}
	/*在这个例子中，我们需要确认文档是正确的类型。“root”是在这个示例中使用文档的根类型。*/
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
		//取出节点中的内容
		if ((!xmlStrcmp(curNode->name, (const xmlChar *)"newNode1")))
		{
			szKey = xmlNodeGetContent(curNode);
			cout << "newNode1" << szKey;
			xmlFree(szKey);
		}
		//查找带有属性attribute的节点
		if (xmlHasProp(curNode, BAD_CAST "attribute"))
		{
			propNodePtr = curNode;
		}
		curNode = curNode->next;
	}
	//查找属性
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

