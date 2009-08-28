/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef __FUNCTION_HXX__
#define __FUNCTION_HXX__

#include <string>
#include <cstdio>
#include "types.hxx"
#include <map>

#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif
namespace types
{
  class EXTERN_TYPES Function : public InternalType
  {
  public :
    enum ReturnValue
    {
      OK,
      Error
    };

    Function * 	getAsFunction(void);
    RealType getType(void) { return RealFunction; }

    typedef ReturnValue (*GW_FUNC)(typed_list &in, int _iRetCount, typed_list &out); 
    typedef int (*OLDGW_FUNC)(char *fname, int* _piKey);

    void					whoAmI();
    virtual ReturnValue call(typed_list &in, int _iRetCount, typed_list &out);

    Function() {};
    Function(std::string _szName, GW_FUNC _pFunc, std::string _szModule);
    ~Function();
    //private:
 
    static Function *createFunction(std::string _szName, GW_FUNC _pFunc, std::string _szModule);
    static Function *createFunction(std::string _szName, OLDGW_FUNC _pFunc, std::string _szModule);


 public :
    std::string			m_szName;
    GW_FUNC					m_pFunc;
    std::string			m_szModule;
  };

  class WrapFunction : public Function
  {
  public :
    WrapFunction(std::string _szName, OLDGW_FUNC _pFunc, std::string _szModule);
    ReturnValue call(typed_list &in, int _iRetCount, typed_list &out);
  private :
    OLDGW_FUNC m_pOldFunc;
  };

	class EXTERN_TYPES GatewayStruct
	{
	public :
		typed_list* m_pin;
		typed_list* m_pout;
		int*	m_piRetCount;

		GatewayStruct(){};
		~GatewayStruct(){};
	};
}


#endif /* !__FUNCTION_HXX__ */
