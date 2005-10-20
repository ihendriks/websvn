<?php

// WebSVN - Subversion repository viewing via the web using PHP
// Copyright (C) 2004 Tim Armes
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --
//
// inifile.inc
//
// Read a .ini style file

class IniFile
{
   var $sections;
   
   function readIniFile($name)
   {
      $contents = file($name);
      $cursection = "";
      $first = true;
      
      $this->sections = array();
      
      for ($line = 0; $line < sizeof($contents); $line++)
      {
         $str = trim($contents[$line]);
         if (!empty($str))
         {
            if ($str{0} != "#" && $str{0} != "'") // Ignore comments
            {
               if ($str{0} == '[') // Found a section name heading
               {
                  $cursection = strtolower(substr($str, 1, strlen($str) - 2));
                  $first = true;
               }
               else
               {
                  if ($cursection != "")
                  {
                     if ($first)
                        $this->sections[$cursection] = array();
                     
                     $parts = split("=", $str);
   
                     $this->sections[$cursection][strtolower(trim($parts[0]))] = strtolower(trim($parts[1]));
                     $first = false;
                  }
               }
            }
         }
      }
   }
   
   function getSections()
   {
      return @$this->sections;
   }

   function getValues($section)
   {
      return @$this->sections[strtolower($section)];
   }

   function getValue($section,$key)
   {
      return @$this->sections[strtolower($section)][strtolower($key)];
   }
}   

?>