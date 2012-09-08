//
//  MCCOperationQueue.h
//
//  Created by Thierry Passeron on 08/09/12.
//  Copyright (c) 2012 Monte-Carlo Computing. All rights reserved.
//

/*
 
 MCCOperationQueue
 A simple operation queue with default queue to which you can submit blocks or any other operations (iOS4+ / OSX 10.6+)
 
 Examples:
 =========
 
   Enqueue a block in the default queue:
 
   [MCCOperationQueue enqueueBlock:^{ ... }];
 
 
   Set the default queue max concurrent operations:
 
   [[MCCOperationQueue queue]setMaxConcurrentOperationCount:2];
   [MCCOperationQueue enqueueBlock:^{ ...block1... }];
   [MCCOperationQueue enqueueBlock:^{ ...block2... }];
   [MCCOperationQueue enqueueBlock:^{ ...block3... }];
   // block3 will be be executed when block1 or block2 finishes
 
   Create a custom queue context:
 
   MCCOperationQueue *context = [MCCOperationQueue contextWithQueue:[[[NSOperationQueue alloc]init]autorelease]];
   [context enqueueBlock:^{ ... }];
   // The execution on blocks in the custom queue is independant from the default queue
 
 
 Canceling a queued operation block
 ----------------------------------
 
 You may cancel any NSOperation that gets submitted to an NSOperationQueue but if a block is already running
 there is no straightforward way to check if the ongoing operation has been canceled within the block itself.
 For this you have to use one of the IBlock methods:
 
  + (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block;
  - (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block;
 
 These methods pass the onging operation to the block such that you can do any required introspection 
 on the runnning operation, hence the 'I' (for introspection).
 
 Example:
 
 NSOperation *o = [MCCOperationQueue enqueueIBlock:^(NSOperation *_self){
  while (!_self.isCancelled) { 
    sleep(1);
  }
 }];
 
 [context enqueueBlock:^{
  [o cancel];
  NSLog(@"sleeping operation cancelled");
 }];
 
*/

#import <Foundation/Foundation.h>

@interface MCCOperationQueue : NSObject

+ (NSOperationQueue *)queue;
+ (void)setQueue:(NSOperationQueue *)queue;
+ (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block;
+ (NSOperation *)enqueueBlock:(id)block;

+ (id)contextWithQueue:(NSOperationQueue *)queue;
- (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block;
- (NSOperation *)enqueueBlock:(id)block;

@end
