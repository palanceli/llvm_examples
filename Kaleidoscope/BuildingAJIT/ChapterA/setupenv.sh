# 生成IR文件
clang -fobjc-arc -emit-llvm -S test/test/main.m -o test/test/main.ll