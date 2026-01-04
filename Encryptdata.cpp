/*
 * Encryptdata.cpp
 *
 * 	Created on: Dec 22, 2023
 *  Author: Ameya Ranade (ranadeameya@outlook.com)
 */

#include "Encryptdata.h"

Encrypt_data::Encrypt_data() {
	// TODO Auto-generated constructor stub

}

Encrypt_data::~Encrypt_data() {
	// TODO Auto-generated destructor stub
}

int Encrypt_data::encrypt_database(char *passcode, int pass_len, void *data_buf, int buf_len)
{
	char key[32];
	gcry_cipher_hd_t handle;


	/* Initialise GCrypt */
	initialise_gcrypt();


	/* Derive key from pass phrase */
	gpg_error_t err = derive_key((const void *)passcode, pass_len, (void *)key, 32);
	if(err != 0)
	{
		error_info(err);
	}
	else
	{
//		printf("derived key ");
//		for(int idx = 0; idx < 32; idx ++)
//		{
//			printf("%02X", (unsigned char)key[idx]);
//		}

	}

    err = gcry_cipher_open(&handle, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_ECB, 0);
     if(err){
    	 error_info(err);
         printf("Error in cipheropen\n");
         exit(1);
     }

     err = gcry_cipher_setkey(handle, key, 32);
     if(err){
    	 error_info(err);
         printf("Error in setkey\n");
         exit(1);
     }

     int *header = (int *)data_buf;
     *header = DATA_HEADER;
//	 printf("\nencrypt_database intext %s \n", (char *)data_buf);
//
//	 printf("\n");
//
//	 for(int idx = 0; idx < 32; idx ++)
//	 {
//		printf("%02X", ((unsigned char *)data_buf)[idx]);
//	 }

     err = gcry_cipher_encrypt(handle, data_buf, buf_len, 0, 0);
     if(err){
    	 error_info(err);
         printf("Error in encrypt\n");
         exit(1);
     }
     else
     {

//		printf("\nencrypt_database outbytes");
//		for(int idx = 0; idx < 32; idx ++)
//		{
//			printf("%02X", ((unsigned char *)data_buf)[idx]);
//		}
//
//		printf("\n");
     }

     gcry_cipher_close(handle);

     return err;
}

int Encrypt_data::decrypt_database(char *passcode, int pass_len,
									void *in_buf, int buf_len)
{
	char key[32];
	gcry_cipher_hd_t handle;

	/* Initialise GCrypt */
	initialise_gcrypt();

	/* Derive key from pass phrase */
	gpg_error_t err = derive_key((const void *)passcode, pass_len, (void *)key, 32);
	if(err != 0)
	{
		error_info(err);
	}
	else
	{
//		printf("derived key ");
//		for(int idx = 0; idx < 32; idx ++)
//		{
//			printf("%02X", (unsigned char)key[idx]);
//		}

	}

    err = gcry_cipher_open(&handle, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_ECB, 0);
     if(err){
    	 error_info(err);
         printf("Error in cipheropen\n");
         exit(1);
     }

     err = gcry_cipher_setkey(handle, key, 32);
     if(err){
    	 error_info(err);
         printf("Error in setkey\n");
         exit(1);
     }

// 	printf("\n decrypt_database in bytes \n");
// 	for(int idx = 0; idx < 32; idx ++)
// 	{
// 		printf("%02X", ((unsigned char *)in_buf)[idx]);
// 	}
//
// 	printf("\n");

     err = gcry_cipher_decrypt(handle, in_buf, buf_len, 0, 0);
     if(err){
    	 error_info(err);
         printf("Error in decrypt\n");
         exit(1);
     }
     else
     {

//		printf("\n decrypt_database outdata \n");
//
//			printf("%02X %02X %02X %02X %02X %02X \n", ((unsigned char *)in_buf)[0],
//														((unsigned char *)in_buf)[1],
//														((unsigned char *)in_buf)[2],
//														((unsigned char *)in_buf)[3],
//														((unsigned char *)in_buf)[4],
//														((unsigned char *)in_buf)[5]);

    	 int *header = (int *)in_buf;

    	 if(*header != DATA_HEADER)
    	 {
    		 printf("******** Wrong password !********** \n");
    		 err = GPG_ERR_USER_1;
    	 }

     }

     gcry_cipher_close(handle);

     return err;
}

void Encrypt_data::initialise_gcrypt()
{
	/* Version check should be the very first call because it
	            makes sure that important subsystems are intialized. */
//	printf("%s\n",gcry_check_version (NULL));
//	if (!gcry_check_version (GCRYPT_VERSION))
	if (!gcry_check_version ("1.8.8"))
	{
		fputs ("libgcrypt version mismatch\n", stderr);
		exit (2);
	}

	/* Disable secure memory. */
	gcry_control (GCRYCTL_DISABLE_SECMEM, 0);
	/* ... If required, other initialization goes here.
	 */
	/* Tell Libgcrypt that initialization has completed. */
	gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
}

void Encrypt_data::error_info(gpg_error_t err)
{
	gcry_err_code_t errcode = gcry_err_code(err);
	printf("Error code returned %d\n", errcode);
	gcry_err_source_t errsrc = gcry_err_source(err);
	printf("Error source returned %d\n", errsrc);
}

gpg_error_t Encrypt_data::derive_key(const void *passphrase, size_t pass_len,
		void *keybuffer, int keylen)
{
	gpg_error_t err;
	char* salt = "CNT5410";

	err = gcry_kdf_derive(passphrase, pass_len,
			GCRY_KDF_PBKDF2, GCRY_MD_SHA3_256,
			salt, 7, 3, keylen, keybuffer);
	return err;
}
