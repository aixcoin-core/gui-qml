// Copyright (c) 2023 Aixcoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "logprintf.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class AixcoinModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<aixcoin::LogPrintfCheck>("aixcoin-unterminated-logprintf");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<AixcoinModule>
    X("aixcoin-module", "Adds aixcoin checks.");

volatile int AixcoinModuleAnchorSource = 0;
