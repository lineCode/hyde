/*
Copyright 2018 Adobe
All Rights Reserved.

NOTICE: Adobe permits you to use, modify, and distribute this file in
accordance with the terms of the Adobe license agreement accompanying
it. If you have received this file from a source other than Adobe,
then your use, modification, or distribution of it requires the prior
written permission of Adobe. 
*/

#pragma once

// clang
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

// application
#include "json.hpp"

using namespace clang;
using namespace clang::ast_matchers;

/**************************************************************************************************/

namespace hyde {

/**************************************************************************************************/

class FunctionInfo : public MatchFinder::MatchCallback {
public:
    FunctionInfo(std::vector<std::string> paths) : _paths(std::move(paths)) {
        _j["functions"] = json::object();
    }

    void run(const MatchFinder::MatchResult& Result) override;

    json getJSON() { return _j; }

    static DeclarationMatcher GetMatcher() { return functionDecl().bind("func"); }

private:
    std::vector<std::string> _paths;
    json _j;
};

/**************************************************************************************************/

} // namespace hyde

/**************************************************************************************************/
