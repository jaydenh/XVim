//
//  XVimSourceView.h
//  XVim
//
//  Created by Shuichiro Suzuki on 2/25/12.
//  Copyright (c) 2012 JugglerShu.Net. All rights reserved.
//
#import "XVimTextViewProtocol.h"

/**
 
 XVimSourceView presents an editing interface to XVim for the underlying
 NSTextView object.
 
 All methods in here must depend directly on NSTextView.
 
 If they depend on Xcode functionality (DVTSourceTextView), they should be in
 XVimSourceView+Xcode.
 
 If they depend only on other public functions, they should be in
 XVimSourceView+Vim.
 
 /// INTERFACE DESIGN ROLE ///
  - Do not define(declare) any mothod which takes index(or range) as current insertion point or base point to take an action.
    "index" is maintained as "_insertionPoint" internally so a client of this class never pass such point.
    (You can define a method which takes "index" to be used internally which sould be declared in .m file)
 **/


typedef struct _XVimRange {
    NSUInteger begin; // begin may be greater than end
    NSUInteger end;
} XVimRange;

NS_INLINE XVimRange XVimMakeRange(NSUInteger begin, NSUInteger end) {
    XVimRange r;
    r.begin = begin;
    r.end = end;
    return r;
}

@interface XVimSourceView : NSObject <XVimTextViewProtocol>
@property(readonly) NSString* string;
@property(readonly) NSUInteger insertionPoint;
@property(readonly) NSUInteger insertionColumn;
@property(readonly) NSUInteger insertionPreservedColumn;
@property(readonly) NSUInteger insertionLine;
@property(readonly) NSUInteger selectionBegin;
@property(readonly) NSUInteger preservedColumn;
@property(readonly) VISUAL_MODE selectionMode;
@property(readonly) CURSOR_MODE cursorMode;

- (id)initWithView:(NSTextView*)view;


// Returns the attached view (DO NOT USE IT IN NEWLY CREATED CODE)
- (NSTextView*)view;

- (void)syncStateFromView;

// Selection ( DO NOT USE IN NEWLY CREATED CODE (except in XVimWindow class))
- (NSRange)selectedRange;
- (void)setSelectedRange:(NSRange)range;

// Utility Methods - These method uses XVimTextViewProtocol to perform its role.
- (void)moveForward;
- (void)moveBackward;
- (void)moveToBeginningOfLine;
- (void)moveToEndOfLine;



// NSTextView functions (Do not use following methods)
- (void)copyText;
- (void)deleteText;
- (void)cutText;
- (void)undo;
- (void)redo;
- (void)moveUp;
- (void)moveDown;
- (void)moveForwardAndModifySelection;
- (void)moveBackwardAndModifySelection;
- (void)deleteForward;
- (void)insertText:(NSString*)text;
- (void)insertText:(NSString*)text replacementRange:(NSRange)range;
- (void)insertNewline;


- (NSColor *)insertionPointColor;

// Scrolling
- (void)scrollTo:(NSUInteger)location;
- (void)scroll:(CGFloat)ratio count:(NSUInteger)count;

// Shows the yellow find indicator for given range
- (void)showFindIndicatorForRange:(NSRange)range;

// Drawing
- (NSUInteger)glyphIndexForPoint:(NSPoint)point;
- (NSRect)boundingRectForGlyphIndex:(NSUInteger)glyphIndex;

// Debug
- (void)dumpState;
@end

