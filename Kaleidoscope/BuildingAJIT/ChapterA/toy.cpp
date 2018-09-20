#include <iostream>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/Interpreter.h>//Otherwise LTO will mess up our binary
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm-c/Core.h>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "KaleidoscopeJIT.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace llvm;
using namespace llvm::orc;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;

ExecutionEngine* EE = NULL;
RTDyldMemoryManager* RTDyldMM = NULL;

typedef void (*func_type)(void*);

// path是bc文件的路径，func_name是要执行的函数名
void Run(const std::string& path, const std::string& func_name) {
  // 首先要读取要执行的bc字节码
  SMDiagnostic error;
  std::unique_ptr<Module> Owner = parseIRFile(path, error, TheContext);
  if(Owner == nullptr) {
    std::cout << "Load Error: " << path << std::endl;
    Owner->dump();
    return;
  }

  // 单例的方法进行初始化，暂未考虑多线程
  std::string ErrStr;
  if (EE == NULL) {
    RTDyldMM = (RTDyldMemoryManager*)new SectionMemoryManager();
    EE = EngineBuilder(std::move(Owner))
    .setErrorStr(&ErrStr)
    .setEngineKind(llvm::EngineKind::JIT)
    .setVerifyModules(true)
    .setMCJITMemoryManager(std::unique_ptr<llvm::RTDyldMemoryManager>(RTDyldMM))
    .setOptLevel(llvm::CodeGenOpt::Default)
    .create();
    
  } else
    EE->addModule(std::move(Owner));
  if (ErrStr.length() != 0)
    std::cerr << "Create Engine Error" << std::endl << ErrStr << std::endl;
  EE->finalizeObject();

  // 获取编译后的函数指针并执行
  uint64_t func_addr = EE->getFunctionAddress(func_name.c_str());
  if (func_addr == 0) {
    printf("错误, 找不到函数: %s\n", func_name.c_str());
    return;
  }
  func_type func = (func_type) func_addr;
  func(NULL); // 需要传参数时可以从这里传递
}

void run2(){
  Run("/Users/palance/Documents/GitHub/llvm_examples/Kaleidoscope/BuildingAJIT/ChapterA/test/test/main.ll", "testEntry");
}

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
  ExecutionEngine* EE=EB.create();
  EE->runStaticConstructorsDestructors(false);
  Function* func=EE->FindFunctionNamed(funcName);
  EE->runFunction(func,ArrayRef<GenericValue>());
  
  return 0;
}
