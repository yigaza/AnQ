// stbSSLOdd.h: interface for the stbSSLOdd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STBSSLODD_H__82EE7C21_DCB5_4210_8A0C_626A417EC50A__INCLUDED_)
#define AFX_STBSSLODD_H__82EE7C21_DCB5_4210_8A0C_626A417EC50A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include "tinyxml.h"
#include "..\include\gs_classTcpIo.h"


class stbSSLOdd  
{
public:
	long LoadRSA(char *fileName,char *passord, RSA *rsa);
	long SaveRSA(char *fileName, char *password,RSA *rsa);
	char * GetNameByRSA(RSA *r);
	char * DecryptByTwoRSA(char *sz, int len, int *lenOut, RSA *me, RSA *other);
	char * RSAPublicDecrypt(char *sz, int len, RSA *me, unsigned int *lenOut);
	char * RSAPrivateDecrypt(char *sz, int len, RSA *me, unsigned int *lenOut);
	char * RSAPublicEncrypt(char *sz, int len, RSA *me, unsigned int *lenOut);
	char * RSAPrivateEncrypt(char *sz,int len,RSA *me,unsigned int *lenOut);
	char * EncryptByTwoRSA(char *sz,int len,int *lenOut,RSA *me,RSA *other);
	long LoadRSA(char *fileName,RSA *rsa);
	long SaveRSA(char *fileName,RSA *rsa);
	RSA * GenRSA(long num);
	char * Base64(char *in,int len,unsigned int *lenOut);
	long BFD(char *password,long passLen,char *in,unsigned int inLen,unsigned char *out,int *lenOut);
	long BFE(char *password,long passLen,char *in,unsigned int inLen,unsigned char *out,int *lenOut);
	long SHA1(void *in,unsigned int len,char *out);
	long MD5(void *in,unsigned int len,char *out);
	stbSSLOdd();
	virtual ~stbSSLOdd();

private:
	const EVP_MD *m_dg_md5;
	const EVP_MD *m_dg_sha1;
};

#endif // !defined(AFX_STBSSLODD_H__82EE7C21_DCB5_4210_8A0C_626A417EC50A__INCLUDED_)


/*
#define SetKey \
  key->n = BN_bin2bn(n, sizeof(n)-1, key->n); \
  key->e = BN_bin2bn(e, sizeof(e)-1, key->e); \
  key->d = BN_bin2bn(d, sizeof(d)-1, key->d); \
  key->p = BN_bin2bn(p, sizeof(p)-1, key->p); \
  key->q = BN_bin2bn(q, sizeof(q)-1, key->q); \
  key->dmp1 = BN_bin2bn(dmp1, sizeof(dmp1)-1, key->dmp1); \
  key->dmq1 = BN_bin2bn(dmq1, sizeof(dmq1)-1, key->dmq1); \
  key->iqmp = BN_bin2bn(iqmp, sizeof(iqmp)-1, key->iqmp); \
  memcpy(c, ctext_ex, sizeof(ctext_ex) - 1); \
  return (sizeof(ctext_ex) - 1);

*/