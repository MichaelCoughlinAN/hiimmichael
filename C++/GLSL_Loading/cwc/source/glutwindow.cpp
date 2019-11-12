//******************************************************************************/
// There are many implementations of glWindow, using glut, SDL, wxWidgets, QT.
//
// This is the FreeGLUT Version.
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glutWindow.h"
#include <iostream>

using namespace cwc;

//-----------------------------------------------------------------------------

std::list<glutWindow*> glutWindow::_gWinInstances;
bool glutWindow::_bLMouseDown;

//-----------------------------------------------------------------------------

glutWindow::glutWindow(void)
{
   _bLMouseDown = false;
   _gWinInstances.push_back(this);
   
   //-------------------------------------------
   // #TODO: Use Parameters to setup this stuff: 
   glutInitWindowSize(640, 480);
   glutInitWindowPosition ( 100, 100 );
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   //--------------------------------------------
   
   _gWindow = glutCreateWindow( "OpenGL Output" );
   _bInit = false;
  
   glutDisplayFunc(sDisplay);
   glutReshapeFunc(sReshape);
   glutMouseFunc(sMouse);
   glutMotionFunc(sMotion);
//#ifdef FREEGLUT
   glutMouseWheelFunc(sMouseWheel);
   glutCloseFunc(sClose);
//#endif   
   glutKeyboardFunc(sKeyDown);
   glutSpecialFunc(sSpecialDown);
   glutKeyboardUpFunc(sKeyUp);
   glutSpecialUpFunc(sSpecialUp);
   glutIdleFunc(sIdle);
   
  
}

//-----------------------------------------------------------------------------

glutWindow::~glutWindow(void)
{
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if (*i == this)
      {
         _gWinInstances.erase(i);
         return;
      }  
      
      i++;   
   }
}

//-----------------------------------------------------------------------------

void glutWindow::sClose(void)
{
   int CurrentWindow = glutGetWindow();
   
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnClose();
         delete (*i);
         return;
      }
      
      i++;
   }
}

//-----------------------------------------------------------------------------

void glutWindow::sReshape(int w, int h)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnResize(w,h);
      }
      
      i++;
   } 
   
}

//-----------------------------------------------------------------------------

void glutWindow::sDisplay(void)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if (!(*i)->_bInit)
      {
         (*i)->OnInit();
         (*i)->_bInit = true;
      }
   
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnRender();
      }
      
      i++;
   }  
}

//-----------------------------------------------------------------------------

void glutWindow::sMouse(int button, int updown, int x, int y)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         if (updown)
         {
            if (button == 0) 
               _bLMouseDown = false;
            (*i)->OnMouseUp(button, x, y);
         }
         else
         {
            if (button == 0) 
               _bLMouseDown = true;
            (*i)->OnMouseDown(button, x, y);   
         }
      }
      
      i++;
   }
}

//-----------------------------------------------------------------------------

void glutWindow::sMotion(int x, int y)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         if (_bLMouseDown)
            (*i)->OnLeftMouseDrag(x, y);
            
         (*i)->OnMouseMove(x, y);   
      }
      
       i++;
   }
}

//-----------------------------------------------------------------------------

void glutWindow::sMouseWheel(int wheel_number, int direction, int x, int y)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnMouseWheel(wheel_number, direction, x, y);
      }
      
      i++;
   }  
}

//-----------------------------------------------------------------------------

void glutWindow::sJoystick( unsigned int a, int b, int c, int d)
{
}

//-----------------------------------------------------------------------------

void glutWindow::sSpecialUp(int key, int x, int y)
{
     int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnKeyUp(key, 0);
      }
      
      i++;
   }  
}

//-----------------------------------------------------------------------------

void glutWindow::sKeyUp(unsigned char key, int x, int y)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnKeyUp(0, key);
      }
      
      i++;
   }  
}

//-----------------------------------------------------------------------------

void glutWindow::sSpecialDown(int key, int x, int y)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnKeyDown(key, 0);
      }
      
      i++;
   }  
}

//-----------------------------------------------------------------------------

void glutWindow::sKeyDown(unsigned char key, int x, int y)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnKeyDown(0, key);
      }
      
      i++;
   } 
}

//-----------------------------------------------------------------------------

void glutWindow::sIdle(void)
{
   int CurrentWindow = glutGetWindow();
   std::list<glutWindow*>::iterator i = _gWinInstances.begin();
   
   while (i!=_gWinInstances.end())
   {
      if ((*i)->_gWindow == CurrentWindow)
      {
         (*i)->OnIdle();
      }
      i++;
   } 
}

//-----------------------------------------------------------------------------

void glutWindow::Repaint()
{
   glutPostWindowRedisplay(_gWindow);
}

//-----------------------------------------------------------------------------

void  glutWindow::SetFullscreen(bool bFullscreen)
{
   if (bFullscreen)
   {
      glutFullScreen();
   }
   else
   {
      int w = 640; //glutGet(GLUT_WINDOW_WIDTH);
      int h = 480; //glutGet(GLUT_WINDOW_HEIGHT);
      int x = 0; //glutGet(GLUT_WINDOW_X);
      int y = 0; //glutGet(GLUT_WINDOW_Y);
      
      glutPositionWindow(x,y);
	  glutReshapeWindow(w,h);
   }
}

//-----------------------------------------------------------------------------
   
void glutWindow::Hide()
{
   glutHideWindow();
}

//-----------------------------------------------------------------------------
   
void glutWindow::Show()
{
   glutShowWindow();
}   

//-----------------------------------------------------------------------------   
   
void  glutWindow::Close()
{
   glutDestroyWindow(_gWindow);
}

//-----------------------------------------------------------------------------