/**
 * \file arguments.h
 *
 * \brief Manipulation of test arguments.
 *
 * Much of the code is in host_test.function, to be migrated here later.
 */

/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 */

#ifndef TEST_ARGUMENTS_H
#define TEST_ARGUMENTS_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stdint.h>
#include <stdlib.h>

typedef union {
    size_t len;
    intmax_t sint;
} mbedtls_test_argument_t;

#endif /* TEST_ARGUMENTS_H */
