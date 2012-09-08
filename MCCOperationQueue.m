//
//  MCCOperationQueue.m
//
//  Created by Thierry Passeron on 08/09/12.
//  Copyright (c) 2012 Monte-Carlo Computing. All rights reserved.
//

#import "MCCOperationQueue.h"

@interface MCCOperationQueue ()
@property (retain, nonatomic) NSOperationQueue *contextQueue;
@end

@implementation MCCOperationQueue
@synthesize contextQueue;

- (void)dealloc {
  self.contextQueue = nil;
  [super dealloc];
}

static NSOperationQueue * _queue = nil;
+ (NSOperationQueue *)queue {
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    if (!_queue) _queue = [[NSOperationQueue alloc]init];
  });
  return _queue;
}

+ (void)setQueue:(NSOperationQueue *)queue {
  if (queue == _queue) return;
  if (_queue) [_queue autorelease];
  _queue = queue;
  [_queue retain];
}

+ (NSOperation *)enqueueBlock:(id)block {
  NSOperation *operation = [NSBlockOperation blockOperationWithBlock:block];
  [[self queue]addOperation:operation];
  return operation;
}

+ (id)contextWithQueue:(NSOperationQueue *)queue {
  MCCOperationQueue *oq = [[MCCOperationQueue alloc]init];
  oq.contextQueue = queue;
  return [oq autorelease];
}

- (NSOperation *)enqueueBlock:(id)block {
  NSAssert(contextQueue, @"no context queue");
  NSOperation *operation = [NSBlockOperation blockOperationWithBlock:block];
  [contextQueue addOperation:operation];
  return operation;
}


#pragma mark enqueue blocks with introspection

+ (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block {
  __block NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{}];
  [operation addExecutionBlock:^{ block(operation); }];
  [[self queue]addOperation:operation];
  return operation;
}

- (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block {
  __block NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{}];
  [operation addExecutionBlock:^{ block(operation); }];
  [contextQueue addOperation:operation];
  return operation;
}

@end
