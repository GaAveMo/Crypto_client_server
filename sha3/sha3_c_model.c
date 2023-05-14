#include "sha3_model.h"

int sha3_dgst_calc(transaction_t* trans) {

    unsigned int  digest_length;
    EVP_MD const * algorithm;
    unsigned int block_size; // in bytes

    if (trans->algo == SHA3_224) {
        algorithm = EVP_sha3_224();
        block_size = 1152/8;

    } else if (trans->algo == SHA3_256) {
        algorithm = EVP_sha3_256();
        block_size = 1088/8;

    } else if (trans->algo == SHA3_384) {
        algorithm = EVP_sha3_384();
        block_size = 832/8;

    } else if (trans->algo == SHA3_512) {
        algorithm = EVP_sha3_512();
        block_size = 576/8; 
    }

    if (trans->finalize == false) {
        if ( (trans->message_bytes % block_size) != 0 ) {
            errno = EINVAL;
            fprintf(stderr, "Error: '%s'"
                    "Only full block messsages are accepted without 'finalize' option\n",
                    strerror(errno));
            return errno;
        }
        errno = EINVAL;
        fprintf(stderr, "Error: '%s'"
                "'finalize == false' is not supported option\n",
                strerror(errno));
        return errno;
    }

    EVP_MD_CTX* mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, algorithm, NULL);
    EVP_DigestUpdate(mdctx, trans->message, trans->message_bytes);

    EVP_DigestFinal_ex(mdctx, trans->result_digest, &digest_length);
    EVP_MD_CTX_destroy(mdctx);

    return 0;
}


int get_digest_length(hash_algo_t algo) {
    if      (algo == SHA3_224) { return SHA224_DIGEST_LENGTH; }
    else if (algo == SHA3_256) { return SHA256_DIGEST_LENGTH; }
    else if (algo == SHA3_384) { return SHA384_DIGEST_LENGTH; }
    else if (algo == SHA3_512) { return SHA512_DIGEST_LENGTH; }

    errno = EINVAL;
    fprintf(stderr, "Error: '%s'"
            "unsupported algorithm requeste. Algo code is '%i'\n",
            strerror(errno), algo);
    return -errno;
}

