#ifndef PosteRazorImageIO_h
#define PosteRazorImageIO_h

class PosteRazorImageIO
{
public:
	virtual ~PosteRazorImageIO() {};
	static PosteRazorImageIO* CreatePosteRazorImageIO(const char* imgFileName);

	virtual int GetPixelWidth(void) = 0;
	virtual int GetPixelHeight(void) = 0;
};
#endif