/* Copyright (c) 2006-2007 Christopher J. W. Lloyd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef _NSTHREAD_H_
#define _NSTHREAD_H_

#import <Foundation/NSException.h>
#import <Foundation/NSDate.h>

@class NSDictionary, NSMutableDictionary, NSAutoreleasePool, NSLock, NSRunLoop;

FOUNDATION_EXPORT NSString * const NSDidBecomeSingleThreadedNotification;
FOUNDATION_EXPORT NSString * const NSWillBecomeMultiThreadedNotification;
FOUNDATION_EXPORT NSString * const NSThreadWillExitNotification;

FOUNDATION_EXPORT_CLASS
@interface NSThread : NSObject {
@public
    NSObject *_target;
    bool          _retainTarget;
    SEL           _selector;
    NSObject *_object;
    double        _priority;
    NSUInteger    _stackSize;
    BOOL           _cancelled;
    NSRunLoop *_runLoop;
    BOOL           _isFinished;
    idretain _threadDictionary;
    idretain _name;
}

+(BOOL)isMultiThreaded;
+(BOOL)isMainThread;

+(NSThread *)mainThread;

+(void)detachNewThreadSelector:(SEL)selector toTarget:target
   withObject:argument;

+(NSThread *)currentThread;
+(NSArray *)callStackReturnAddresses;
+(double)threadPriority;
+(void)setThreadPriority:(double)value;

+(void)sleepUntilDate:(NSDate *)date;
+(void)sleepForTimeInterval:(NSTimeInterval)value;

+(void)exit;

-init;
-initWithTarget:target selector:(SEL)selector object:argument;

-(BOOL)isMainThread;
-(BOOL)isCancelled;
-(BOOL)isExecuting;
-(BOOL)isFinished;

-(void)start;
-(void)cancel;
-(void)main;

-(NSString *)name;
-(NSUInteger)stackSize;

-(NSMutableDictionary *)threadDictionary;

-(void)setName:(NSString *)value;
-(void)setStackSize:(NSUInteger)value;
+(NSArray *)callStackSymbols;

// private
-(NSMutableDictionary *)sharedDictionary;
-(void)setSharedObject:object forClassName:(NSString *)className;

@end

@interface NSObject (NSThreadPerformAdditions)
-(void)performSelector:(SEL)selector onThread:(NSThread *)thread withObject:(id)object waitUntilDone:(BOOL)waitUntilDone modes:(NSArray *)modes;
-(void)performSelector:(SEL)selector onThread:(NSThread *)thread withObject:(id)object waitUntilDone:(BOOL)waitUntilDone;
-(void)performSelectorOnMainThread:(SEL)selector withObject:object waitUntilDone:(BOOL)waitUntilDone modes:(NSArray *)modes;
-(void)performSelectorOnMainThread:(SEL)selector withObject:object waitUntilDone:(BOOL)waitUntilDone;
-(void)performSelectorInBackground:(SEL)selector withObject:object;
@end

// PRIVATE
FOUNDATION_EXPORT NSThread *NSCurrentThread(void);
FOUNDATION_EXPORT id NSThreadSharedInstance(NSString *className);
FOUNDATION_EXPORT id NSThreadSharedInstanceDoNotCreate(NSString *className);

#endif /* _NSTHREAD_H_ */