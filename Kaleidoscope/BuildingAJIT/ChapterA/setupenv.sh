# 生成IR文件
clang -fobjc-arc -emit-llvm -S test/test/main.m -o test/test/main.ll

# 生成机器码
# clang -fobjc-arc -framework Foundation main.m -o main