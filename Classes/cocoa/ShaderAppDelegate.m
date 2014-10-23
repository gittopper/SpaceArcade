//
//  SpaceArcadeAppDelegate.m
//  SpaceArcade
//
//  Created by Noel on 8/21/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "ShaderAppDelegate.h"
#import "EAGLView.h"

@implementation ShaderAppDelegate

@synthesize window;
@synthesize glView;

- (void)applicationDidFinishLaunching:(UIApplication *)application {
    
	glView.paused = NO;
	[glView startAnimation];
}


- (void)applicationWillResignActive:(UIApplication *)application {
    glView.paused = YES;
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    glView.paused = NO;
}


- (void)dealloc {
	[window release];
	[glView release];
	[super dealloc];
}
- (IBAction)drag:(UIPanGestureRecognizer*)recognizer {
    [glView drag:recognizer];
}

- (IBAction)tap:(UITapGestureRecognizer *)sender {
    [glView tap:sender];
}

@end
