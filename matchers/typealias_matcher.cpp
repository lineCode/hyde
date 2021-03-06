/*
Copyright 2018 Adobe
All Rights Reserved.

NOTICE: Adobe permits you to use, modify, and distribute this file in
accordance with the terms of the Adobe license agreement accompanying
it. If you have received this file from a source other than Adobe,
then your use, modification, or distribution of it requires the prior
written permission of Adobe. 
*/

// identity
#include "typealias_matcher.hpp"

// stdc++
#include <iostream>

// clang
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

// application
#include "json.hpp"
#include "matchers/utilities.hpp"

using namespace clang;
using namespace clang::ast_matchers;

/**************************************************************************************************/

namespace hyde {

/**************************************************************************************************/

void TypeAliasInfo::run(const MatchFinder::MatchResult& Result) {
    auto node = Result.Nodes.getNodeAs<TypeAliasDecl>("typealias");

    if (!PathCheck(_paths, node, Result.Context)) return;

    json info = StandardDeclInfo(Result.Context, node);

    // do not process class type aliases here.
    if (!info["parents"].empty()) return;

    info["type"] = node->getUnderlyingType().getAsString();

    if (auto template_decl = node->getDescribedAliasTemplate()) {
        info["template_parameters"] = GetTemplateParameters(template_decl);
    }

    _j["typealiases"].push_back(std::move(info));
}

/**************************************************************************************************/

} // namespace hyde

/**************************************************************************************************/
