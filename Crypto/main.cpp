#include<iostream>
#include<ctime>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <openssl/md5.h>
using namespace std;

const char *src_str = "zxcvbnmasdfghjklqwertyuiop012345";

void testMD5()
{
    unsigned char md[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)src_str, strlen(src_str), md);
    MD5_CTX ctx;

    MD5_Init(&ctx);
    MD5_Update(&ctx, (char*)src_str, strlen(src_str));
    MD5_Final(md, &ctx);
}

void testSHA256(){
	
	SHA256_CTX c;
	unsigned char md[SHA256_DIGEST_LENGTH];
	SHA256((unsigned char*)src_str, strlen(src_str), md);

	SHA256_Init(&c);
	SHA256_Update(&c,src_str,strlen(src_str));
	SHA256_Final(md,&c);
	OPENSSL_cleanse(&c,sizeof(c));
	
}

 int main()
 {
     clock_t startTime,endTime;
     startTime = clock()*1000;//计时开始
	 cout<<startTime<<endl;
     testMD5();
     endTime = clock()*1000;//计时结束
	 cout<<endTime<<endl;
     cout << "The run time is:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
     system("pause");
     return 0;
 }