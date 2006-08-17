c     --------------------------
c     Copyright INRIA
c     --------------------------
c
      subroutine scitzer(fname)
c     ----------------------------
      character*(*) fname
      include '../stack.h'
      double precision dnrm2,tol,atol,eps,gi,rcond,ur,ui,vr,vi,xr,xi
      integer p,ind,q,job,ido,n,top1
      integer iadr,sadr

      iadr(l)=l+l-1
      sadr(l)=(l/2)+1

      if(top+1-rhs+lhs.ge.bot) then
         call error(18)
         return
      endif
      eps=0.1*sqrt(stk(leps))
c
      err=0

      if(lhs.ne.1.or.rhs.ne.3) then
         call error(39)
         return
      endif

c     calcule de zeros multivariables
      if(rhs.ne.4) then
         call error(42)
         return
      endif
      if(lhs.ne.2.and.lhs.ne.3) then
         call error(41)
         return
      endif
c   matrice d
      id=iadr(lstk(top))
      if(istk(id).ne.1) then
         err=4
         call error(53)
         return
      endif
      if(istk(id+3).ne.0) then
         err=4
         call error(52)
         return
      endif
      md=istk(id+1)
      nd=istk(id+2)
      ld=sadr(id+4)
c    matrice c
      top=top-1
      ic=iadr(lstk(top))
      if(istk(ic).ne.1) then
         err=3
         call error(53)
         return
      endif
      if(istk(ic+3).ne.0) then
         err=3
         call error(52)
         return
      endif
      mc=istk(ic+1)
      nc=istk(ic+2)
      lc=sadr(ic+4)
c      matrice b
      top=top-1
      ib=iadr(lstk(top))
      if(istk(ib).ne.1) then
         err=2
         call error(53)
         return
      endif
      if(istk(ib+3).ne.0) then
         err=2
         call error(52)
         return
      endif
      mb=istk(ib+1)
      nb=istk(ib+2)
      lb=sadr(ib+4)
c      matrice a
      top=top-1
      ia=iadr(lstk(top))
      if(istk(ia).ne.1) then
         err=1
         call error(53)
         return
      endif
      if(istk(ia+3).ne.0) then
         err=1
         call error(52)
         return
      endif
      ma=istk(ia+1)
      na=istk(ia+2)
      if(na.ne.ma) then
         err=1
         call error(20)
         return
      endif
      la=sadr(ia+4)
c
      if(mb.ne.na.or.nc.ne.na.or.nb.ne.nd.or.mc.ne.md) then
         call error(60)
         return
      endif
      if(na.eq.0) then
         return
      endif
      lr=ld+md*nd
      li=lr+na
      laf=li+na
      lbf=laf+(na+mc)*(nb+na)
      lka=lbf+(na+mc)*(nb+na)
      nwrk1=max(nb,mc)
      nwrk2=max(nwrk1,na)+1
      lk1=lka+na*na
      lk2=lk1+nwrk1
      err=lk2+nwrk2-lstk(bot)
      if(err.gt.0) then
         call error(17)
         return
      endif
      call sszer(na,nb,mc,stk(la),na,stk(lb),stk(lc),mc,stk(ld),eps
     x     ,stk(lr),stk(li),nu,irank,stk(laf)
     x     ,na+mc,stk(lbf),na+nb,stk(lka),stk(lk1),nwrk1,
     x           stk(lk2),nwrk2,err)
      if(err.gt.0) then
         call error(24)
         return
      endif
c     sortie des resultats
      if(irank.eq.0.and.nu.gt.0) then
         call dset(nu,0.0d0,stk(lr),1)
         call dset(nu,0.0d0,stk(li),1)
         call dset(nu,0.0d0,stk(lk2),1)
      endif
      istk(ia+1)=nu
      istk(ia+2)=min(nu,1)
      istk(ia+3)=1
      call unsfdcopy(nu,stk(lr),1,stk(la),1)
      call unsfdcopy(nu,stk(li),1,stk(la+nu),1)
      lstk(top+1)=la+nu+nu
      top=top+1
      ib=iadr(lstk(top))
      lb=sadr(ib+4)
      istk(ib)=1
      istk(ib+1)=nu
      istk(ib+2)=min(nu,1)
      istk(ib+3)=0
      call unsfdcopy(nu,stk(lk2),1,stk(lb),1)
      lstk(top+1)=lb+nu
      if(lhs.eq.3) then
         top=top+1
         ib=iadr(lstk(top))
         lb=sadr(ib+4)
         istk(ib)=1
         istk(ib+1)=1
         istk(ib+2)=1
         istk(ib+3)=0
         stk(lb)=irank
         lstk(top+1)=lb+1
      endif
      goto 99
      
   99    return
      end
c     ----------------------------