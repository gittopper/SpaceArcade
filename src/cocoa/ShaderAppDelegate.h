//
//  SpaceArcadeAppDelegate.h
//  SpaceArcade
//
//  Created by Noel on 8/21/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@class EAGLView;

@interface ShaderAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    EAGLView *glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;
- (IBAction)drag:(UIPanGestureRecognizer *)sender;
- (IBAction)tap:(UITapGestureRecognizer *)sender;

@end

