#pragma once

#include "../FileGroup.h"

#define PACK(data,size) std::make_pair(data, size)
#define FAILED -1
#define PACKLEN(n) (*(pLead)(void *)u)

typedef size_t Lead;
typedef Lead * pLead;
#define LEADSIZE sizeof(Lead)


typedef std::vector<std::pair<char *, size_t> > DataType_T;/*内部存储数据类型*/

typedef void* LPVOID;

enum InputType:int {
	CFILESTREAM, BINARYSTREAM
};

class XData {
private:
	size_t S;/*总数据大小*/
	size_t index = 0;/*当前节点index*/
	DataType_T datas;/*数据*/
	DataType_T::iterator gIt;
	FILE * pF;
	InputType type;
public:
	XData();
	XData(void * data, size_t size);
	XData(FILE * pf);
	void push(void * data, size_t size);
	void rewind();/*回到起点*/
	size_t next();
	size_t size();/*返回数据包大小*/
	size_t get(void *des);/*返回当前指针指向的数据包大小	des为数据指针地址*/
	
	operator void*();/*返回整个数据包的内容*/
	
	~XData();
};

