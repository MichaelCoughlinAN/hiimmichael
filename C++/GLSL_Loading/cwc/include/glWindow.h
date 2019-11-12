//*****************************************************************************
// Window Interface
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/

#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <list>

namespace cwc
{
   //! \ingroup app
   class glWindow
   {
   public:
      glWindow(void);
      virtual ~glWindow(void);
      
      // Events:
      
      //! Called on idle. This should never be used to draw anything.
      virtual void OnIdle(void) = 0;
      
      //! Called when window requires paint
      virtual void OnRender(void) = 0;
      
      //! Called when Window is resized
      virtual void OnResize(int nWidth, int nHeight) = 0;
      
      //! Called when Window is created
      virtual void OnInit(void) = 0;
      
      //! Called when Window is closed.
      virtual void OnClose(void) = 0;
      
      //! Called when Mouse button is pressed
      virtual void OnMouseDown(int button, int x, int y) = 0;
      
      //! Called when Mouse button is released
      virtual void OnMouseUp(int button, int x, int y) = 0;
      
      //! Called when Mouse is moved (without pressing any button)
      virtual void OnMouseMove(int x, int y) = 0;
      
      //! Called while Left Mouse button is pressed.
      virtual void OnLeftMouseDrag(int x, int y) = 0;
      
      //! Called when mouse wheel is used
      virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) = 0;
      
      //! Called when a key is pressed on keyboard
      virtual void OnKeyDown(int nKey, char cAscii) = 0;
      
      //! Called when a key is released on keyboard
      virtual void OnKeyUp(int nKey, char cAscii) = 0;
      
      // Commands:
      
      //! Force Repaint
      virtual void Repaint() = 0;
      
      //! Switch window to fullscreen (true) or windowed mode (false).
      virtual void SetFullscreen(bool bFullscreen) = 0;
      
      //! Hide the window
      virtual void Hide() = 0;;
      
      //! Show the window
      virtual void Show() = 0;;
     
      //! Close the window
      virtual void  Close()= 0; // Close Window
       
      //! Attach a LUA Script for event handling. (Not all events must be covered by this script)
      bool AttachScript(char* filename, bool nShowCompileErrors=true);

   protected:
      bool  _bScriptAttached;
   };   
}

#endif
