## Description

MCCOperationQueue is a Simple NSOperationQueue with default queuing and context queuing abilities mainely focused on Blocks (iOS4+, OSX 10.6+)

## Usage

### Using the default queue

```objective-c
[MCCOperationQueue enqueueBlock:^{ ... }];
```

### Using a custom queue context

```objective-c
MCCOperationQueue *context = [MCCOperationQueue contextWithQueue:[[[NSOperationQueue alloc]init]autorelease]];
[context enqueueBlock:^{ ... }];
``` 

### Cancellation of executing blocks

You may cancel any NSOperation that gets submitted to an NSOperationQueue but if a block is already running
there is no straightforward way to check if the ongoing operation has been canceled within the block itself.
For this you have to use one of the IBlock methods:

```objective-c
+ (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block;
- (NSOperation *)enqueueIBlock:(void(^)(NSOperation *))block;
``` 
 
These methods pass the onging operation to the block such that you can do any required introspection 
on the runnning operation, hence the 'I' (for introspection).
 
#### Example

```objective-c
NSOperation *o = [MCCOperationQueue enqueueIBlock:^(NSOperation *_self){
 while (!_self.isCancelled) { 
   sleep(1);
 }
}];
 
[context enqueueBlock:^{
 [o cancel];
 NSLog(@"sleeping operation cancelled");
}];
```

## License terms

Copyright (c), 2012 Thierry Passeron

The MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
