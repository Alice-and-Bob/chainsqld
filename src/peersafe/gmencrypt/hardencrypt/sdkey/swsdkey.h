//------------------------------------------------------------------------------
/*
 This file is part of chainsqld: https://github.com/chainsql/chainsqld
 Copyright (c) 2016-2018 Peersafe Technology Co., Ltd.
 
	chainsqld is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
 
	chainsqld is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
 */
//==============================================================================

#ifndef	__SWSDKEY_H
#define	__SWSDKEY_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef void* HANDLE;
    typedef unsigned char BYTE;
    
#define IN
#define OUT
    
    //����Ա/�û����� ����
#define TYPE_SO				1	//����Ա pin.
#define TYPE_USER			2	//�û� pin.
#define TYPE_PIN_MINLEN		4	//Min Pin Len
#define TYPE_PIN_MAXLEN		16	//Max Pin Len
    
    //��Կ/֤������
#define TYPE_SIGN			2	//ǩ������
#define TYPE_ENCRYPT		1	//��������
    
    //�����궨��
#define MAX_KEY_NUMBER		4		//���������
    
    
    //���
#define TYPE_LABEL_NAME_MINLEN		5		//��С������Ƴ���
#define TYPE_LABEL_NAME_MAXLEN		16		//��������Ƴ���
    
    
    //
    //��ȡSDKEY�豸��Ϣ�궨��
    //
#define EP_FREE_SIZE 					1	//SDKey ʣ��ռ�
#define EP_SERIAL_NUMBER			2	//SDKey Ӳ��Ψһ���к�
#define EP_MAX_RETRY_TIMES		3	//��ȡ��ǰSDKEYʣ��Ŀ������Դ���
    
    //
    //ժҪ�㷨����
    //
#define HASH_ALG_MD2	1
#define HASH_ALG_MD5	2
#define HASH_ALG_SHA1_160	3
#define SGD_SHA1 3
#define SGD_SM3	4
    
    //
    //�Գ��㷨����
    //
    
#define ALG_DES			1
#define ALG_3DES			2
#define ALG_AES			3
#define ALG_SSF33			4
#define ALG_SM1			5
#define ALG_SM4         6
    
    //������ʽ
#define PADDING_TYPE_NONE		0
#define PADDING_TYPE_PKCS5		1
    
    //
    //����ģʽ
    //
#define ALG_MOD_ECB			1
#define ALG_MOD_CBC			2
    
    
    //�û��ļ���
#define EP_PUBLIC							0x00000001		//������ ��ȡ���ݲ���pin����
#define EP_PRIVATE 						0x00000002		//˽���� ��ȡ������pin����
#define EP_FILENAME_MAXLEN				24//20				//�û��ļ����Ƶ���󳤶�
#define EP_FILE_MAX_NUM_PUB				10				//�洢�û������ļ����������
#define EP_FILE_MAX_NUM_PRI				10				//�洢�û�˽���ļ����������
#define EP_FILE_MAX_NUM				 (EP_FILE_MAX_NUM_PUB+EP_FILE_MAX_NUM_PRI)	//�洢�û��ļ����������
    
    //���� FILEINFO �ṹ��Ҫ�о�ʱʹ��
    typedef struct
    {
        unsigned char 	pbFileName[EP_FILENAME_MAXLEN];	//�ļ�����
        unsigned long	dwFileNameLen;					//�ļ����Ƴ���
        unsigned long	dwFileType;						//�ļ�����
        unsigned long	dwFileLen;						//�ļ���С
    }FILEINFO, *PFILEINFO;
    
    /*ECC*/
#define ECC_MAX_MODULUS_BITS_LEN 256
    /*ECC��Կ���ݽṹ*/
    typedef struct Struct_ECCPUBLICKEYBLOB{
        BYTE XCoordinate[ECC_MAX_MODULUS_BITS_LEN/8];
        BYTE YCoordinate[ECC_MAX_MODULUS_BITS_LEN/8];
    } ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;
    
    /*ECC˽Կ���ݽṹ*/
    typedef struct Struct_ECCPRIVATEKEYBLOB{
        BYTE PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];
    } ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB;
    
    /*ECCǩ�����ݽṹ*/
    typedef struct Struct_ECCSIGNATUREBLOB{
        BYTE r[ECC_MAX_MODULUS_BITS_LEN/8];
        BYTE s[ECC_MAX_MODULUS_BITS_LEN/8];
    } ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;
    
    //-----------------------------------------------------------------------------
    //�������
    //-----------------------------------------------------------------------------
#define SDKEY_SUCCESS						0x00000000	//�����ɹ�
#define SDKEY_FAILED						0x20000001	//����ʧ��
#define SDKEY_KEY_REMOVED					0x20000002	//δ����SDKEY
#define SDKEY_KEY_INVALID					0x20000003	//����SDKEYʧ��/SDKEY��Ч
#define SDKEY_INVALID_PARAMETER  			0x20000004	//��������
#define SDKEY_VERIFIEDPIN_FAILED			0x20000005	//��֤����ʧ��
#define SDKEY_USER_NOT_LOG_IN				0x20000006	//�û�û�е�½��û����֤����
#define SDKEY_BUFFER_TOO_SMALL       		0x20000007	//������̫С
#define SDKEY_CONTAINER_TOOMORE 			0x20000008	//������������,����10��
#define SDKEY_ERR_GETEKEYPARAM				0x20000009	//��ȡSDKEY��Ϣʧ��
#define SDKEY_ERR_PINLOCKED					0x20000010	//�����Ѿ�����
#define SDKEY_ERR_CREATEFILE				0x20000011	//�����ļ�����
#define SDKEY_ERR_EXISTFILE					0x20000012	//�ļ��Ѵ��ڴ���
#define SDKEY_ERR_OPENFILE					0x20000013	//���ļ�����
#define SDKEY_ERR_READFILE					0x20000014	//���ļ�����
#define SDKEY_ERR_WRITEFILE					0x20000015	//д�ļ�����
#define SDKEY_ERR_NOFILE					0x20000016	//û���ҵ��ļ�����
    
#define SDKEY_ERR_PARAMETER_NOT_SUPPORT				0x20000020	//��֧�ֵĲ���
#define SDKEY_ERR_FUNCTION_NOT_SUPPORT				0x20000021	//��֧�ֵĺ���
    
    
    /*
     �������ܣ�	��SDKEY,�õ��������
     ����˵����	hKey:		���ز������
     ����ֵ��	SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_OpenCard(IN OUT HANDLE* hKey);
    
    /*
     �������ܣ�	�ر�SDKEY
     ����˵����	hKey:		�������
     ����ֵ��	SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_CloseCard(IN HANDLE hKey);
    
    /*
     �������ܣ�	�û�LogIn
     ����˵����	hKey:		�������
     ulPINType:	����Ա/�û���������
     pbPIN:		����Ա/�û�����
     ulPINLen:	����Ա/�û������
     pulRetry:	��������Դ���
     ����ֵ��	SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_LogIn(IN HANDLE	hKey,
                               IN unsigned long			ulPINType,
                               IN const unsigned char*		pbPIN,
                               IN unsigned long			ulPINLen,
                               OUT unsigned long		*pulRetry);
    
    /*
     �������ܣ�	�û�LogOut
     ����˵����	hKey:		�������
     ����ֵ��	SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_LogOut(IN HANDLE hKey);
    
    /*
     �������ܣ�	�޸Ŀ���
     ����˵����	hKey:		�������
     ulPINType:	����Ա/�û���������
     pbOldPIN:		����Ա/�û��ɿ���
     ulOldPINLen:	����Ա/�û��ɿ����
     pbNewPIN:		����Ա/�û��¿���
     ulNewPINLen:	����Ա/�û��¿����
     pulRetry: ������֤ʧ��ʱ���ؿ����Դ���
     ����ֵ��	SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_ChangePIN(IN HANDLE	hKey,
                                   IN unsigned long	ulPINType,
                                   IN const unsigned char*	pbOldPIN,
                                   IN unsigned long		ulOldPINLen,
                                   IN const unsigned char*	pbNewPIN,
                                   IN unsigned long		ulNewPINLen,
                                   OUT unsigned long		*pulRetry);
    
    /*
     �������ܣ�	��������
     ����˵����	hKey:		�������
     pbPIN:		����Ա����
     ulPINLen:	����Ա�����
     pbNewPIN:		�û��¿���
     ulNewPINLen:	�û��¿����
     pulRetry: ������֤ʧ��ʱ���ع���Ա��������Դ���
     ����ֵ��	SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_UnLock(IN HANDLE	hKey,
                                IN const unsigned char*	 pbPIN,    //����Ա����
                                IN unsigned long			ulPINLen,
                                IN const unsigned char*	     pbNewPIN,  //�µ��û�����
                                IN unsigned long			ulNewPINLen,
                                OUT unsigned long		*pulRetry);
    
    
    /*
     �������ܣ�	ȡ��SDKEYӲ������
     ����˵����	hKey:		�������
     dwParam:	�����Ϣ���ͣ������ SDKEY�豸��Ϣ�궨��
     pbData:			�������
     pdwDataLen:		������ݳ���
     dwFlags:		ȡֵ0�������ֽ�
     ����ֵ��	SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_GetKeyParam(IN HANDLE		hKey,
                                     IN unsigned long		dwParam,
                                     OUT unsigned char		*pbData,
                                     IN OUT unsigned long	*pdwDataLen);
    
    /*
     �������ܣ� ��SDKEY�ڴ����ļ�
     ����˵����	hKey:   �������
     *FileName    ˽���ļ�������
     FileNameLen  �ļ����Ƴ���
     MaxFileLen   ����ļ�����
     Flag         �ļ����� (���û��ļ���),˽�����ļ����ǹ������ļ�
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ��ע:��sdkey�ڵ��ļ�������Ŀ¼�ĸ��
     */
    unsigned long  SDKEY_CreateFile(IN HANDLE hKey,
                                    IN unsigned char *FileName,
                                    IN unsigned long FileNameLen,
                                    IN unsigned long MaxFileLen,
                                    IN unsigned long Flag    );
    
    /*
     �������ܣ� д���ݵ�SDKEY
     ����˵���� hKey:   �������
     *FileName    ˽���ļ�������
     FileNameLen  �ļ����Ƴ���
     *pbData      ��������
     pbDataLen    ���ݳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_WriteData(IN HANDLE hKey,
                                   IN unsigned char *FileName,
                                   IN unsigned long FileNameLen,
                                   IN unsigned char *pbData,
                                   IN unsigned long pbDataLen);
    
    
    /*
     �������ܣ� ��SDKEY�ڶ�ȡ����
     ����˵���� hKey:   �������
     *FileName    ˽���ļ�������
     FileNameLen  �ļ����Ƴ���
     *pbData      ��������
     pbDataLen    ���ݳ���
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_ReadData(IN HANDLE hKey,
                                  IN unsigned char *FileName,
                                  IN unsigned long FileNameLen,
                                  OUT unsigned char *pbData,
                                  OUT unsigned long *pbDataLen);
    
    /*
     �������ܣ�  ɾ��SDKEY��ָ������
     ����˵���� hKey:   �������
     *FileName    ˽���ļ�������
     FileNameLen  �ļ����Ƴ���
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_DelFile(IN HANDLE hKey,
                                 IN unsigned char *FileName,
                                 IN unsigned long FileNameLen);
    
    /*
     �������ܣ� �о�SDKEY���ļ�����
     ����˵���� hKey:   �������
     *pbFileInfo    �ļ����
     pdwFileNum  �ļ�����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long  SDKEY_ListFile(IN HANDLE hKey,
                                  OUT FILEINFO *pbFileInfo,
                                  OUT unsigned long *pdwFileNum);
    
    /*
     �������ܣ� ���������
     ����˵���� hKey:   �������
     ulRandLen �����������������
     pRandom   ���������Ļ�����ָ��
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_GenRandom(IN HANDLE hKey,
                                  IN unsigned long ulRandLen,
                                  OUT unsigned char *pRandom);
    
    /*
     �������ܣ� ����RSA��Կ
     ����˵���� hKey:   �������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     ulModulusLen   rsa��Կģ����֧��1024
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ��ע��һ����Կ������֧��˫��Կ����ǩ���ͼ���(����)2�֡�
     */
    unsigned long SDKEY_GenerateRsaKeyPair(IN HANDLE hKey,
                                           IN unsigned long ulAlias,
                                           IN unsigned long ulKeyUse,
                                           IN unsigned long ulModulusLen);
    
    /*
     �������ܣ� ��ȡ��Կ��Ϣ
     ����˵���� hKey:   �������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pDerPubKey:der����Ĺ�Կ
     pulDerPubKeyLen����Կ���ȣ�����1024bits��rsa��Կ,der����ĳ���Ϊ140�ֽ�
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ��ע��һ����Կ������֧��˫��Կ����ǩ���ͼ���(����)2�֡�
     */
    unsigned long SDKEY_GetRsaPubLicKey(IN HANDLE hKey,
                                        IN unsigned long ulAlias,
                                        IN unsigned long ulKeyUse,
                                        OUT unsigned char *pDerPubKey,
                                        OUT unsigned long *pulDerPubKeyLen);
    
    /*
     �������ܣ� ����֤�鵽SDKEY��
     ����˵���� hKey:   �������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pDerCert   Der�����֤��
     ulDerCertLen ֤�鳤��
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SetCertificate(IN HANDLE hKey,
                                       IN unsigned long ulAlias,
                                       IN unsigned long ulKeyUse,
                                       IN unsigned char *pDerCert,
                                       IN unsigned long ulDerCertLen);
    
    
    /*
     �������ܣ� ����֤��
     ����˵���� hKey:   �������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pDerCert   Der�����֤��
     pulDerCertLen ֤�鳤��
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_GetCertificate(IN HANDLE hKey,
                                       IN unsigned long ulAlias,
                                       IN unsigned long ulKeyUse,
                                       OUT unsigned char *pDerCert,
                                       OUT unsigned long *pulDerCertLen);
    
    /*
     �������ܣ� rsaǩ����pkcs1��ʽ��
     ����˵���� hKey:   			�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     ulHashType  		ժҪ�㷨���ͣ�HASH_ALG_MD2,HASH_ALG_MD5,HASH_ALG_SHA1_160
     
     pInData 			��ǩ����ԭ��
     ulInDataLen    	��ǩ����ԭ�ĳ���
     pSignValue				ǩ��ֵ
     pulSignValueLen	ǩ��ֵ����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_RSASign(IN HANDLE hKey,
                                IN unsigned long ulAlias,
                                IN unsigned long ulKeyUse,
                                IN unsigned long ulHashType,
                                IN unsigned char *pInData,
                                IN unsigned long ulInDataLen,
                                OUT unsigned char *pSignValue,
                                OUT unsigned long *pulSignValueLen);
    
    /*
     �������ܣ� ��֤ǩ����pkcs1��ʽ��
     ����˵���� hKey:�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     ulHashTypeժҪ�㷨���ͣ�
					HASH_ALG_MD2,HASH_ALG_MD5,HASH_ALG_SHA1_160
     pInData 	��ǩ����ԭ��
     ulInDataLen��ǩ����ԭ�ĳ���
     pSignValue ǩ��ֵ
     ulSignValueLen ǩ��ֵ����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_RSAVerify(IN HANDLE hKey,
                                  IN unsigned long ulAlias,
                                  IN unsigned long ulKeyUse,
                                  IN unsigned long ulHashType,
                                  IN unsigned char *pInData,
                                  IN unsigned long ulInDataLen,
                                  IN unsigned char *pSignValue,
                                  IN unsigned long ulSignValueLen);
    
    
    /*
     �������ܣ� ��Կ���ܣ�pkcs1��ʽ��
     ����˵���� hKey:�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pPlainData	����
     ulPlainDataLen	���ĳ���
     pCipherData 	����
     pulCipherDataLen���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_RSAPubKeyEncrypt(IN HANDLE hEkey,
                                         IN unsigned long ulAlias,
                                         IN unsigned long ulKeyUse,
                                         IN unsigned char * pPlainData,
                                         IN unsigned long ulPlainDataLen,
                                         OUT unsigned char * pCipherData,
                                         OUT unsigned long * pulCipherDataLen);
    
    
    /*
     �������ܣ� ˽Կ���ܣ�pkcs1��ʽ��
     ����˵���� hEkey:   			�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pCipherData 			����
     ulCipherDataLen    	���ĳ���
     pPlainData				����
     pulPlainDataLen	���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_RSAPriKeyDecrypt(IN HANDLE hEkey,
                                         IN unsigned long ulAlias,
                                         IN unsigned long ulKeyUse,
                                         IN unsigned char *pCipherData,
                                         IN unsigned long ulCipherDataLen,
                                         OUT unsigned char *pPlainData,
                                         OUT unsigned long *pulPlainDataLen);
    
    /*
     �������ܣ� ˽Կ���ܣ�pkcs1��ʽ��
     ����˵���� hKey:�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pPlainData	����
     ulPlainDataLen	���ĳ���
     pCipherData 	����
     pulCipherDataLen���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_RSAPriKeyEncrypt(IN HANDLE hEkey,
                                         IN unsigned long ulAlias,
                                         IN unsigned long ulKeyUse,
                                         IN unsigned char * pPlainData,
                                         IN unsigned long ulPlainDataLen,
                                         OUT unsigned char * pCipherData,
                                         OUT unsigned long * pulCipherDataLen);
    
    
    /*
     �������ܣ� ��Կ���ܣ�pkcs1��ʽ��
     ����˵���� hEkey:   			�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pCipherData 			����
     ulCipherDataLen    	���ĳ���
     pPlainData				����
     pulPlainDataLen	���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_RSAPubKeyDecrypt(IN HANDLE hEkey,
                                         IN unsigned long ulAlias,
                                         IN unsigned long ulKeyUse,
                                         IN unsigned char *pCipherData,
                                         IN unsigned long ulCipherDataLen,
                                         OUT unsigned char *pPlainData,
                                         OUT unsigned long *pulPlainDataLen);
    
    /*
     �������ܣ� �Գ��㷨����
     ����˵���� hEkey:   			�������
     ulAlgFlag			�㷨���ͣ��� �Գ��㷨���ͺ궨��
     ulAlgMode		����ģʽ ���� ����ģʽ�궨��
     iv						��ʼ������
     pKey					��Կ
     pPlainData			����
     ulPlainDataLen	���ĳ���
     pCipherData 		����
     pulCipherDataDataLen   ���ĳ���
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymEncrypt(IN HANDLE hEkey,
                                   IN unsigned long ulAlgFlag,
                                   IN unsigned long ulAlgMode,
                                   IN unsigned char *iv,
                                   IN unsigned char *pKey,
                                   IN unsigned char *pPlainData,
                                   IN unsigned long ulPlainDataLen,
                                   OUT unsigned char *pCipherData,
                                   OUT unsigned long *pulCipherDataDataLen);
    
    /*
     �������ܣ� �Գ��㷨����
     ����˵���� hEkey:   �������
     ulAlgFlag				�㷨����,�� �Գ��㷨���ͺ궨��
     ulAlgMode			����ģʽ �� ����ģʽ�궨��
     iv							��ʼ������
     pKey						��Կ
     pCipherData 			����
     ulCipherDataDataLen    	���ĳ���
     pPlainData				����
     pulPlainDataLen	���ĳ���
     
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymDecrypt(IN HANDLE hEkey,
                                   IN unsigned long ulAlgFlag,
                                   IN unsigned long ulAlgMode,
                                   IN unsigned char *iv,
                                   IN unsigned char *pKey,
                                   IN unsigned char *pCipherData ,
                                   IN unsigned long ulCipherDataDataLen,
                                   OUT unsigned char *pPlainData,
                                   OUT unsigned long *pulPlainDataLen);
    
    /*
     �������ܣ� �Գ��㷨���ܳ�ʼ��
     ����˵���� hEkey:   			�������
     ulAlgFlag			�㷨���ͣ��� �Գ��㷨���ͺ궨��
     ulAlgMode		����ģʽ ���� ����ģʽ�궨��
     ulPadding			������ʽ����������ʽ�궨��
     iv						��ʼ������
     pKey					��Կ
     phKey				���ص��㷨������
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymEncryptInit(
                                       IN HANDLE hEkey,
                                       IN unsigned long ulAlgFlag,
                                       IN unsigned long ulAlgMode,
                                       IN unsigned long ulPadding,
                                       IN unsigned char *iv,
                                       IN unsigned char *pKey,
                                       OUT HANDLE	*phKey);
    
    /*
     �������ܣ� �Գ��㷨�����м䴦����
     ����˵���� hEkey:   			�������
     phKey				��SDKEY_SymEncryptInit���ɵ��㷨������
     pPlainData			����
     ulPlainDataLen	���ĳ���
     pCipherData 		����
     pulCipherDataLen   ���ĳ���
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymEncryptUpdate(
                                         IN HANDLE hEkey,
                                         IN HANDLE phKey,
                                         IN unsigned char	*pPlainData,
                                         IN unsigned long ulPlainDataLen,
                                         OUT unsigned char *pCipherData,
                                         OUT unsigned long *pulCipherDataLen);
    
    /*
     �������ܣ� �Գ��㷨���ܽ�������
     ����˵���� hEkey:   			�������
     phKey				��SDKEY_SymEncryptInit���ɵ��㷨������
     pCipherData 		����
     pulCipherDataLen   ���ĳ���
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymEncryptFinal(
                                        IN HANDLE hEkey,
                                        IN HANDLE phKey,
                                        OUT unsigned char *pCipherData,
                                        OUT unsigned long *pulCipherDataLen);
    
    /*
     �������ܣ� �Գ��㷨���ܳ�ʼ��
     ����˵���� hEkey:   			�������
     ulAlgFlag			�㷨���ͣ��� �Գ��㷨���ͺ궨��
     ulAlgMode		����ģʽ ���� ����ģʽ�궨��
     ulPadding			������ʽ����������ʽ�궨��
     iv						��ʼ������
     pKey					��Կ
     phKey				���ص��㷨������
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymDecryptInit(
                                       IN HANDLE hEkey,
                                       IN unsigned long ulAlgFlag,
                                       IN unsigned long ulAlgMode,
                                       IN unsigned long ulPadding,
                                       IN unsigned char *iv,
                                       IN unsigned char *pKey,
                                       OUT HANDLE	*phKey);
    
    /*
     �������ܣ� �Գ��㷨�����м䴦����
     ����˵���� hEkey:   			�������
     phKey				��SDKEY_SymDecryptInit���ɵ��㷨������
     pCipherData 		����
     pulCipherDataLen   ���ĳ���
     pPlainData			����
     ulPlainDataLen	���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymDecryptUpdate(
                                         IN HANDLE hEkey,
                                         IN HANDLE phKey,
                                         IN unsigned char	*pCipherData,
                                         IN unsigned long ulCipherDataLen,
                                         OUT unsigned char *pPlainData,
                                         OUT unsigned long *pulPlainDataLen);
    
    /*
     �������ܣ� �Գ��㷨���ܽ�������
     ����˵���� hEkey:   			�������
     phKey				��SDKEY_SymDecryptInit���ɵ��㷨������
     pPlainData 		����
     pulPlainDataLen ���ĳ���
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_SymDecryptFinal(
                                        IN HANDLE hEkey,
                                        IN HANDLE phKey,
                                        OUT unsigned char *pPlainData,
                                        OUT unsigned long *pulPlainDataLen);
    
    //ver2.2 add sm2 sm3 support
    /*
     �������ܣ� ECCǩ����SM2��
     ����˵���� hKey:   			�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pInData 			��ǩ����HASHֵ
     ulInDataLen    	��ǩ����HASHֵ����
     pSignValue			ǩ��ֵ
     pulSignValueLen	ǩ��ֵ����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_ECCSign(IN HANDLE hKey,
                                IN unsigned long ulAlias,
                                IN unsigned long ulKeyUse,
                                IN unsigned char *pInData,
                                IN unsigned long ulInDataLen,
                                OUT unsigned char *pSignValue,
                                OUT unsigned long *pulSignValueLen);
    
    /*
     �������ܣ� ECC��ǩ��SM2��
     ����˵���� hKey:�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pInData 	��ǩ����HASHֵ
     ulInDataLen��ǩ����HASHֵ����
     pSignValue ǩ��ֵ
     ulSignValueLen ǩ��ֵ����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_ECCVerify(IN HANDLE hKey,
                                  IN unsigned long ulAlias,
                                  IN unsigned long ulKeyUse,
                                  IN unsigned char *pInData,
                                  IN unsigned long ulInDataLen,
                                  IN unsigned char *pSignValue,
                                  IN unsigned long ulSignValueLen);
    
    
    /*
     �������ܣ� ECC��Կ���ܣ�SM2��
     ����˵���� hKey:�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pPlainData	����
     ulPlainDataLen	���ĳ���
     pCipherData 	����
     pulCipherDataLen���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ˵�������ĳ���Ϊ����+96�ֽڣ�˳��ֱ�ΪC1C3C2������C1Ϊһ���㳤��Ϊ64�ֽڣ�C3���ȹ̶�Ϊ32�ֽڣ�C2����ͬ����
     */
    unsigned long SDKEY_ECCEncrypt(IN HANDLE hEkey,
                                   IN unsigned long ulAlias,
                                   IN unsigned long ulKeyUse,
                                   IN unsigned char * pPlainData,
                                   IN unsigned long ulPlainDataLen,
                                   OUT unsigned char * pCipherData,
                                   OUT unsigned long * pulCipherDataLen);
    
    
    /*
     �������ܣ� ECC˽Կ���ܣ�SM2��
     ����˵���� hEkey:   			�������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pCipherData 			����
     ulCipherDataLen    	���ĳ���
     pPlainData				����
     pulPlainDataLen	���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ˵�������ĸ�ʽ�ο����ܺ�����˵��
     */
    unsigned long SDKEY_ECCDecrypt(IN HANDLE hEkey,
                                   IN unsigned long ulAlias,
                                   IN unsigned long ulKeyUse,
                                   IN unsigned char *pCipherData,
                                   IN unsigned long ulCipherDataLen,
                                   OUT unsigned char *pPlainData,
                                   OUT unsigned long *pulPlainDataLen);
    
    /*
     �������ܣ� �ⲿECCǩ����SM2��
     ����˵���� hKey:   			�������
     pPriKey			�ⲿ�����ECC˽Կ
     ulPriKeyLen		ECC˽Կ����
     pInData 			��ǩ����HASHֵ
     ulInDataLen    	��ǩ����HASHֵ����
     pSignValue			ǩ��ֵ
     pulSignValueLen	ǩ��ֵ����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_ExtECCSign(IN HANDLE hKey,
                                   IN unsigned char *pPriKey,
                                   IN unsigned long ulPriKeyLen,
                                   IN unsigned char *pInData,
                                   IN unsigned long ulInDataLen,
                                   OUT unsigned char *pSignValue,
                                   OUT unsigned long *pulSignValueLen);
    
    /*
     �������ܣ� �ⲿECC��ǩ��SM2��
     ����˵���� hKey				�������
     pPubKey		�ⲿ�����ECC��Կ
     ulPubKeyLen	��Կ����
     pInData 		��ǩ����HASHֵ
     ulInDataLen	��ǩ����HASHֵ����
     pSignValue	ǩ��ֵ
     ulSignValueLen ǩ��ֵ����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_ExtECCVerify(IN HANDLE hKey,
                                     IN unsigned char *pPubKey,
                                     IN unsigned long ulPubKeyLen,
                                     IN unsigned char *pInData,
                                     IN unsigned long ulInDataLen,
                                     IN unsigned char *pSignValue,
                                     IN unsigned long ulSignValueLen);
    
    
    /*
     �������ܣ� �ⲿECC��Կ���ܣ�SM2��
     ����˵���� hKey:�������
     pPubKey		�ⲿ�����ECC��Կ
     ulPubKeyLen	��Կ����
     pPlainData		����
     ulPlainDataLen	���ĳ���
     pCipherData 	����
     pulCipherDataLen���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ˵�������ĳ���Ϊ����+96�ֽڣ�˳��ֱ�ΪC1C3C2������C1Ϊһ���㳤��Ϊ64�ֽڣ�C3���ȹ̶�Ϊ32�ֽڣ�C2����ͬ����
     */
    unsigned long SDKEY_ExtECCEncrypt(IN HANDLE hEkey,
                                      IN unsigned char *pPubKey,
                                      IN unsigned long ulPubKeyLen,
                                      IN unsigned char * pPlainData,
                                      IN unsigned long ulPlainDataLen,
                                      OUT unsigned char * pCipherData,
                                      OUT unsigned long * pulCipherDataLen);
    
    
    /*
     �������ܣ� �ⲿECC˽Կ���ܣ�SM2��
     ����˵���� hEkey:   			�������
     pPriKey			�ⲿ�����ECC˽Կ
     ulPriKeyLen		ECC˽Կ����
     pCipherData 			����
     ulCipherDataLen    	���ĳ���
     pPlainData				����
     pulPlainDataLen	���ĳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ˵�������ĸ�ʽ�ο����ܺ�����˵��
     */
    unsigned long SDKEY_ExtECCDecrypt(IN HANDLE hEkey,
                                      IN unsigned char *pPriKey,
                                      IN unsigned long ulPriKeyLen,
                                      IN unsigned char *pCipherData,
                                      IN unsigned long ulCipherDataLen,
                                      OUT unsigned char *pPlainData,
                                      OUT unsigned long *pulPlainDataLen);
    
    /*
     �������ܣ� ����ECC��Կ��SM2��
     ����˵���� hKey:   �������
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     ulModulusLen  ECC��Կģ����ĿǰSM2Ϊ256bit
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ��ע��һ����Կ������֧��˫��Կ����ǩ���ͼ���(����)2�֡�
     */
    unsigned long SDKEY_GenECCKeyPair(IN HANDLE hKey,
                                      IN unsigned long ulAlias,
                                      IN unsigned long ulKeyUse,
                                      IN unsigned long ulModulusLen);
    
    /*
     �������ܣ� ��������ECC��Կ��SM2��
     ����˵���� hKey:   �������
     ulModulusLen  ECC��Կģ����ĿǰSM2Ϊ256bit
     pPubKey ECC��Կ
     pulPubKeyLen ECC��Կ����
     pPriKey ECC˽Կ
     pulPriKeyLen ECC˽Կ����
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_GenExtECCKeyPair(IN HANDLE hKey,
                                         IN unsigned long ulModulusLen,
                                         OUT unsigned char *pPubKey,
                                         OUT unsigned long *pulPubKeyLen,
                                         OUT unsigned char *pPriKey,
                                         OUT unsigned long *pulPriKeyLen);
    
    /*
     �������ܣ� ��ȡ��Կ��Ϣ
     ����˵���� hKey:   �������  
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pPubKey: ECC��Կ
     pulPubKeyLen����Կ����
     
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     ��ע��һ����Կ������֧��˫��Կ����ǩ���ͼ���(����)2�֡�
     */ 
    unsigned long SDKEY_GetECCPublicKey(IN HANDLE hKey,
                                        IN unsigned long ulAlias,
                                        IN unsigned long ulKeyUse,
                                        OUT unsigned char *pPubKey,
                                        OUT unsigned long *pulPubKeyLen);
    
    /*
     �������ܣ�	Hash�����ʼ��
     ����˵����	hKey		�������
     ulAlgo	Hash�㷨��ʾ��Ŀǰ֧��SGD_SM3��SGD_SHA1
     hHash	Hash������
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_HashInit(IN HANDLE hKey,
                                 IN unsigned long ulAlgo,
                                 OUT HANDLE *hHash);
    
    /*
     �������ܣ�	Hash��ID�Ĵ����ʼ��
     ����˵����	hKey		�������
     ulAlgo	Hash�㷨��ʾ����ID�ĳ�ʼ����֧��SGD_SM3
     pECCPubKey ECC��Կ
     ulECCPubKeyLen ECC��Կ����
     pID ID����
     ulIDLen ID�����ݳ���
     hHash	Hash������
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_HashInit_ID(IN HANDLE hKey,
                                    IN unsigned long ulAlgo,
                                    IN unsigned char *pECCPubKey,
                                    IN unsigned long ulECCPubKeyLen,
                                    IN unsigned char *pID,
                                    IN unsigned long ulIDLen,
                                    OUT HANDLE *hHash);
    
    /*
     �������ܣ�	Hash�����м�κ���
     ����˵����	hKey		�������
     hHash	Hash������
     pInData ����������
     ulInDataLen ���������ݳ���
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_HashUpdate(IN HANDLE hKey,
                                   IN HANDLE hHash,
                                   IN unsigned char *pInData,
                                   IN unsigned long ulInDataLen);
    
    /*
     �������ܣ�	Hash�����������
     ����˵����	hKey		�������
     hHash	Hash������
     pHashData Hash���
     ulHashDataLen Hash�������
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_HashFinal(IN HANDLE hKey,
                                  IN HANDLE hHash,
                                  OUT unsigned char *pHashData,
                                  OUT unsigned long *pulHashDataLen);
    
    /*
     �������ܣ�	Hash������
     ����˵����	hKey		�������
     ulAlgo	Hash�㷨��ʾ��Ŀǰ֧��SGD_SM3��SGD_SHA1
     pInData ����������
     ulInDataLen ���������ݳ���
     pHashData Hash���
     ulHashDataLen Hash�������
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_Hash(IN HANDLE hKey,
                             IN unsigned long ulAlgo,
                             IN unsigned char *pInData,
                             IN unsigned long ulInDataLen,
                             OUT unsigned char *pHashData,
                             OUT unsigned long *pulHashDataLen);
    
    //ver2.2.0.1 add import ecc key pair function
    /*
     �������ܣ� ����ECC��Կ�ԣ�SM2��
     ����˵���� hKey:�������  
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pPubKey 	ECC��Կ
     ulPubKeyLen ECC��Կ����
     pPriKey ECC˽Կ
     ulPriKeyLen ˽Կ����          
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_ImportEccKeyPair(IN HANDLE hKey,
                                         IN unsigned long ulAlias,
                                         IN unsigned long ulKeyUse,
                                         IN unsigned char *pPubKey,
                                         IN unsigned long ulPubKeyLen,
                                         IN unsigned char *pPriKey,
                                         IN unsigned long ulPriKeyLen);
    
    
    
    //ver2.2.0.3�Ժ�  ����SM2��ԿЭ�̹���
    
    /*
     �������ܣ� ���𷽵�һ������,������ԿЭ�̲����������
     ʹ��ECC��ԿЭ���㷨��Ϊ����Ự��Կ������Э�̲�����������ʱECC��Կ�ԵĹ�Կ��Э�̾����
     ����˵����  hKey:�������  
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT			
     pTempPubKey�� ������ʱ��Կ
     pulTempPubKeyLen�� ������ʱ��Կ����   
     phAgreementHandle�� ���ص���ԿЭ�̾��
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_GenAgreementDataWithECC(IN HANDLE hKey,
                                                IN unsigned long ulAlias,
                                                IN unsigned long ulKeyUse,											
                                                OUT unsigned char *pTempPubKey,
                                                OUT unsigned long *pulTempPubKeyLen,
                                                OUT HANDLE *phAgreementHandle);
    /*
     �������ܣ�  ��Ӧ������,����Э�����ݲ�����Ự��Կ��
     ʹ��ECC��ԿЭ���㷨������Э�̲���������Ự��Կ�������ʱECC��Կ�Թ�Կ��������Э�̳�������Կ��
     ����˵����  hKey:�������  
     ulAlias: ��Կ�����ţ���0 �� (MAX_KEY_NUMBER-1)
     ulKeyUse����Կ��;��TYPE_SIGN ��TYPE_ENCRYPT
     pSponsorPubKey��       ����ECC��Կ
     ulSponsorPubKeyLen��   ����ECC��Կ����
     pSponsorTempPubKey��   ������ʱ��Կ
     ulSponsorTempPubKeyLen��������ʱ��Կ����
     ulAgreementKeyLen��   Э�̵ĻỰ��Կ���ȣ�������64�ֽ�
     pID��         ��Ӧ��ID��������32�ֽ�
     ulIDLen��     ��Ӧ��ID����
     pSponsorID��  ����ID��������32�ֽ�
     ulSponsorIDLen������ID����
     pTempPubKey��    ��Ӧ����ʱ��Կ
     pulTempPubKeyLen ��Ӧ����ʱ��Կ���� 
     pAgreementKey��  Э�̳����ĻỰ��Կ
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_GenAgreementDataAndKeyWithECC(IN HANDLE hKey,
                                                      IN unsigned long ulAlias,
                                                      IN unsigned long ulKeyUse,
                                                      IN unsigned char *pSponsorPubKey,       
                                                      IN unsigned long ulSponsorPubKeyLen,
                                                      IN unsigned char *pSponsorTempPubKey,
                                                      IN unsigned long ulSponsorTempPubKeyLen,
                                                      IN unsigned long ulAgreementKeyLen,           
                                                      IN unsigned char *pID,
                                                      IN unsigned long  ulIDLen,
                                                      IN unsigned char *pSponsorID,
                                                      IN unsigned long  ulSponsorIDLen,
                                                      OUT unsigned char *pTempPubKey,
                                                      OUT unsigned long *pulTempPubKeyLen,
                                                      OUT unsigned char *pAgreementKey);
    
    /*
     �������ܣ����𷽵ڶ�������,����Ự��Կ��
     ʹ��ECC��ԿЭ���㷨��ʹ������Э�̾������Ӧ����Э�̲�������Ự��Կ��ͬʱ���ػỰ��Կ��
     ����˵����  hKey:�������  
     hAgreementHandle����ԿЭ�̾��
     pResponsePubKey�� ��Ӧ��ECC��Կ
     ulResponsePubKeyLen����Ӧ��ECC��Կ����
     pResponseTempPubKey�� ��Ӧ����ʱECC��Կ
     ulResponseTempPubKeyLen����Ӧ����ʱECC��Կ����
     ulAgreementKeyLen��ҪЭ�̵ĻỰ��Կ���ȣ�������64�ֽ�
     pID�� 	         ����ID��������32�ֽ�
     ulIDLen��        ����ID����
     pResponseID��    ��Ӧ��ID��������32�ֽ�
     ulResponseIDLen����Ӧ��ID����
     pAgreementKey��  Э�̳����ĻỰ��Կ
     ����ֵ�� SDKEY_SUCCESS:�ɹ����������������
     */
    unsigned long SDKEY_GenKeyWithECC(IN HANDLE hKey,
                                      IN HANDLE hAgreementHandle,
                                      IN unsigned char *pResponsePubKey,
                                      IN unsigned long ulResponsePubKeyLen,
                                      IN unsigned char *pResponseTempPubKey,
                                      IN unsigned long ulResponseTempPubKeyLen,
                                      IN unsigned long ulAgreementKeyLen,
                                      IN unsigned char *pID, 
                                      IN unsigned long ulIDLen,
                                      IN unsigned char *pResponseID,
                                      IN unsigned long ulResponseIDLen,
                                      OUT unsigned char *pAgreementKey);
    
#ifdef __cplusplus
}
#endif

#endif	 
