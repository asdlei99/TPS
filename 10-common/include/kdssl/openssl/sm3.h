#ifndef HEADER_SM3_ONE_H
# define HEADER_SM3_ONE_H

#include <openssl/opensslconf.h>
#include <openssl/e_os2.h>

#ifdef KD_EXT
#include <stddef.h>

# ifdef  __cplusplus
extern "C" {
# endif

#ifndef SM3_DIGEST_LENGTH
#define SM3_DIGEST_LENGTH       32
#endif /** SM3_DIGEST_LENGTH*/
 
void sm3(const unsigned char *data, size_t datalen, unsigned char digest[SM3_DIGEST_LENGTH]);

# ifdef  __cplusplus
}
# endif
 
#endif /** KD_EXT */

#endif /** HEADER_SM3_ONE_H */

