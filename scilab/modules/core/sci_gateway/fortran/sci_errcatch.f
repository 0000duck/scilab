
      subroutine interrcatch
c     Copyright INRIA
      include 'stack.h'
      integer topk,p
      logical checkrhs,checklhs,getscalar,cremat,getsmat,checkval
      character*9 opt
      character*9 pause,cont,kill,stp,nomess
      integer iadr
c
      data local/21/
c    
      iadr(l)=l+l-1
      pause ='pause    '
      cont  ='continue '
      kill  ='kill     '
      stp   ='stop     '
      nomess='nomessage'

c
      topk=top
      rhs=max(0,rhs)
      if(.not.checklhs('errcatch',1,1)) return
      if(.not.checkrhs('errcatch',0,3)) return
      catch=0

      if(rhs.eq.0) then
         errct=0
         errpt=0
         top=top+1
         call objvide('errcatch',top)
         return
      endif
      num=0
      imode=0
      imess=0


      do 201 i=1,rhs
         top=topk-rhs+i
         il=iadr(lstk(top))
         if(istk(il).lt.0) il=iadr(istk(il+1))
         if(istk(il).eq.1.and.i.eq.1) then
            if(.not.getscalar('errcatch',topk,top,l)) return
            num=nint(stk(l))
            if(dfloat(num).ne.stk(l).or.num.lt.-1) then
               err=i
               call error(44)
               return
            endif
         else if(istk(il).eq.10.and.i.gt.1) then
            if(.not.getsmat('errcatch',topk,top,m,n,1,1,il1,n1)) return
            if(.not.checkval('errcatch',m*n,1) ) return
            n1=min(n1,9)
            call cvstr(n1,istk(il1),opt,1)
            if(opt(1:n1).eq.cont(1:n1)) then
               imode=1
            elseif(opt(1:n1).eq.pause(1:n1)) then
               imode=2
            elseif(opt(1:n1).eq.nomess(1:n1)) then
               imess=1
            elseif(opt(1:n1).eq.stp(1:n1)) then
               imode=3
            elseif(opt(1:n1).eq.kill(1:n1)) then
               imode=0
            else
               err=i
               call error(44)
               return
            endif
         else
            err=i
            call error(44)
            return
         endif
 201  continue
      top=topk-rhs
      errct=(8*imess+imode)*100000+abs(num)
      catch=max(imode,1)
      if(num.lt.0) errct=-errct
      p=pt+1
 202  p=p-1
      if(p.eq.0) goto 203
      if(int(rstk(p)/100).ne.5) goto 202
 203  errpt=p
      top=top+1
      call objvide('errcatch',top)
      return
      end