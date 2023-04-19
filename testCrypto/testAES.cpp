#include <iostream>
#include <openssl/md5.h> // 如果你直接拷贝我的程序运行， 那注定找不到md5.h
#pragma comment(lib, "libeay32.lib")

using namespace std;
 
int main()
{
    const char *data = "hello world";   // 原始数据
    unsigned char md[16] = {0};
 
	MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, data, strlen(data));
    MD5_Final(md, &ctx);
    
	int i = 0;
	char buf[33] = {0};
    char tmp[3] = {0};
    for(i = 0; i < 16; i++ )
	{
        sprintf(tmp,"%02X", md[i]);
        strcat(buf, tmp);
    }
 
    cout << buf << endl;  // data的md5值
 
    return 0;
}