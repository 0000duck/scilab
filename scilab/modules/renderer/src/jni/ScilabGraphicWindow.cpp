
/*

Copyright 2007 INRIA

Author : Sylvestre Ledru

This software is a computer program whose purpose is to hide the complexity
of accessing Java objects/methods from C++ code.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
*/
#include "ScilabGraphicWindow.hxx"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <jni.h>

namespace org_scilab_modules_gui_graphicWindow {

// Returns the current env

JNIEnv * ScilabGraphicWindow::getCurrentEnv() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);
return curEnv;
}
// Destructor

ScilabGraphicWindow::~ScilabGraphicWindow() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);

curEnv->DeleteGlobalRef(this->instance);
curEnv->DeleteGlobalRef(this->instanceClass);
}

// Constructors

ScilabGraphicWindow::ScilabGraphicWindow(JavaVM * jvm_) {
jmethodID constructObject = NULL ;
jobject localInstance ;
jclass localClass ;
const std::string className="org/scilab/modules/gui/graphicWindow/ScilabGraphicWindow";
const std::string construct="<init>";
const std::string param="()V";
jvm=jvm_;

JNIEnv * curEnv = getCurrentEnv();

localClass = curEnv->FindClass( className.c_str() ) ;
if (localClass == NULL) {
std::cerr << "Could not get the Class " << className <<  std::endl;
exit(EXIT_FAILURE);
}

this->instanceClass = (jclass) curEnv->NewGlobalRef(localClass) ;
if (this->instanceClass == NULL) {
std::cerr << "Could not create a Global Ref of " << className <<  std::endl;
exit(EXIT_FAILURE);
}

constructObject = curEnv->GetMethodID( this->instanceClass, construct.c_str() , param.c_str() ) ;
if(constructObject == NULL){
std::cerr << "Could not retrieve the constructor of the class " << className << " with the profile : " << construct << param << std::endl;
exit(EXIT_FAILURE);
}

localInstance = curEnv->NewObject( this->instanceClass, constructObject ) ;
if(localInstance == NULL){
std::cerr << "Could not instance the object " << className << " with the constructor : " << construct << param << std::endl;
exit(EXIT_FAILURE);
}
 
this->instance = curEnv->NewGlobalRef(localInstance) ;
if(this->instance == NULL){
std::cerr << "Could not create a new global ref of " << className << std::endl;
exit(EXIT_FAILURE);
}
                /* Methods ID set to NULL */
voidsetFigureIndexjintID=NULL; 


}

ScilabGraphicWindow::ScilabGraphicWindow(JavaVM * jvm_, jobject JObj) {
        jvm=jvm_;

        JNIEnv * curEnv = getCurrentEnv();

        this->instanceClass = (jclass) curEnv->NewGlobalRef(curEnv->GetObjectClass(JObj));
        if (this->instanceClass == NULL) {
               std::cerr << "Could not create a Global Ref of " << this->instanceClass <<  std::endl;
               exit(EXIT_FAILURE);
        }

        this->instance = curEnv->NewGlobalRef(JObj) ;
        if(this->instance == NULL){
               std::cerr << "Could not create a new global ref of " << this->instanceClass << std::endl;
               exit(EXIT_FAILURE);
        }
        /* Methods ID set to NULL */
        voidsetFigureIndexjintID=NULL; 


}

// Generic methods


void ScilabGraphicWindow::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
std::cerr << "Fail to enter monitor." << std::endl;
exit(EXIT_FAILURE);
}
}


void ScilabGraphicWindow::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {
std::cerr << "Fail to exit monitor." << std::endl;
exit(EXIT_FAILURE);
}
}

// Method(s)

void ScilabGraphicWindow::setFigureIndex (long figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (this->voidsetFigureIndexjintID == NULL)
{
this->voidsetFigureIndexjintID = curEnv->GetMethodID(this->instanceClass, "setFigureIndex", "(I)V" ) ;
if (this->voidsetFigureIndexjintID == NULL) {
std::cerr << "Could not access to the method setFigureIndex" << std::endl;
exit(EXIT_FAILURE);
}
}
  curEnv->CallVoidMethod( this->instance, voidsetFigureIndexjintID ,figureIndex);

if (curEnv->ExceptionOccurred()) {
curEnv->ExceptionDescribe() ;
}


}

}
