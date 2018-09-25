//
//  main.m
//  test
//
//  Created by palance on 2018/9/18.
//  Copyright © 2018 palance. All rights reserved.
//

#import <Foundation/Foundation.h>

void testEntry(){
  float x = 0;
  for(int i=1; i<1000000; i++){
    if(i % 3 == 0){
      x = x * i;
    }else if(i % 7 == 0){
      x = x / i;
    }else if(i % 11 == 0){
      x = x - i;
    }else{
      x = x + i;
    }
  }

	// NSLog(@"x=%f\n", x);
  NSLog(@"Hello, test entry!");
}

int main(int argc, const char * argv[]) {
  @autoreleasepool {
    double time_begin = CFAbsoluteTimeGetCurrent();
    testEntry();
    double time_end = CFAbsoluteTimeGetCurrent();
    NSInteger time_interval = 1000 * (time_end - time_begin);  //单位毫秒	
    NSLog(@"time_interval: %ld. \n", time_interval);
  }
  return 0;
}
