#ifndef MIF_COMPRESS_H
#define MIF_COMPRESS_H
#include <stdint.h>
#include <mif/type/blob.h>

int mif_compress(MifBlob data, MifBlob* out);

int mif_uncompress(MifBlob data, MifBlob* out);
#endif
