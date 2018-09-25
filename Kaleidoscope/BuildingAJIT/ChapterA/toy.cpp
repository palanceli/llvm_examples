#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/Interpreter.h>//Otherwise LTO will mess up our binary
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <sys/time.h>
#include <unistd.h>

using namespace llvm;
using namespace std;

int main() {
  char* szDir;
  if((szDir = (char*)getcwd(NULL, 0)) == NULL){
    printf("Failed to get cwd\n");
    return -1;
  }
  printf("current dir is: %s\n", szDir);
  
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();
  printf("--- 0\n");
  
  SMDiagnostic SMD;
  LLVMContext context;
  std::string err;
  const string llPath = "/Users/palance/Documents/GitHub/llvm_examples/Kaleidoscope/BuildingAJIT/ChapterA/test/test/main.ll";
  const string funcName = "testEntry";
  EngineBuilder EB(parseIRFile(llPath, SMD,context));
  printf("--- 1\n");
  EB.setEngineKind(EngineKind::Interpreter);
  printf("--- 2\n");
  EB.setErrorStr(&err);
  printf("--- 3\n");
  ExecutionEngine* EE = EB.create();
  printf("--- 4\n");
  
  EE->runStaticConstructorsDestructors(false);
  Function* func=EE->FindFunctionNamed(funcName);
  
  struct timeval tvBegin, tvEnd;
  gettimeofday(&tvBegin, NULL);
  
  EE->runFunction(func,ArrayRef<GenericValue>());
  
  gettimeofday(&tvEnd, NULL);
  //<1>.获得毫秒数:
  double dDuration = 1000 * (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0);
  printf("dDuration=%.2f ms. \n", dDuration);
  
  return 0;
}
