// stbSSLOdd.cpp: implementation of the stbSSLOdd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stbSSLOdd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


stbSSLOdd::stbSSLOdd()
{
	OpenSSL_add_all_algorithms();
	OpenSSL_add_all_ciphers();
	OpenSSL_add_all_digests();


	m_dg_md5=EVP_get_digestbyname("md5");
	m_dg_sha1=EVP_get_digestbyname("sha1");
	
	RAND_screen();
	RAND_load_file(".rnd",1024);
}

stbSSLOdd::~stbSSLOdd()
{
	RAND_write_file(".rnd");
	EVP_cleanup();
}

long stbSSLOdd::MD5(void *in, unsigned int len, char *out)
{
	EVP_MD_CTX mdctx;
	 
	unsigned int lenOut;
    EVP_MD_CTX_init(&mdctx);
	EVP_DigestInit_ex(&mdctx, m_dg_md5, NULL);	
	EVP_DigestUpdate(&mdctx, in,len);
	EVP_DigestFinal_ex(&mdctx,(unsigned char *)out, &lenOut);
	EVP_MD_CTX_cleanup(&mdctx);

  return 0;
}

long stbSSLOdd::SHA1(void *in, unsigned int len, char *out)
{
	EVP_MD_CTX mdctx;
	 
	unsigned int lenOut;
    EVP_MD_CTX_init(&mdctx);
	EVP_DigestInit_ex(&mdctx, m_dg_sha1, NULL);	
	EVP_DigestUpdate(&mdctx, in,len);
	EVP_DigestFinal_ex(&mdctx,(unsigned char *)out, &lenOut);
	EVP_MD_CTX_cleanup(&mdctx);

  return 0;
}

long stbSSLOdd::BFE(char *password,long passLen,char *in,unsigned int inLen,unsigned char *out,int *lenOut)
{
	unsigned char key[16];unsigned char iv[8];
	char szsha1[20],szmd5[16];
	MD5(password,passLen,szmd5);
	SHA1(password,passLen,szsha1);
	memcpy(key,szsha1,16);
	memcpy(iv,szmd5,8);

	EVP_CIPHER_CTX ctx;        
    EVP_CIPHER_CTX_init(&ctx);
    EVP_EncryptInit_ex(&ctx, EVP_bf_cbc(), NULL, key, iv);
    if(!EVP_EncryptUpdate(&ctx, (unsigned char *)out, lenOut, (const unsigned char *)in, inLen)){	return 1;        }
   	int tmplen;
    if(!EVP_EncryptFinal_ex(&ctx, out + (*lenOut), &tmplen)){	return 1;        }            
    (*lenOut) += tmplen;
    EVP_CIPHER_CTX_cleanup(&ctx);
	return 0;
}

long stbSSLOdd::BFD(char *password, long passLen, char *in, unsigned int inLen, unsigned char *out, int *lenOut)
{
	unsigned char key[16];unsigned char iv[8];
	char szsha1[20],szmd5[16];
	MD5(password,passLen,szmd5);
	SHA1(password,passLen,szsha1);
	memcpy(key,szsha1,16);
	memcpy(iv,szmd5,8);

	EVP_CIPHER_CTX ctx;        
    EVP_CIPHER_CTX_init(&ctx);
    EVP_DecryptInit_ex(&ctx, EVP_bf_cbc(), NULL, key, iv);
    if(!EVP_DecryptUpdate(&ctx, (unsigned char *)out, lenOut, (const unsigned char *)in, inLen)){	return 1;        }
   	int tmplen;
    if(!EVP_DecryptFinal_ex(&ctx, out + (*lenOut), &tmplen)){	return 1;        }            
     (*lenOut) += tmplen;
    EVP_CIPHER_CTX_cleanup(&ctx);
	return 0;
}

char * stbSSLOdd::Base64(char *in, int len, unsigned int *lenOut)
{
	 BIO *bio, *b64;
	 bio = BIO_new(BIO_s_mem());
	 b64 = BIO_new(BIO_f_base64());
	 //bio = BIO_new_fp(stdout, BIO_NOCLOSE);
	 bio = BIO_push(b64, bio);
	 BIO_write(bio,in,len);
//	 char sz[200];	 
	 BIO_flush(bio);
	 char *out=(char *)malloc((long)(len*1.5+5));
	 (*lenOut)=0;
	 for(;;)
	 {
		 int lenTemp=BIO_read(bio->next_bio,out+(*lenOut),1024);		 
		 (*lenOut)+=lenTemp;
		 if(lenTemp<=1024)break;
	 }
	 BIO_free_all(bio);

	 realloc(out,(*lenOut)+1);
	 out[*lenOut]=0;
	 return out;
	 //return 0;
}

RSA * stbSSLOdd::GenRSA(long num)
{	
	return RSA_generate_key(num,65537,0,0);
}


#define writebn(n) \
	if(n) \
	{	\
	sz=BN_bn2hex(n); \
	len=strlen(sz); \
	BIO_write(out,&len,sizeof(len)); \
	BIO_write(out,sz,len); \
	OPENSSL_free(sz); \
	} \
	else \
	{ \
		len=0; \
		BIO_write(out,&len,sizeof(len)); \
	}

long stbSSLOdd::SaveRSA(char *fileName, RSA *rsa)
{
	BIO *out;
	out = BIO_new_file(fileName, "w");
	if(!out)return 1;
	long len;char *sz;


	writebn(rsa->n);
	writebn(rsa->e);
	writebn(rsa->d);
	writebn(rsa->p);
	writebn(rsa->q);
	writebn(rsa->dmp1);
	writebn(rsa->iqmp);

  
	BIO_free(out);	
	return 0;
}
#undef writebn

#define readbn(n) \
	k=BIO_read(out,&len,sizeof(len)); \
	if(len!=0) \
	{	 \
		sz=(char *)malloc(len); \
		BIO_read(out,sz,len); \
		BN_hex2bn(&(n),sz); \
		free(sz); \
	}	

long stbSSLOdd::LoadRSA(char *fileName, RSA *rsa)
{
	BIO *out;
	out = BIO_new_file(fileName, "r");
	if(!out)return 1;
	long len;char *sz;
	long k;

	readbn(rsa->n);
	readbn(rsa->e);
	readbn(rsa->d);
	readbn(rsa->p);
	readbn(rsa->q);
	readbn(rsa->dmp1);
	readbn(rsa->iqmp);
		 
	BIO_free(out);	

	return 0;
}

#undef readbn

char * stbSSLOdd::EncryptByTwoRSA(char *sz, int len, int *lenOut, RSA *me, RSA *other)
{	
	*lenOut=0;
	char *sz1,*sz2;
	unsigned int lenOut1,lenOut2;
	sz1=this->RSAPrivateEncrypt(sz,len,me,&lenOut1);
	if(sz1==0)return 0;
	sz2=this->RSAPublicEncrypt(sz1,lenOut1,other,&lenOut2);
	if(sz2==0)return 0;
	free(sz1);
	*lenOut=lenOut2;
	return sz2;
//(char *sz, int len, int *lenOut, RSA *me, RSA *other)


/*	unsigned char *usz=(unsigned char *)sz;
	long lenMe=RSA_size(me);
	long lenMePiece=lenMe-11-1;
	long lenMeCharTime=(len/lenMePiece);
	if(lenMeCharTime*lenMePiece<len)lenMeCharTime++;
	long lenMeCharSize=lenMeCharTime*lenMe;
	unsigned char *szMe=(unsigned char *)malloc(lenMeCharSize);
	long nowAt=0;
	for(long i=0;i<lenMeCharTime;i++)
	{
		long lenNow=len;
		if(len>lenMePiece)lenNow=lenMePiece;
		long k=RSA_private_encrypt(lenNow,usz+nowAt,szMe+(lenMe*i),me,RSA_PKCS1_PADDING);				
		nowAt+=lenMePiece;
		len-=lenNow;
	}
	long len1=lenMeCharTime*lenMe;

	long lenOther=RSA_size(other);
	long lenOtherPiece=lenOther-41-1;
	long lenOtherCharTiOther=(len1/lenOtherPiece);
	if(lenOtherCharTiOther*lenOtherPiece<len1)lenOtherCharTiOther++;
	long lenOtherCharSize=lenOtherCharTiOther*lenOther;
	unsigned char *szOther=(unsigned char *)malloc(lenOtherCharSize);

	nowAt=0;
	for(i=0;i<lenOtherCharTiOther;i++)
	{
		long lenNow=len1;
		if(len1>lenOtherPiece)lenNow=lenOtherPiece;
		long k=RSA_public_encrypt(lenNow,szMe+nowAt,szOther+(lenOther*i),other,RSA_PKCS1_OAEP_PADDING);
		nowAt+=lenOtherPiece;
		len1-=lenNow;
	}
	free(szMe);
	*lenOut=(lenOtherCharTiOther*lenOther);
	return (char *)szMe;

  */


		/*
	RSA_size(rsa) - 11;


	f=m_pFriends[0]->rsa;
	long lenA=RSA_size(f);
	unsigned char to[2560],to1[2560],to2[2560],to3[2560],to4[2560];
	RSA_public_encrypt(len,sz,to,f,RSA_PKCS1_OAEP_PADDING);
	memset(sz,0,1000);
	//两个大小不一致
	RSA_private_encrypt(lenA/2,to,to1,rsa,RSA_PKCS1_PADDING);
	RSA_private_encrypt(lenA/2,to+len/2,to2,rsa,RSA_PKCS1_PADDING);

	RSA_public_decrypt(lenA,to1,to3,rsa,RSA_PKCS1_PADDING);
	RSA_public_decrypt(lenA,to2,to4,rsa,RSA_PKCS1_PADDING);
	
	memcpy(to3+lenA/2,to4,lenA/2);

	RSA_private_decrypt(lenA,to,sz,f,RSA_PKCS1_OAEP_PADDING);
*/

	return 0;
}

char * stbSSLOdd::RSAPrivateEncrypt(char *sz, int len, RSA *me, unsigned int *lenOut)
{
	*lenOut=0;
	unsigned char *usz=(unsigned char *)sz;
	long lenMe=RSA_size(me);
	long lenMePiece=lenMe-11-1;
	long lenMeCharTime=(len/lenMePiece);
	if(lenMeCharTime*lenMePiece<len)lenMeCharTime++;
	long lenMeCharSize=lenMeCharTime*lenMe;
	unsigned char *szMe=(unsigned char *)malloc(lenMeCharSize);
	if(szMe==0)return 0;
	long nowAt=0;
	for(long i=0;i<lenMeCharTime;i++)
	{
		long lenNow=len;
		if(len>lenMePiece)lenNow=lenMePiece;
		long k=RSA_private_encrypt(lenNow,usz+nowAt,szMe+(lenMe*i),me,RSA_PKCS1_PADDING);				
		if(k!=lenMe)
		{
			free(szMe);			
			return 0;
		}
		nowAt+=lenMePiece;
		len-=lenNow;
	}
//	long len1=lenMeCharTime*lenMe;
	*lenOut=lenMeCharSize;
	return (char *)szMe;
}

char * stbSSLOdd::RSAPublicEncrypt(char *szMe, int len, RSA *other, unsigned int *lenOut)
{
	*lenOut=0;
	long lenOther=RSA_size(other);
	long lenOtherPiece=lenOther-41-1;
	long lenOtherCharTiOther=(len/lenOtherPiece);
	if(lenOtherCharTiOther*lenOtherPiece<len)lenOtherCharTiOther++;
	long lenOtherCharSize=lenOtherCharTiOther*lenOther;
	unsigned char *szOther=(unsigned char *)malloc(lenOtherCharSize);
	if(szOther==0){return 0;}
	long nowAt=0;
	for(long i=0;i<lenOtherCharTiOther;i++)
	{
		long lenNow=len;
		if(len>lenOtherPiece)lenNow=lenOtherPiece;
		long k=RSA_public_encrypt(lenNow,(const unsigned char *)(szMe+nowAt),szOther+(lenOther*i),other,RSA_PKCS1_OAEP_PADDING);

//		char szMeTemp
//		long ak=RSA_private_decrypt(lenNow,szOther+(lenOther*i),szMeTemp,other,RSA_PKCS1_PADDING);

		if(k!=lenOther)return 0;
		nowAt+=lenOtherPiece;
		len-=lenNow;
	}
	*lenOut=(lenOtherCharTiOther*lenOther);
	return (char *)szOther;
}

char * stbSSLOdd::RSAPrivateDecrypt(char *sz, int len, RSA *me, unsigned int *lenOut)
{
	*lenOut=0;
	unsigned char *usz=(unsigned char *)sz;
	long lenMe=RSA_size(me);
	long lenMePiece=lenMe;
	long lenMeCharTime=(len/lenMePiece);
	if(lenMeCharTime*lenMePiece<len)lenMeCharTime++;
	long lenMeCharSize=lenMeCharTime*lenMe;
	unsigned char *szMe=(unsigned char *)malloc(lenMeCharSize+1);
	unsigned char *szMeTemp=(unsigned char *)malloc(lenMe);
	if(szMe==0)return 0;
	long nowAt=0;
	long lenOutNow=0;
	for(long i=0;i<lenMeCharTime;i++)
	{
		long lenNow=len;
		if(len>lenMePiece)lenNow=lenMePiece;
//	RSA_public_decrypt(lenA,to1,to3,rsa,RSA_PKCS1_PADDING);
//RSA_PKCS1_OAEP_PADDING
		long k=RSA_private_decrypt(lenNow,usz+nowAt,szMeTemp,me,RSA_PKCS1_OAEP_PADDING);
		
		//long k=RSA_private_decrypt(lenNow,usz+nowAt,szMeTemp,me,RSA_PKCS1_PADDING);				
		if(k<0)
		{
//			long kf=ERR_get_error();
//			char sz[1000];
//			char *df=ERR_error_string(kf,sz);
			
			free(szMe);			
			free(szMeTemp);
			return 0;
		}
		memcpy(szMe+lenOutNow,szMeTemp,k);		
		lenOutNow+=k;
		nowAt+=lenMePiece;
		len-=lenNow;
	}	
	*lenOut=lenOutNow;
	free(szMeTemp);
	realloc(szMe,lenOutNow+1);
	return (char *)szMe;
}

char * stbSSLOdd::RSAPublicDecrypt(char *sz, int len, RSA *me, unsigned int *lenOut)
{
	*lenOut=0;
	unsigned char *usz=(unsigned char *)sz;
	long lenMe=RSA_size(me);
	long lenMePiece=lenMe;
	long lenMeCharTime=(len/lenMePiece);
	if(lenMeCharTime*lenMePiece<len)lenMeCharTime++;
	long lenMeCharSize=lenMeCharTime*lenMe;
	unsigned char *szMe=(unsigned char *)malloc(lenMeCharSize+1);
	unsigned char *szMeTemp=(unsigned char *)malloc(lenMe);
	if(szMe==0)return 0;
	long nowAt=0;
	long lenOutNow=0;
	for(long i=0;i<lenMeCharTime;i++)
	{
		long lenNow=len;
		if(len>lenMePiece)lenNow=lenMePiece;
//	RSA_public_decrypt(lenA,to1,to3,rsa,RSA_PKCS1_PADDING);
		long k=RSA_public_decrypt(lenNow,usz+nowAt,szMeTemp,me,RSA_PKCS1_PADDING);				
		if(k<0)
		{
			free(szMe);			
			free(szMeTemp);
			return 0;
		}
		memcpy(szMe+lenOutNow,szMeTemp,k);		
		lenOutNow+=k;
		nowAt+=lenMePiece;
		len-=lenNow;
	}	
	*lenOut=lenOutNow;
	free(szMeTemp);
	realloc(szMe,lenOutNow+1);
	return (char *)szMe;
}

char * stbSSLOdd::DecryptByTwoRSA(char *sz, int len, int *lenOut, RSA *me, RSA *other)
{
	*lenOut=0;
	char *sz1,*sz2;
	unsigned int lenOut1,lenOut2;
	sz1=this->RSAPrivateDecrypt(sz,len,me,&lenOut1);
	if(sz1==0)return 0;
	sz2=this->RSAPublicDecrypt(sz1,lenOut1,other,&lenOut2);
	if(sz2==0)return 0;
	free(sz1);
	*lenOut=lenOut2;
	return sz2;
}

char * stbSSLOdd::GetNameByRSA(RSA *rsa)
{
	char *c1,*c2;
	long n1,n2;
	c1=BN_bn2hex(rsa->n);
	c2=BN_bn2hex(rsa->e);
	n1=strlen(c1);
	n2=strlen(c2);
	char *name=(char *)malloc(n1+n2+2);
	strcpy(name,c1);
	strcat(name+n1,"-");
	strcat(name+n1+1,c2);

	OPENSSL_free(c1); 
	OPENSSL_free(c2); 
	
	return name;
}

long stbSSLOdd::SaveRSA(char *fileName, char *password, RSA *rsa)
{
	//偷懒的办法
	SaveRSA(fileName,rsa);
	BIO *out;
	out = BIO_new_file(fileName, "r");
	char *sz=(char *)malloc(1024*1024);
	char *sz1=(char *)malloc(1024*1024+4086);
	long k=BIO_read(out,sz,1024*1024);	
	BIO_free(out);	
	//if(k==1024*1024) 文件太长...
	
	int lenOut;
	BFE(password,strlen(password),sz,k,(unsigned char *)sz1,&lenOut);
	
	out = BIO_new_file(fileName, "w");
	BIO_write(out,sz1,lenOut); 
  
	BIO_free(out);	
	free(sz);free(sz1);

	return 0;
}

long stbSSLOdd::LoadRSA(char *fileName, char *passord, RSA *rsa)
{
	BIO *out;
	out = BIO_new_file(fileName, "r");
	char *sz=(char *)malloc(1024*1024);
	char *sz1=(char *)malloc(1024*1024+4086);
	long k=BIO_read(out,sz,1024*1024);
	BIO_free(out);	
	//if(k==1024*1024) 文件太长...
	
	int lenOut;
	k=BFD(passord,strlen(passord),sz,k,(unsigned char *)sz1,&lenOut);

	if(k){
		free(sz);free(sz1);
		return k;
	}
	
	char sTemp[]="~~temp38610r740f74031947fj652gdd345";
	out = BIO_new_file(sTemp, "w");	
	BIO_write(out,sz1,lenOut); 
	BIO_free(out);
	long kd=LoadRSA(sTemp,rsa);
	
	
#ifdef WIN32
	CFile::Remove(sTemp);	
#else

#endif

	return kd;
}
