/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <UIKit/UIKit.h>

#import <React/RCTDefines.h>

extern NSString *const RCTJavaScriptLoaderErrorDomain;

NS_ENUM(NSInteger) {
  RCTJavaScriptLoaderErrorNoScriptURL = 1,
  RCTJavaScriptLoaderErrorFailedOpeningFile = 2,
  RCTJavaScriptLoaderErrorFailedReadingFile = 3,
  RCTJavaScriptLoaderErrorFailedStatingFile = 3,
  RCTJavaScriptLoaderErrorURLLoadFailed = 3,
  RCTJavaScriptLoaderErrorBCVersion = 4,
  RCTJavaScriptLoaderErrorBCNotSupported = 4,

  RCTJavaScriptLoaderErrorCannotBeLoadedSynchronously = 1000,
};

@interface RCTLoadingProgress : NSObject

@property (nonatomic, copy) NSString *status;
@property (strong, nonatomic) NSNumber *done;
@property (strong, nonatomic) NSNumber *total;

@end

@interface RCTSource : NSObject

/**
 * URL of the source object.
 */
@property (strong, nonatomic, readonly) NSURL *url;

/**
 * JS source (or simply the binary header in the case of a RAM bundle).
 */
@property (strong, nonatomic, readonly) NSData *data;

/**
 * Length of the entire JS bundle. Note that self.length != self.data.length in the case of certain bundle formats. For
 * instance, when using RAM bundles:
 *
 *  - self.data will point to the bundle header
 *  - self.data.length is the length of the bundle header, i.e. sizeof(facebook::react::BundleHeader)
 *  - self.length is the length of the entire bundle file (header + contents)
 */
@property (nonatomic, readonly) NSUInteger length;

@end

typedef void (^RCTSourceLoadProgressBlock)(RCTLoadingProgress *progressData);
typedef void (^RCTSourceLoadBlock)(NSError *error, RCTSource *source);

@interface RCTJavaScriptLoader : NSObject

+ (void)loadBundleAtURL:(NSURL *)scriptURL onProgress:(RCTSourceLoadProgressBlock)onProgress onComplete:(RCTSourceLoadBlock)onComplete;

/**
 * @experimental
 * Attempts to synchronously load the script at the given URL. The following two conditions must be met:
 *   1. It must be a file URL.
 *   2. It must not point to a text/javascript file.
 * If the URL does not meet those conditions, this method will return nil and supply an error with the domain
 * RCTJavaScriptLoaderErrorDomain and the code RCTJavaScriptLoaderErrorCannotBeLoadedSynchronously.
 */
+ (NSData *)attemptSynchronousLoadOfBundleAtURL:(NSURL *)scriptURL
                               runtimeBCVersion:(int32_t)runtimeBCVersion
                                   sourceLength:(int64_t *)sourceLength
                                          error:(NSError **)error;

@end