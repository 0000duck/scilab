/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2014-2015 - Scilab Enterprises - Calixte DENIZET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

// This file has been generated, so don't modify it by hand !!

#include "checkers/Checkers.hxx"

namespace analysis
{
    TIType Checkers::check_imag(GVN & gvn, const TIType & in0)
    {
        switch (in0.type)
        {
        case TIType::COMPLEX :
        {
            return TIType(gvn, TIType::DOUBLE, in0.rows, in0.cols);
        }
        case TIType::DOUBLE :
        {
            return in0;
        }
        default :
            return TIType(gvn);
        }
    }

} // namespace analysis