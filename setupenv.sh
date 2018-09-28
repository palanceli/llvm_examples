# 修改${LLVM_DIR}/examples/Kaleidoscope/BuildingAJIT/CMakeLists.txt，添加ChapterA:
# add_subdirectory(ChapterA)

LLVM_DIR="$HOME/Documents/GitHub/llvm"
LLVM_EXAMPLES_DIR="$HOME/Documents/GitHub/llvm_examples"

ln -s ${LLVM_EXAMPLES_DIR}/Kaleidoscope/BuildingAJIT/ChapterA ${LLVM_DIR}/examples/Kaleidoscope/BuildingAJIT/ChapterA

# # 修改${LLVM_DIR}/tools/clang/examples/CMakeLists.txt，添加FindClassDecls:
# add_subdirectory(FindClassDecls)
ln -s ${LLVM_EXAMPLES_DIR}/FindClassDecls ${LLVM_DIR}/tools/clang/examples/FindClassDecls
