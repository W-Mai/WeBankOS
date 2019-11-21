#pragma once

#include "../FileGroup.h"

#define PACK(data,size) std::make_pair(data, size)
#define FAILED -1
#define PACKLEN(n) (*(pLead)(void *)u)

typedef size_t Lead;
typedef Lead * pLead;
#define LEADSIZE sizeof(Lead)


typedef std::vector<std::pair<char *, size_t> > DataType_T;/*�ڲ��洢��������*/

typedef void* LPVOID;

enum InputType:int {
	CFILESTREAM, BINARYSTREAM
};

class XData {
private:
	size_t S;/*�����ݴ�С*/
	size_t index = 0;/*��ǰ�ڵ�index*/
	DataType_T datas;/*����*/
	DataType_T::iterator gIt;
	FILE * pF;
	InputType type;
public:
	XData();
	XData(void * data, size_t size);
	XData(FILE * pf);
	void push(void * data, size_t size);
	void rewind();/*�ص����*/
	size_t next();
	size_t size();/*�������ݰ���С*/
	size_t get(void *des);/*���ص�ǰָ��ָ������ݰ���С	desΪ����ָ���ַ*/
	
	operator void*();/*�����������ݰ�������*/
	
	~XData();
};

