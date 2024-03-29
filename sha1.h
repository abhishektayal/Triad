/*      $OpenBSD: sha1.h,v 1.5 2007/09/10 22:19:42 henric Exp $ */

/*
 * SHA-1 in C
 * By Steve Reid <steve@edmweb.com>
 * 100% Public Domain
 */

#ifndef _SHA1_H_
#define _SHA1_H_

/* csci551 fa2011 change begin */
#include <stdint.h>
/*
 * This source is openbsd which likes u_int32_t;
 * POSIX says uint32_t. 
 * Fix that.
 */
#define u_int32_t uint32_t
#define u_int64_t uint64_t
unsigned int projb_hash(unsigned char *buffer, int buffer_length);
/* csci551 fa2011 change end */

#define SHA1_BLOCK_LENGTH               64
#define SHA1_DIGEST_LENGTH              20

typedef struct {
        u_int32_t       state[5];
        u_int64_t       count;
        unsigned char   buffer[SHA1_BLOCK_LENGTH];
} SHA1_CTX;
  
void SHA1Init(SHA1_CTX * context);
void SHA1Transform(u_int32_t state[5], const unsigned char buffer[SHA1_BLOCK_LENGTH]);
void SHA1Update(SHA1_CTX *context, const unsigned char *data, unsigned int len);
void SHA1Final(unsigned char digest[SHA1_DIGEST_LENGTH], SHA1_CTX *context);

#endif /* _SHA1_H_ */
