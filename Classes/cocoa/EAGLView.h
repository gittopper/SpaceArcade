//
//  EAGLView.h
//  SpaceArcade
//
//  Created by Noel on 8/21/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//


#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>

/*
This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
The view content is basically an EAGL surface you render your OpenGL scene into.
Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
*/

struct GamePimpl;

@interface EAGLView : UIView {
    
@private
  
    EAGLContext *context;   
	
    NSTimer *animationTimer;
    BOOL paused;

    struct GamePimpl *gp;
}

@property BOOL paused;

- (void)startAnimation;
- (void)stopAnimation;
- (void)drawView;
- (void)drag:(UIPanGestureRecognizer *)recognizer;
- (void)tap:(UITapGestureRecognizer *)sender;
@end
