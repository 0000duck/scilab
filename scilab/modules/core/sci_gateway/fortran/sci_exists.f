
      subroutine intexists(job)
c     Copyright INRIA
      include 'stack.h'
      integer topk
      integer id(nsiz)
      logical checkrhs,checklhs,cremat,getsmat,checkval,crebmat
      integer flag
      integer local,nolocal
      integer iadr,sadr
c
      data local/21/
      data nolocal/23/
c    
      iadr(l)=l+l-1
      sadr(l)=(l/2)+1
c
      topk=top

      if(.not.checklhs('exists',1,1)) return
      if(.not.checkrhs('exists',1,2)) return

      flag=0
c
      if(rhs.eq.2) then
         if(.not.getsmat('exists',topk,top,m,n,1,1,il,n1)) return
         if(.not.checkval('exists',m*n,1) ) return
         if(istk(il).eq.local) flag=1
         if(istk(il).eq.nolocal) flag=2
         top=top-1
      endif


      if(.not.getsmat('exists',topk,top,m1,n1,1,1,il,n)) return
      if(.not.checkval('exists',m1*n1,1) ) return
      call namstr(id,istk(il),n,0)

c     look for  variables in the stack
      if(flag.eq.2) then
c      in the full calling context
c      but not in the local environment
         fin=-7
         call stackg(id)
      elseif(flag.eq.1) then
c      just in local environment
         fin=-3
         call stackg(id)
         ilw=iadr(lstk(top))
         top=top-1
         if(istk(ilw).lt.0) then
            fin=1
         else
            fin=0
         endif
      else
c      in all the stack
         fin=-1
         call stackg(id)
         if (fin.le.0) then
c      look for libraries functions
            fin=-3
            kfun=fun
            call funs(id)
            fun=kfun
         endif
      endif
c
      if(job.eq.0) then
c     exists returns 0 or 1
         if(.not.cremat('exists',top,0,1,1,l,lc)) return
         if (fin.gt.0) then
            stk(l)=1.0d0
         else
            stk(l)=0.0d0
         endif
      else
c     isdef returns %f or %t
         if(.not.crebmat('exists',top,1,1,l)) return
         if (fin.gt.0) then
            istk(l)=1
         else
            istk(l)=0.0d0
         endif
      endif
      fin=1
      return
      end
