#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/Interpreter.h>//Otherwise LTO will mess up our binary
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>

using namespace llvm;
using namespace std;

int main() {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();
  
  SMDiagnostic SMD;
  LLVMContext context;
  std::string err;
  const string llPath = "/Users/palance/Documents/GitHub/llvm_examples/Kaleidoscope/BuildingAJIT/ChapterA/test/test/main.ll";
  const string funcName = "testEntry";
  EngineBuilder EB(parseIRFile(llPath, SMD,context));
  EB.setEngineKind(EngineKind::Interpreter);
  EB.setErrorStr(&err);
  ExecutionEngine* EE = EB.create();
  EE->runStaticConstructorsDestructors(false);
  Function* func=EE->FindFunctionNamed(funcName);
  EE->runFunction(func,ArrayRef<GenericValue>());
  
  return 0;
}
