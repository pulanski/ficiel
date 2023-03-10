cc_library(
    name = "decompress",
    srcs = glob(["lib/decompress/zstd*.c"]) + [
        "lib/decompress/zstd_decompress_block.h",
        "lib/decompress/zstd_decompress_internal.h",
        "lib/decompress/zstd_ddict.h",
    ],
    hdrs = glob(["lib/decompress/*_impl.h"]),
    strip_include_prefix = "lib/decompress",
    deps = [
        ":common",
        ":legacy",
    ],
)

cc_library(
    name = "deprecated",
    srcs = glob(["lib/deprecated/*.c"]),
    hdrs = glob(["lib/deprecated/*.h"]),
    deps = [":common"],
)

cc_library(
    name = "compress",
    srcs = [
        "lib/compress/hist.c",
        "lib/compress/zstd_compress.c",
        "lib/compress/zstd_double_fast.c",
        "lib/compress/zstd_fast.c",
        "lib/compress/zstd_lazy.c",
        "lib/compress/zstd_ldm.c",
        "lib/compress/zstd_opt.c",
        "lib/compress/zstdmt_compress.c",
    ],
    hdrs = [
        "lib/compress/zstd_compress_internal.h",
        "lib/compress/zstd_double_fast.h",
        "lib/compress/zstd_fast.h",
        "lib/compress/zstd_lazy.h",
        "lib/compress/zstd_ldm.h",
        "lib/compress/zstd_opt.h",
        "lib/compress/zstdmt_compress.h",
    ],
    deps = [":common"],
)

cc_library(
    name = "hist",
    hdrs = ["lib/compress/hist.h"],
    strip_include_prefix = "lib/compress",
)

cc_library(
    name = "threading",
    srcs = ["lib/common/threading.c"],
    hdrs = ["lib/common/threading.h"],
    copts = ["-DZSTD_MULTITHREAD"],
    linkopts = ["-pthread"],
)

cc_library(
    name = "pool",
    srcs = ["lib/common/pool.c"],
    hdrs = ["lib/common/pool.h"],
    deps = [
        ":debug",
        ":threading",
        ":zstd_common",
    ],
)

cc_library(
    name = "xxhash",
    srcs = ["lib/common/xxhash.c"],
    hdrs = [
        "lib/common/xxhash.h",
    ],
    # copts = [
    #     "-DXXH_NAMESPACE=ZSTD_",
    # ],
)

cc_library(
    name = "zstd_header",
    hdrs = ["lib/zstd.h"],
    strip_include_prefix = "lib",
)

cc_library(
    name = "zstd_common",
    srcs = ["lib/common/zstd_common.c"],
    hdrs = [
        "lib/common/zstd_internal.h",
    ],
    deps = [
        ":compiler",
        ":debug",
        ":entropy",
        ":errors",
        ":mem",
        ":zstd_header",
    ],
)

cc_library(
    name = "entropy",
    srcs = [
        "lib/common/entropy_common.c",
        "lib/common/fse_decompress.c",
        "lib/compress/fse_compress.c",
        "lib/compress/huf_compress.c",
        "lib/decompress/huf_decompress.c",
    ],
    hdrs = [
        "lib/common/fse.h",
        "lib/common/huf.h",
    ],
    includes = ["lib/common"],
    deps = [
        ":bitstream",
        ":compiler",
        ":debug",
        ":errors",
        ":hist",
        ":mem",
        ":threading",
        ":xxhash",
    ],
)

cc_library(
    name = "common",
    deps = [
        ":bitstream",
        ":compiler",
        ":cpu",
        ":debug",
        ":entropy",
        ":errors",
        ":mem",
        ":pool",
        ":threading",
        ":xxhash",
        ":zstd_common",
    ],
)

cc_library(
    name = "util",
    hdrs = ["programs/util.h"],
    deps = [
        ":mem",
        ":platform",
    ],
)

cc_library(
    name = "datagen",
    srcs = ["programs/datagen.c"],
    hdrs = ["programs/datagen.h"],
    deps = [
        ":mem",
        ":platform",
    ],
)

cc_library(
    name = "platform",
    hdrs = ["programs/platform.h"],
)

cc_binary(
    name = "zstd",
    srcs = ["programs/zstdcli.c"],
    deps = [":zstd_lib"],
)

# _ZSTD_HEADERS = [
#     "lzma.h",
# ]
#
# _ZSTD_PREFIXED_HEADERS = ["zstd/include/" + hdr for hdr in _ZSTD_HEADERS]

# In order to limit the damage from the `includes` propagation
# via `:zstd`, copy the public headers to a subdirectory and
# expose those.
# genrule(
#     name = "copy_public_headers",
#     srcs = _ZSTD_HEADERS,
#     outs = _ZSTD_PREFIXED_HEADERS,
#     cmd = "cp $(SRCS) $(@D)/zstd/include/",
# )

cc_library(
    name = "zstd_lib",
    srcs = glob(
        ["programs/*.c"],
        exclude = [
            "programs/datagen.c",
            "programs/zstdcli.c",
        ],
    ),
    # Include the un-prefixed headers in srcs to work
    # around the fact that zlib isn't consistent in its
    # choice of <> or "" delimiter when including itself.
    # + _ZSTD_HEADERS,
    hdrs = glob(
        ["programs/*.h"],
        exclude = [
            "programs/datagen.h",
            "programs/platform.h",
            "programs/util.h",
        ],
    ),
    copts = [
        # "-DZSTD_GZCOMPRESS",
        # "-DZSTD_GZDECOMPRESS",
        # "-DZSTD_LZMACOMPRESS",
        # "-DZSTD_LZMADECOMPRES",
        # "-DZSTD_LZ4COMPRESS",
        # "-DZSTD_LZ4DECOMPRES",
    ],
    linkopts = [
        # "-lz",
        # "-llzma",
        # "-llz4",
    ],
    # + _ZSTD_PREFIXED_HEADERS,
    deps = [
        ":datagen",
        ":libzstd",
        ":mem",
        ":util",
        ":xxhash",
        ":zdict",
    ],
    # includes = ["zstd/include/"],
)
