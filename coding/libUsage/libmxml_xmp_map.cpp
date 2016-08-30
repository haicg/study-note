/**********************************************************************
** \file xml_map.cpp
** \brief
** \author lihaicg
** \date 2016年03月26日 星期六 16时17分24秒
** Mail:  lihaicg@126.com
************************************************************************/

#include <iostream>
#include <map>
#include <mxml.h>
using namespace std;

static map<int, int> repeat_map;
int save_map_xml(const char *filename, map<int, int> &map_value)
{

	mxml_node_t *curnode = NULL, *doc = NULL, *topnode = NULL;	/* XML documentation tree */
	map<int, int>::iterator iter;
	char tmpbuf[64];
	FILE *fp = NULL;
	doc = mxmlNewXML("1.0");
	topnode = mxmlNewElement(doc, "map");
    for (iter=map_value.begin(); iter != map_value.end(); ++iter) {
		curnode = mxmlNewElement(topnode, "node");
		snprintf(tmpbuf, sizeof(tmpbuf), "%d", iter->first);
		mxmlElementSetAttr(curnode, "key", tmpbuf);
		snprintf(tmpbuf, sizeof(tmpbuf), "%d", iter->second);
		mxmlElementSetAttr(curnode, "value", tmpbuf);
	}

	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("can not open the xml file!\n");
		return -2;
	}

	mxmlSaveFile(doc, fp, MXML_NO_CALLBACK);
	fclose(fp);

	if (doc != NULL) {
		mxmlDelete(doc);
	}
	return 0;
}

int load_map_xml(const char *filename, map<int, int> &map_value)
{

	FILE *fp = NULL;
	mxml_node_t *curnode = NULL, *doc = NULL, *topnode = NULL, *tmpnode = NULL;	/* XML documentation tree */
	int key;
	int value;
	char *attr_ptr = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("can not open the xml file!\n");
		return -1;
	}
	doc = mxmlLoadFile(MXML_NO_PARENT, fp, MXML_NO_CALLBACK);
	fclose(fp);

	topnode = mxmlFindElement(doc, doc, "map", NULL, NULL, MXML_DESCEND);
	curnode = topnode->child;
	while (curnode != NULL) {
		if (curnode->type != MXML_ELEMENT) {
			curnode = curnode->next;
			continue;
		}
		attr_ptr = (char *)mxmlElementGetAttr(curnode, "key");
		key = atoi(attr_ptr);
		attr_ptr = (char *)mxmlElementGetAttr(curnode, "value");
		value = atoi(attr_ptr);
		map_value[key] = value;
		curnode = curnode->next;
	}
	if (doc != NULL) {
		mxmlDelete(doc);
	}

	return 0;
}


int main ()
{
	map<int, int> store_map;
	map<int, int>::iterator iter;
	repeat_map[1] = 1;
	repeat_map[2] = 2;
	save_map_xml("test_map.xml", repeat_map);
	load_map_xml("test_map.xml", store_map);
	for (iter=store_map.begin(); iter != store_map.end(); iter++) {
		cout<<iter->first <<":"<< iter->second<<endl;
	}
	return 0;
}
