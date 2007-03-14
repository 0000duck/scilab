function res=mfile2sci(fil,res_path,Recmode,only_double,verbose_mode,prettyprint)
// Copyright INRIA
// This function performs translation of a single M-file
// - fil: file name
// - res_path: path to write translated file in (default value is fil path)
// - Recmode: recursive mode (default value is false)
// Authors: S.S. and V.C.

// Get default arguments
[lhs,rhs]=argn(0)
if rhs<6 then prettyprint=%F,end
if rhs<5 then verbose_mode=3,end
if rhs<4 then only_double=%F,end
if rhs<3 then Recmode=%F,end
if rhs<2 then res_path="./",end
if rhs<1 then res=m2sci_gui();return;end
if MSDOS then
  fil=strsubst(fil,"\","/")
  res_path=strsubst(res_path,"\","/")
end
if part(res_path,length(res_path))<>"/" then 
  res_path=res_path+"/"
end
// Loads libraries related to m2sci
if exists("m2scikernellib")==0 then load("SCI/modules/m2sci/macros/m2sci/kernel/lib"),end
if exists("m2scipercentlib")==0 then load("SCI/modules/m2sci/macros/m2sci/percent/lib"),end
if exists("m2scisci_fileslib")==0 then load("SCI/modules/m2sci/macros/m2sci/sci_files/lib"),end

if multi_fun_file(fil,res_path,Recmode,only_double,verbose_mode,prettyprint) then
  res=1
  return
end

// Get context
global("m2sci_infos")
global("mtlbref_fun")
global("mtlbtool_fun")
global("not_mtlb_fun")
[l,mac]=where()
Reclevel=size(find(mac=="mfile2sci"),"*")
tpcallpos=min(find(mac=="translatepaths"));
guicallpos=min(find(mac=="m2sci_gui"));
if size(find(mac=="m2sci_gui"),"*")==1 & tpcallpos<guicallpos then // Bug 679
  Reclevel=Reclevel-1
end
if size(find(mac=="multi_fun_file"),"*")==1 then
  Reclevel=Reclevel-1
end

if Reclevel==1 then
  nametbl=[]
else
  m2sci_infos_save=m2sci_infos
end
m2sci_infos=[%f %f]

margin=part(" ",ones(1,3*(Reclevel-1)))
margin="  "
rec=gettext("messages","m2sci_message_3");
dble=gettext("messages","m2sci_message_1");
pretty=gettext("messages","m2sci_message_1");
if prettyprint then pretty=gettext("messages","m2sci_message_2");end
if Recmode then rec=gettext("messages","m2sci_message_4");end
if only_double then dble=gettext("messages","m2sci_message_2");end

res=[]

// Handle file path
// File name
k=strindex(fil,".")
if k<>[]
  ke=k($)-1
  base_name=part(fil,1:ke)
else
  ke=length(fil)
  base_name=fil
end
// File path
k=strindex(fil,"/")
if k==[] then
  file_path="./"
else
  file_path=part(fil,1:k($))
end
// Others M-files in directory
if exists("Paths")==0 then
  Paths=file_path,
  if MSDOS then
    Paths=strsubst(Paths,"/","\")
    mfiles=listfiles(Paths+"*.m")
    sep="\"
  else
    mfiles=listfiles(Paths+"*.m")
    sep="/"
  end
end

// Function name
fnam=part(base_name,k($)+1:ke) // File name without extension

// logfile initialisation
if exists("logfile")==0 then
  [tempfd1,ierr1]=file('open',pathconvert(TMPDIR)+gettext("messages","m2sci_message_5"),"old")
  if ierr1==0 then
    load(pathconvert(TMPDIR)+gettext("messages","m2sci_message_5"))
    file('close',tempfd1)
    file('close',logfile)
    mdelete(pathconvert(TMPDIR)+gettext("messages","m2sci_message_5"))
  end
  logfile=file('open',res_path+"m2sci_"+fnam+".log","unknown")
  save(pathconvert(TMPDIR)+gettext("messages","m2sci_message_5"),logfile)
end

// Output beginning message
mss=[gettext("messages","m2sci_message_6");
    gettext("messages","m2sci_message_7")+" "+fil;
    gettext("messages","m2sci_message_8")+" "+res_path;
    gettext("messages","m2sci_message_9")+" "+rec;
    gettext("messages","m2sci_message_10")+" "+dble;
    gettext("messages","m2sci_message_11")+" "+string(verbose_mode);
    gettext("messages","m2sci_message_12")+" "+pretty]
m2sci_info(mss,-1);

// Read in the file as text
m2sci_info(gettext("messages","m2sci_message_13"),-1);
txt=mgetl(fil);
m2sci_info(gettext("messages","m2sci_message_14"),-1);

//Replace TAB by SPACE
txt=strsubst(txt,code2str(-40),"")

if txt==[] then
  m2sci_infos(msprintf(gettext("messages","m2sci_message_15"),fil),-1);
  return
end
tmptxt=txt

// Make minor changes on syntax
m2sci_info(gettext("messages","m2sci_message_16"),-1);
ierr=execstr("load(''"+pathconvert(TMPDIR)+fnam+ ".tree'',''txt'',''helppart'',''batch'')",'errcatch','n')
if ierr<>0 | exists('txt')==0 | exists('batch')==0 & strindex(res_path,TMPDIR)==[] then
  [helppart,txt,batch]=m2sci_syntax(txt)
elseif ierr==0 & newest(fil,pathconvert(TMPDIR)+fnam+ ".tree")==1 then
    [helppart,txt,batch]=m2sci_syntax(tmptxt)
end

m2sci_info(gettext("messages","m2sci_message_17"),-1);

// Write .cat file and update whatis
if helppart<>[] then
  catfil=res_path+fnam+".cat"
  whsfil=res_path+"whatis"
  mputl(helppart,catfil)
  if exists("whsfil_unit")==1 then
    write(whsfil_unit,stripblanks(helppart(1))+" |"+fnam,"(a)")
  end
end

if txt~=[] then
  quote="''";
  dquote="""";
  kc=strindex(txt(1),"function");
  kc=kc(1);

  // Define Scilab function
  fprot=funcprot();
  funcprot(0);
  
  // Blanks in file name are replaced by _ for batch
  // kc+9 because 'function '
  ksc=min(strindex(txt(1),";")) // searching for a comment on first line after function prototype
  if isempty(ksc) then 
    ksc=length(txt(1))+1;
    firstline=[]
  else
    firstline=part(txt(1),ksc+1:length(txt(1)));
  end
  
  func_proto=part(txt(1),kc+9:ksc-1)
  keq=min(strindex(func_proto,"="))
  kpar=min(strindex(func_proto,"("))
  if isempty(keq) then
    keq=1
  end
  if isempty(kpar) then
    kpar=length(func_proto)+1
  end
  func_proto=part(func_proto,1:keq)+..
      strsubst(stripblanks(part(func_proto,keq+1:kpar-1))," ","_")+..
      part(func_proto,kpar:length(func_proto))

  deff(func_proto,[firstline;txt(2:$)],"n")
  w=who("get");
  mname=w(1);
  nametbl=[nametbl;mname]
  if fnam<>mname & ~batch then // warning is not displayed for a batch file
    mss=msprintf(gettext("messages","m2sci_message_18"),fil,mname,fnam,mname,mname,mname);
    m2sci_info(mss,-1);
  end

  // Compilation
  execstr("comp("+mname+",1)")
  funcprot(fprot)

  // Get Scilab pseudo code of the function
  m2sci_info(gettext("messages","m2sci_message_19"),-1); 
  macr=evstr(mname)
  mtlbtree=macr2tree(macr);
  if ~batch then
    mtlbtree.name=mname;
  else
    mtlbtree.name="";
  end
  
  //Transfom a equal instructions(if lhs are multi_operation insert and expression is a funcall) in the matlab tree to sup_equal instructions
  global("tmpvarnb")
  tmpvarnb=0;
  level=[0,0];
  ninstr=1;
  while ninstr<=size(mtlbtree.statements)-3
    mtlbtree.statements(ninstr)=transformtree(mtlbtree.statements(ninstr))
    ninstr=ninstr+1
  end

  // Perform the translation
  [scitree,trad,hdr,crp]=m2sci(mtlbtree,w(1),Recmode,prettyprint)

  //Creation of fname_resume.log file
 // if mtlbref_fun<>[]|not_mtlb_fun<>[]|mtlbtool_fun<>[] then
    //resume_logfile initialisation
    if exists("resume_logfile")==0 then
      [tempfd2,ierr2]=file('open',pathconvert(TMPDIR)+gettext("messages","m2sci_message_20"),"old")
      if ierr2==0 then
        load(pathconvert(TMPDIR)+gettext("messages","m2sci_message_20"))
        file('close',tempfd2)
        file('close',resume_logfile)
        mdelete(pathconvert(TMPDIR)+gettext("messages","m2sci_message_20"))
      end
      resume_logfile=file('open',res_path+gettext("messages","m2sci_message_21")+"_m2sci_"+fnam+".log",'unknown')
      save(pathconvert(TMPDIR)+gettext("messages","m2sci_message_20"),resume_logfile)
    end
       
    //number of matlab reference functions, matlab toolboxes functions, not matlab functions
    size1=size(mtlbref_fun,1)
    size2=size(mtlbtool_fun,1)
    size3=size(not_mtlb_fun,1)
    
    if size(mtlbref_fun,"*")<>0 then
      mtlbref_fun(:,1)=""""+mtlbref_fun(:,1)+""""
    end
    if size(mtlbtool_fun,"*")<>0 then
      mtlbtool_fun(:,1)=""""+mtlbtool_fun(:,1)+""""
    end
    if size(not_mtlb_fun,"*")<>0 then
      not_mtlb_fun(:,1)=""""+not_mtlb_fun(:,1)+""""
    end

    info_resume=[msprintf(gettext("messages","m2sci_message_22"),fnam);
	"*";
	msprintf(gettext("messages","m2sci_message_23"),size1);
	mtlbref_fun(:,1)+mtlbref_fun(:,2);
	"*";
	msprintf(gettext("messages","m2sci_message_24"),size2);
	mtlbtool_fun(:,1)+mtlbtool_fun(:,2);
	"*";
	msprintf(gettext("messages","m2sci_message_25"),size3);
	not_mtlb_fun(:,1)+not_mtlb_fun(:,2);
	"*"]

    write(resume_logfile,margin+info_resume)
    file("close",resume_logfile)
    mdelete(pathconvert(TMPDIR)+gettext("messages","m2sci_message_20"))
  //end
  
  m2sci_info(gettext("messages","m2sci_message_26"),-1);

  crp(1)=""; // Delete function prototype
  if isempty(firstline) then
    res=[hdr;crp]
  else
    hdr(1)=hdr(1)+" "+crp(2);
    crp(2)=[];
    res=[hdr;crp];
  end

  // Strip last return and blank lines
  n=size(res,1)
  while res(n)==part(" ",1:length(res(n))) then 
    n=n-1
  end
  res=res(1:n)

  // Write sci-file
  ext=".sci"
  scifil=res_path+fnam+ext
  mputl(res,scifil)

  // Write sci_<mname>.sci translation file
  if trad<>[] then
    sci_fil=res_path+"sci_"+mname+".sci"
    mputl(trad,sci_fil)
    res=1
  else
    res=0
  end

  // Output summary information
  infos=[]
  if m2sci_infos(1) then
    infos=gettext("messages","m2sci_message_27");
  end
  if m2sci_infos(2) then
    infos=[infos;gettext("messages","m2sci_message_28")]
  end

  nametbl($)=[]

else
  infos=gettext("messages","m2sci_message_29");
end

// End of translation messages
mss=gettext("messages","m2sci_message_30");

m2sci_info([infos;mss],-1);

if Reclevel>1 then
  m2sci_infos=m2sci_infos_save
end

file("close",logfile)
clearglobal m2sci_infos
clearglobal mtlbref_fun
clearglobal mtlbtool_fun
clearglobal not_mtlb_fun
// For execution called by translatepaths()
//nametbl=resume(nametbl)
mdelete(pathconvert(TMPDIR)+fnam+ ".tree")
mdelete(pathconvert(TMPDIR)+gettext("messages","m2sci_message_5"))

endfunction
