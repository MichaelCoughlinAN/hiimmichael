/*
 *  handleGraphicsArgs.h
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of libSIVELab (libsivelab).
 *
 * libsivelab is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libsivelab is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libsivelab.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SIVELAB_HANDLE_GRAPHICS_ARGS_H__
#define __SIVELAB_HANDLE_GRAPHICS_ARGS_H__ 1

#include <iostream>
#include <string>

#include "ArgumentParsing.h"
#include "Vector3D.h"

namespace sivelab {

  // Derived from the Argument parsing class so that each can add to
  // this argument list.
  class GraphicsArgs : public ArgumentParsing
  {
  public:
    GraphicsArgs();
    ~GraphicsArgs() {}

    void process(int argc, char *argv[]);

    bool verbose;
    int width;
    int height;
    float aspectRatio;
    bool useShadow;
    Vector3D bgColor;
    
    bool useDepthOfField;
    float depthOfFieldDistance;

    int numCpus;

    int rpp;

    int recursionDepth;
    
    std::string splitMethod;
    
    std::string inputFileName;
    std::string outputFileName;
  };

}

#endif // __HANDLE_ARGS_H__
