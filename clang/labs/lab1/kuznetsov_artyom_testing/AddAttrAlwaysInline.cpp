#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "llvm/Support/raw_ostream.h"

namespace {
class PrintClassMembersVisitor final
    : public clang::RecursiveASTVisitor<PrintClassMembersVisitor> {
public:
  explicit PrintClassMembersVisitor(clang::ASTContext *context)
      : m_context(context) {}
  bool VisitCXXRecordDecl(clang::CXXRecordDecl *declaration) {
    declaration->dump();
    return true;
  }

private:
  clang::ASTContext *m_context;
};

class PrintClassMembersConsumer final : public clang::ASTConsumer {
public:
  explicit PrintClassMembersConsumer(clang::ASTContext *сontext)
      : m_visitor(сontext) {}

  void HandleTranslationUnit(clang::ASTContext &context) override {
    m_visitor.TraverseDecl(context.getTranslationUnitDecl());
  }

private:
  PrintClassMembersVisitor m_visitor;
};

class PrintClassMembersAction final : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &ci, llvm::StringRef) override {
    return std::make_unique<PrintClassMembersConsumer>(&ci.getASTContext());
  }

  bool ParseArgs(const clang::CompilerInstance &ci,
                 const std::vector<std::string> &args) override {
    return true;
  }
};
} // namespace

static clang::FrontendPluginRegistry::Add<PrintClassMembersAction>
    X("aai_plugin", "Adds the always_inline attribute to functions without conditions");