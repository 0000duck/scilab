      subroutine useascommand(fname)
c     Copyright INRIA
      include 'stack.h'
      logical checkrhs,checklhs,cremat,getscalar,getsmat,checkval
      integer topk,id(nsiz)
      integer iadr,sadr
      character*1 opt
      character*(*) fname
c
c    
      iadr(l)=l+l-1
      sadr(l)=(l/2)+1
c
      rhs=max(0,rhs)
      if(.not.checkrhs(fname,1,2)) return
      if(.not.checklhs(fname,1,1)) return

      job=1
      topk=top
      
      if(rhs.eq.2) then
         if(.not.getsmat(fname,topk,top,m,n,1,1,l,nl))return
         if (nl.ne.1) then
            err=2
            call error(36)
            return
         endif
         call cvstr(nl,istk(l),opt,1)
         top=top-1

         if(opt.eq.'a') then
            job=1
         elseif (opt.eq.'d') then
            job=2
         else
            err=2
            call error(36)
            return
         endif
      endif
      if(.not.getsmat(fname,topk,top,m,n,1,1,l,n1)) return
      if(.not.checkval(fname,m*n,1) ) return
      call namstr(id,istk(l),n1,0)
      call comand(id,job)
      if(err.gt.0) return
      il=iadr(lstk(top))
      istk(il)=0
      lstk(top+1)=lstk(top)+1
      return
      end
      