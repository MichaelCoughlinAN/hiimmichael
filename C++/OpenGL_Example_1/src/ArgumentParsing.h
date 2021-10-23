/*
 *  ArgumentParsing.h
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of libSIVELab library (libsivelab).
 *
 * libSIVELab is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libSIVELab is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libSIVELab.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SIVELAB_ARGUMENT_PARSING_H__
#define __SIVELAB_ARGUMENT_PARSING_H__ 1

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

namespace sivelab
{
  class ArgumentParsing
  {
  public:

    enum ArgTypes
      {
	NONE,
	INT,
	FLOAT,
	CHAR,
	STRING
      };
    
    ArgumentParsing();
    virtual ~ArgumentParsing();

    void reg(const std::string& argName, const std::string &description, ArgTypes t, char shortArgName=0);
    int processCommandLineArgs(int argc, char *argv[]) { return process(argc, argv); }

    bool isSet(const std::string& argName);
    bool isSet(const std::string& argName, int &argValue);
    bool isSet(const std::string& argName, float &argValue);
    bool isSet(const std::string& argName, char &argValue);
    bool isSet(const std::string& argName, std::string &argValue);

    void printUsage() const;

  protected:
    int process(int argc, char *argv[]);
	
  private:

    po::options_description m_optDesc; 
    po::variables_map m_varMap;        
  };
}

#endif // __SIVELAB_ARGUMENT_PARSING_H__ 1
