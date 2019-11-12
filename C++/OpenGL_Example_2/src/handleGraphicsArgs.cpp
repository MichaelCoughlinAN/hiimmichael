/*
 *  handleGraphicsArgs.cpp
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

#include "handleGraphicsArgs.h"

using namespace sivelab;

GraphicsArgs::GraphicsArgs()
  : verbose(false), width(100), height(100), 
    aspectRatio(1.0), useShadow(true), bgColor(0.0, 0.0, 0.0),
    useDepthOfField(false),
    depthOfFieldDistance(0),
    numCpus(1), rpp(1), 
    recursionDepth(4),
    splitMethod("objectMedian"),
    inputFileName(""), outputFileName("")
{
  reg("help", "help/usage information", ArgumentParsing::NONE, '?');
  reg("verbose", "turn on verbose output", ArgumentParsing::NONE, 'v');
  reg("inputfile", "input file name to use", ArgumentParsing::STRING, 'i');
  reg("outputfile", "output file name to use", ArgumentParsing::STRING, 'o');
  reg("numcpus", "num of cores to use", ArgumentParsing::INT, 'n');
  reg("width", "width of image (default is 100)", ArgumentParsing::INT, 'w');
  reg("height", "height of image (default is 100)", ArgumentParsing::INT, 'h');
  reg("aspect", "aspect ratio in width/height of image (default is 1)", ArgumentParsing::FLOAT, 'a');
  reg("depth", "depth of field focus distance (default is 0.0 or OFF)", ArgumentParsing::FLOAT, 'd');
  reg("rpp", "rays per pixel (default is 1)", ArgumentParsing::INT, 'r');
  reg("recursionDepth", "recursion depth (default is 4)", ArgumentParsing::INT, 'k');
  reg("split", "split method for bvh construction (default is objectMedian)", ArgumentParsing::STRING, 's');
}

void GraphicsArgs::process(int argc, char *argv[])
{
  processCommandLineArgs(argc, argv);

  if (isSet("help"))
    {
      printUsage();
      exit(EXIT_SUCCESS);
    }

  verbose = isSet("verbose");
  if (verbose) std::cout << "Verbose Output: ON" << std::endl;
  
  isSet("width", width);
  if (verbose) std::cout << "Setting width to " << width << std::endl;
  
  isSet("height", height);
  if (verbose) std::cout << "Setting height to " << height << std::endl;

  // recalculate aspect ratio in lieu of aspectRatio being set
  aspectRatio = width / (float)height;  // as in W to H as in 16:9
  
  isSet("aspect", aspectRatio);
  if (verbose) std::cout << "Setting aspect ratio to " << aspectRatio << std::endl;

  if (isSet("depth", depthOfFieldDistance))
    {
      useDepthOfField = true;
      if (verbose) std::cout << "Setting depth of field distance to " << depthOfFieldDistance << std::endl;
    }

  isSet("numcpus", numCpus);
  if (verbose) std::cout << "Setting num cpus to " << numCpus << std::endl;

  isSet("rpp", rpp);
  if (verbose) std::cout << "Setting rays per pixel to " << rpp << std::endl;

  isSet("recursionDepth", recursionDepth);
  if (verbose) std::cout << "Setting recursionDepth to " << recursionDepth << std::endl;
  
  isSet("split", splitMethod);
  if (verbose) std::cout << "Setting split method to " << splitMethod << std::endl;

  isSet("inputfile", inputFileName);
  if (verbose) std::cout << "Setting inputFileName to " << inputFileName << std::endl;

  isSet("outputfile", outputFileName);
  if (verbose) std::cout << "Setting outputFileName to " << outputFileName << std::endl;
}

