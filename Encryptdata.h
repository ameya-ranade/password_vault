/*
 * Encryptdata.h
 *
 *  Created on: Dec 28, 2023
 *  Author: Ameya Ranade  (ranadeameya@outlook.com)
 */

#ifndef ENCRYPTDATA_H_
#define ENCRYPTDATA_H_

#include <gcrypt.h>

#define DATA_HEADER			0x7A795A59

class Encrypt_data {
public:
	Encrypt_data();
	virtual ~Encrypt_data();

	int encrypt_database(char *passcode, int pass_len, void *data_buf, int buf_len);
	int decrypt_database(char *passcode, int pass_len, void *data_buf, int buf_len);
	void initialise_gcrypt();
	void error_info(gpg_error_t err);

	gpg_error_t derive_key(const void *passphrase, size_t pass_len,
			void *keybuffer, int keylen);
};

#endif /* ENCRYPTDATA_H_ */
