*      subroutine error(n)
c     -------------------------
c     error display and handling
c     n : the error number
c!
c     Copyright INRIA
      integer n
      include 'stack.h'

      integer num,imess,imode,errtyp,lct1
      logical trace
c
      call errmds(num,imess,imode)
      trace=.not.((num.lt.0.or.num.eq.n).and.imess.ne.0)
c
c     de-activate output control
      lct1=lct(1)
      lct(1)=0
c
      errtyp=0
c      if(err1.eq.0.and.err2.eq.0) then
      if(err1.eq.0) then
c     . locate the error in the current statement
        if(trace) call errloc(n)
c     . output error message
        if(.not.trace) lct(1)=-1
        call errmsgf(n,errtyp)
        lct(1)=0
      endif
c
c     handle the error
      call errmgr(n,errtyp)
c
c     re-activate output control
      lct(1)=lct1
c
      return
      end

 
  

      subroutine errmds(num,imess,imode)
c     -------------------------
c     this routine extract error modes out of errct variable
c     imess:  if 0 error message is displayed
c     imode:  error recovery mode
c     num  : error to catch, if num=-1 all errors are catched
      include 'stack.h'
      integer num,imode,imess
c
      num=0
      if(errct.gt.0) then
        num=errct-100000*int(errct/100000)
        imode=errct/100000
       else if(errct.lt.0) then
        num=-1
        imode=-errct/100000
      endif
      imess=imode/8
      imode=imode-8*imess
c
      return
      end


      subroutine depfun(lunit,trace,first)
c     depile une macro ou un execstr
c Bug 1091 corrected - Francois VOGEL November 2004
c Bug 1417 corrected - Francois VOGEL May 2005
      include 'stack.h'
      integer lunit
      logical trace,first,callback
      integer sadr,ll,leng,ival(2)
      double precision val
      equivalence (ival(1),val)
c
      sadr(l)=(l/2)+1
c
      ll=lct(5)
      k=lpt(1)-(13+nsiz)
      lpt(1)=lin(k+1)
      lpt(2)=lin(k+2)
      lpt(3)=lin(k+3)
      lpt(4)=lin(k+4)
      lpt(6)=k
      ival(1)=lin(k+8)
      ival(2)=lin(k+9)
      stk(lstk(isiz))=val

c     recherche du nom de la function correspondant a ce niveau
      lk=sadr(lin(k+6))
      if(lk.le.lstk(top+1)) then
         km=0
      else
         km=lin(k+5)-1
      endif
 1503 km=km+1
      if(km.gt.isiz)goto 1513
      if(lstk(km).ne.lk) goto 1503
c
 1513 continue
      ilk=lin(k+6)
      if(trace) then
         m=0
         if(istk(ilk).ne.10) then
            if(first) then
               buf='at line '
               m=11
               nlc=0
               call linestore(lct(8))
            else
               buf='line '
               m=6
               call whatln(lpt(1),lpt(2),lpt(6),nlc,l1,ifin)
            endif
            write(buf(m+1:m+5),'(i4)') lct(8)-nlc
            m=m+4
            buf(m+1:m+18)=' of function     '
            m=m+13
            if (km.le.isiz) then
               call cvnamel(idstk(1,km),buf(m+1:m+nlgh),1,leng)
               if(first) then
                  call funnamestore(buf(m+1:m+nlgh),leng)
                  first=.false.
               endif
               m=m+leng
            endif
         else
            buf='in  execstr instruction'
            m=26
         endif
         callback=rstk(pt-1).eq.706.or.rstk(pt-1).eq.606
         if(callback) then
            buf(1:26)='while executing a callback'
            m=26
         else
            buf(m+1:m+14)=' called by :'
            m=m+14
         endif
         call basout(io,lunit,buf(1:m))
         lct(8)=lin(k+12+nsiz)
c     
         if (.not.callback) then
            call whatln(lpt(1),lpt(2),lpt(6),nlc,l1,ifin)
            m=ifin-l1+1
            if(m.gt.ll) then
               l1=max(l1,lpt(2)-ll/2)
               m=min(ifin-l1,ll)
            endif

            if(l1.gt.0.and.m.gt.0.and.m+l1-1.le.lsiz) then
               call cvstr(m,lin(l1),buf(1:m),1)
               call basout(io,lunit,buf(1:m))
               if(istk(ilk).eq.10) then
                  if(first) then
                     if(m.gt.24) m=24
                     call funnamestore(buf(1:m),m) 
                     first=.false.
                  endif
               endif
            endif
         endif
      endif
c
      macr=macr-1
      if(istk(ilk).ne.10.and.rstk(pt-1).ne.909) bot=lin(k+5)
      return
      end

      subroutine depexec(lunit,trace,first,pflag)
c     pflag ,indique si c'est une pause qui a ete depilee
c Bug 1091 corrected - Francois VOGEL November 2004
c Bug 1417 corrected - Francois VOGEL May 2005
      include 'stack.h'
      logical trace,first,pflag
      integer mode(2),lunit,ll

      ll=lct(5)
      call whatln(lpt(1),lpt(2),lpt(6),nlc,l1,ifin)
      if(rio.ne.rte) then
c     exec
         k=lpt(1)-(13+nsiz)
         lpt(1)=lin(k+1)
         lpt(2)=lin(k+4)
         lpt(6)=k
c
         if (trace) then
            if(first) then
               buf='at line '
               m=11
               nlc=0
               call linestore(lct(8))
            else
               buf='line '
               m=6
            endif
            write(buf(m+1:m+5),'(i4)') lct(8)-nlc
            m=m+4
            buf(m+1:m+29)=' of exec file called by :'
            m=m+29
            call basout(io,lunit,buf(1:m))
            lct(8)=lin(k+12+nsiz)
c     
            call whatln(lpt(1),lpt(2),lpt(6),nlc,l1,ifin)
            m=ifin-l1+1
            if(m.gt.ll) then
               l1=max(l1,lpt(2)-ll/2)
               m=min(ifin-l1,ll)
            endif
            call cvstr(m,lin(l1),buf,1)
            call basout(io,lunit,buf(1:m))
            if(first) then
               if(m.gt.24) m=24
               call funnamestore(buf(1:m),m) 
               first=.false.
            endif
         endif
         mode(1)=0
         call clunit(-rio,buf,mode)
 1505    pt=pt-1
         if(rstk(pt).ne.902) goto 1505
         rio=pstk(pt)
         pflag=.false.
      else
c     pause
         top=ids(2,pt-1)
         pflag=.true.
      endif
      return
      end


      subroutine errloc(n)
c     this routines shows the approximate location of the error in the
c     current statement
c!
      include 'stack.h'

c      integer sadr

      character mg*9,bel*1,line*340,fmt*7
      integer n,ll,m,m1,lp,nd
      data mg /' !--error'/,bel/' '/
c
c      sadr(l)=(l/2)+1
c
      ll=lct(5)

      lunit = wte
      m1=lpt(2)-lpt(1)
      if(m1.lt.1) m1=1
c
      if(macr.eq.0.and.rio.eq.rte) goto 1000
      call whatln(lpt(1),lpt(2),lpt(6),nlc,l1,ifin)
      m=ifin-l1+1
      if(m.gt.ll) then
         l1=max(l1,lpt(2)-ll/2)
         m=min(ifin-l1,ll)
      endif
      m1=max(0,lpt(2)-l1)

      if(m.gt.0) then
         call cvstr(m,lin(l1),line,1)
         call basout(io,lunit,line(1:max(m,1)))
      endif
 1000 line=' '
      if(m1+15.gt.ll) m1=ll-16
      line(m1+1:m1+9)=mg
      lp=m1+11
      nd=int(log10(float(n)))+1
      write(fmt,'(''(i'',i2,'')'')') nd
      write(line(lp:lp+nd-1),fmt) n
      lp=lp+nd
      line(lp:lp)=bel
      call basout(io,lunit,line(1:lp))
      return
      end

