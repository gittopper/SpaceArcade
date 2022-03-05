#include "spacegame.h"

#import "EAGLView.h"
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#include <OpenGLES/ES2/gl.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "fileresourceloader.h"

using namespace Game;

struct GamePimpl
{
    GamePimpl()
    {
        game = new SpaceGame;
    }
    ~GamePimpl()
    {
        delete game;
    }
    SpaceGame* game;
};


// A class extension to declare private methods
@interface EAGLView ()

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) NSTimer *animationTimer;

- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;

@end


@implementation EAGLView

@synthesize context;
@synthesize animationTimer;
@synthesize paused;

// You must implement this method
+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (id)initWithCoder:(NSCoder*)coder {
    
    if ((self = [super initWithCoder:coder])) {
        gp = new GamePimpl;
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
		// Make sure this is the right version!
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (!context || ![EAGLContext setCurrentContext:context]) {
            [self release];
            return nil;
        }
        
        NSString* pathStr = [NSString stringWithFormat:@"%@/", [[NSBundle mainBundle] resourcePath]];
        const char* resPath = [pathStr cStringUsingEncoding:NSASCIIStringEncoding];
        
        ResourceLoader* loader = new FileResourceLoader;
        loader->setResourcesPath(resPath);
        
        const bool ok = gp->game->getRenderer()->initRenderer(loader);
		assert(ok);
		
    }
    return self;
}


- (void)drawView 
{
    
    [EAGLContext setCurrentContext:context];
    gp->game->renderStep();
    [context presentRenderbuffer:GL_RENDERBUFFER_OES];
}


- (void)layoutSubviews {
    [EAGLContext setCurrentContext:context];
    [self destroyFramebuffer];
    [self createFramebuffer];
    [self drawView];
}


- (BOOL)createFramebuffer {
    
    gp->game->getRenderer()->createFramebuffer();
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    if(!gp->game->getRenderer()->updateInfoAboutWindow()) {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    gp->game->setupGame();
    
    return YES;
}


- (void)destroyFramebuffer {
    gp->game->getRenderer()->destroyFramebuffer();
}


- (void)startAnimation {
    self.animationTimer = [NSTimer scheduledTimerWithTimeInterval:gp->game->getAnimationInterval() target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}


- (void)stopAnimation {
    self.animationTimer = nil;
}


- (void)setAnimationTimer:(NSTimer *)newTimer {
    [animationTimer invalidate];
    animationTimer = newTimer;
}


- (void)paused:(BOOL)p {
    
    if (p)
    {
        gp->game->pause();
        [self stopAnimation];
    }
    else
    {
        gp->game->resume();
        if (animationTimer)
        {
            [self startAnimation];
        }
    }
}


- (void)dealloc {
    
    [self stopAnimation];
    
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    delete gp;
    [context release];  
    [super dealloc];
}

- (void)drag:(UIPanGestureRecognizer *)recognizer {
    CGPoint translation = [recognizer velocityInView:self.viewForBaselineLayout];
    gp->game->drag(translation.x, translation.y);
    
}
- (void)tap:(UITapGestureRecognizer *)sender {
    CGPoint translation = [sender locationInView:self.viewForBaselineLayout];
    gp->game->tap(translation.x, translation.y);
}

@end
