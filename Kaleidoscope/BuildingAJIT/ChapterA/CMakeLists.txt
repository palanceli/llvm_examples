set(LLVM_LINK_COMPONENTS
  Analysis
  Core
  ExecutionEngine
  InstCombine
  Interpreter
  MC
  IRReader
  Object
  RuntimeDyld
  ScalarOpts
  Support
  native
  )

add_kaleidoscope_chapter(BuildingAJIT-ChA
  toy.cpp
  toy2.cpp
  )

if(LLVM_COMPILER_IS_GCC_COMPATIBLE)
  target_compile_options(BuildingAJIT-ChA PRIVATE
    -Wno-unused-private-field
    )
endif()
