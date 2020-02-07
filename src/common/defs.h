// Copyright (c) 2019-2020 The Bigbang developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BIGBANG_DEFS_H
#define BIGBANG_DEFS_H

//hard fork: change of hash algorithm and its input, and update of template address of multiple signature
static const unsigned int HEIGHT_HASH_MULTI_SIGNER_MAINNET = 78256;
static const unsigned int HEIGHT_HASH_MULTI_SIGNER_TESTNET = 20;
extern unsigned int HEIGHT_HASH_MULTI_SIGNER;

// hard fork: change of hash algorithm and its input, and pow adjust.
static const unsigned int HEIGHT_HASH_POW_ADJUST_MAINNET = 178256;
static const unsigned int HEIGHT_HASH_POW_ADJUST_TESTNET = 40;
extern unsigned int HEIGHT_HASH_POW_ADJUST;

#endif //BIGBANG_DEFS_H
