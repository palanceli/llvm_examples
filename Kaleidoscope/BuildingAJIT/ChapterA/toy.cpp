#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/Interpreter.h>//Otherwise LTO will mess up our binary
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <sys/time.h>
#include <unistd.h>
#include <dlfcn.h>

using namespace llvm;
using namespace std;

//extern "C" {
//char * __CFConstantStringClassReference = "";
//}

int main(int argc, char ** argv, char **envp) {
  
  void *handle = dlopen("/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation", RTLD_LAZY|RTLD_GLOBAL);
//  void *sym = dlsym(handle, "__CFConstantStringClassReference");
//  printf("__CFConstantStringClassReference: %p\n", sym);
//  for (char **env = envp; *env != 0; env++)
//  {
//    char *thisEnv = *env;
//    printf("%s\n", thisEnv);
//  }
  
  
  char* szDir;
  if((szDir = (char*)getcwd(NULL, 0)) == NULL){
    printf("Failed to get cwd\n");
    return -1;
  }
  printf("current dir is: %s\n", szDir);
  
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
  
  struct timeval tvBegin, tvEnd;
  gettimeofday(&tvBegin, NULL);
  
  EE->runFunction(func,ArrayRef<GenericValue>());
  
  gettimeofday(&tvEnd, NULL);
  //<1>.获得毫秒数:
  double dDuration = 1000 * (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0);
  printf("dDuration=%.2f ms. \n", dDuration);
  
  return 0;
}
