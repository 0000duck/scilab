/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2015 - Scilab Enterprises - Calixte DENIZET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef __COVER_MACRO_INFO_HXX__
#define __COVER_MACRO_INFO_HXX__

#include <iostream>
#include <string>
#include <cinttypes>

namespace coverage
{

struct CoverMacroInfo
{
    const std::wstring macroModule;
    const std::wstring macroFilePath;
    const uint64_t instrsCount;
    const uint64_t branchesCount;
    const uint64_t pathsCount;

    CoverMacroInfo(const std::wstring & _macroModule, const std::wstring & _macroFilePath, const uint64_t _instrsCount, const uint64_t _branchesCount, const uint64_t _pathsCount) : macroModule(_macroModule), macroFilePath(_macroFilePath), instrsCount(_instrsCount), branchesCount(_branchesCount), pathsCount(_pathsCount) { }

    friend std::wostream & operator<<(std::wostream & out, const CoverMacroInfo & cmi)
    {
        out << L"instrs: " << cmi.instrsCount << L" branches: " << cmi.branchesCount << L" paths: " << cmi.pathsCount;
        return out;
    }

    void toBin(std::fstream & out) const;
    static CoverMacroInfo fromBin(std::fstream & in);
};

} // namespace coverage

#endif // __COVER_MACRO_INFO_HXX__