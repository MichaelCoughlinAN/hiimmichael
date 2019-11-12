/*
 *  ArgumentParsing.cpp
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of libSIVELab library (libsivelab).
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

#include <cassert>
#include "ArgumentParsing.h"

using namespace sivelab;

ArgumentParsing::ArgumentParsing()
  : m_optDesc("Allowed options")
{
};

ArgumentParsing::~ArgumentParsing()
{
}

void ArgumentParsing::reg(const std::string& argName, const std::string &description, ArgTypes t, char shortArgName)
{
  std::ostringstream argName_wShort;

  argName_wShort << argName;
  if (shortArgName)
    argName_wShort << "," << shortArgName;

  if (t == NONE)
    {
      m_optDesc.add_options()
	(argName_wShort.str().c_str(), description.c_str());
    }
  else if (t == INT)
    {
      m_optDesc.add_options()
	(argName_wShort.str().c_str(), po::value<int>(), description.c_str());
    }
  else if (t == FLOAT)
    {
      m_optDesc.add_options()
	(argName_wShort.str().c_str(), po::value<float>(), description.c_str());
    }
  else if (t == CHAR)
    {
      m_optDesc.add_options()
	(argName_wShort.str().c_str(), po::value<char>(), description.c_str());
    }
  else if (t == STRING)
    {
      m_optDesc.add_options()
	(argName_wShort.str().c_str(), po::value<std::string>(), description.c_str());
    }
}

void ArgumentParsing::printUsage() const
{
  std::cout << m_optDesc << std::endl;
}

bool ArgumentParsing::isSet(const std::string& argName)
{
  if (m_varMap.count(argName)) 
    return true;
  else
    return false;
}

bool ArgumentParsing::isSet(const std::string& argName, int &argValue)
{
  if (m_varMap.count(argName)) 
    {
      argValue = m_varMap[argName].as<int>();
      return true;
    }

  return false;
}

bool ArgumentParsing::isSet(const std::string& argName, float &argValue)
{
  if (m_varMap.count(argName)) 
    {
      argValue = m_varMap[argName].as<float>();
      return true;
    }

  return false;
}

bool ArgumentParsing::isSet(const std::string& argName, char &argValue)
{
  if (m_varMap.count(argName)) 
    {
      argValue = m_varMap[argName].as<char>();
      return true;
    }

  return false;
}

bool ArgumentParsing::isSet(const std::string& argName, std::string &argValue)
{
  if (m_varMap.count(argName)) 
    {
      argValue = m_varMap[argName].as<std::string>();
      return true;
    }

  return false;
}

int ArgumentParsing::process(int argc, char *argv[])
{
  po::store(po::parse_command_line(argc, argv, m_optDesc), m_varMap);
  po::notify(m_varMap);    

  return 1;
}

