#include "Ministry.h"

Ministry::Ministry()
{}

Ministry::~Ministry()
{}

Ministry* Ministry::create(const char* pszFileName)
{
	Ministry* ministry = new Ministry;
	if (ministry && ministry->initWithFile(pszFileName))
	{
		ministry->autorelease();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}
