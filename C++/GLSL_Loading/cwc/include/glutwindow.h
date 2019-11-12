//*****************************************************************************
// Window (GLUT Implementation)
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/


#ifndef GL_GLUTWINDOW_H
#define GL_GLUTWINDOW_H

#include <list>
#include "glWindow.h"

namespace cwc
{
   //! \ingroup app
   class glutWindow : public glWindow
   {
   public:
      glutWindow(void);
      virtual ~glutWindow(void);
      
      // Events:
      
      //! Called on idle. This should never be used to draw anything.
      virtual void OnIdle(void){};
      
      //! Called when window requires paint
      virtual void OnRender(void){};
      
      //! Called when Window is resized
      virtual void OnResize(int nWidth, int nHeight){};
      
      //! Called when Window is created
      virtual void OnInit(void){};
      
      //! Called when Window is closed.
      virtual void OnClose(void){};
      
      //! Called when Mouse button is pressed
      virtual void OnMouseDown(int button, int x, int y){}; 
      
      //! Called when Mouse button is released
      virtual void OnMouseUp(int button, int x, int y){}; 
      
      //! Called when Mouse is moved (without pressing any button)
      virtual void OnMouseMove(int x, int y){};
      
      //! Called while Left Mouse button is pressed.
      virtual void OnLeftMouseDrag(int x, int y){};
      
      //! Called when mouse wheel is used
      virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){};
      
      //! Called when a key is pressed on keyboard
      virtual void OnKeyDown(int nKey, char cAscii){};
      
      //! Called when a key is released on keyboard
      virtual void OnKeyUp(int nKey, char cAscii){}; 
      
      // Commands:
      
      //! Force Repaint
      virtual void Repaint();
      
      //! Sets window to fullscreen or windowed mode.
      virtual void  SetFullscreen(bool bFullscreen);
      
      //! Hide the window
      virtual void Hide();
      
      //! Show the window
      virtual void Show();
     
      //! Close the window
      virtual void  Close(); // Close Window
       
   protected:   
      static std::list<glutWindow*> _gWinInstances;
      int _gWindow;  // Window Number

   private:
      bool _bInit;
      static bool _bLMouseDown;
      
      // Glut Related:
      static void sClose(void);
      static void sReshape(int w, int h);
      static void sDisplay(void);
      static void sMouse(int button, int updown, int x, int y);
      static void sMouseWheel(int wheel_number, int direction, int x, int y);
      static void sMotion(int x, int y);
      static void sJoystick( unsigned int buttonMask, int x, int y, int z); // GLUT_JOYSTICK_BUTTON_A
      static void sSpecialUp(int key, int x, int y);
      static void sKeyUp(unsigned char key, int x, int y);
      static void sSpecialDown(int key, int x, int y);
      static void sKeyDown(unsigned char key, int x, int y);
      static void sIdle(void);
   };   
}

#endif
