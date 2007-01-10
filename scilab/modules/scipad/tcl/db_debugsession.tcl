proc tonextbreakpoint_bp {{checkbusyflag 1} {stepmode "nostep"}} {
    if {[getdbstate] == "ReadyForDebug"} {
        clearscilaberror
        execfile_bp $stepmode
    } elseif {[getdbstate] == "DebugInProgress"} {
        resume_bp $checkbusyflag $stepmode
    } else {
        tk_messageBox -message "Unexpected debug state in proc tonextbreakpoint_bp: please report"
    }
}

proc execfile_bp {{stepmode "nostep"}} {
    global funnameargs listoftextarea funsinbuffer waitmessage watchvars
    global setbptonreallybreakpointedlinescmd
    if {[isscilabbusy 5]} {return}
    showinfo $waitmessage

    # create the setbpt command
    set setbpcomm ""
    foreach textarea [filteroutpeers $listoftextarea] {
        set tagranges [$textarea tag ranges breakpoint]
        foreach {tstart tstop} $tagranges {
            set infun [whichfun [$textarea index $tstart] $textarea]
            if {$infun != {} } {
                set funname [lindex $infun 0]
                set lineinfun [expr [lindex $infun 1] - 1]
                set setbpcomm [concat $setbpcomm "setbpt(\"$funname\",$lineinfun);"]
            } else {
                # <TODO> .sce case if some day the parser uses pseudocode noops
                # with the wrapper implementation, breakpoints are always
                # inside a function at the time of exec
            }
        }
    }

    # exec the required file(s), which are the current one
    # and the one containing the function to debug
    if {$funnameargs != ""} {
        setdebuggerbusycursor
        if {[execfile "current"] == -1} {
            # in case execing the file produced an error, restore the cursors
            unsetdebuggerbusycursor
        }
        # exec file containing the function to debug
        # <TODO> this fails if the same function name can be found in more
        #        than one single buffer
        # note : we can't exec *all* buffers because some might contain
        # non-Scilab scripts, which is not checked by execfile
        set funname [string range $funnameargs 0 [expr [string first "(" $funnameargs] - 1]]
        foreach textarea [filteroutpeers $listoftextarea] {
            if {[info exists funsinbuffer($textarea)]} {
                if {[lsearch $funsinbuffer($textarea) $funname] != -1 && \
                     $textarea != [gettextareacur]} {
                    if {[execfile $textarea] == -1} {
                        unsetdebuggerbusycursor
                    }
                }
            }
        }
        set setbptonreallybreakpointedlinescmd $setbpcomm
        setdbstate "DebugInProgress"
        set commnvars [createsetinscishellcomm $watchvars]
        set watchsetcomm [lindex $commnvars 0]
        if {$watchsetcomm != ""} {
            # no need for $visibilitycomm, i.e. [lindex $commnvars 2]
            # because here the shell is still at the --> prompt
            ScilabEval_lt "$watchsetcomm" "seq"
        }
        ScilabEval_lt "$setbpcomm; $funnameargs;" "seq"
        updateactivebreakpoint
        getfromshell
        checkendofdebug_bp $stepmode
    } else {
        # <TODO> .sce case if some day the parser uses pseudocode noops
    }
}

# <TODO> step by step support
# I have no satisfactory solution for the time being.
# The heart of the matter with step by step execution is that
# once the execution is stopped there is no way of knowing what is the next
# line of code to execute. Of course, it is usually the next code line in the
# sci file, but this is not necessarily true in for, while, if, and case
# structures. I do not foresee any other remedy than a complete code analysis
# performed in Tcl (!), but this is a huge task I'm not prepared to go into.
# Moreover, all this analysis is already (and surely better) done by the
# Scilab interpreter, therefore the best way would probably be to add a new
# Scilab function that would return the line number of the next instruction to
# be executed. This should no be such a tricky thing to do, drawing inspiration
# e.g. from setbpt, where, whatln and so on. However, despite my repeated
# demands for information about the internals to the Scilab team, I never could
# obtain any documentation nor help on this topic. Hence an elegant solution
# for step execution is still to be achieved. Better than nothing, I
# implemented a brute force approach that basically sets a breakpoint
# everywhere. This works but is obviously sub-optimal.

proc stepbystepinto_bp {{checkbusyflag 1} {rescanbuffers 1}} {
# perform "step into" debug
    stepbystep_bp $checkbusyflag "into" $rescanbuffers
}

proc stepbystepover_bp {{checkbusyflag 1} {rescanbuffers 1}} {
# perform "step over" debug
    stepbystep_bp $checkbusyflag "over" $rescanbuffers
}

proc stepbystepout_bp {{checkbusyflag 1} {rescanbuffers 1}} {
# perform "step out" debug
    stepbystep_bp $checkbusyflag "out" $rescanbuffers
}

proc stepbystep_bp {checkbusyflag stepmode rescanbuffers} {
# set a breakpoint in Scilab on really every line of every function
# of every opened buffer consistently with the current step mode,
# run execution, delete all those breakpoints and restore the
# breakpoints that were really set by the user
    global funnameargs
    global logicallinenumbersranges previousstepscope
    global CurBreakpointedMacros CurBreakpointedLines ; # globality mandatory, and only used while skipping lines

    if {[getdbstate] == "ReadyForDebug"} {
        # always a busy check - this code part cannot be entered
        # while skipping lines without executable statements
        # (which might occur during step by step)
        if {[isscilabbusy 5]} {return}

        clearscilaberror

#        showwrappercode

        if {$funnameargs != ""} {
            set funname [string range $funnameargs 0 [expr [string first "(" $funnameargs] - 1]]
            ScilabEval_lt "setbpt(\"$funname\",1);" "seq"
        } else {
            # <TODO> .sce case if some day the parser uses pseudocode noops
        }
        # here tricky (but correct) behaviour!! (see below for same comment)
        execfile_bp $stepmode
        if {$funnameargs != ""} {
            ScilabEval_lt "delbpt(\"$funname\",1);" "seq"
        } else {
            # <TODO> .sce case if some day the parser uses pseudocode noops
        }

        # hidewrappercode is performed in checkendofdebug_bp

    } elseif {[getdbstate] == "DebugInProgress"} {
        # no busy check to allow to skip lines without code (step by step)
        if {$checkbusyflag} {
            if {[isscilabbusy 5]} {return}
        }
        if {$funnameargs != ""} {

#            showwrappercode

            switch -- $stepmode {
                "into"  {set stepscope "current&ancill"}
                "over"  {set stepscope "currentcontext"}
                "out"   {set stepscope "callingcontext"}
                default {set stepscope "allscilabbuffers" ;# should never happen}
            }
            # because the user can open or close files during debug,
            # getlogicallinenumbersranges must be called at each step
            # however, do it a minima, i.e. not when skipping no code lines
            if {![info exists previousstepscope] || \
                ![info exists logicallinenumbersranges]} {
                foreach {logicallinenumbersranges CurBreakpointedMacros CurBreakpointedLines} \
                        [getlogicallinenumbersranges $stepscope] {}
            } else {
                if {$rescanbuffers || ($previousstepscope != $stepscope) } {
                    foreach {logicallinenumbersranges CurBreakpointedMacros CurBreakpointedLines} \
                            [getlogicallinenumbersranges $stepscope] {}
                }
            }
            updatebptcomplexityindicators_bp $CurBreakpointedMacros $CurBreakpointedLines
            set previousstepscope $stepscope
            set cmd $logicallinenumbersranges
            # check Scilab limits in terms of breakpoints
            if {$cmd == "-1"} {
                # abort step-by-step command - do nothing
            } elseif {$cmd == "0"} {
                # execute "Go to next breakpoint" instead
                tonextbreakpoint_bp
            } else {
                # no limit exceeded - go on one step
                regsub -all -- {\(} $cmd "setbpt(" cmdset
                regsub -all -- {\(} $cmd "delbpt(" cmddel
                ScilabEval_lt "$cmdset" "seq"
                # here tricky (but correct) behaviour!!
                # resume_bp calls checkendofdebug_bp that constructs a string
                # containing TCL_EvalStr("Scilab_Eval_lt ... seq"","scipad")
                # this string is itself evaluated by a ScilabEval_lt seq, so the order
                # in queue is first Tcl_EvalStr("Scilab_Eval_lt ... seq"","scipad")
                # queued by checkendofdebug_bp, and second $cmddel queued from here
                # Then Scilab executes the statements one by one: the first item
                # results in queueing at the end what is in the ScilabEval_lt (the ...
                # above) and that's all. Then $cmddel gets executed, and finally
                # the ... get executed
                # Order of execution is therefore $cmddel and, after it only, the
                # contents of proc checkendofdebug_bp
                resume_bp $checkbusyflag $stepmode
                ScilabEval_lt "$cmddel" "seq"
            }

            # hidewrappercode is performed in checkendofdebug_bp

        } else {
            # <TODO> .sce case if some day the parser uses pseudocode noops
        }

    } else {
        tk_messageBox -message "Unexpected debug state in proc stepbystep_bp: please report"
    }
}

proc getlogicallinenumbersranges {stepscope} {
# get all logical line numbers ranges of all functions from the given
# step by step scope $stepscope, which can be
#   - allscilabbuffers : functions from all scilab scheme buffers
#   - configuredfoo    : only the function that was selected in the
#                        configure box
#   - currentcontext   : functions listed in the call stack at the
#                        current stop point
#   - callingcontext   : functions listed in the call stack at the
#                        current stop point, except the first one
#   - current&ancill   : userfuns and libfuns called by the function
#                        where debugger has currently stopped in,
#                        plus functions from "currentcontext" above
# return value is a list with 3 elements: {item1 n m} where:
#  item1 is normally a single string:
#   ("$fun1",1:max1);("$fun2",1:max2);...;("$funN",1:maxN);
# this format is especially useful when this string is used to set or
# delete breakpoints in all the lines - just use a regsub to replace
# the opening parenthesis by setbpt( or delbpt(
# for libfun ancillaries, max is always 1 such that the output string
# is simplified for these items: ("$libfun1",1)
#  n is the number of currently breakpointed macros
#  m is the number of currently breakpointed lines
# in case any Scilab limit is exceeded, item1 is a string containing
# a return code:
#   "0"  : the calling procedure should apply "Go to next breakpoint" instead
#          of the intended step-by-step command
#   "-1" : the calling procedure should cancel the step-by-step command

    global ScilabCodeMaxBreakpointedMacros ScilabCodeMaxBreakpoints
    global debugassce
    global callstackfuns callstacklines

    set cmd ""
    set nbmacros 0 ; # used to test max number of breakpointed macros
    set nbbreakp 0 ; # used to test max number of breakpoints

    foreach {ta funsinthatta} [getallfunsinalltextareas] {
        if {[lindex $funsinthatta 0] == "0NoFunInBuf"} {
            continue
        }
        foreach {funname funline precfun} $funsinthatta {

            if {![isinstepscope $funname $stepscope]} {
                continue
            }

            set curpos [getendfunctionpos $ta $precfun]
            if {$curpos == -1} {
                # can't happen in principle
                # <TODO>: It happens however in well-formed functions containing a string
                #         containing the word "function", the string being quoted with
                #         single quotes when these strings are not colorized (options menu)
                #         Find a better way to handle such cases than just this messageBox!
                tk_messageBox -message "getendfunctionpos returned $curpos in proc getlogicallinenumbersranges: please report"
            }

            # $curpos now contains the index in $ta of the first n of the word
            # endfunction corresponding to $funname
            set nbcontlines [countcontlines $ta $precfun $curpos]
            scan $precfun "%d." startoffun 
            scan $curpos  "%d." endoffun 
            set lastlogicalline [expr $endoffun - $startoffun - $nbcontlines +1]

            # if the debug occurs on a .sce file wrapped in a function, the
            # last four logical line numbers contain the code added to return
            # local variables to the calling level and should not be
            # breakpointed since they constitute hidden code
            # however, this must not be done for user-defined functions in
            # the case of mixed .sce/.sci files, it must only be done for
            # the wrapper function which is the one that has the
            # endfunction keyword on the last line of the buffer
            # in details: end -1c (last newline) -1l linestart (prev. line)
            # +1c (first n of "endfunction")
            if {$debugassce && \
                [$ta compare $curpos == [$ta index "end -1c -1l linestart + 1c"]]} {
                incr lastlogicalline -4
            }

            append cmd "(\"$funname\",1:" $lastlogicalline ");"

            incr nbbreakp $lastlogicalline
        }
        incr nbmacros
    }
    # libfun ancillaries of the function where the debugger is currently in
    # note: variable callstackfuns is set by Scilab script FormatWhereForWatch
    if {$stepscope == "current&ancill"} {
        set currentfunction [lindex $callstackfuns 0]
        set taofcurrentfunction [lindex [funnametofunnametafunstart $currentfunction] 1]
        if {$taofcurrentfunction == ""} {
            # the textarea containing the function where the debugger is
            # currently in has been closed previously by the user
            # this probably means that the user does not want to continue
            # stepping in that function, therefore don't open it again!
            # this is obtained simply by doing nothing here, no ancillary
            # is breakpointed (ancillaries of a foo here include foo itself)
            # note: closure of the main file (the one that contains the
            # function to debug) is treated in proc removefuns_bp
        } else {
            set lfanclist [getlistofancillaries $taofcurrentfunction $currentfunction "libfun"]
            foreach libfunanc $lfanclist {
                # check if ancillary is already breakpointed - if it is, then its
                # breakpointed lines range is greater than just the first line
                # -> nothing to do
                # note: escaped quotes mandatory to distinguish "modulo" from
                # "pmodulo" !
                if {[string first "\"$libfunanc\"" $cmd] == -1} {
                    append cmd "(\"$libfunanc\",1);"
                    incr nbbreakp
                    incr nbmacros
                }
            }
        }
    }
    # libfun ancillaries for nested constructs, e.g. pmodulo(modulo()),
    # breakpoint all the ancillaries that show up on the calling line
    # of the upper level function
    if {[llength $callstackfuns] > 1} {
        set callingfunction [lindex $callstackfuns 1]
        set callingfuncline [lindex $callstacklines 1]
        set taofcallingfunction [lindex [funnametofunnametafunstart $callingfunction] 1]
        if {$taofcallingfunction == ""} {
            # the textarea containing the upper level function has been
            # closed previously by the user
            # Scipad should still breakpoint the ancillaries of that calling
            # function, the problem is that it cannot know which ancillaries
            # are contained in that function without opening and colorizing
            # the corresponding file that was closed
            # Scipad even cannot breakpoint just the calling function itself
            # because the last line number of that function is not known,
            # therefore the only solution is to do nothing!
            # consequence: when stepping out of the current function, the
            # calling function will be skipped and execution will stop again
            # in the caller of the caller
        } else {
            set lfanclist [getlistofancillaries $taofcallingfunction $callingfunction "libfun" $callingfuncline]
            foreach libfunanc $lfanclist {
                # check if ancillary is already breakpointed - if it is, then its
                # breakpointed lines range is greater than just the first line
                # -> nothing to do
                # note: escaped quotes mandatory to distinguish "modulo" from
                # "pmodulo" !
                if {[string first "\"$libfunanc\"" $cmd] == -1} {
                    append cmd "(\"$libfunanc\",1);"
                    incr nbbreakp
                    incr nbmacros
                }
            }
        }
    }

    # From help setbpt: The maximum number of functions with breakpoints
    #                   enabled must be less than 100 and the maximum number
    #                   of breakpoints is set to 1000
    # Check it and ask what to do if any limit is exceeded
    if {$nbmacros >= $ScilabCodeMaxBreakpointedMacros} {
       # number is > 100%
       updatebptcomplexityindicators_bp $nbmacros $nbbreakp
       set mes [concat [mc "You have currently"] $nbmacros [mc "functions in your opened files."] \
                        [mc "Scilab supports a maximum of"] $ScilabCodeMaxBreakpointedMacros \
                        [mc "possible breakpointed functions (see help setbpt)."] \
                        [mc "Step-by-step hence cannot be performed."] \
                        [mc "This command will actually run to the next breakpoint."] ]
        set answer [tk_messageBox -message $mes -title [mc "Too many breakpointed functions"] \
                        -icon warning -type okcancel]
        switch -- $answer {
            ok     {set cmd "0"}
            cancel {set cmd "-1"}
        }
        set nbmacros [countallbreakpointedmacros]
    }
    if {$nbbreakp >= $ScilabCodeMaxBreakpoints} {
        # number is > 100%
        updatebptcomplexityindicators_bp $nbmacros $nbbreakp
        set mes [concat [mc "Executing this command would require to set"] $nbbreakp \
                        [mc "breakpoints in your opened files."] \
                        [mc "Scilab supports a maximum of"] $ScilabCodeMaxBreakpoints \
                        [mc "possible breakpoints in Scilab (see help setbpt)."] \
                        [mc "Step-by-step hence cannot be performed."] \
                        [mc "This command will actually run to the next breakpoint."] ]
        set answer [tk_messageBox -message $mes -title [mc "Too many breakpoints"] \
                        -icon warning -type okcancel]
        switch -- $answer {
            ok     {set cmd "0"}
            cancel {set cmd "-1"}
        }
        set nbbreakp [countallbreakpointedlines]
    }

    return [list $cmd $nbmacros $nbbreakp]
}

proc isinstepscope {funname stepscope} {
# return true if function name $funname is in step scope $stepscope
# see proc getlogicallinenumbersranges for the available scopes
    global funnameargs
    global callstackfuns
    global debugger_fun_ancillaries

    # the debugger ancillaries cannot be debugged and shouldn't be stepped
    if {[lsearch -exact $debugger_fun_ancillaries $funname] != -1} {
        return false
    }

    if {$stepscope == "allscilabbuffers"} {
        return true

    } elseif {$stepscope == "configuredfoo"} {
        set oppar [expr [string first "\(" $funnameargs] - 1]
        set configuredfunname [string range $funnameargs 0 $oppar]
        if {$funname == $configuredfunname} {
            return true
        } else {
            return false
        }

    } elseif {$stepscope == "currentcontext"} {
        # note: variable callstackfuns is set by Scilab script FormatWhereForWatch
        if {[lsearch -exact $callstackfuns $funname] != -1} {
            return true
        } else {
            return false
        }

    } elseif {$stepscope == "callingcontext"} {
        # note: variable callstackfuns is set by Scilab script FormatWhereForWatch
        if {[llength $callstackfuns] > 1} {
            set callcont [lreplace $callstackfuns 0 0]
            if {[lsearch -exact $callcont $funname] != -1} {
                return true
            } else {
                return false
            }
        } else {
            return false
        }

    } elseif {$stepscope == "current&ancill"} {
        # current context plus ancillaries tagged as "userfun"
        # try current context first since looking for ancillaries is slow
        if {[isinstepscope $funname "currentcontext"]} {
            return true
        } else {
            set currentfunction [lindex $callstackfuns 0]
            set taofcurrentfunction [lindex [funnametofunnametafunstart $currentfunction] 1]
            set ufanclist [getlistofancillaries $taofcurrentfunction $currentfunction "userfun"]
            if {[lsearch -exact $ufanclist $funname] != -1} {
                return true
            } else {
                return false
            }
        }

    } else {
        tk_messageBox -message "Unexpected step scope ($stepscope) in proc isinstepscope. Please report."
        return false
    }
}

proc runtocursor_bp {{checkbusyflag 1} {skipbptmode 0}} {
    global cursorfunname cursorfunline

    # no busy check to allow to skip stops at the wrong breakpoint
    if {$checkbusyflag} {
        if {[isscilabbusy 5]} {return}
    }

    set textarea [gettextareacur]

    # if the cursor is in the wrapper code (.sce files case), move it out
    if {[lsearch [$textarea tag names insert] "db_wrapper"] != -1} {
        set wrapstart [$textarea tag prevrange "db_wrapper" insert]
        set wrapstart [lindex $wrapstart 0]
        $textarea mark set insert "$wrapstart - 1 c"
    }

    set infun [whichfun [$textarea index insert] $textarea]
    if {$infun!=""} {
        if {!$skipbptmode} {
            set cursorfunname [lindex $infun 0]
            # substract 1 since we want to stop before this line and not after
            set cursorfunline [expr [lindex $infun 1] - 1]
            if {$cursorfunline == 0} {
                # cursor is on the function definition line
                set cursorfunline 1
            }
        }
        set setbpcomm "setbpt(\"$cursorfunname\",$cursorfunline);"
        ScilabEval_lt $setbpcomm "seq"
        tonextbreakpoint_bp $checkbusyflag "runtocur"
        set delbpcomm "delbpt(\"$cursorfunname\",$cursorfunline);"
        ScilabEval_lt $delbpcomm "seq"
    } else {
        showinfo [mc "Cursor must be in a function"]
    }
}

proc iscursorplace_bp {} {
# return true if the current stop occurs at line $cursorfunline of
# function $cursorfunname
# return false otherwise
    global cursorfunname cursorfunline
    global callstackfuns callstacklines
    if {[lindex $callstackfuns 0] == $cursorfunname} {
        if {[expr [lindex $callstacklines 0] -1] == $cursorfunline} {
            return true
        }
    }
    return false
}

proc resume_bp {{checkbusyflag 1} {stepmode "nostep"}} {
    global funnameargs waitmessage watchvars

    # no busy check to allow to skip lines without code (step by step)
    if {$checkbusyflag} {
        if {[isscilabbusy 5]} {return}
    }

    showinfo $waitmessage
    if {$funnameargs != ""} {
        setdebuggerbusycursor
        set commnvars [createsetinscishellcomm $watchvars]
        set watchsetcomm [lindex $commnvars 0]
        if {$watchsetcomm != ""} {
            set visibilitycomm [lindex $commnvars 2]
            ScilabEval_lt "$visibilitycomm;$watchsetcomm" "seq"
            set returnwithvars [lindex $commnvars 1]
            ScilabEval_lt "$returnwithvars" "seq"
        } else {
            ScilabEval_lt "resume(0)" "seq"
        }
        updateactivebreakpoint
        getfromshell
        checkendofdebug_bp $stepmode
    } else {
        # <TODO> .sce case if some day the parser uses pseudocode noops
    }
}

proc goonwo_bp {} {
    global funnameargs waitmessage

    if {[isscilabbusy 5]} {return}

    showinfo $waitmessage
    if {$funnameargs != ""} {
        removeallactive_bp
        removescilab_bp "with_output"
        ScilabEval_lt "resume(0)" "seq"
        getfromshell
        checkexecutionerror_bp
    } else {
        # <TODO> .sce case if some day the parser uses pseudocode noops
    }
    setdbstate "ReadyForDebug"
}

proc break_bp {} {
    if {[isscilabbusy]} {

# Many solutions were explored, none is fully functional.
# Apparently the problem boils down to sending a sync command
# while in a seq execution (the one from the very beginning
# of the debug, which executes the function to debug)
# See also bug 1086 for that sort of issues

# 1. send a seq pause preceded by flush
# two flushes since the first one may just queue new commands
# (see proc checkendofdebug_bp)
#        ScilabEval_lt "flush"
#        ScilabEval_lt "flush"
#        ScilabEval_lt "pause" "seq"
#        updateactivebreakpoint 4
#        getfromshell 4

# 2. send a sync pause
# apparently same result with:
#       ScilabEval_lt "pause" "sync"
#       updateactivebreakpoint 3
#       getfromshell 3

# 3. launch a new core Fortran command that only says call sigbas(2)
#    i.e. set iflag to 1 (true), i.e. an interrupt has occurred
#    Note that this command already exists in C (void SignalCtrC)
#      ScilabEval "breaksgl" "sync" "seq"
#      updateactivebreakpoint 4
#      getfromshell 4

# 4. set breakpoints everywhere during run (details copied
#    from stepbystep_bp)
if {1} {
global funnameargs
global setbptonreallybreakpointedlinescmd
set checkbusyflag 0
        if {$funnameargs != ""} {
            # because the user can open or close files during debug,
            # getlogicallinenumbersranges must be called at each step
            set stepmode "into"
            set stepscope "allscilabbuffers"
            set cmd [getlogicallinenumbersranges $stepscope]
            # check Scilab limits in terms of breakpoints
            if {$cmd == "-1" || $cmd == "0"} {
                # impossible to set the required breakpoints
                tk_messageBox -message "Too many bpts or bpted funs!"
                return
            } else {
                # no limit exceeded - go on one 
                regsub -all -- {\(} $cmd "setbpt(" cmdset
                regsub -all -- {\(} $cmd "delbpt(" cmddel
                ScilabEval_lt "$cmdset" "sync" ;# "seq"
                updateactivebreakpoint 4
                ScilabEval_lt "$cmddel" "seq"
                getfromshell 4
            }
        } else {
            # <TODO> .sce case if some day the parser uses pseudocode noops
    #        resume_bp
        }
}

# <TODO> Remove next line and allow to continue debug
# Problem: Scilab does not stop at breakpoints located after the break command point!
#        setdbstate "NoDebug"
    } else {
        showinfo [mc "No effect - The debugged file is not stuck"]
    }
}

proc canceldebug_bp {} {
    global funnameargs waitmessage

    if {[isscilabbusy 5]} {return}

    if {[getdbstate] == "DebugInProgress"} {
        showinfo $waitmessage
        if {$funnameargs != ""} {
            removeallactive_bp
            ScilabEval_lt "abort" "seq"
            removescilab_bp "with_output"
            getfromshell
            cleantmpScilabEvalfile
        }
    } else {
        # [getdbstate] is "ReadyForDebug" - nothing to do
    }

    scedebugcleanup_bp 

    # dbstate must be set explicitely to NoDebug here, because
    # scedebugcleanup_bp does nothing for .sci files
    setdbstate "NoDebug"

}
