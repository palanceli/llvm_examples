//#include "llvm/ADT/STLExtras.h"
//#include "llvm/ExecutionEngine/GenericValue.h"
//#include "llvm/ExecutionEngine/MCJIT.h"
//#include "llvm/ExecutionEngine/Interpreter.h"
//#include "llvm/ExecutionEngine/SectionMemoryManager.h"
//#include "llvm/IR/Verifier.h"
//#include "llvm/IR/Constants.h"
//#include "llvm/IR/DerivedTypes.h"
//#include "llvm/IR/IRBuilder.h"
//#include "llvm/IR/Instructions.h"
//#include "llvm/IR/LLVMContext.h"
//#include "llvm/IR/Module.h"
//#include "llvm/IRReader/IRReader.h"
//#include "llvm/Support/SourceMgr.h"
//#include "llvm/Support/ManagedStatic.h"
//#include "llvm/Support/TargetSelect.h"
//#include "llvm/Support/MemoryBuffer.h"
//#include "llvm/Support/raw_ostream.h"
//#include "llvm/Support/DynamicLibrary.h"
//#include "llvm/Support/Debug.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace llvm;

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//


//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//
namespace {
static std::unique_ptr<DIBuilder> DBuilder;


//===----------------------------------------------------------------------===//
// Code Generation
//===----------------------------------------------------------------------===//

static std::unique_ptr<Module> TheModule;
static std::map<std::string, AllocaInst *> NamedValues;

//===----------------------------------------------------------------------===//
// "Library" functions that can be "extern'd" from user code.
//===----------------------------------------------------------------------===//

#ifdef LLVM_ON_WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

//
//ExecutionEngine* EE = NULL;
//RTDyldMemoryManager* RTDyldMM = NULL;
//
//void initEE(std::unique_ptr<Module> Owner) {
//  std::string ErrStr;
//  if (EE == NULL) {
//    RTDyldMM = (RTDyldMemoryManager*)new SectionMemoryManager();
//    EE = EngineBuilder(std::move(Owner))
//    .setErrorStr(&ErrStr)
//    .setEngineKind(llvm::EngineKind::JIT)
//    .setVerifyModules(true)
//    .setMCJITMemoryManager(std::unique_ptr<llvm::RTDyldMemoryManager>(RTDyldMM))
//    .setOptLevel(llvm::CodeGenOpt::Default)
//    .create();
//
//  } else
//    EE->addModule(std::move(Owner));
//  if (ErrStr.length() != 0)
//    std::cerr << "Create Engine Error" << std::endl << ErrStr << std::endl;
//  EE->finalizeObject();
//}

typedef void (*func_type)(void*);

//// path是bc文件的路径，func_name是要执行的函数名
//void Run(const std::string& path, const std::string& func_name) {
//
//  // 首先要读取要执行的bc字节码
//  SMDiagnostic error;
//  std::unique_ptr<Module> Owner = parseIRFile(path, error, TheContext);
//  if(Owner == nullptr) {
//    std::cout << "Load Error: " << path << std::endl;
//    Owner->dump();
//    return;
//  }
//
//  // 单例的方法进行初始化，暂未考虑多线程
//  initEE(std::move(Owner));
//
//  // 获取编译后的函数指针并执行
//  uint64_t func_addr = EE->getFunctionAddress(func_name.c_str());
//  if (func_addr == 0) {
//    printf("错误, 找不到函数: %s\n", func_name.c_str());
//    return;
//  }
//  func_type func = (func_type) func_addr;
//  func(NULL); // 需要传参数时可以从这里传递
//}
//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

int main2() {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();

  // Add the current debug info version into the module.
  TheModule->addModuleFlag(Module::Warning, "Debug Info Version",
                           DEBUG_METADATA_VERSION);

  // Darwin only supports dwarf2.
  if (Triple(sys::getProcessTriple()).isOSDarwin())
    TheModule->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);
  
//  Run("/Users/palance/Documents/GitHub/test/test/test/main.ll", "testEntry");

  return 0;
}
}
