c			======================================
c     Copyright INRIA
c			======================================
      subroutine intludel(id)
      include '../stack.h'
      integer id(nsiz),top0
      integer iadr, sadr

      iadr(l)=l+l-1
      sadr(l)=(l/2)+1

      rhs = max(0,rhs)
      top0=top+1-rhs

      lw = lstk(top+1)
      l0 = lstk(top+1-rhs)
      if (rhs .ne. 1) then
         call error(39)
         return
      endif
      if (lhs .ne. 1) then
         call error(41)
         return
      endif
c     checking variable fmat (number 1)
c     
      il1 = iadr(lstk(top-rhs+1))

      if (istk(il1) .ne. 128) then
         err=1
         call error(218)
         return
      endif
      l1 = sadr(il1+4)

      call ludel1(stk(l1))
      if (err .gt. 0) return
c     
      top=top-rhs
c     no output variable
      top=top+1
      il=iadr(lstk(top))
      istk(il)=0
      lstk(top+1)=lstk(top)+1
      return
      end
c			======================================
