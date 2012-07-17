//
//  main.c
//  KeyboardCatcher
//
// Thanks, stackoverflow: http://stackoverflow.com/questions/3885896/globally-hiding-cursor-from-background-app
//  Created by Brett Renfer on 6/12/12.
//  Copyright (c) 2012 Rockwell Group. All rights reserved.
//

#include <ApplicationServices/ApplicationServices.h>

static bool controlDown = false;
static bool altDown = false;
static bool commandDown = false;
static bool shiftDown = false;

CGEventRef myCGEventCallback(CGEventTapProxy proxy, CGEventType type,  CGEventRef event, void *refcon) {
    
    
    uint32_t eventType = (uint32_t)type;
    //printf("%u\n", eventType);
    int64_t key = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
//    printf("%lld is key\n", key);
        
    CGEventFlags flags = CGEventGetFlags(event);
    controlDown = (flags & kCGEventFlagMaskControl) == kCGEventFlagMaskControl;
    shiftDown   = (flags & kCGEventFlagMaskShift) == kCGEventFlagMaskShift;
    commandDown = (flags & kCGEventFlagMaskCommand) == kCGEventFlagMaskCommand;
    altDown     = (flags & kCGEventFlagMaskAlternate) == kCGEventFlagMaskAlternate;

    // change spaces
    if ( (controlDown && type == 10) || 
        // fullscreen
        (commandDown && shiftDown && key == 3) || 
        (commandDown && controlDown && key == 3) || 
        // command tabs to other stuff
        (commandDown && key == 48 ) ||
        // command quit
        (commandDown && key == 12 ) ||
        // spotlight
        ( commandDown && key == 49 ) ||      
        // new browser tab
        (commandDown && key == 17 ) ||    
        // close window
        (commandDown && key == 13 ) ||
        // new browser window
        (commandDown && key == 45 ) //||
        // force quit
        //( commandDown && altDown && key == 53)
        ){
        return NULL;
    }
    
    return event; 
}

int main (int argc, const char * argv[]) {
    CFMachPortRef eventTap;  
    CFRunLoopSourceRef runLoopSource;
    
    eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, kCGEventMaskForAllEvents, myCGEventCallback, NULL);
    runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);
    CFRunLoopRun();
    return 0;
}
